# 金融风险管理-实验6

**小组成员**：谭顺予，汪科，田昊东，程圣杰

## 实验过程

### 步骤1：读取数据

首先，从CSV文件中读取股票价格数据。文件名为`stock_data.csv`，该文件中第二至第四列包含三只股票的收盘价。

```matlab
data = readtable('stock_data.csv');
prices = table2array(data(:, 2:4));  % 提取收盘价并转换为数组
```

### 步骤2：定义估计期和回测期

定义分析的时间窗口。估计期为2016年1月1日至2019年12月30日，回测期为2019年12月31日至2020年3月31日。

```matlab
estimation_period = datetime('2016-01-01'):datetime('2019-12-30');
backtest_period = datetime('2019-12-31'):datetime('2020-03-31');
data_dates = datetime(data{:, 'x__'});  % 将日期列转换为datetime类型
estimation_data = prices(ismember(data_dates, estimation_period), :);
backtest_data = prices(ismember(data_dates, backtest_period), :);
```

### 步骤3：计算日收益率

计算估计期内的日收益率，使用对数收益率公式。

```matlab
estimation_returns = diff(log(estimation_data)) * 100;
```

### 步骤4：计算VaR

首先设定置信水平，并计算需要的VaR位置。然后根据该位置从排序后的日收益率中计算每只股票的VaR。

```matlab
alpha = 0.05;
num_days = size(estimation_returns, 1);
sorted_returns = sort(estimation_returns);
VaR_positions = ceil(alpha * (num_days - 1)); 
P0 = mean(estimation_data(1,:));  % 以估计期初价格作为初始价格
VaR_values = -sorted_returns(VaR_positions, :) * P0;
disp('每只股票的VaR:');
disp(VaR_values);
```

### 步骤5：计算组合VaR

对组合收益率进行排序，并计算组合的VaR。

```matlab
portfolio_returns = sum(estimation_returns, 2) / 3;
sorted_portfolio_returns = sort(portfolio_returns);
portfolio_VaR = -sorted_portfolio_returns(VaR_positions) * P0;
disp('组合的VaR:');
disp(portfolio_VaR);
```

### 步骤6：回测VaR模型

计算回测期的日收益率，并统计违约次数（即损失超过VaR的天数）。

```matlab
backtest_returns = diff(log(backtest_data)) * 100;
breach_counts = sum(backtest_returns*P0 < -repmat(VaR_values, size(backtest_returns, 1), 1));
disp('违约次数:');
disp(breach_counts);
```

## 实验结果分析与结论

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240502171956476.png" alt="image-20240502171956476" style="zoom: 50%;" />

- 每只股票的VaR：第一只股票的VaR为47.8677，第二只为67.5504，第三只为37.8609。这意味着在给定的置信水平下（通常是95%），预期在一个交易日内，第一只股票最大可能损失约47.87单位，第二只约67.55单位，第三只约37.86单位。股票二的VaR最高，表明其风险最大，而股票三的VaR最低，风险相对较小。

- 组合的VaR：组合的VaR为38.1708。这表明整个投资组合在相同置信水平下，预期在一个交易日内的最大可能损失约为38.17单位。组合的VaR低于任何单只股票的VaR，这是因为组合内的资产之间存在分散化效应，降低了整体风险。
- 违约次数为7, 9, 8，分别对应三只股票，意味着在回测期间，每只股票的实际损失超过其计算的VaR的天数分别是7天、9天和8天。