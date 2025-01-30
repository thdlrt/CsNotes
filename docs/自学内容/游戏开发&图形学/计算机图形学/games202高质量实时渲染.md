## 实时阴影
### percentage closer soft shadows（PCSS）
#### percentage closer filtering（PCF）
- 硬阴影相当于只有 01 两种状态，通过 pcf 可以生成含中间状态的软阴影
	- 是在阴影生成阴影过程中使用，而不只是后处理
- 从 shadowmap 取样时取一个较大范围的值，并取平均值作为阴影的强度
	- 采样范围就决定了阴影的硬度
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129210147.png)
#### 软阴影的渲染
- 通常阴影的硬度并不是恒定的，与遮挡物与投射平面的距离相关，距离越近阴影的硬度越大
	- 具体的规则 $w_{Penumbra}=(d_{Receiver}-d_{Blocker})\cdot w_{Light}/d_{Blocker}$
	- ![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129210802.png)
	- 通过估计不同位置的 penumbra 大小来决定 pc 采样防范未的大小，即阴影的硬度
		- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129211420.png)

- 更简单的估计：只根据灯光范围大小，scene 和灯光的距离来估计
	- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250129211751.png)
### Variance Soft Shadow Mapping (VSSM)
- 解决 PCSS **第一步和第三步**范围操作速度慢的问题
- 优化 step 1：blocker depth 阴影硬度的求解
- 优化 step 3：shadowmap 在一定范围内小于一个距离的点的数目
	- 假设正态分布，只需要平均值和方差来确定分布就能估计数目
	- 平均可以使用 mipmap 存储
	- 方差使用均值计算 $\mathrm{Var}(X)=\mathrm{E}(X^2)-\mathrm{E}^2(X)$