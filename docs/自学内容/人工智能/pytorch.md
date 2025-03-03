## 基本概念
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
- 定义数据的**组织方式**
- 提供标准化的**数据访问**方法
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
- 从`Dataset`中高效生成批量数据
- 原始数据 → Dataset → 单样本处理 → DataLoader → 批量生成 → 模型训练/验证
- 可以方便的实现：
	- 批量控制
	- 数据打乱
	- 并行加载
	- 内存管理
```python
trainloader = DataLoader(dataset = dataset, batch_size = 1)
w = torch.tensor(-15.0,requires_grad=True)
b = torch.tensor(-10.0,requires_grad=True)
LOSS_Loader = []

def train_model_DataLoader(epochs):
    
    # Loop
    for epoch in range(epochs):
        
        # SGD is an approximation of out true total loss/cost, in this line of code we calculate our true loss/cost and store it
        Yhat = forward(X)
        
        # store the loss 
        LOSS_Loader.append(criterion(Yhat, Y).tolist())
        
        for x, y in trainloader:
            
            # make a prediction
            yhat = forward(x)
            
            # calculate the loss
            loss = criterion(yhat, y)
            
            # Section for plotting
            get_surface.set_para_loss(w.data.tolist(), b.data.tolist(), loss.tolist())
            
            # Backward pass: compute gradient of the loss with respect to all the learnable parameters
            loss.backward()
            
            # Updata parameters slope
            w.data = w.data - lr * w.grad.data
            b.data = b.data - lr* b.grad.data
            
            # Clear gradients 
            w.grad.data.zero_()
            b.grad.data.zero_()
            
        #plot surface and data space after each epoch    
        get_surface.plot_ps()
```
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

#### 工作流程
- ![image.png|400](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250301123501.png)
- PyTorch 中的优化流程
	- 从 `trainloader` 读取小批量数据 `x, y`。
	- 输入 `x` 至模型，计算预测值 `yhat`。
	- 使用损失函数计算预测值与真实值之间的误差（`loss`）。
	- 使用反向传播（`backward()`）计算梯度。
	- 使用优化器（`optimizer.step()`）更新模型参数。
	- 清空梯度（`optimizer.zero_grad()`），进入下一轮循环。
- `model.state_dict()`返回一个字典，包含模型的所有可学习参数（如权重、偏置）及其当前值。
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250301202244.png)
	- optim 表示优化器
	- lr 为学习率
- 使用 pytorch 提供的一系列类来实现算法[[3 3_PyTorchway_v3.ipynb]]
```python
from torch import nn, optim
#线性回归类定义
class linear_regression(nn.Module):
    # Constructor
    def __init__(self, input_size, output_size):
        super(linear_regression, self).__init__()
        self.linear = nn.Linear(input_size, output_size)
    # Prediction
    def forward(self, x):
        yhat = self.linear(x)
        return yhat
        
#损失函数与优化器      
criterion = nn.MSELoss() # 均方误差损失
model = linear_regression(1, 1) # 实例化模型 
optimizer = optim.SGD(model.parameters(), lr=0.01) # 优化器绑定模型参数

trainloader = DataLoader(dataset = dataset, batch_size = 1)
#参数手动初始化
model.state_dict()['linear.weight'][0] = -15 model.state_dict()['linear.bias'][0] = -10

#初始化参数 → 数据加载 → 前向传播 → 损失计算
# ↑									↓ 
#参数更新 ← 梯度清零 ← 反向传播 ← 损失计算
def train_model_BGD(iter):
    for epoch in range(iter):
        for x, y in trainloader:
            yhat = model(x)                   # 前向传播
            loss = criterion(yhat, y)         # 损失计算
            get_surface.set_para_loss(...)    # 可视化更新
            optimizer.zero_grad()             # 梯度清零
            loss.backward()                   # 反向传播
            optimizer.step()                 # 参数更新
```
- 保存模型参数 `torch.save(model.state_dict(), 'lol_win_predictor.pth')`
- 加载模型 
```python
#先创建模型然后加载参数
# 创建新模型实例（需保持与原模型相同结构） 
loaded_model = LogisticRegressionModel(input_dim=X_train_tensor.shape[1])
loaded_model.load_state_dict(torch.load('lol_win_predictor.pth'))
```

#### 超参数调优
- 将数据集划分为训练、验证、测试数据集
	- **训练阶段**：使用**训练集**更新模型参数（梯度下降）。
	- **验证阶段**：使用**验证集**评估不同超参数配置的性能。
	- **测试阶段**：使用**测试集**仅进行一次最终评估。
- **训练集**
	- 直接用于模型参数的训练（如通过**梯度下降**优化权重和偏置）
	- 占数据总量的 **60%~80%**（依数据规模调整）
- **验证集**
	- 用于 **超参数调优**（如**学习率**、正则化系数、网络层数等）。
	- 评估模型的泛化能力，防止过拟合训练数据。
	- 占数据总量的 **10%~20%**。
	- 需与训练集独立分布，反映真实场景数据特性。
- **测试集**
	- **最终评估** 模型在未知数据上的性能（模拟真实场景）。
	- 仅在模型完全确定（超参数固定、训练完成）后使用一次。
	- 占数据总量的 **10%~20%**。
	- **严禁参与训练或调参**，否则会导致过拟合测试集。
- 为什么区分训练集和验证集：
	- 如果在训练集上多次尝试不同学习率（或其他超参数），模型会间接“记住”验证集的特征，导致验证集上的性能被高估（本质是过拟合验证集）。
	- 训练集的损失反映模型对已知数据的拟合程度，而验证集的损失反映模型对未知数据的预测能力。
	- 利用验证集进行超参数调优可以提升模型的泛化能力，保证在未知数据（测试集上的表现）
[[3 6_training_and_validation_v3.ipynb]]
#### 随机梯度下降
- 每次迭代**只使用一个样本**(依次选择) 计算成本，而不是使用所有的样本
	- 通过 **单个样本** 的梯度来**近似**全体数据的梯度，迭代更新模型参数。
	- 迭代表示用一个元素进行计算，计算一趟称为一个周期
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250301115110.png)
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250301115120.png)
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250301115134.png)


```python
# The function for training the model

LOSS_SGD = []
w = torch.tensor(-15.0, requires_grad = True)
b = torch.tensor(-10.0, requires_grad = True)

def train_model_SGD(iter):
    
    # Loop
    for epoch in range(iter):
        
        # SGD is an approximation of out true total loss/cost, in this line of code we calculate our true loss/cost and store it
        Yhat = forward(X)

        # store the loss 
        LOSS_SGD.append(criterion(Yhat, Y).tolist())
        
        for x, y in zip(X, Y):
            
            # make a pridiction
            yhat = forward(x)
        
            # calculate the loss 
            loss = criterion(yhat, y)

            # Section for plotting
            get_surface.set_para_loss(w.data.tolist(), b.data.tolist(), loss.tolist())
        
            # backward pass: compute gradient of the loss with respect to all the learnable parameters
            loss.backward()
        
            # update parameters slope and bias
            w.data = w.data - lr * w.grad.data
            b.data = b.data - lr * b.grad.data

            # zero the gradients before running the backward pass
            w.grad.data.zero_()
            b.grad.data.zero_()
            
        #plot surface and data space after each epoch    
        get_surface.plot_ps()
```
#### 小批量梯度下降
- 将数据集拆分，每次选择**一部分**计算成本，兼顾效率与准确性
[[3 2_mini-batch_gradient_descent_v3.ipynb]]
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250301121328.png)
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250301121358.png)

- 通过 dataloader 可以方便的实现以批为单位取出
```python
dataset = Data()
trainloader = DataLoader(dataset = dataset, batch_size = 5)
w = torch.tensor(-15.0, requires_grad = True)
b = torch.tensor(-10.0, requires_grad = True)
LOSS_MINI5 = []
lr = 0.1

def train_model_Mini5(epochs):
    for epoch in range(epochs):
        Yhat = forward(X)
        get_surface.set_para_loss(w.data.tolist(), b.data.tolist(), criterion(Yhat, Y).tolist())
        get_surface.plot_ps()
        LOSS_MINI5.append(criterion(forward(X), Y).tolist())
        for x, y in trainloader:
            yhat = forward(x)
            loss = criterion(yhat, y)
            get_surface.set_para_loss(w.data.tolist(), b.data.tolist(), loss.tolist())
            loss.backward()
            w.data = w.data - lr * w.grad.data
            b.data = b.data - lr * b.grad.data
            w.grad.data.zero_()
            b.grad.data.zero_()
```
#### 多元线性回归
[[4 2 multiple_linear_regression_training_v2.ipynb]]
#### 多重输出线性回归
- 多套参数，有输出输出多个不同的结果
	- ![image.png|400](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250302134604.png)
	- ![image.png|400](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250302134936.png)
#### 逻辑回归
- 如果一个数据中的顶点类型可以通过线性划分，那么称其为线性可分的
- 映射函数：从任意大小映射到 `0~1` 范围
```python
sig = nn.Sigmoid()
yhat = sig(z)
```
- 此外为了避免阶梯状代价函数（无法收敛到最低处），使用对数代价函数
[[5 3_cross_entropy_logistic_regression_v2.ipynb]]
```python
class logistic_regression(nn.Module):
    
    # Constructor
    def __init__(self, n_inputs):
        super(logistic_regression, self).__init__()
        self.linear = nn.Linear(n_inputs, 1)
        
    # Prediction
    def forward(self, x):
        yhat = torch.sigmoid(self.linear(x))
        return yhat
        
model = logistic_regression(1)
# 对数成本函数
def criterion(yhat,y):
    out = -1 * torch.mean(y * torch.log(yhat) + (1 - y) * torch.log(1 - yhat))
    return out

# Build in criterion
# criterion = nn.BCELoss()

trainloader = DataLoader(dataset = data_set, batch_size = 3)
learning_rate = 2
optimizer = torch.optim.SGD(model.parameters(), lr = learning_rate)

def train_model(epochs):
    for epoch in range(epochs):
        for x, y in trainloader:
            yhat = model(x)
            loss = criterion(yhat, y)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            get_surface.set_para_loss(model, loss.tolist())
        if epoch % 20 == 0:
            get_surface.plot_ps()
            
train_model(100)
```
## 实操
### 逻辑回归分类算法