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
- 使用固定的随机数生成器种子值，确保代码的**可重复性** `torch.manual_seed(0)`
- `原始数据 → Dataset → 单样本处理 → DataLoader → 批量生成`
#### Dataset
- 定义数据的组织方式
- 提供标准化的数据访问方法
- **重写**来实现 Dataset 类
```python
from torch.utils.data import Dataset

class toy_set(Dataset):
    def __init__(self, length = 100, transform = None):
        self.len = length
        self.x = 2 * torch.ones(length, 2)
        self.y = torch.ones(length, 1)
        self.transform = transform
        """初始化数据路径、预处理参数等"""
    
    def __len__(self):
        return self.len
        """返回数据集总样本数"""

    def __getitem__(self, idx):
        sample = self.x[index], self.y[index]
        if self.transform:
            sample = self.transform(sample)     
        return sample
        """返回单个样本（支持索引访问）"""
```
#### DataLoader
- 
#### 变换
- 用于变换数据的变换类
```python
class add_mult(object):

# Constructor
def __init__(self, addx = 1, muly = 2):
    self.addx = addx
    self.muly = muly

# Executor
def __call__(self, sample):
    x = sample[0]
    y = sample[1]
    x = x + self.addx
    y = y * self.muly
    sample = x, y
    return sample
    
#对数据进行转换
a_m = add_mult()
data_set = toy_set()
a_m(data_set[i])
#也可以在创建数据集时就传递变换
cust_data_set = toy_set(transform = a_m)
```
- 组合多种变换
```python
from torchvision import transforms

# 定义第二个变化类
class mult(object):

# Constructor
def __init__(self, mult = 100):
    self.mult = mult
    
# Executor
def __call__(self, sample):
    x = sample[0]
    y = sample[1]
    x = x * self.mult
    y = y * self.mult
    sample = x, y
    return sample
    
#组合变化
data_transform = transforms.Compose([add_mult(), mult()])
data_transform(data_set[0])
```
## 算法
### 线性回归预测
- 使用模型
```python
from torch.nn import Linear
# 模型的wb参数会被随机初始化
model = Linear(in_features = 1, out_features = 1, bias=True)# 输入的特征数目、输出的特征数目、是否包含偏置项
```
#### 使用 pytorch 实现梯度下降的线性回归算法
[[2 3_training_slope_and_bias_v3.ipynb]]
```python
import torch
X = torch.arange(-3, 3, 0.1).view(-1, 1)
f = 1 * X - 1
# Add noise
Y = f + 0.1 * torch.randn(X.size())

def forward(x):#预测计算
    return w * x + b
def criterion(yhat,y):#成本计算
    return torch.mean((yhat-y)**2)
#初始化参数
w = torch.tensor(-15.0, requires_grad = True)
b = torch.tensor(-10.0, requires_grad = True)
lr = 0.1
LOSS = []
#执行训练
def train_model(iter):
    # Loop
    for epoch in range(iter):

        # make a prediction
        Yhat = forward(X)

        # calculate the loss 
        loss = criterion(Yhat, Y)

        # Section for plotting
        get_surface.set_para_loss(w.data.tolist(), b.data.tolist(),     loss.tolist())
        if epoch % 3 == 0:
            get_surface.plot_ps()

        # store the loss in the list LOSS
        LOSS.append(loss)

        # backward pass: compute gradient of the loss with respect  to all the learnable parameters
        loss.backward()

        # update parameters slope and bias
        w.data = w.data - lr * w.grad.data
        b.data = b.data - lr * b.grad.data

        # zero the gradients before running the backward pass
        w.grad.data.zero_()
        b.grad.data.zero_()
train_model(15)
```
![image.png|400](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250301011302.png)
#### 随机梯度下降
#### 小批量梯度下降
#### 优化