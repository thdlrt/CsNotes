> 三个模式，本文主要介绍3-pass-cs
> [GitHub - SnapdragonStudios/snapdragon-gsr](https://github.com/SnapdragonStudios/snapdragon-gsr)

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

| Pass     | 目标                           | 输入                          | 输出                              | 核心           |
| -------- | ---------------------------- | --------------------------- | ------------------------------- | ------------ |
| Convert  | 把源帧中的几何信息转成便于时域处理的表征         | Opaque/Color、Depth、Velocity | YCoCg 色度、Motion+Depth+Alpha     | 预处理、色域变换     |
| Activate | 用上一帧历史校正当前信息，提前标能安全累积以及易出错的像 | Prev-LumaHistory、Convert 输出 | MotionDepth**Clip**、LumaHistory | 深度裁剪、边缘判定    |
| Upscale  | 真正做放大和时间插值，输出 Display 分辨率    | Activate 输出、Prev-History    | SceneColorOutput、HistoryOutput  | Lanczos、时域滤波 |
- Convert 与 Activate 在 **Render 分辨率**运行。
- Upscale 在 **Display 分辨率**运行，只处理颜色。
### Activate

### Convert
- 
### Upscale

## 代码解析
### Activate
### Convert
### Upscale
## 在 Unity 中的实现