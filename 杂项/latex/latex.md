## 排版



## 数学

### 常用&示例

- $$\sqrt{x} + \sqrt{x^{2}+\sqrt{y}} = \sqrt[3]{k_{i}} - \frac{x}{m}$$
- $$\vec{a} + \overrightarrow{AB} + \overleftarrow{DE}$$
- $$  \lim_{x \to \infty} x^2_{22} - \int_{1}^{5}x\mathrm{d}x$$
- $$\sum_{n=1}^{20} n^{2} = \prod_{j=1}^{3} y_{j}  + \lim_{x \to -2} \frac{x-2}{x} $$
- $$ x_{1},x_{2},\ldots,x_{5}  \quad x_{1} + x_{2} + \cdots + x_{n} $$
- $a \times b , a \cdot b , a \mid b$

### 标号

- 上标`^`；下标`_`；空格`  \quad  `
  - 对于同一个字符的上标和下标没有先后顺序
  - 可以用于积分、求和等数学算子的上下参数

- 角度$90^\circ$
- 上下标识$\overline{a+b}$ $\underline a$ $\hat{a}$ $\overset{a}{b}$ $\underset{a}{b}$
- 箭头$\overrightarrow{AB}$ $\underleftarrow{AB}$
- 上点$\dot{a}$ $\ddot{s}$ $\dddot{a}$
- $\exists \ \forall$
- 花括号$\overbrace{a_0,a_1,\dots,a_n}^{共n+1项}$
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710214006362.png" alt="image-20230710214006362" style="zoom:33%;" />
- 常用字母
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710140719398.png" alt="image-20230710140719398" style="zoom: 50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710141137994.png" alt="image-20230710141137994" style="zoom:50%;" />


### 公式

- 分式$\frac{2+a}{2a}$
  - dfrac较大分式；tfrac较小分式
- 二项式$\binom{2}{1}$
- 根式$\sqrt[3]{8}$
- 矩阵（使用`$$ $$`内部放置latex语句）
  - $$\begin{pmatrix} a_{11} & a_{12} & a_ {13} \\ 0 & a_{22} & a_{23} \\ 0 & 0 & a_{33} \end{pmatrix}$$
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710135339420.png" alt="image-20230710135339420" style="zoom: 50%;" />
  - &分割列；\\\\分割行
  - \sybstack{}只有一列的无括号矩阵，便于排版
    - $\sum_{\substack{0<i<n \\ o<j<i}} A_{ij}$

### 数学算子

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710141608056.png" alt="image-20230710141608056" style="zoom: 50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710211738091.png" alt="image-20230710211738091" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710211747446.png" alt="image-20230710211747446" style="zoom:50%;" />
  - $\varlimsup_{k\to\infty}A_k=\lim_{J\to\infty}\lim_{K\to\infty}\bigcap_{j=1}^J\bigcup_{k=j}^KA_K$

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710212526566.png" alt="image-20230710212526566" style="zoom:33%;" />

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710212544667.png" alt="image-20230710212544667" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710212618162.png" alt="image-20230710212618162" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710212644480.png" alt="image-20230710212644480" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710212702740.png" alt="image-20230710212702740" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710213625833.png" alt="image-20230710213625833" style="zoom:33%;" />
  - $\xrightarrow[x\leq0]{x\geq 1}$
- 括号
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230710213721965.png" alt="image-20230710213721965" style="zoom:33%;" />
  - 使用`\left \right可以实现括号嵌套自动缩放`
  - $\left[\frac12\left(x^2+y^2\right)\right]$

### 多行公式

- cases括号$\begin{cases}a+b=b+a\\ab=ba\end{cases}$

- 使用\&对齐公式

  - $$
    a^b \equiv
    \begin{cases}
    a^{b\mod\varphi(m)} & \text{gcd}(a,m)=1 \\
    a^b & b<\varphi(m) \\
    a^{b\mod{\varphi(m)}+\varphi(m)} & b\geq\varphi(m)
    \end{cases}
    \ (\mod m)
    $$

  - 
