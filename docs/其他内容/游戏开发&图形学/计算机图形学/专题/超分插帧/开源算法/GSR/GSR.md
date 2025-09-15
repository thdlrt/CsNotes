> 三个模式，本文主要介绍3-pass-cs
> [GitHub - SnapdragonStudios/snapdragon-gsr](https://github.com/SnapdragonStudios/snapdragon-gsr)
> [Site Unreachable](https://zhuanlan.zhihu.com/p/8980985121) 

## 算法介绍
- 3-pass模式的流程为：Activate → Convert → Upscale
	- 2-pass模式，则只需：Convert → Upscale

- 使用的 UniformBuffer 统一缓冲区

| 字段                         | 说明                 |
| -------------------------- | ------------------ |
| `vec2 renderSize `         | 渲染分辨率              |
| `vec2 displaySize`         | 显示分辨率              |
| `vec2 renderSizeRcp`       | 渲染尺寸倒数             |
| `vec2 displaySizeRcp`      | 显示尺寸倒数             |
| `vec2 jitterOffset`        | 抖动偏移               |
| `vec4 clipToPrevClip[4]`   | 当前到前一帧裁剪空间变换矩阵$^1$ |
| `float preExposure`        | 用于色调映射的场景曝光值$^2$   |
| `float cameraFovAngleHor ` | 相机的水平FOV角度 $^3$    |
| `float cameraNear`         | 相机的近裁剪面距离          |
| `uint reset`               | 是否重置累计             |
1：主要用于**静态物体**的处理（因为在计算变换矩阵时默认物体的世界坐标不会发生变化）
- 计算当前帧投影矩阵的逆矩阵，把裁剪空间坐标变回相机空间
- 计算当前帧视图矩阵的逆矩阵，把相机空间坐标变回世界空间
- 将这两个逆变换组合，得到从裁剪空间直接回到世界空间的变换矩阵
- 再用上一帧的视投矩阵和这个逆变换矩阵相乘，得到“当前裁剪空间→上一帧裁剪空间”的总变换。
```c
glm::mat4 inv_proj       = glm::inverse(current_proj);
glm::mat4 inv_view       = glm::inverse(current_view);
glm::mat4 inv_vp         = inv_view * inv_proj;
glm::mat4 clipToPrevClip = (previous_view_proj * inv_vp);
```
2：用于色调映射前的曝光矫正，以便帧间色彩保持一致，这个值表示的就是上一帧的曝光值 / 当前帧的曝光值
- 在做帧间混合、累积的时候（如TAA），如果曝光值有变化，就要按照这个比例把上一帧的亮度调到和当前帧一致，否则会出现“残影变暗/变亮”的现象。
3：这个字段通常是用来描述相机的水平视场角，在做坐标变换、运动矢量等运算时要用到。

![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250607202858.png)
- 超分需要的输入信息：
	- `InputQpaqueColor`：当前帧渲染完所有**不透明物体**后的颜色贴图
	- `InputColor`：当前帧**所有物体渲染完毕**后的最终颜色贴图。
	- `InputDepth`：应用渲染主Pass时输出的深度贴图
	- `InputVelocity`：当前帧的运动矢量贴图

- 3-pass 版本的功能设计与划分如下，本文之后的每个部分都是围绕这三个部分分别介绍

| Pass     | 目标                           | 输入                          | 输出                              | 核心           |
| -------- | ---------------------------- | --------------------------- | ------------------------------- | ------------ |
| Convert  | 把源帧中的几何信息转成便于时域处理的表征         | Opaque/Color、Depth、Velocity | YCoCg 色度、Motion+Depth+Alpha     | 预处理、色域变换     |
| Activate | 用上一帧历史校正当前信息，提前标能安全累积以及易出错的像 | Prev-LumaHistory、Convert 输出 | MotionDepth**Clip**、LumaHistory | 深度裁剪、边缘判定    |
| Upscale  | 真正做放大和时间插值，输出 Display 分辨率    | Activate 输出、Prev-History    | SceneColorOutput、HistoryOutput  | Lanczos、时域滤波 |

- Convert 与 Activate 在 **Render 分辨率**运行。
- Upscale 在 **Display 分辨率**运行，只处理颜色。
### Convert
- 预处理所有输入的几何与色彩信息，将其整理成便于后续时域插值和超分的格式。
- 主要做：深度膨胀、运动估计、半透明遮罩生成、色彩空间变换。

- 本阶段的输入就是算法**输入**的那四项（颜色和深度）
- **输出**

| 名称                     | 介绍                                 |
| ---------------------- | ---------------------------------- |
| Colorluma（YCoCg Color） | 存储转换后的YCoCg色度分量（后续Upscale主输入）。     |
| MotionDepthAlphaBuffer | 存储每像素的运动矢量（RG）、膨胀深度（B）、Alpha遮罩（A）。 |
- 深度膨胀：
	- 对每个像素，取其自身及周围3x3范围内的最小深度
	- 这样做能修补低分辨率情况下深度贴图的空洞、裂缝问题
- 运动矢量生成：
	- 对于**有InputVelocity**（即应用主动给了运动矢量的像素），直接解码，填入结果。
    - 对于**没有InputVelocity**（通常静态物体、或者应用没填），就用“深度+clipToPrevClip”逆推像素运动。
- 半透明遮罩：
	- 比较InputColor和InputOpaqueColor的alpha通道：
    - 如果InputColor的alpha < 阈值（如0.99），则判定为**半透明像素**，写入MotionDepthAlphaBuffer的A通道为0，否则为1。
	- 后续Upscale时，α=0的像素不会做历史累积，避免UI、玻璃拖影
- 色彩空间变化：
	- 把InputColor的RGB转换到YCoCg空间，分别存储亮度（Y）和色度（Co、Cg）分量。
	- YCoCg空间亮度与色度分离，便于后续做最小/最大/方差裁剪，提升去噪与插值质量。
### Activate
- 像素可靠性分析：判断哪些像素的历史值可以安全利用，哪些像素因遮挡/剧烈变化不应使用历史信息。
- 边缘与亮度突变检测：检测像素是否处于边缘或明暗剧变区域，为后续时域融合提供权重与保护。
- 历史亮度维护：为下一帧的判断保存亮度信息，实现帧间的“亮度异常检测”。

**输入**

| 名称                     | 介绍                             |
| ---------------------- | ------------------------------ |
| PrevLumaHistory        | 上一帧每像素亮度的历史数据                  |
| MotionDepthAlphaBuffer | Convert Pass 输出的运动、深度、alpha等信息 |
| Colorluma              | Convert Pass 输出的 YCoCg 色彩      |

**输出**

| 名称                         | 介绍                                |
| -------------------------- | --------------------------------- |
| MotionDepthClipAlphaBuffer | 存储运动、深度裁剪（depthClip）、alpha、无边缘等标记 |
| LumaHistory                | 本帧的亮度历史                           |

- 深度裁剪判定：
	- 检测像素是否被遮挡
	- 通过运动矢量将本帧像素投影到上一帧，采样上一帧的深度，如果两者差异很大，说明可能被遮挡，需要标记为不可安全基类的深度值，写入到MotionDepthClipAlphaBuffer
- 亮度边缘与突变检测
	- 检测哪些像素位于边缘或亮度剧烈变化区，这些地方容易有“鬼影”或“历史脏数据”，需要特殊处理。
	- 对当前像素及周围3x3区域的亮度做极值分析。如果最大亮度 - 最小亮度 < 阈值，则认为该像素处于非边缘，可以更放心地用历史数据。最后将标记写入 MotionDepthClipAlphaBuffer
- 亮度历史信息维护
	- 为后续帧判断亮度突变（比如闪烁、亮暗跳变）提供参考，防止时域累积“拖尾”。
### Upscale
- 将低分辨率的结果上采样到高分辨率，输出锐利且无明显噪声的色彩。
- 融合历史（时域）信息，进一步去除抖动、噪点和插值伪影，提升画面稳定性。

**输入**

| 名称                         | 介绍                                               |
| -------------------------- | ------------------------------------------------ |
| MotionDepthClipAlphaBuffer | 来自Activate/Convert Pass，含运动、深度裁剪（clip）、alpha、边缘等 |
| Colorluma                  | YCoCg色度（低分辨率，含亮度与色差）                             |
| PrevHistory                | 上一帧Upscale输出的历史色彩（高分辨率）                          |
**输出**

| 名称               | 介绍           |
| ---------------- | ------------ |
| SceneColorOutput | 最终超分输出（高分辨率） |
| HistoryOutput    |              |
- Lanczos 上采样（空间超分）
	- 对每个目标高分辨率像素，按比例采样低分辨率 Colorluma（YCoCg）图像的**3x3（9点）邻域**。
	- 使用 Lanczos2 滤波器进行权重加权插值，得到上采样后的基础色彩。
	- 在采样过程中，同时统计该邻域的最小值、最大值、方差（Y、Co、Cg通道分别统计），用于后续裁剪。
- 历史色彩可信度分析（时域融合准备）
	- 结合 MotionDepthClipAlphaBuffer 里的信息，分析历史数据是否可靠
	- 若像素被判定为不可累积（如遮挡、半透明、高速运动等），则大幅降低历史色彩的权重
- 历史色彩裁剪
	- 用当前邻域的 min/max/variance（方差）对历史色彩做“夹紧”处理，防止历史漂移出当前色彩统计范围
	- 防止历史噪点、伪影被无限累积
- 时域融合
	- 根据权重对历史颜色和当前帧颜色进行融合
- YCoCg到RGB的逆变换
## 代码解析
### Convert
[[sgsr2_convert.comp]]
### Activate
[[sgsr2_activate.comp]]
### Upscale
[[sgsr2_upscale.comp]]
## 在 Unity 中的实现
### Convert
```c

```
### Activate
```c

```
### Upscale
```c

```