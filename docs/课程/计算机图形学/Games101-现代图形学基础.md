## 线性代数基础

- 投影<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705094433677.png" alt="image-20230705094433677" style="zoom: 33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705094408593.png" alt="image-20230705094408593" style="zoom: 15%;" />



- 叉乘
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705094854131.png" alt="image-20230705094854131" style="zoom:33%;" />
  - 对于三维直角坐标系
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101014464.png" alt="image-20230705101014464" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705095355307.png" alt="image-20230705095355307" style="zoom:33%;" />
  - 判断左右、内外（p在三角形三条边的同一边（左边））<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705095708064.png" alt="image-20230705095708064" style="zoom:33%;" />

- 矩阵
  - 乘法符合结合律、分配律
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101406981.png" alt="image-20230705101406981" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101428671.png" alt="image-20230705101428671" style="zoom:33%;" />
  - 表示向量运算
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705101657723.png" alt="image-20230705101657723" style="zoom:33%;" />

## 变换

### 二维变换

- 缩放
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705104154105.png" alt="image-20230705104154105" style="zoom:33%;" />
  - s为负数时也可以用于图像的翻转
- 变形
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705104504994.png" alt="image-20230705104504994" style="zoom:33%;" />
- 旋转（以原点为中心点）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705104522160.png" alt="image-20230705104522160" style="zoom:33%;" />
  - 旋转矩阵的转置等于逆（正交矩阵）

#### 齐次坐标

- 目的：用矩阵乘法（线性变化）表示平移
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705105530183.png" alt="image-20230705105530183" style="zoom:33%;" />
- 用三维向量表示二维坐标
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705105957413.png" alt="image-20230705105957413" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705110729591.png" alt="image-20230705110729591" style="zoom:33%;" />
    - **先线性变化再平移**
  - 通过第三维度是1/0来判断是点还是向量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705110613745.png" alt="image-20230705110613745" style="zoom:33%;" />
    - 点加点表示两个点的中点（规格化）

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705110923011.png" alt="image-20230705110923011" style="zoom:33%;" />
- **逆矩阵**可以表示**逆变换**
- 连乘（注意先进行的在**右侧**）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705111602621.png" alt="image-20230705111602621" style="zoom:33%;" />
- 以任一点为原点旋转
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705111931171.png" alt="image-20230705111931171" style="zoom: 33%;" />

### 三维变换

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705112020193.png" alt="image-20230705112020193" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705112115221.png" alt="image-20230705112115221" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705113438466.png" alt="image-20230705113438466" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705113455204.png" alt="image-20230705113455204" style="zoom:33%;" />
- 旋转公式（绕任一过原点的向量n旋转）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705114627385.png" alt="image-20230705114627385" style="zoom:33%;" />

### 视图变化

- 相机参数（观测矩阵）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705115308858.png" alt="image-20230705115308858" style="zoom:33%;" />
    - position：原点位置
    - look-at：相机指向
    - up direction：相机头方向（即绕指向的旋转，就是相机上方的指向）
  - 固定相机的位置，移动物体，标准位置：
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705180340120.png" alt="image-20230705180340120" style="zoom: 50%;" />
  - 回正过程
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705180837520.png" alt="image-20230705180837520" style="zoom:33%;" />
    - 先平移再旋转（逆矩阵便于确定旋转方式）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182029845.png" alt="image-20230705182029845" style="zoom:33%;" />

### 投影变化

#### 正交投影

- 平行线仍然平行<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182825442.png" alt="image-20230705182825442" style="zoom:33%;" />
- 看作摄像机无限远，平行投射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705183034320.png" alt="image-20230705183034320" style="zoom:33%;" />
  - 想当于扔掉z坐标
- 长方形投影到标准正方体（观测矩阵）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705183815650.png" alt="image-20230705183815650" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705183829219.png" alt="image-20230705183829219" style="zoom:33%;" />

#### 透视投影

- 近大远小<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182859731.png" alt="image-20230705182859731" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705182959157.png" alt="image-20230705182959157" style="zoom:50%;" />
  - 四棱锥投射
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705184740070.png" alt="image-20230705184740070" style="zoom:33%;" />
  - 将锥形“挤压”为长方体，再做正交投影
- 坐标变换
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185005754.png" alt="image-20230705185005754" style="zoom: 33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185348679.png" alt="image-20230705185348679" style="zoom:33%;" />
  - 变换矩阵
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185919398.png" alt="image-20230705185919398" style="zoom:33%;" />
  - 近平面的xyz均不发生变化
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705185949350.png" alt="image-20230705185949350" style="zoom:33%;" />
    - 可知与xy无关，前两项为0
  - 远平面的xy发生压缩，但是z不发生变化（中心点的xyz均不变）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705190049429.png" alt="image-20230705190049429" style="zoom:33%;" />
  - 即<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705190139231.png" alt="image-20230705190139231" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705190326063.png" alt="image-20230705190326063" style="zoom:33%;" />
  - 压缩+正交

## 光栅化

- 光栅化：将图像显示在屏幕上

- 视锥
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705195643643.png" alt="image-20230705195643643" style="zoom:33%;" />
  - 长宽比、垂直可视角度（红线角度）
- 屏幕
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705200526116.png" alt="image-20230705200526116" style="zoom:33%;" />
  - 将标准正方体映射到屏幕上
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705200732208.png" alt="image-20230705200732208" style="zoom:33%;" />
- 使用最简单的多边形——**三角形**来表示一切
- 简易采样决定像素是否显示<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202357596.png" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202512612.png" alt="image-20230705202512612" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202526369.png" alt="image-20230705202526369" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705202734257.png" alt="image-20230705202734257" style="zoom:33%;" />
  - 使用向量叉乘判断（是否在三条边的同一侧）
  - 但是这种方法会出现严重的走样问题
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705204001597.png" alt="image-20230705204001597" style="zoom:33%;" />

### 反走样

- 事件、空间上的问题，由采样频率不足引起
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705210016059.png" alt="image-20230705210016059" style="zoom:33%;" />

- 先模糊后采样

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705205023851.png" alt="image-20230705205023851" style="zoom:33%;" />

- 傅里叶级数展开

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705205535746.png" alt="image-20230705205535746" style="zoom:33%;" />
  - 傅里叶变换：可以将一个函数变换为另一个
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705205610906.png" alt="image-20230705205610906" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/40cf849e55ed95732a60b52d4019d609_r.jpg" alt="img" style="zoom: 50%;" />
  - 仅仅有频谱（振幅谱）是不够的，我们还需要一个相位谱（不同波的起始相位）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/07199fc0250791d768771b50c098e26a_r.jpg" alt="img" style="zoom:33%;" />

- 滤波

  - 在频域可以十分方便的实现滤波（去除指定竖线）
  - 去除某些特定频率的波

  - 卷积
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705212537943.png" alt="image-20230705212537943" style="zoom:33%;" />
    - 信号范围内平均处理

  - 时域的相乘等于频域的卷积，时域的卷积等于频域相乘
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705212715013.png" alt="image-20230705212715013" style="zoom:33%;" />

  - 采样就是重复原始信号频谱<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230234448.png" alt="image-20230705230234448" style="zoom:33%;" />
    - 采样率过低时会发生频谱重叠
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705225914520.png" alt="image-20230705225914520" style="zoom:33%;" />
  - 模糊（卷积）可以减少重叠，减少走样
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230138093.png" alt="image-20230705230138093" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230342691.png" alt="image-20230705230342691" style="zoom:33%;" />

- MSAA多采样反走样（卷积计算开销大）

  - 像素内部添加更多的采样点<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230610889.png" alt="image-20230705230610889" style="zoom:33%;" />
  - 覆盖采样点数目来决定模糊状态（抗锯齿）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705230656738.png" alt="image-20230705230656738" style="zoom:33%;" />

### 深度遮挡

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

### Blinn-Phong着色模型

- 高光、漫反射、环境光
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705234429839.png" alt="image-20230705234429839" style="zoom:33%;" />
  - 着色只考虑物体自身
- 漫反射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705234922833.png" style="zoom:33%;" />
  - 角度会影响反射的强度
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705235058342.png" alt="image-20230705235058342" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230705235520417.png" alt="image-20230705235520417" style="zoom:33%;" />
  - 漫反射与v的方向无关
- 高光
  - 观察方向和镜面反射方向接近时看到高光
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706092213901.png" alt="image-20230706092213901" style="zoom:33%;" />
  - 将观察方向与镜面方向接近转化为半程向量（角平分线）和法线的接近程度
  - 用指数表示高光衰减
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706093241355.png" alt="image-20230706093241355" style="zoom:33%;" /> 

- 环境光
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706094302227.png" alt="image-20230706094302227" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706094343294.png" alt="image-20230706094343294" style="zoom:33%;" />

### 着色频率

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706094654726.png" alt="image-20230706094654726" style="zoom:33%;" />
  -  面着色Flat shading
  - 点着色Gouraud shading
  - 像素着色Phong shading、
- 确定顶点的法线
  - 使用相邻面的法线来求平均
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706095747210.png" alt="image-20230706095747210" style="zoom:33%;" />
- 像素的法线
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706100014116.png" alt="image-20230706100014116" style="zoom:33%;" />

### 实时渲染管线

- 指渲染的一系列过程，图像是如何渲染出来的
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706100232686.png" alt="image-20230706100232686" style="zoom:33%;" />
  - 输入三维空间的点
  - 投影到二维平面上
  - 点构成成三角形
  - 对三角形进行光栅化
  - 对三角形进行着色

### 纹理映射

- 定义任何一个点的属性
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706154430087.png" alt="image-20230706154430087" style="zoom:33%;" />
  - 纹理映射：3维->2维
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706155402173.png" alt="image-20230706155402173" style="zoom:33%;" />
  - 通过坐标三角形顶点颜色映射

- 重心坐标
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706161338947.png" alt="image-20230706161338947" style="zoom:33%;" />
  - 可以使用三角形面积之比计算出来
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706162806562.png" alt="image-20230706162806562" style="zoom:33%;" />
  -  <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706163045057.png" alt="image-20230706163045057" style="zoom:33%;" />
  - 计算得到参数后可以用这几个参数做插值
  - 问题：投影之后的重心坐标会发生变化，因此要先插值再投影
- 纹理映射（双线性插值）（纹理过小）
  - 当显示分辨率远高于纹理分辨率时可能存在映射问题，如坐标转化后为小数，可能使得多个坐标映射到相同的纹理位置，造成显示不准确
  - 采用周围4个点的数值进行插值（两次水平一次垂直）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706172208264.png" alt="image-20230706172208264" style="zoom:33%;" />
- Mipmap范围查询（纹理过大）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706174502149.png" alt="image-20230706174502149" style="zoom:33%;" />
  - 范围查询：快速获取一个区域内颜色的平均值
    - 而不是超采样，这样可以减少重复计算
    - 建立不同的层
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706174824188.png" style="zoom:33%;" />
  - 映射相邻点区域，选取距离最大值为映射范围正方型的边长<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706175452958.png" alt="image-20230706175452958" style="zoom:33%;" />
  - 问题：不同层之间的过度不连续
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706180309960.png" alt="image-20230706180309960" style="zoom:33%;" />
    - 不同层上双线性插值，再在两层之间插值。（三线性插值）
  - 并不是所有像素都是压缩正方形（过采样）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706181304364.png" alt="image-20230706181304364" style="zoom:33%;" />
    - 各向异性过滤（对长条区域快速范围查询）
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
  - 扰动法线<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706184104600.png" alt="image-20230706184104600" style="zoom:33%;" />
    - 法线通过求导得到的切线得到
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706184802484.png" alt="image-20230706184802484" style="zoom:33%;" />
  - 二维图像上同理通过黑白变化计算<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706184817165.png" alt="image-20230706184817165" style="zoom: 33%;" />
  - 法线模拟vs位移<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706185019444.png" alt="image-20230706185019444" style="zoom:33%;" />

## 几何

### 隐式表述

- 数学表达式
  - 不告诉点都在哪，只告诉点的位置满足的约束（判断是否在几何上），如`f(x,y,z)=0`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706233235852.png" alt="image-20230706233235852" style="zoom:33%;" />
- csg法
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706234848733.png" alt="image-20230706234848733" style="zoom:33%;" />
- 距离函数
  - 空间中任何一个点到物体表面的最短距离
  - 通过距离函数来得到几何形体混合的效果
  - 插值（应用）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706235644170.png" alt="image-20230706235644170" style="zoom:33%;" />
    - 通过正负划分边界
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707001420918.png" alt="image-20230707001420918" style="zoom:33%;" />

### 显示表述

- 直接表示
  - 规定平面图形和二维到三维的映射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706233403094.png" alt="image-20230706233403094" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230706233636662.png" alt="image-20230706233636662" style="zoom:33%;" />
  - 但不容易判断内部和外部
  - 区别隐式曲面与显示曲面的关键就在于是否可以直接表示出所有的点
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
- 四点
  -  多次t划分直至剩下一个点
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707211546574.png" alt="image-20230707211546574" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707211724731.png" alt="image-20230707211724731" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707212011614.png" alt="image-20230707212011614" style="zoom:33%;" />
- 分段：点过多时不易于控制
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707213247492.png" alt="image-20230707213247492" style="zoom:33%;" />
  - 直接分段不够平滑（4个点一段）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707213259047.png" alt="image-20230707213259047" style="zoom:33%;" />
  - c^0^连续：曲线首尾相接
  - c^1^连续：切线连续

### 曲面

- 贝塞尔曲面
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707215834137.png" alt="image-20230707215834137" style="zoom:33%;" />
  - **双重**贝塞尔曲线
- 曲面loop细分
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707220818242.png" alt="image-20230707220818242" style="zoom:33%;" />
  - 划分为更多三角形并调整位置使得更加贴近原先的图像
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707225708716.png" alt="image-20230707225708716" style="zoom:33%;" />
  - 新顶点的位置由周围旧顶点的位置计算得到
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707230254250.png" alt="image-20230707230254250" style="zoom:33%;" />
  - 旧顶点的位置由原先的位置和周围点的位置决定
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707230347683.png" style="zoom:33%;" />
- Catmull-Clark细分（处理四边形面）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707231458185.png" alt="image-20230707231458185" style="zoom:33%;" />
  - 连接边、面的中点
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707231505479.png" alt="image-20230707231505479" style="zoom:33%;" />
  - 非四边形会产生奇异点，会在细分之后消失（因此之后奇异点数目不会再发生变化，即只有第一次细分时变化）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707231829386.png" alt="image-20230707231829386" style="zoom:33%;" />

- 曲面简化
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707220830993.png" alt="image-20230707220830993" style="zoom:33%;" />
  - 边坍缩
    - 删去边，捏成一个点
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707232409037.png" alt="image-20230707232409037" style="zoom:33%;" />
    - 用偏差（二次误差）计算新位置（到原先各面的平方和最小）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707232521945.png" alt="image-20230707232521945" style="zoom:33%;" />
    - 优先坍缩造成二次误差最小的边（使用优先队列）

- 曲面正则化（直到曲面简化，减少细节丢失）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707220845910.png" alt="image-20230707220845910" style="zoom:33%;" />

## 光线追踪

- Shadow Mapping（处理点光源）
  - 阴影：人能看到的位置，但光源看不到的位置
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234220403.png" alt="image-20230707234220403" style="zoom:33%;" />
  - 可以记录光源到不同物体的最短距离，来判断是否被遮挡形成阴影
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234622435.png" alt="image-20230707234622435" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234634718.png" alt="image-20230707234634718" style="zoom:33%;" />
    - 存在数值精度问题
    - 存在深度信息图（shadowmap）分辨率与实际渲染分辨率不匹配的问题
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707234643695.png" alt="image-20230707234643695" style="zoom:33%;" />
- 硬阴影与软阴影
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230707235609373.png" alt="image-20230707235609373" style="zoom:33%;" />
  - 点光源只会产生硬阴影
  - 当光源被部分遮挡时会产生软阴影
- 光线追踪应用了光路可逆性，从眼睛出发直至光源进行追踪
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708092756902.png" alt="image-20230708092756902" style="zoom:33%;" />
  - 从眼睛向外寻找，到达最近的（可观察物体）然后与光源连线计算着色结果（可见性）

### Whitted-Style Ray Tracing

- 一种递归算法，可以处理多次反射的情况
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708093259968.png" alt="image-20230708093259968" style="zoom:33%;" />
  - 着色叠加
- 光线
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708094310500.png" alt="image-20230708094310500" style="zoom:33%;" />
  - 点加方向
  - 解任意曲面
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708094545633.png" alt="image-20230708094545633" style="zoom:33%;" />
- 光线与三角形面求交
  - 使用一条法向量加上一个点来表示一个平面，并且通过向量乘法判断一个点是否在平面上
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708095659898.png" style="zoom:33%;" />
  - 法一：先求和平面的交点，再判断是否属于某个三角形
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708100348543.png" alt="image-20230708100348543" style="zoom:33%;" />
  - 法二：利用中心坐标直接判断（三个参数都非负）
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
    - 光线进入所有对面才真正进入了盒子，光线 离开任何一个对面就离开了盒子
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708110125119.png" alt="image-20230708110125119" style="zoom:33%;" />
  
- Uniform Spatial Partitions（AABB加速光线追踪）

  - 先和盒子求交，再决定是否要和物体求交
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708111146232.png" alt="image-20230708111146232" style="zoom:33%;" />

  - 划分的各自数目要恰当（但是均匀划分存在一系列问题，因为物体的分布不是均匀的）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708191224698.png" alt="image-20230708191224698" style="zoom: 33%;" />

- 几种不均匀划分方式（划分是广信追踪的准备工作）

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708192117492.png" alt="image-20230708192117492" style="zoom:33%;" />

- KD-Tree

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708192359516.png" alt="image-20230708192359516" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708212902708.png" alt="image-20230708212902708" style="zoom:33%;" />
  - 难点：判断三角形与盒子是否交很难，并且三角形可能跨盒子

- (BVH)物体划分

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708213437753.png" alt="image-20230708213437753" style="zoom:33%;" />
    - 确定包围盒；对包围盒内的物体进行划分；分别重新计算包围盒；继续计算。

  - 一个物体只会出现在一个盒子中
  - 可以每次都选择位于中间的三角形用于划分
  - 求交过程<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708215158007.png" alt="image-20230708215158007" style="zoom:33%;" />


### 辐射度量学

- 准确定义物理光照
- Radiant flux：单位时间的能量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708220326227.png" alt="image-20230708220326227" style="zoom:33%;" />
- Radiant Intensity：辐射能量
  - 单位立体角辐射的能量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708221019629.png" alt="image-20230708221019629" style="zoom:33%;" />
  - 立体角：
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708221146340.png" alt="image-20230708221146340" style="zoom:33%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708221803814.png" alt="image-20230708221803814" style="zoom:33%;" />
- Irradiance：单位面能量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708225633808.png" alt="image-20230708225633808" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708230202366.png" alt="image-20230708230202366" style="zoom:33%;" />
    - 随着半径增大，Irradiance减小；Radiant Intensity恒定
- Radiance：传播过程的能量
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
  - BRDF就是能量被如何分配到不同放线<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708233526839.png" alt="image-20230708233526839" style="zoom:33%;" />
  - 所有光源的辐射->反射总光线<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708233840810.png" alt="image-20230708233840810" style="zoom:33%;" />
  - 渲染方程：自发光+反射光<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708234338841.png" alt="image-20230708234338841" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708234751059.png" alt="image-20230708234751059" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708235018969.png" alt="image-20230708235018969" style="zoom:33%;" />
  - 递归弹射（包含多次反射**即全局光照**（直接光照+间接光照））<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230708235900191.png" alt="image-20230708235900191" style="zoom:33%;" />

#### 蒙特卡罗积分

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709085252585.png" alt="image-20230709085252585" style="zoom:33%;" />
- 使用随机采样获取积分区域内的值，用于进一步的积分计算
- （均匀采样）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709085408396.png" alt="image-20230709085408396" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709085416035.png" alt="image-20230709085416035" style="zoom:33%;" />

#### 路径追踪

- 解决Whitted-Style Ray不正确的地方
- 用蒙特卡洛积分表示反射方程
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709091915429.png" alt="image-20230709091915429" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709092950726.png" alt="image-20230709092950726" style="zoom:33%;" />
  - N!=1时N会指数级增长
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709093026135.png" alt="image-20230709093026135" style="zoom:33%;" />
  - 为了避免指数增长，只考虑一个方向（这就是路径追踪）
  - 采样足够多的经过同一个像素的光线来减少误差<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709093237329.png" alt="image-20230709093237329" style="zoom:33%;" />
  - 向不同方向随机发光
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709093429284.png" alt="image-20230709093429284" style="zoom:33%;" />
  - 为了避免无限递归，随即决定发反射次数（何时开始停止反射）
  - 概率p继续反射，（1-p）不再继续发射<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709094812062.png" alt="image-20230709094812062" style="zoom:33%;" />
    - 由于除以p，期望不变
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709095033407.png" alt="image-20230709095033407" style="zoom:33%;" />
- 采样效率低：光源太小，大部分发出的路径都不会到达光源
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709095531705.png" alt="image-20230709095531705" style="zoom:33%;" />
  - 改用光源来进行采样、积分
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709100416475.png" alt="image-20230709100416475" style="zoom:33%;" />
    - dA是立体角dw对应光源上的区域（先将dA映射到平行方向，然后两个平行表面是成比例的）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709100612954.png" alt="image-20230709100612954" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709100920862.png" alt="image-20230709100920862" style="zoom:33%;" />
    - 对于直接光照采用dA计算，对于间接光照仍然采用随机 方式

## 材质与外观

- 反射角计算
  - （菲涅⽿项）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709105229295.png" alt="image-20230709105229295" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111102180.png" alt="image-20230709111102180" style="zoom:33%;" />
    - 入射角越大，反射越强 （绝缘体，如玻璃）
  - 金属<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111217100.png" alt="image-20230709111217100" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111357074.png" alt="image-20230709111357074" style="zoom:33%;" />
- 折射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709110651481.png" alt="image-20230709110651481" style="zoom:33%;" />
- 微表面模型
  - 远处看材质，近处看几何（表面凹凸不平 ）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709111942766.png" alt="image-20230709111942766" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709112348765.png" alt="image-20230709112348765" style="zoom:33%;" />
    - 法线分布是否集中决定是漫反射还是镜面反射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709113045372.png" style="zoom:33%;" />
    - 菲涅尔项：总共有多少能量被反射
    - shadowing-masking：修正光线遮挡（入射角很大时反射光发现很可能会被表面上的凹凸遮挡）
    - distribution of normals：法线分布情况
  - 微表面方向性：各向同性/各向异性
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709113753033.png" alt="image-20230709113753033" style="zoom:33%;" />
    - 各向同性：反射结果只与 入射光与反射光的夹角相关<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709115045068.png" alt="image-20230709115045068" style="zoom:33%;" />
      - （四维）：入射光线和反射光线的坐标（二维）
      - 对于各向异性可以化简为三维
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709113933413.png" alt="image-20230709113933413" style="zoom:33%;" />
- BRDF性质
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709114203505.png" alt="image-20230709114203505" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709114224042.png" alt="image-20230709114224042" style="zoom:33%;" />
  - 能量收敛
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709114417284.png" alt="image-20230709114417284" style="zoom:33%;" />

### 高级光线传播

- BDPT双向路径追踪
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709125601288.png" alt="image-20230709125601288" style="zoom: 33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709120747552.png" alt="image-20230709120747552" style="zoom:33%;" />
- MLT
  - 使用马尔科夫链，找到一条有效路径后可以更好地找到有用的相关路径
  - 问题：难以确定覆盖率（局部自动推导）,可能存在覆盖率不均匀，何时收敛
- Photon Mapping 光子映射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709123959664.png" alt="image-20230709123959664" style="zoom:33%;" />
  - 首先由光源发射光子
  - 然后由摄像机发送进行观察
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709124821506.png" alt="image-20230709124821506" style="zoom:33%;" />
    - 找周围最近n个光子占据的面积大小，从而得到光子密度
    - 根据局部光子密度进行渲染
    - 不过由于光子数目有限，因此存在偏差
    - **有偏**：存在偏差，但样本足够多时会收敛
- VCM：双向路径+光子追踪
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
  - 双重圆柱模型<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133149938.png" alt="image-20230709133149938" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133521939.png" alt="image-20230709133521939" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133534764.png" alt="image-20230709133534764" style="zoom:33%;" />

### 表面模型

- Translucent Material:（半透明）
  - 次表面反射<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709133811091.png" alt="image-20230709133811091" style="zoom:33%;" />
  - BSSRDF就好像内部也有一个光源（双光源模拟）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709134123772.png" alt="image-20230709134123772" style="zoom:33%;" />

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
  - 快门速度（曝光时长）
    - 由于快门让然是逐渐打开的，不同位置的曝光时间存在误差，因此存在果冻效应
    - 光圈大小减小一倍，曝光面积会减少为1/4即快门要延长为原来的4倍
  - iso
    - 简单增益，增大信号强度
    - 会放大噪声
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709163244915.png" alt="image-20230709163244915" style="zoom:33%;" />

### 镜头

- 物距、像距<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709165307006.png" alt="image-20230709165307006" style="zoom:33%;" />
- 景深
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709170131194.png" alt="image-20230709170131194" style="zoom:33%;" />
    - 像投射在了传感器前面，在传感器上呈圆形
    - 其他条件一定时光圈越小CoC也越小，景深越弱
    - 认为当CoC足够小时图象是清晰的
  - 光圈f数=焦距/光圈直径
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709171355075.png" alt="image-20230709171355075" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709171415497.png" alt="image-20230709171415497" style="zoom:33%;" />

### 模拟渲染

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709172112189.png" alt="image-20230709172112189" style="zoom: 33%;" />
- 清晰范围（可接受CoC大小的成像范围）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709172646808.png" alt="image-20230709172646808" style="zoom:33%;" />

### 光场

#### 全光函数

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709173911389.png" alt="image-20230709173911389" style="zoom:33%;" />

  - 从任意位置以不同角度来看世界

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

- 将原本的单个像素进一步拆分，将单个像素细分为不同的方向
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

- 质点弹簧系统

  - 弹簧连接质点<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709203041124.png" alt="image-20230709203041124" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709203227037.png" alt="image-20230709203227037" style="zoom:33%;" />
    - 单位向量表示方向
  - 为了让物体最终停下来，添加反方向摩擦力（弹簧**内部**的摩擦力）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709204039960.png" alt="image-20230709204039960" style="zoom:33%;" />
  - 添加抵抗各方向弯折的弹簧<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709204711839.png" alt="image-20230709204711839" style="zoom:33%;" />

- 粒子系统

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

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709205649883.png" alt="image-20230709205649883" style="zoom:33%;" />

- 逆运动学：告知运动轨迹，自动计算运动方向

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230709210237548.png" alt="image-20230709210237548" style="zoom:33%;" />

  