### Tensors 张量
- 使用 pytorch 张量组成神经网络，作为神经网络中数据流动的结拜呢单位
- 张量可以表示不同维度的数据
	- 标量（0维张量）：单个数值，如 `torch.tensor(3.14)`
	- 向量（1维张量）：一维数组，如 `torch.tensor([1, 2, 3])`
	- 矩阵（2维张量）：二维数组，如 `torch.tensor([[1, 2], [3, 4]])`
	- 高维张量：更高维度的数据，如图像（3维：通道×高×宽）
#### Tensors 1D
- 一维数组 
```python
import torch
a = torch.tensor([7, 4, 3, 2, 6])
a[i] #下标访问
a.dtype #张量的数据类型
a.type #张量的类型
a.tolist() #转化为数组
a.size()
a.ndimension() #维数
a = a.type(torch.FloatTensor) #进行类型转换
#创建时指定数据类型
a = torch.tensor([7, 4, 3, 2, 6], dtype = torch.int32) 
```
- 张量的类型包含设备信息和数据类型，张量的数据类型主要包含数据精度（数据类型的细分）
	- CPU 张量：`torch.FloatTensor`（浮点型）、`torch.IntTensor`（整型）
	- GPU 张量：`torch.cuda.FloatTensor`、`torch.cuda.IntTensor`
- 重塑张量形状
	- 新形状的总元素数必须与原张量一致
	- 允许使用 `-1` 自动推断某一维度大小
```python
a = torch.randn(2, 3)  # 形状为 (2, 3)
b = a.view(3, 2)       # 合法，总元素数 6
c = a.view(4, -1)       # 非法，总元素数 6 无法整除 4
```
- 与 numpy 的转换
	- `form_numpy(numpy_array)` 
	- `numpy()`
#### Tensors 2D
- ![image.png|300](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250228121846.png)
- 不同于矩阵乘法，张量相乘的结果就是对应位置的元素相乘 `A*b`
	- 也可以进行矩阵乘法 `torch.mm(A,B)`
### 微分
- 导数的计算
```python
x = torch.tensor(2, requires_grad=True) # 跟踪计算图
y = x ** 2
y.backward()
x.grad #获取计算结果，在x=2处x**2的导数4
#偏导数
u = torch.tensor(1.0,requires_grad=True)
v = torch.tensor(2.0,requires_grad=True)
f = u * v + u ** 2
f.backward()
u.grad
v.grad
```
### 数据集
