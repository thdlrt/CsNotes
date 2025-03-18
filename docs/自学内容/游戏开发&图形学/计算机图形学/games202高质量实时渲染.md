## 数学
- 两个重要的微积分不等式
	- Schwarz 不等式：$\left[\int_{a}^{b}f(\:x\:)\:g(\:x\:)\:\mathrm{d}x\:\right]^{2}\leqslant\int_{a}^{b}f^{2}\left(\:x\:\right)\mathrm{d}x\cdot\int_{a}^{b}g^{2}\left(\:x\:\right)\mathrm{d}x$
	- Minkowski 不等式：$\left\{\int_{a}^{b}\left[f(x)+g(x)\right]^{2}\mathrm{d}x\right\}^{\frac{1}{2}}\leqslant\left\{\int_{a}^{b}f^{2}(x)\mathrm{d}x\right\}^{\frac{1}{2}}\:+\:\left\{\int_{a}^{b}g^{2}(x)\mathrm{d}x\right\}^{\frac{1}{2}}$
	- $\int_\Omega f(x)g(x)\:\mathrm{d}x\approx\frac{\int_\Omega f(x)\:\mathrm{d}x}{\int_\Omega\:\mathrm{d}x}\cdot\int_\Omega g(x)\:\mathrm{d}x$ 约等条件：$\Omega$ 积分范围很小或 g 函数足够光滑，积分域内变化较小
- 应用：渲染方程![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318115802.png)
	- 蓝色为入射光相关；黄色为反射性质；红色为集合修正因子
	- 可以近似为![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318115847.png)
- 其条件就是：积分域小（入射光范围小，如一个点光源）或积分内的函数比较光滑（如比较漫反射的 BRDF）
## 实时阴影
### percentage closer soft shadows（PCSS）
#### percentage closer filtering（PCF）
- 硬阴影相当于只有 01 两种状态，通过 pcf 可以生成含中间状态的软阴影
	- 是在阴影生成阴影过程中使用，而不只是后处理
- 从 shadowmap 取样时取一个**较大范围**的值，并取平均值作为阴影的强度
	- 采样范围就决定了阴影的硬度
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129210147.png)
#### 软阴影的渲染
- 通常阴影的硬度并不是恒定的，与遮挡物与投射平面的**距离**相关，距离越近阴影的硬度越大
	- 具体的规则 $w_{Penumbra}=(d_{Receiver}-d_{Blocker})\cdot w_{Light}/d_{Blocker}$
	- ![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129210802.png)
	- 通过估计不同位置的 penumbra 大小来决定 pc 采样防范未的大小，即阴影的硬度
		- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129211420.png)

- 更简单的估计：只根据灯光范围大小，scene 和灯光的距离来估计
	- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129211751.png)
### Variance Soft Shadow Mapping (VSSM)
- 解决 PCSS **第一步和第三步**范围操作速度慢的问题
- 优化 step 3：shadowmap 在一定范围内小于一个距离的点的数目
	- 假设正态分布，只需要平均值和方差来确定分布就能估计数目
	- 平均可以使用 mipmap 存储（mipmap 存储误差较大）使用前缀和存储更加请准
	- 方差使用均值计算 $\mathrm{Var}(X)=\mathrm{E}(X^2)-\mathrm{E}^2(X)$
	- 再使用切比雪夫不等式进行估计 $P(x>t)\leq\frac{\sigma^2}{\sigma^2+(t-\mu)^2}$ 当做"等式"
- 优化 step 1：blocker depth 阴影硬度的求解
	- 注意求的是遮挡物（比目标点距离近的点）的距离平均值（如图中蓝色部分平均值），而不是 mipmap 一定范围内所有点的平均值
	- ![image.png|151](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130195033.png)
	- 比如目标点为 7，那么只对红色部分求平均值
	- $\frac{N_{1}}{N}Z_{unocc}+\frac{N_{2}}{N}Z_{occ}=Z_{Avg}$ 遮挡物的百分比乘以遮挡物平均深度+非遮挡物部分分就是总共的平均深度
	- 设采样点深度为 $t$ 则可以假定 $Z_{unocc} = t$
	- 同样可以用切比雪夫不等式求解
		- ![image.png|300](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130200147.png)
### SDF 软阴影
- 使用 SDF 距离场估计软阴影
	- 速度快
	- 质量高
- 从投影面上一点看向面光源
	- ![image.png|238](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318170755.png)
	- 一个角度上一点的 SDF 越小表示不收遮挡的安全角越小，阴影就越硬
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130204927.png)
	- 取角度方向上距离场**最小值**作为安全距离
	- 计算近似角度 $\min\left\{\frac{k\cdot\mathrm{SDF}(p)}{p-o},1.0\right\}$ 通过使用 $k$ 而不是反三角函数精确计算来减少计算的开销
		- ![image.png|246](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318171131.png)
		- k 决定了阴影的硬度

## 环境光照
### splitsum 方法预处理的 IBL
- IBL **基于图片的光照**
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130211317.png)
	- 通常 BRDF 有以下性质中的一个：镜面反射（范围小）；漫反射（变化小, **更光滑**）
	- 这就可以使用**近似** $\int_\Omega f(x)g(x)\mathrm{~d}x\approx\frac{\int_{\Omega_G}f(x)\mathrm{~d}x}{\int_{\Omega_G}\mathrm{~d}x}\cdot\int_\Omega g(x)\mathrm{~d}x$（为了避免通过采样计算，这很慢）
	- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130211841.png)
	- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130212632.png)
	- 因此可以对**环境光贴图进行预 prefiltering**（如生成一系列 mipmap）针对不同 BRDF 预生成
	- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130212722.png)
	- **前半部分的计算**就是相当于对一定区域的环境光贴图做 filtering
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130213359.png)
	- 计算后半部分
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130214409.png)
	- 两个近似描述![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130214824.png)
	- 由此利用菲涅尔项的近似
	- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130215037.png)
	- 可以近似认为只和 roughness 和 $\theta$ 有关，可以用一个纹理存储二维预计算结果![image.png|290](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250130215942.png)
	- 这里的角度是出射方向，入射方向是在积分预计算时对所有方向进行了计算
#### 环境光照的阴影
- 只从**最亮的（几）个光源**生成阴影（来减少计算量）
### 实时环境光照
#### 球面谐波函数
- 球函数就是一系列**二维基函数**
	- 球面谐波函数十一组定义在球面上的拯救函数，作用类似于在一维场合中用傅里叶级数分解函数
	- 通过球面谐波函数，可以高效逼近环境光，并简化积分运算
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318183151.png)
- 可以通过积分求出任何函数 $f$ 在基函数 $B_{i}$ 上的投影（即 $B_i$ 的**系数**）$c_i=\int_\Omega f (\omega) B_i (\omega)\:\mathrm{d}\omega$

- **漫反射的 BRDF** 表现就像一个低通滤波
	- ![image.png|200](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318185112.png)
	- 只有**前三阶**的系数较大，后面系数都趋近 0，也就是只需要使用少量的球面谐波函数就可以描述 $E_{Im}=A_1L_{Im}$ 就有很好的效果
#### Precomputed Radiance Transfe（PRT）
- 渲染方程：![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318190215.png)
	- 三项均可以**用球面函数来描述**
- 进行拆分：认为**只有光照**在渲染过程中**变化**
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250318190449.png)
	- 
## 全局光照
