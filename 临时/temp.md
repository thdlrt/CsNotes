# 金融风险管理-实验4

> **小组成员**：谭顺予，汪科，田昊东，程圣杰
>
> ## 实验过程
>
> ### 步骤1：数据下载
>
> 首先，从CCER数据库下载三只股票的数据，并使用Matlab的`xlsread`函数读取数据。
>
> ```matlab
> stock_data = xlsread("C:\Users\18373\Desktop\前复权价格.xlsx");
> ```
>
> ### 步骤2：计算日收益率
>
> 提取第一只股票的价格数据，并计算其日收益率。这里使用`price2ret`函数转换价格数据为收益率。
>
> ```matlab
> data = stock_data(:,1:3);
> yield = price2ret(data);
> yield_first = yield(:,1);
> ```
>
> ### 步骤3：正态假设下的日VaR计算
>
> 在正态分布假设下，使用`portvrisk`函数计算95%置信水平下的日VaR。这里，组合价值假设为每只股票100股。
>
> ```matlab
> yield_estimate = yield(1:973, 1);
> RiskThreshold = 0.05;
> total_var = portvrisk(mean(yield_estimate), std(yield_estimate), RiskThreshold, 1);
> total_var_amount = total_var * data(974, 1) * 100;
> ```
>
> ### 步骤4：VaR回测
>
> 使用计算得到的VaR对后续期间的股票表现进行回测。计算期间内超出VaR预测的损失天数，并计算Z统计量来评估VaR模型的准确性。
>
> ```matlab
> count = sum(yield_first(974:end) < -total_var);
> z = (count - RiskThreshold * length(yield(974:end, 1))) / sqrt(RiskThreshold * (1 - RiskThreshold) * length(yield(974:end, 1)));
> ```
>
> ### 步骤5：收益率正态性检验
>
> 使用QQ图（`qqplot`函数）检验第一只股票收益率的正态性。若收益率服从正态分布，则其分位数应与标准正态分布的分位数呈线性关系。
>
> ```matlab
> figure(2)
> qqplot(yield_first)
> title('收益率正态性检验 QQ 图')
> ```
>
> ## 实验结果分析与结论
>
> - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/c119452c7438b80c85c6a117c5cd729.png" alt="c119452c7438b80c85c6a117c5cd729" style="zoom: 80%;" />
> - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/43dc3e99b530fcb52c813beaedacf60.png" alt="43dc3e99b530fcb52c813beaedacf60" style="zoom: 80%;" />
> - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/f534c76320814d3ede8c107ee6627d0.png" alt="f534c76320814d3ede8c107ee6627d0" style="zoom:50%;" />

​	日VaR的计算结果为188.7021元，意味着在95%的置信水平下，预计不超过5%的机会在一天内损失超过此金额。本实验中即为第一只股票在给定的时间点持有100股，可能会面临的最大损失。

​	回测的结果显示，实际损失超出VaR估计的天数比预期的少，表明VaR模型较为保守，此外Z值的正负还可以指示模型是过于保守还是过于激进。对于Z值的显著性检验表明，在0.05的显著性水平下，样本均值不显著大于零。这表明VaR模型并没有系统性地低估或高估风险。

​	根据QQ图显示结果，可以看到数据点主要围绕红色的对角线排列，但在两端存在一些偏离。明收益率的分布在大部分数据中接近正态分布，但在极端值上有所偏离，即金融时间序列中常见的“厚尾”现象。这也说明在评估风险时可能需要考虑到股票收益率的尾部风险，因为正态分布可能无法完全捕捉极端变化的概率。

​	显著性检验结果中t统计量的值为1.51，低于临界值1.65，意味着在0.05的显著性水平下，我们不能拒绝零假设，即样本均值不显著大于零，这进一步表明我们的VaR模型没有显示出系统性偏差。