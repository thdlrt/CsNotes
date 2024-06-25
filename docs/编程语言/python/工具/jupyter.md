## 基本操作

- 全部执行cell>>run all 
- 编辑>>清除输出
- `jupyter notebook`启动
  - `jupyter lab`
- 语句前[]表示语句的执行次数

## 魔术符号

- %行魔术；\%%格子魔术；%lsmagic列举所有魔术
  - 都是%或\%%开头加上具体魔术指令

- `timeit`执行1000次计算平均执行时间
  - `time`执行一次
- HTML：添加html
- 运行python程序`%run name.py`，文件中的所有定义的变量、函数等都可以随后进行访问和使用

  - 后面也可以根生运行参数

- `%load`将py代码文件直接导入到一个代码格中
- `%timeit`统计运行时间
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231106143049506.png" alt="image-20231106143049506" style="zoom: 50%;" />
- 创建可视图象

  - ```python
    import matplotlib.pyplot as plt
    plt.plot([1,2,3,4])
    ```
  - 



## 快捷键

- 1~6：切换为标题
- m：切换为markdown；y：切换为代码块
- ctrl+回车 运行代码块
- 停止执行 ctrl+c
- tab调出自动补全
- 光标点击函数名，shift+tab显示说明文档
- 单独变量名+？输出相关的详细信息（自省），如果对象是一个函数或实例方法会显示定义过的文档字符串

  - 定义文档字符串

    - ```python
      def add_numbers(a, b):
      """
      Add two numbers together
      Returns
      -------
      the_sum : type of arguments
      """
      return a + b
      ```

  - 使用??显示函数的源码
- 