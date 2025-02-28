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
a = a.type(tor)
#创建时指定数据类型
a = torch.tensor([7, 4, 3, 2, 6], dtype = torch.int32) 
```
- 张量的类型包含设备信息和数据类型，张量的数据类型主要包含数据精度（数据类型的细分）
	- CPU 张量：`torch.FloatTensor`（浮点型）、`torch.IntTensor`（整型）
	- GPU 张量：`torch.cuda.FloatTensor`、`torch.cuda.IntTensor`