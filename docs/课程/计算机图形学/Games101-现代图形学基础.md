## 线性代数基础

- **点乘**主要用来求两个单位向量的**夹角**
  - 可以用于判断两个方向的**接近程度**（夹角），判断**前后**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/20240318154923.png" alt="image.png|250" style="zoom:50%;" />



- 叉乘
  - <img src=" https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705094854131.png" alt="image-20230705094854131" style="zoom:50%;" />
  - 可以用于求出三维直角坐标系(右手坐标系)，指导两个方向就能推导出第三个方向$\overrightarrow{x}\times \overrightarrow{y}=\overrightarrow{z}$
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705095355307.png" alt="image-20230705095355307" style="zoom:33%;" />
  - 判断**左右、内外**（p在三角形三条边的同一边（左边））<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705095708064.png" alt="image-20230705095708064" style="zoom:33%;" />
- 矩阵
  - 乘法符合结合律、分配律，**没有**交换律
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101406981.png" alt="image-20230705101406981" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101428671.png" alt="image-20230705101428671" style="zoom:33%;" />
  - 表示向量运算
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101657723.png" alt="image-20230705101657723" style="zoom:33%;" />

## 变换

### 变换基础

- 缩放
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705104154105.png" alt="image-20230705104154105" style="zoom:33%;" />
  - s为负数时也可以用于图像的翻转
- 变形（切变）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705104504994.png" alt="image-20230705104504994" style="zoom:33%;" />
- 旋转（以原点为中心点）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705104522160.png" alt="image-20230705104522160" style="zoom:33%;" />
  - 旋转矩阵的转置等于逆（正交矩阵）

#### 齐次坐标

- 目的：用矩阵乘法（**线性变化**）无法表示**平移**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705105530183.png" alt="image-20230705105530183" style="zoom:33%;" />
- 用三维向量表示二维坐标
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705105957413.png" alt="image-20230705105957413" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705110729591.png" alt="image-20230705110729591" style="zoom:33%;" />
    - **先线性变化再平移**
  - 通过第三维度是1/0来判断是点还是向量，向量的第三维为0，因而向量不会因为平移而发生改变
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705110613745.png" alt="image-20230705110613745" style="zoom:33%;" />
    - 点加点表示两个点的中点（规格化，保证第三维为1）

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705110923011.png" alt="image-20230705110923011" style="zoom:33%;" />
- **逆矩阵**可以表示**逆变换**
- 连乘（注意先进行的在**右侧**）
  - 组合变换通常**先旋转后平移**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705111602621.png" alt="image-20230705111602621" style="zoom:33%;" />
  
- 以任一点为原点旋转
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705111931171.png" alt="image-20230705111931171" style="zoom: 33%;" />

#### 三维变换

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705112020193.png" alt="image-20230705112020193" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705112115221.png" alt="image-20230705112115221" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705113438466.png" alt="image-20230705113438466" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705113455204.png" alt="image-20230705113455204" style="zoom:33%;" />
- 罗德里格旋转公式（绕任一过原点的向量n旋转）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705114627385.png" alt="image-20230705114627385" style="zoom:33%;" />
- 以上矩阵变换的方式不适用于线性插值（并不是线性连续变化的），如果需要动画、插值需要使用**四元数**

### 视图变化

- **mvp** 矩阵变化
  - 代表了模型（Model）、视图（View）、投影（Projection）三个变换矩阵的乘积
  - **模型矩阵**：将对象的局部坐标系（模型空间）转换到世界坐标系（世界空间）。这个变换涉及到物体的位移、旋转和缩放。
  - **视图矩阵**：将世界坐标系转换到观察者（或摄像机）的坐标系（视图空间）。这个变换通常涉及到将摄像机（视点）移动到原点，并进行必要的旋转，使得观察者面向场景的特定部分。
  - **投影矩阵**：将视图空间中的坐标转换到裁剪空间，进而通过透视除法转换为归一化设备坐标（NDC）。这个变换定义了一个可视范围，通常是一个锥形体（透视投影）或者一个长方体（正交投影）。

- 相机参数（视图 矩阵）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705115308858.png" alt="image-20230705115308858" style="zoom:33%;" />
    - position：原点位置
    - look-at：相机指向
    - up direction：相机头方向（即绕指向的旋转，就是相机上方的指向）
  - 固定相机的位置，移动物体，标准位置：
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705180340120.png" alt="image-20230705180340120" style="zoom: 50%;" />
  - 回正过程（同时移动相机和物体，相对关系不变）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705180837520.png" alt="image-20230705180837520" style="zoom:33%;" />
    - 先平移再旋转（逆矩阵便于确定旋转方式）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182029845.png" alt="image-20230705182029845" style="zoom:33%;" />

### 投影变化

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182959157.png" alt="image-20230705182959157" style="zoom:50%;" />

#### 正交投影

- 平行线仍然平行<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182825442.png" alt="image-20230705182825442" style="zoom:33%;" />
- 看作摄像机无限远，**平行投射**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705183034320.png" alt="image-20230705183034320" style="zoom:33%;" />
  - 相当于**扔掉z坐标**
- 长方形投影到标准正方体（观测矩阵）
  - 先平移到原点，再进行缩放
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705183815650.png" alt="image-20230705183815650" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705183829219.png" alt="image-20230705183829219" style="zoom:33%;" />
  - 归一化到长度为1，具体的长宽由 fov 和比率计算得到
    - 通常由fov得到y，再乘以比率得到x；
  

#### 透视投影

- 近大远小<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182859731.png" alt="image-20230705182859731" style="zoom:33%;" />
  - 四棱锥投射
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705184740070.png" alt="image-20230705184740070" style="zoom:33%;" />
  - 先将锥形“**挤压**”为长方体，再做**正交投影**
- 坐标变换
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185005754.png" alt="image-20230705185005754" style="zoom: 33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185348679.png" alt="image-20230705185348679" style="zoom:33%;" />
  - 变换矩阵
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185919398.png" alt="image-20230705185919398" style="zoom:33%;" />
    - 还无法确定z如何变化
  - 明确的是在**近/远平面**的 $z$ 均不发生变化
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185949350.png" alt="image-20230705185949350" style="zoom:33%;" />
    - 可知与xy无关，前两项为0（利用**近平面**上变化前后的**$z$不发生变化**来进行计算）
  - **远平面**的xy发生压缩，但是z不发生变化（中心点的xyz均不变）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705190049429.png" alt="image-20230705190049429" style="zoom:33%;" />
  - 即<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705190139231.png" alt="image-20230705190139231" style="zoom:33%;" />
  - 更确切的说n=zNear;f=zFar即**最近/远可见距离**
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705190326063.png" alt="image-20230705190326063" style="zoom:33%;" />
  - 压缩+正交

```cpp
Eigen::Matrix4f projection;

    Eigen:: Matrix4f persp_to_ortho;
    persp_to_ortho << zNear, 0, 0, 0,
                      0, zNear, 0, 0,
                      0, 0, zNear + zFar, -zNear * zFar,
                      0, 0, 1, 0;
    Eigen::Matrix4f ortho;
    float top = zNear * tan(eye_fov / 2 / 180 * MY_PI);
    float right = top * aspect_ratio;
    ortho << 1 / right, 0, 0, 0,
             0, 1 / top, 0, 0,
             0, 0, 2 / (zNear - zFar), 0,
             0, 0, 0, 1;
    projection = ortho * persp_to_ortho;
```



## 光栅化

- 光栅化：将图像**显示在屏幕上**，矢量图形转化为像素网格
- 视锥
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705195643643.png" alt="image-20230705195643643" style="zoom:33%;" />
  - 影响因素：**长宽比**、**垂直可视角度**（红线角度）
- 屏幕
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705200526116.png" alt="image-20230705200526116" style="zoom:33%;" />
  - 将标准正方**体映射到屏幕上**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705200732208.png" alt="image-20230705200732208" style="zoom:33%;" />
- 使用最简单的多边形——**三角形**来表示一切
  - 最简单多边形，任何图形都可以划分为三角形

- 判断点是否在三角形内部
  - 通过叉乘得到三个向量后，可以通过两两点乘来确定方向是否相同


```cpp
static bool insideTriangle(int x, int y, const Vector3f* _v)
{   
    Vector3f AB = _v[1] - _v[0];
    Vector3f BC = _v[2] - _v[1];
    Vector3f CA = _v[0] - _v[2];
    Vector3f AP = Vector3f(x, y, 0) - _v[0];
    Vector3f BP = Vector3f(x, y, 0) - _v[1];
    Vector3f CP = Vector3f(x, y, 0) - _v[2];
    Vector3f cross1 = AB.cross(AP);
    Vector3f cross2 = BC.cross(BP);
    Vector3f cross3 = CA.cross(CP);
    if(cross1.dot(cross2) > 0 && cross2.dot(cross3) > 0 && cross3.dot(cross1) > 0)
        return true;   
    return false;
}
```

- 简易采样（就是离散化）决定像素是否显示
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202357596.png" style="zoom:33%;" />
  - 使用**像素中心**进行采样<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202512612.png" alt="image-20230705202512612" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202526369.png" alt="image-20230705202526369" style="zoom:33%;" />
    - 判断中心点是否在三角形内部（使用向量叉乘，在三条边同方向）
    - 不需要遍历所有的点，可以使用包围盒进行优化
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318192736159.png" alt="image-20240318192736159" style="zoom:33%;" />
    - 更加优秀的算法
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318192907431.png" alt="image-20240318192907431" style="zoom:33%;" />

  - 但是这种方法会出现严重的走样问题
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705204001597.png" alt="image-20230705204001597" style="zoom:33%;" />


### 反走样&抗锯齿

- 时间、空间上的问题，**采样频率不足就会引起走样**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705210016059.png" alt="image-20230705210016059" style="zoom:33%;" />
- 先模糊后采样

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705205023851.png" alt="image-20230705205023851" style="zoom:33%;" />
- 傅里叶级数展开
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705205535746.png" alt="image-20230705205535746" style="zoom:33%;" />
  - 傅里叶变换：实现函数在**时域和频域**之间的变化
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705205610906.png" alt="image-20230705205610906" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/40cf849e55ed95732a60b52d4019d609_r.jpg" alt="img" style="zoom: 50%;" />
  - 仅仅有频谱（振幅谱）是不够的，我们还需要一个相位谱（不同波的起始相位）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/07199fc0250791d768771b50c098e26a_r.jpg" alt="img" style="zoom:33%;" />
- 对于图片来说
  - 时域表示图片上的像素变化快慢
  - 频域用黑色图表示，中间为低频四周为高频

- 滤波
  - 在**频域**可以十分方便的实现滤波（**去除指定竖线**（去除某个频率））
  - 卷积
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705212537943.png" alt="image-20230705212537943" style="zoom:33%;" />
    - 信号**范围内平均**处理
  - **时域的相乘等于频域的卷积，时域的卷积等于频域相乘**
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705212715013.png" alt="image-20230705212715013" style="zoom:33%;" />
  - 采样就是重复原始信号频谱<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230234448.png" alt="image-20230705230234448" style="zoom:33%;" />
    - 左侧的在时域上相乘，域右侧上做卷积是等价的
    - 采样率过低时会发生频谱重叠
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705225914520.png" alt="image-20230705225914520" style="zoom:33%;" />
  - 模糊（卷积）可以**减少重叠**，减少走样（屏幕分辨率高时走样少，是因为**采样频率高**）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230138093.png" alt="image-20230705230138093" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230342691.png" alt="image-20230705230342691" style="zoom:33%;" />
- **MSAA**多采样反走样（卷积计算开销大）
  - 像素内部添加更多的采样点<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230610889.png" alt="image-20230705230610889" style="zoom:33%;" />
  - 覆盖采样点数目来决定模糊状态（抗锯齿）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230656738.png" alt="image-20230705230656738" style="zoom:33%;" />

#### 反走样的方法总结

- 抗锯齿
    - MSAA：像像素内添加更多的采样点，根据覆盖采样点的数目决定显示状态（不透明度）
    - FXAA：分析渲染后的图像来检测锯齿边缘，性能开销较低
    - TAA：通过多帧信息提高图像质量，在时间上的累计和平滑，减少锯齿同时保持图像细节
- 超分辨率
    - 深度学习（DLSS）：：通过分析图像的局部模式和纹理信息，超分辨率算法尝试推断高分辨率图像中可能出现的细节和结构。通过学习大量低分辨率与高分辨率图像对应的关系，能够生成高质量的高分辨率图像。

### 深度缓冲（测试）

- 如何绘制深度不同具有遮挡关系的不同图像（三角形）？
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705232435826.png" alt="image-20230705232435826" style="zoom:33%;" />
- 深度缓冲
  - 生成图象时额外生成一个深度图，用于表示每个像素的深度信息
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705232748652.png" alt="image-20230705232748652" style="zoom:33%;" />
  - 根据深度信息判断是否要进行覆盖
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705233302274.png" alt="image-20230705233302274" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705233135393.png" alt="image-20230705233135393" style="zoom:33%;" />

## 着色

- 对不同物体应用不同材质
- 着色**只考虑物体自身**，不考虑其他的物体的影响（如阴影等）

### Blinn-Phong反射模型

- 高光、漫反射、环境光
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705234429839.png" alt="image-20230705234429839" style="zoom:33%;" />
- 漫反射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705234922833.png" style="zoom:33%;" />
  - **平面与光线的夹角**会影响反射的强度，接受的光的比率可以使用$cos\theta$表示
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705235058342.png" alt="image-20230705235058342" style="zoom:50%;" />
  - 对于点光源，**距离光源的距离**也会影响反射的强度（总能量一定，距离越大半径越大，单位面积自然越小）对于半径为r的位置，光照强度使用$I/r^2$来表示
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318205850062.png" alt="image-20240318205850062" style="zoom: 20%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705235520417.png" alt="image-20230705235520417" style="zoom:33%;" />
  - 漫反射与v的方向无关（均匀反射）
- 高光
  - 观察方向和镜面反射方向接近时看到高光
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706092213901.png" alt="image-20230706092213901" style="zoom:33%;" />
  - 通过**半程向量**（角平分线）和法线的夹角判断接近程度
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318210959363.png" alt="image-20240318210959363" style="zoom:33%;" />
  - 用指数表示高光衰减
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706093241355.png" alt="image-20230706093241355" style="zoom:33%;" /> 
  
- 环境光
  - 认为环境光恒定
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706094302227.png" alt="image-20230706094302227" style="zoom:33%;" />
  
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706094343294.png" alt="image-20230706094343294" style="zoom:33%;" />

### 着色频率

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706094654726.png" alt="image-20230706094654726" style="zoom:33%;" />
  -  面着色
  - 点着色
  - 像素着色
- 确定**顶点的法线**
  - 使用相邻面的法线来求平均
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706095747210.png" alt="image-20230706095747210" style="zoom:33%;" />
- **像素的法线**：使用重心坐标确定
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706100014116.png" alt="image-20230706100014116" style="zoom:33%;" />
- 随着采样频率提升（模型面数）不同着色频率之间的**差距越来越小**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318212454444.png" alt="image-20240318212454444" style="zoom: 25%;" />


### 实时渲染管线

- 指渲染的一系列过程，图像是如何渲染出来的
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706100232686.png" alt="image-20230706100232686" style="zoom:33%;" />
  - 输入三维空间的点
  - 投影到二维平面上（mvp矩阵变换）
  - 点构成三角形
  - 对三角形进行光栅化（采样（反走样）+深度缓冲）
  - 对三角形进行着色（如布林冯反射模型、纹理摸映射）

### 纹理映射

- 定义任何一个点的属性
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706154430087.png" alt="image-20230706154430087" style="zoom:33%;" />
  - 纹理映射：3维->2维
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706155402173.png" alt="image-20230706155402173" style="zoom:33%;" />
  - 通过坐标**三角形顶点**颜色映射

- 知道了顶点的着色，还需要插值，对内部其他点进行着色（如何通过三角形的顶点得到内部参数的平滑过渡）
  
- **重心坐标**
  - 三角型内任一点可以使用**顶点坐标的线性组合**表示（参数和为1（在三角形所在平面上）且非负（在三角形内部））
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706161338947.png" alt="image-20230706161338947" style="zoom:33%;" />
  - 可以使用三角形面积之比计算出来
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706162806562.png" alt="image-20230706162806562" style="zoom:33%;" />
  - 将任何一点的转化为用顶点表示
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706163045057.png" alt="image-20230706163045057" style="zoom:33%;" />
  - 计算得到参数后可以用这几个参数做插值$V=\alpha V_A+\beta V_B+r V_C$
  - 问题：投影之后的重心坐标会发生变化，因此要先插值再投影
  
- 纹理映射（双线性插值）（纹理过小）
  - 当显示分辨率远高于纹理分辨率时可能存在映射问题，如坐标转化后为小数，可能使得多个坐标映射到相同的纹理位置，造成显示不准确
  - 采用周围4个点的数值进行插值（两次水平一次垂直）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706172208264.png" alt="image-20230706172208264" style="zoom:33%;" />
- Mipmap范围查询（纹理过大）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706174502149.png" alt="image-20230706174502149" style="zoom:33%;" />
  - 范围查询：**快速**获取一个（方形）区域内颜色的近似平均值
    - 建立不同的层
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706174824188.png" style="zoom:33%;" />
    - mipmap所占用的**额外**空间为原图的**1/3**
  - 映射**相邻点区域**，选取距离**最大值**为映射范围**正方型的边长**<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706175452958.png" alt="image-20230706175452958" style="zoom:33%;" />
  - 问题：不同层之间的过度不连续
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706180309960.png" alt="image-20230706180309960" style="zoom:33%;" />
    - 不同层上双线性插值，再在两层之间插值。（三线性插值）
  - 并不是所有像素都是压缩正方形（过采样）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706181304364.png" alt="image-20230706181304364" style="zoom:33%;" />
    - 各向异性过滤（对长条区域快速范围查询）总开销为原本的三倍
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706181428953.png" alt="image-20230706181428953" style="zoom:33%;" />

#### 纹理应用

- 环境光照
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706182726472.png" alt="image-20230706182726472" style="zoom:33%;" />
  - 上下扭曲严重，不是均匀描述<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706183455340.png" alt="image-20230706183455340" style="zoom:33%;" />
  - 立方体包围法<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706183506530.png" alt="image-20230706183506530" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706183515877.png" alt="image-20230706183515877" style="zoom:33%;" />
- 凹凸贴图
  - 定义点相对基础面的相对高度
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706183842672.png" alt="image-20230706183842672" style="zoom:33%;" />
  - 通过法线差异模拟高度变化
  - **扰动法线**<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706184104600.png" alt="image-20230706184104600" style="zoom:33%;" />
    - 法线通过求导得到的切线旋转得到
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706184802484.png" alt="image-20230706184802484" style="zoom:33%;" />
  - 二维图像上同理通过黑白变化计算<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706184817165.png" alt="image-20230706184817165" style="zoom: 33%;" />
  - 法线模拟vs位移<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706185019444.png" alt="image-20230706185019444" style="zoom:33%;" />

## 几何

### 隐式表述

- 数学表达式
  - 不告诉点都在哪，只告诉**点的位置是否满足的约束**（判断是否在几何上），如`f(x,y,z)=0`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706233235852.png" alt="image-20230706233235852" style="zoom:33%;" />
- csg法
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706234848733.png" alt="image-20230706234848733" style="zoom:33%;" />
- 距离函数
  - 空间中任何一个点到物体表面的最短距离
  - 通过距离函数来得到几何形体混合的效果
  - 插值（应用）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706235644170.png" alt="image-20230706235644170" style="zoom:33%;" />
    - 通过正负划分边界
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707001420918.png" alt="image-20230707001420918" style="zoom:33%;" />
- 分型描述（自相似）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318230440273.png" style="zoom:33%;" />


### 显示表述

- 直接表示
  - 规定**平面图形**和二维到三维的**映射**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706233403094.png" alt="image-20230706233403094" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706233636662.png" alt="image-20230706233636662" style="zoom:33%;" />
  - 区别隐式曲面与显示曲面的关键就在于是否可以直接表示出所有的点
  - 显示的问题在于**不容易判断**一个点在不在几何体上
- 点云表示 
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707205754492.png" alt="image-20230707205754492" style="zoom:33%;" />
- 多边形面
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707205819560.png" alt="image-20230707205819560" style="zoom:33%;" />


### 贝塞尔曲线

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707210656622.png" alt="image-20230707210656622" style="zoom:33%;" />
  - 两个端点、方向（切线）确定一条曲线
- 时间t贝塞尔曲线上的点
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707211233908.png" alt="image-20230707211233908" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707211258321.png" alt="image-20230707211258321" style="zoom:33%;" />
  - 将每个时间t的点连起来就得到了贝塞尔曲线
- 四点
  -  多次t划分**直至剩下一个点**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707211546574.png" alt="image-20230707211546574" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707211724731.png" alt="image-20230707211724731" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707212011614.png" alt="image-20230707212011614" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318232516865.png" alt="image-20240318232516865" style="zoom:33%;" />
- 分段：点过多时不易于控制；贝塞尔曲线还具有凸包性质，在几个控制点限定的范围之内
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707213247492.png" alt="image-20230707213247492" style="zoom:33%;" />
  - 直接分段不够平滑（4个点一段）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707213259047.png" alt="image-20230707213259047" style="zoom:33%;" />
  - c^0^连续：曲线首尾相接
  - c^1^连续：切线连续

### 曲面

- 贝塞尔曲面
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240318233552317.png" alt="image-20240318233552317" style="zoom: 25%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707215834137.png" alt="image-20230707215834137" style="zoom: 25%;" />
  - **双重**贝塞尔曲线
  

#### 曲面细分

- 曲面细分的基本思路
  - 划分为**更多三角**形并**调整位置**使得更加贴近原先的图像
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707225708716.png" alt="image-20230707225708716" style="zoom:33%;" />

- 曲面**loop细分**
  - **新顶点**（如每条边的**中点**）的位置由周围旧顶点的位置计算得到
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707230254250.png" alt="image-20230707230254250" style="zoom:33%;" />
    - 由周围旧点的加权平均得到
  - **旧顶点**的位置由原先的位置和周围点的位置决定
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707230347683.png" style="zoom:33%;" />
    - 相信自己也相信周围旧点，计算加权平均
- **Catmull-Clark细分**（处理四边形面）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707231458185.png" alt="image-20230707231458185" style="zoom:33%;" />
    - 称度不为4的点为**奇异点**
  - 连接边、面的中点
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707231505479.png" alt="image-20230707231505479" style="zoom:33%;" />
  - 非四边形会产生奇异点，非四边形面会在**细分之后消失**（做一次细分之后只有四边形面了，因此之后奇异点数目不会再发生变化，即**只有第一次细分时变化**）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707231829386.png" alt="image-20230707231829386" style="zoom:33%;" />

#### 曲面简化

- 边坍缩
  - 删去边，捏成一个点
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707232409037.png" alt="image-20230707232409037" style="zoom:33%;" />
  - 用偏差（二次误差）计算新位置（到原先各面的**平方和最小**）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707232521945.png" alt="image-20230707232521945" style="zoom:33%;" />
  - **优先坍缩**造成二次误差最小的边（使用优先队列）

#### 曲面正则化

- 曲面正则化（直到曲面简化，减少细节丢失）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707220845910.png" alt="image-20230707220845910" style="zoom:33%;" />

## 光线追踪

- Shadow Mapping阴影映射（只能处理点光源、硬阴影）光栅化的阴影处理
  - 阴影：人能看到的位置，但**光源看不到的位置**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234220403.png" alt="image-20230707234220403" style="zoom:33%;" />
  - 记录**光源**到不同物体的**最短距离**，将摄像机看到的位置与光源的深度距离比较来判断是否被遮挡形成阴影
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234622435.png" alt="image-20230707234622435" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234634718.png" alt="image-20230707234634718" style="zoom:33%;" />
    - 存在数值精度问题
    - 存在深度信息图（shadowmap）分辨率与实际渲染分辨率不匹配的问题
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234643695.png" alt="image-20230707234643695" style="zoom:33%;" />
- 硬阴影与软阴影
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707235609373.png" alt="image-20230707235609373" style="zoom:33%;" />
  - 点光源只会产生硬阴影
  - 当光源被**部分遮挡**时会产生软阴影
- 光线追踪应用了光路可逆性，从眼睛出发直至光源进行追踪
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708092756902.png" alt="image-20230708092756902" style="zoom:33%;" />
  - 从眼睛向外寻找，到达最近的（可观察物体）然后与光源连线计算着色结果（可见性）

### Whitted-Style Ray Tracing

- 一种递归算法，可以处理多次反射（折射）的情况（打到光滑表面就继续反射，打到漫反射就停止）
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708093259968.png" alt="image-20230708093259968" style="zoom:33%;" />
  - 着色叠加
- 光线与图形的交点（几何隐式表示）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708094310500.png" alt="image-20230708094310500" style="zoom:33%;" />
  - 点加方向表示光线 $r(t)=o+td$
  - 解任意曲面与光线的交点
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708094545633.png" alt="image-20230708094545633" style="zoom:33%;" />
- 光线与三角形面求交（几何显式表示）
  - 使用一条法向量加上一个点来表示一个平面，并且通过向量乘法判断一个点是否在平面上
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708095659898.png" style="zoom:33%;" />
  - 法一：先求**和平面的交点**，再判断是否**属于某个三角形**
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708100348543.png" alt="image-20230708100348543" style="zoom:33%;" />
  - 法二：利用重心坐标直接判断（三个参数都非负）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708101437239.png" alt="image-20230708101437239" style="zoom:33%;" />

#### 优化

- 包围盒
  - 用简单的几何图形框住物体<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708102648627.png" alt="image-20230708102648627" style="zoom:33%;" />
    - 只有光线和包围盒会发生碰撞才去考虑光线和物体三角形面的相交情况
  - AABB轴对齐（xyz）包围盒
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708104843234.png" alt="image-20230708104843234" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708105432269.png" alt="image-20230708105432269" style="zoom:33%;" />
  - 记录与平面的交点，求交后得到与包围盒的交点
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708105702893.png" alt="image-20230708105702893" style="zoom:33%;" />
    - 光线**进入所有**对面才真正进入了盒子，光线 **离开任何**一个对面就离开了盒子
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708110125119.png" alt="image-20230708110125119" style="zoom:33%;" />
  
- Uniform Spatial Partitions（AABB加速光线追踪）

  - 先和盒子求交，再决定是否要和物体求交
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708111146232.png" alt="image-20230708111146232" style="zoom:33%;" />

  - 划分的各自数目要恰当（但是均匀划分存在一系列问题，因为物体的分布不是均匀的）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708191224698.png" alt="image-20230708191224698" style="zoom: 33%;" />

- **空间划分**方法
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708192117492.png" alt="image-20230708192117492" style="zoom:33%;" />
  
- Oct-Tree（八叉树）：问题：随着维度增加，划分数目指数增加

- KD-Tree

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708192359516.png" alt="image-20230708192359516" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708212902708.png" alt="image-20230708212902708" style="zoom:33%;" />
  - 难点：判断**三角形与盒子是否交**很难，并且三角形可能跨盒子

- (BVH)**物体划分**

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708213437753.png" alt="image-20230708213437753" style="zoom:33%;" />
    - 确定包围盒；对包围盒内的物体进行划分；分别重新计算包围盒；继续计算。

  - 一个物体只会出现在一个盒子中（盒子中也一定有物体）
  - 可以每次都选择位于中间的三角形用于划分
  - 求交过程（与节点相交了，再继续去看子节点）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708215158007.png" alt="image-20230708215158007" style="zoom:33%;" />


### 辐射度量学

- **准确**定义物理光照
- Radiant flux：**单位时间的能量**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708220326227.png" alt="image-20230708220326227" style="zoom:33%;" />
- Radiant Intensity：辐射强度（辐射能量）
  - Radiant Intensity是指光源在特定方向上单位立体角内的辐射功率（Radiant Flux，单位是Watts）。它描述了光源在**某个方向上**的“亮度”有多**强**。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708221019629.png" alt="image-20230708221019629" style="zoom:33%;" />
  - 立体角：
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708221146340.png" alt="image-20230708221146340" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708221803814.png" alt="image-20230708221803814" style="zoom:33%;" />
    - 注意强度只与立体角相关，与距离无关
- Irradiance：辐照度（单位面能量）
  - Irradiance是指达到某个表面**单位面积**上的辐射功率。它衡量的是光源对物体表面的照射能力，反映了物体**表面接收到的光能量**有多少。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708225633808.png" alt="image-20230708225633808" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708230202366.png" alt="image-20230708230202366" style="zoom:33%;" />
    - 随着半径增大，Irradiance减小；Radiant Intensity恒定
  
- Radiance：辐射亮度（传播过程的能量）
  - **单位面积上单位立体角内**的辐射功率。它是描述光在空间中传播的基本物理量，综合考虑了方向性和空间分布
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708230557368.png" alt="image-20230708230557368" style="zoom:33%;" />
    - 单位面积向特定方向的单位角内的能量辐射
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708232550470.png" alt="image-20230708232550470" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708232557250.png" alt="image-20230708232557250" style="zoom:33%;" />
  - Radiance是考虑特定入射方向的Irradiance
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708233048471.png" alt="image-20230708233048471" style="zoom:33%;" />


#### BRDF

- 描述一个方向反射到另外一个方向的过程
- 接受能量=输出能量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708233350627.png" alt="image-20230708233350627" style="zoom:33%;" />
  - BRDF就是能量被如何分配到不同方向
  - 所有光源的辐射->反射总光线
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319122540620.png" alt="image-20240319122540620" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319122347958.png" alt="image-20240319122347958" style="zoom:33%;" />
    - 这是一个递归计算过程
  - 渲染方程：自发光+反射光加和（包含多次反射递归）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708234338841.png" alt="image-20230708234338841" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708234751059.png" alt="image-20230708234751059" style="zoom:33%;" />
  - 简化表示<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708235018969.png" alt="image-20230708235018969" style="zoom:33%;" />
  - 递归弹射（包含多次反射**即全局光照**（直接光照+间接光照））<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708235900191.png" alt="image-20230708235900191" style="zoom:33%;" />

#### 蒙特卡罗路径追踪

- 蒙特克罗积分

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709085252585.png" alt="image-20230709085252585" style="zoom:33%;" />

  - 使用**随机采样**获取积分区域内的值，用于进一步的积分计算

  - （均匀采样）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709085408396.png" alt="image-20230709085408396" style="zoom:33%;" />

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709085416035.png" alt="image-20230709085416035" style="zoom:33%;" />


- 解决Whitted-Style Ray不正确的地方，**Whitted不能处理好漫反射**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319135928162.png" alt="image-20240319135928162" style="zoom:33%;" />

- 用蒙特卡洛积分表示反射方程
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709091915429.png" alt="image-20230709091915429" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709092950726.png" alt="image-20230709092950726" style="zoom:33%;" />
  - N（一根光线反射后探测数目）!=1时N会指数级增长
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319141155446.png" alt="image-20240319141155446" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709093026135.png" alt="image-20230709093026135" style="zoom:33%;" />
  - 为了避免指数增长，只考虑**一个方向**（这就是路径追踪）
  - 采样足够多的经过同一个像素的光线来减少误差<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709093237329.png" alt="image-20230709093237329" style="zoom:33%;" />
  - 向不同方向随机发光
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709093429284.png" alt="image-20230709093429284" style="zoom:33%;" />
  - 为了避免无限递归，(RR)随机决定发反射次数（何时开始停止反射）
  - 概率p继续反射，（1-p）不再继续发射<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709094812062.png" alt="image-20230709094812062" style="zoom:33%;" />
    - 渲染结果要$L_0/p$，这样保证期望不变，即：$E=P*(L_0/P)+(1-P)*0=L_0$
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709095033407.png" alt="image-20230709095033407" style="zoom:33%;" />
- 采样效率低：光源太小，大部分发出的路径都不会到达光源
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709095531705.png" alt="image-20230709095531705" style="zoom:33%;" />
  - 改用向光源来进行采样、积分
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709100416475.png" alt="image-20230709100416475" style="zoom:33%;" />
    - dA是立体角dw对应光源上的区域（先将dA映射到平行方向，然后两个平行表面是成比例的）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709100612954.png" alt="image-20230709100612954" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709100920862.png" alt="image-20230709100920862" style="zoom:33%;" />
    - 对于直接光照采用dA计算，对于间接光照仍然采用随机方式

## 材质与外观

- **材质=BRDF决定如何进行反射**

### 反射与折射

- 类镜面反射材质（如铜镜）、
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319150054098.png" alt="image-20240319150054098" style="zoom: 25%;" />
- 透明物体（如水，可以折射进去）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319150120994.png" alt="image-20240319150120994" style="zoom:25%;" />

- 反射角计算
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709105229295.png" alt="image-20230709105229295" style="zoom:33%;" />
- 菲涅⽿项，反射的程度与夹角（入射角）有关
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111102180.png" alt="image-20230709111102180" style="zoom:33%;" />
    - **入射角越大，反射越强** （绝缘体，如玻璃）
  - 金属
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111217100.png" alt="image-20230709111217100" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111357074.png" alt="image-20230709111357074" style="zoom:33%;" />
- 折射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709110651481.png" alt="image-20230709110651481" style="zoom:33%;" />

### 微表面模型

- 远处看材质，近处看几何（表面凹凸不平 ）
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111942766.png" alt="image-20230709111942766" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709112348765.png" alt="image-20230709112348765" style="zoom:33%;" />
  - 法线分布是否集中决定是漫反射还是镜面反射
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709113045372.png" style="zoom:33%;" />
  - 菲涅尔项：总共有多少能量被反射
  - shadowing-masking：修正光线遮挡（入射角很大时反射光发现很可能会被表面上的凹凸遮挡）
  - distribution of normals：法线分布情况
- 微表面的方向性：各向同性/各向异性
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709113753033.png" alt="image-20230709113753033" style="zoom:33%;" />
  - 各向同性：反射结果只与 入射光与反射光的夹角相关<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709115045068.png" alt="image-20230709115045068" style="zoom:33%;" />
    - 各向异性下（四维）：入射光线和反射光线的坐标
    - 对于各向同性可以化简为三维（两个坐标->差）

- BRDF性质
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709114203505.png" alt="image-20230709114203505" style="zoom:33%;" />
    - BRDF是非负的
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709114224042.png" alt="image-20230709114224042" style="zoom:33%;" />
    - 具有可逆性（交换入射、出射）
  - 能量收敛
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709114417284.png" alt="image-20230709114417284" style="zoom:33%;" />
- BRDF的测量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319155006214.png" alt="image-20240319155006214" style="zoom:33%;" />

### 高级光线传播

- 无偏：蒙特卡洛估计的期望是正确的

#### 无偏光线传输

- BDPT**双向路径**追踪
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709125601288.png" alt="image-20230709125601288" style="zoom: 33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709120747552.png" alt="image-20230709120747552" style="zoom:33%;" />
- MLT
  - 适用于较为困难的场景
  - 使用马尔科夫链，找到一条有效路径后可以更好地找到有用的相关路径
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319161050055.png" alt="image-20240319161050055" style="zoom: 33%;" />
  - 问题：难以确定覆盖率（局部自动推导）,可能存在覆盖率不均匀，**何时收敛**（因此不适用与连续动画）
  

#### 有偏光线传输

- Photon Mapping 光子映射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709123959664.png" alt="image-20230709123959664" style="zoom:33%;" />
  - 首先由**光源**发射光子，然后由摄像机发送进行观察
  - 擅长渲染光斑
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709124821506.png" alt="image-20230709124821506" style="zoom:33%;" />
    - 找周围最近n个光子占据的面积大小，从而得到**光子密度**
    - 根据局部光子密度进行渲染
    - 不过由于光子数目有限，因此存在偏差
    - **有偏**：存在偏差，会造成模糊（用一个范围的数目估计一个点），但样本足够多时会**收敛**
- VCM：**双向路径+光子追踪**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709125657992.png" alt="image-20230709125657992" style="zoom:33%;" />
- IR实时辐射度
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709125730381.png" alt="image-20230709125730381" style="zoom:33%;" />
  - 将已经被照亮的面认为光源，用他们再去照亮别的

### 外观建模

#### 非表面模型

- 光线会进入到物体内部

- 如在云雾中的散射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709131733573.png" alt="image-20230709131733573" style="zoom:33%;" />

#### 毛发

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709132124387.png" alt="image-20230709132124387" style="zoom:33%;" />
- 光线穿入<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709132149614.png" alt="image-20230709132149614" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709132509349.png" alt="image-20230709132509349" style="zoom:33%;" />
  - （动物毛发）双重圆柱模型<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133149938.png" alt="image-20230709133149938" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133521939.png" alt="image-20230709133521939" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133534764.png" alt="image-20230709133534764" style="zoom:33%;" />

#### 表面模型

- Translucent Material:（指光线射入后从不确定的位置出来）
  - 次表面反射<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133811091.png" alt="image-20230709133811091" style="zoom:33%;" />
  - BSSRDF就好像**内部也有一个光源**（双光源模拟）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709134123772.png" alt="image-20230709134123772" style="zoom:33%;" />
  
- 布料材质

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240319164113189.png" alt="image-20240319164113189" style="zoom:33%;" />

    


## 相机

- 不能直接使用传感器捕获图像，因为来自所有方向的光线会映射到同一点，无法区分 
- 视场FOV
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709162015120.png" alt="image-20230709162015120" style="zoom:33%;" />
  - 以35mm胶片为基准（传感器大小）来定义fov
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709162300047.png" alt="image-20230709162300047" style="zoom:33%;" />
  - 画面裁切<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709162502367.png" alt="image-20230709162502367" style="zoom:33%;" />
- 曝光
  - 进光量*时间<img src="C:\Users\MSI\AppData\Roaming\Typora\typora-user-images\image-20230709162749444.png" alt="image-20230709162749444" style="zoom:33%;" />
  - 光圈
    - FN中的N是1/光圈直径
  - 快门速度（曝光时长）
    - 由于快门让然是逐渐打开的，不同位置的曝光时间存在误差，因此存在果冻效应
    - 光圈大小减小一倍，曝光面积会减少为1/4即快门要延长为原来的4倍
  - iso
    - 简单增益，增大信号强度
    - 会放大噪声
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709163244915.png" alt="image-20230709163244915" style="zoom:33%;" />

### 镜头

- 物距、像距<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709165307006.png" alt="image-20230709165307006" style="zoom: 25%;" />
- 景深
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709170131194.png" alt="image-20230709170131194" style="zoom:33%;" />
    - 像投射在了传感器前面，在传感器上呈**圆形**（称为CoC）
    - 其他条件一定时光圈越小（改变C的长度）CoC也越小，景深越弱
    - 认为当CoC足够小时图象是清晰的
  - 光圈f数=焦距/光圈直径
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709171355075.png" alt="image-20230709171355075" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709171415497.png" alt="image-20230709171415497" style="zoom:33%;" />
  - 焦距越大、光圈越小CoC越大

#### 模拟渲染

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709172112189.png" alt="image-20230709172112189" style="zoom: 33%;" />
- 清晰范围（可接受CoC大小的成像范围）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709172646808.png" alt="image-20230709172646808" style="zoom:33%;" />
  - Depth of field表示在焦内的区域，越小表示景深越严重


### 光场

#### 全光函数

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709173911389.png" alt="image-20230709173911389" style="zoom:33%;" />

  - 任何时间从任意位置以不同角度来看世界

- 光线

  - 起点+方向
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709174459778.png" alt="image-20230709174459778" style="zoom:33%;" />
  - 两点 <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709174540581.png" alt="image-20230709174540581" style="zoom:33%;" />

- 光场

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709174952153.png" alt="image-20230709174952153" style="zoom:33%;" />
  - 看物体就是从物体向外看的状况
  - 全光函数就记录了物体向**不同方向发光**的情况 
  - 可以得到任意方向物体观测情况

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709180111668.png" alt="image-20230709180111668" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709180134008.png" alt="image-20230709180134008" style="zoom:33%;" />
  - 两种观察模式（uv为物体盒内st为外侧）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709180344456.png" alt="image-20230709180344456" style="zoom:33%;" />
    - 一点看向世界
    - 不同角度去看向同一点

#### 光场照相机

- 将原本的单个像素进一步**拆分**，将单个像素细分为不同的方向
- 选择来自不同方向的信息，对画面做出调整<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709184808585.png" alt="image-20230709184808585" style="zoom:33%;" />

### 色彩

- SPD谱功率密度：描述光在不同波长上的分布
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709185519530.png" alt="image-20230709185519530" style="zoom:33%;" />
- 人眼
  - 三种细胞对颜色的到三个不同的值SML（不同颜色对不同细胞的刺激值）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709190553132.png" alt="image-20230709190553132" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709190542032.png" alt="image-20230709190542032" style="zoom:33%;" />
  - 同色异谱：不同颜色，但是SML值相同
- 色彩混合
  - 加色系统<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709191105967.png" alt="image-20230709191105967" style="zoom:33%;" />
  - CIE RGB
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709191322250.png" alt="image-20230709191322250" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709191501123.png" alt="image-20230709191501123" style="zoom:33%;" />

#### 颜色空间

- sRGB：Standardized RGB 
- CIE XYZ
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709192139532.png" alt="image-20230709192139532" style="zoom:33%;" />
  - 人造匹配系统（这些）
- XZ表示颜色，Y表示明度，归一化后可以得到<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709195259655.png" alt="image-20230709195259655" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709195336518.png" alt="image-20230709195336518" style="zoom:33%;" />
- HSL
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709195707879.png" alt="image-20230709195707879" style="zoom:33%;" />
- 减色系统（打印）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709200323720.png" alt="image-20230709200323720" style="zoom:33%;" />

## 动画

- 关键帧动画
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709202301977.png" alt="image-20230709202301977" style="zoom:33%;" />


### 质点弹簧系统

- 弹簧连接质点<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709203041124.png" alt="image-20230709203041124" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709203227037.png" alt="image-20230709203227037" style="zoom:33%;" />
  - 单位向量表示方向
- 为了让物体最终停下来，添加反方向摩擦力（弹簧**内部**的摩擦力）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709204039960.png" alt="image-20230709204039960" style="zoom:33%;" />
- 添加抵抗各方向弯折的弹簧<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709204711839.png" alt="image-20230709204711839" style="zoom:33%;" />

### 粒子系统

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709205041017.png" style="zoom:33%;" />

- 粒子在速度场中的运动（知道粒子在任意位置的速度），结合起点，计算例子的运动方程

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709211743748.png" alt="image-20230709211743748" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709211753844.png" alt="image-20230709211753844" style="zoom:33%;" />
  - 欧拉法方法（上一帧估计下一帧）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709211926568.png" alt="image-20230709211926568" style="zoom:33%;" />
  - 要求t很小才能足够精细并且不稳定<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709213346189.png" alt="image-20230709213346189" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709213111686.png" alt="image-20230709213111686" style="zoom:33%;" />

- 改进

  - 中点法
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709213806098.png" alt="image-20230709213806098" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709213920961.png" alt="image-20230709213920961" style="zoom:33%;" />
    - 先用欧拉方法计算，得到中点，用中点的方向再移动
  - 自适应法，根据误差判断是否还需要继续划分<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709214211113.png" alt="image-20230709214211113" style="zoom:33%;" />
  - 隐式欧拉方法
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709214354671.png" alt="image-20230709214354671" style="zoom:33%;" />

  - Runge-Kutta Families
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709215954648.png" alt="image-20230709215954648" style="zoom:33%;" />
  - Position-Based
    - 根据位置利用数学、机器学习的方法而不是物理模拟，如利用水的不可压缩性，通过水的密度，对流体运动进行约束和模拟
  - 刚体模拟
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709221354495.png" alt="image-20230709221354495" style="zoom:33%;" />

### 运动学

- 正向运动学：告知如何进行运动

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709205649883.png" alt="image-20230709205649883" style="zoom:33%;" />

- 逆运动学：告知**运动轨迹**，自动计算运动方向

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709210237548.png" alt="image-20230709210237548" style="zoom:33%;" />
  - 手动操控
- 动作捕捉 