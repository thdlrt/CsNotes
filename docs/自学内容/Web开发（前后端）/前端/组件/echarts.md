# [Apache ECharts](https://echarts.apache.org/zh/index.html)

## 基本步骤

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/echarts.png" style="zoom: 50%;" />

```javascript
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <script src="echarts.js"></script>//引入文件
    <style>
        .box {
            width: 400px;
            height: 400px;
            background-color: pink;
        }
    </style>
</head>
<body>
    <div class="box"></div>//准备容器
    <script>
        var myChart = echarts.init(document.querySelector('.box'));//实例化对象
        var option = {//指定配置项和数据
            title: {
                text: 'ECharts 入门示例'
            },
            tooltip: {},
            legend: {
                data: ['销量']
            },
            xAxis: {
                data: ['衬衫', '羊毛衫', '雪纺衫', '裤子', '高跟鞋', '袜子']
            },
            yAxis: {},
            series: [
                {
                    name: '销量',
                    type: 'bar',
                    data: [5, 20, 36, 10, 10, 20]
                }
            ]
        };
        myChart.setOption(option);//将配置项实例给对象
    </script>
</body>
</html>
```

### 选择不同样式的图表

- [官方示例](https://echarts.apache.org/examples/zh/index.html)

## 基本概念

### 图表的大小

- 需要在 HTML 中先定义一个 `<div>` 节点，并且通过 CSS 使得该节点具有**宽度和高度**，图表的大小默认即为该节点的大小。

  - 或者在初始化时为图表指定大小

  - ```js
    <div id="main"></div>
    <script type="text/javascript">
      var myChart = echarts.init(document.getElementById('main'), null, {
        width: 600,
        height: 400
      });
    </script>
    ```

- 监听图表容器的大小并改变图表大小

  - 可以监听页面的 `resize` 事件获取浏览器大小改变的事件，然后调用 [`echartsInstance.resize`](https://echarts.apache.org/api.html#echartsInstance.resize) 改变图表的大小

  - ```js
    </style>
    <div id="main"></div>
    <script type="text/javascript">
      var myChart = echarts.init(document.getElementById('main'));
      window.addEventListener('resize', function() {
        myChart.resize({
      width: 800,
      height: 400
    });//参数可选，不指定的化会自动进行调整
      });
    </script>
    ```

### 样式

- 对于非初始化的选项，在option中进行设置

  - 应用设置好的option`myChart.setOption(option);`
  - [配置文档](https://echarts.apache.org/zh/option.html#title)
  - series：显示图标的样式（是一个数组，可以设置多个数据同时进行显示）
  - data：数据集
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/ec.png" style="zoom: 67%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/ttol.png" style="zoom: 80%;" />

- ```js
  option = {
    series: {
      type: 'scatter',
  
      itemStyle: {
        // 普通样式。
        normal: {
          // 点的颜色。
          color: 'red'
        },
        // 高亮样式。
        emphasis: {
          // 高亮时点的颜色。
          color: 'blue'
        }
      },
  
      label: {
        // 普通样式。
        normal: {
          show: true,
          // 标签的文字。
          formatter: 'This is a normal label.'
        },
        // 高亮样式。
        emphasis: {
          show: true,
          // 高亮时标签的文字。
          formatter: 'This is a emphasis label.'
        }
      }
    }
  };
  ```

#### 主题

- 除了默认主题外，其他主题可以在 [主题编辑器](https://echarts.apache.org/theme-builder.html) 里访问到。也可以使用这个主题编辑器，自己编辑主题。
  - 默认神色主题`var chart = echarts.init(dom, 'dark');`
  - [主题编辑器 - Apache ECharts](https://echarts.apache.org/zh/theme-builder.html)
- 如果保存为 UMD 格式的 JS 文件，文件内部已经做了自注册，直接引入 JS 即可：
  - `var chart = echarts.init(dom, 'vintage');`

#### 坐标轴系统

#### x-y轴

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230508151827935.png" alt="image-20230508151827935" style="zoom:50%;" />

- ```js
  option = {
    xAxis: {//表示x轴
      type: 'time',
      name: '销售时间'
      // ...
    },
    yAxis: {
      type: 'value',
      name: '销售数量'
      // ...
    }
    // ...
  };
  ```

- 在二维数据中，轴也可以有多个。ECharts 中一般情况下单个 grid 组件最多只能放两个 x/y 轴，多于两个 x/y 轴需要通过配置 offset属性防止同个位置多个轴的重叠。两个 x 轴显示在上下，两个 y 轴显示在左右两侧。

  - `yAxis:[{},{}]`

- 属性

  - 轴线axisLine
  - 刻度axisTick
  - 刻度标签axisLabel
  
    - 自动转化后显示
  
    - ```js
              formatter: function (value) {
                  return formatDate(value);
              }
      ```
  
- 

#### 图例legend

- ```js
   legend: {
      // Try 'horizontal'
      orient: 'vertical',
      right: 10,
      top: 'center'
    },
  ```

- 可以在内部设置显示的样式

  - 颜色，图表样式等（icon)

- 也可设置name属性，方便不同的的series进行选择

### 数据

- 法一：给每个series设置数据

  - ```js
    option = {
      xAxis: {
        type: 'category',
        data: ['Matcha Latte', 'Milk Tea', 'Cheese Cocoa', 'Walnut Brownie']
      },
      yAxis: {},
      series: [
        {
          type: 'bar',
          name: '2015',
          data: [89.3, 92.1, 94.4, 85.4]
        },
        {
          type: 'bar',
          name: '2016',
          data: [95.8, 89.4, 91.2, 76.9]
        },
        {
          type: 'bar',
          name: '2017',
          data: [97.7, 83.1, 92.5, 78.1]
        }
      ]
    };
    ```

- 将数据设置在数据集（dataset）中

  - ```js
    option = {
      legend: {},
      tooltip: {},
      dataset: {
        // 提供一份数据。
        source: [
          ['product', '2015', '2016', '2017'],
          ['Matcha Latte', 43.3, 85.8, 93.7],
          ['Milk Tea', 83.1, 73.4, 55.1],
          ['Cheese Cocoa', 86.4, 65.2, 82.5],
          ['Walnut Brownie', 72.4, 53.9, 39.1]
        ]
      },
      // 声明一个 X 轴，类目轴（category）。默认情况下，类目轴对应到 dataset 第一列。
      xAxis: { type: 'category' },
      // 声明一个 Y 轴，数值轴。
      yAxis: {},
      // 声明多个 bar 系列，默认情况下，每个系列会自动对应到 dataset 的每一列。
      series: [{ type: 'bar' }, { type: 'bar' }, { type: 'bar' }]
    };
    ```

  - 也可以使用常见的“对象数组”的格式：

    - ```js
      option = {
        legend: {},
        tooltip: {},
        dataset: {
          // 用 dimensions 指定了维度的顺序。直角坐标系中，如果 X 轴 type 为 category，
          // 默认把第一个维度映射到 X 轴上，后面维度映射到 Y 轴上。
          // 如果不指定 dimensions，也可以通过指定 series.encode
          // 完成映射，参见后文。
          dimensions: ['product', '2015', '2016', '2017'],
          source: [
            { product: 'Matcha Latte', '2015': 43.3, '2016': 85.8, '2017': 93.7 },
            { product: 'Milk Tea', '2015': 83.1, '2016': 73.4, '2017': 55.1 },
            { product: 'Cheese Cocoa', '2015': 86.4, '2016': 65.2, '2017': 82.5 },
            { product: 'Walnut Brownie', '2015': 72.4, '2016': 53.9, '2017': 39.1 }
          ]
        },
        xAxis: { type: 'category' },
        yAxis: {},
        series: [{ type: 'bar' }, { type: 'bar' }, { type: 'bar' }]
      };
      ```

#### 数据的映射

- 指定 `数据集` 的列（column）还是行（row）映射为 `系列（series）`。这件事可以使用 series.seriesLayoutBy 属性来配置。默认是按照列（column）来映射。（将一列中不同行按照顺序映射到不同的series）

  - 默认第一行为维度名，表示后面数据行每一列对应的含义，一个维度名及其所对应的列表示一个**维度**

  - 也可以设置 `dataset.sourceHeader: true` 显示声明第一行（列）就是维度

    - 分离式写法

    - ```js
      dataset: {
          dimensions: ['score', 'amount'],
          source: [
            [89.3, 3371],
            [92.1, 8123],
            [94.4, 1954],
            [85.4, 829]
          ]
        }
      ```

  - ```js
    option = {
      legend: {},
      tooltip: {},
      dataset: {
        source: [
          ['product', '2012', '2013', '2014', '2015'],
          ['Matcha Latte', 41.1, 30.4, 65.1, 53.3],
          ['Milk Tea', 86.5, 92.1, 85.7, 83.1],
          ['Cheese Cocoa', 24.1, 67.2, 79.5, 86.4]
        ]
      },
      xAxis: [
        { type: 'category', gridIndex: 0 },
        { type: 'category', gridIndex: 1 }
      ],
      yAxis: [{ gridIndex: 0 }, { gridIndex: 1 }],
      grid: [{ bottom: '55%' }, { top: '55%' }],
      series: [
        // 这几个系列会出现在第一个直角坐标系中，每个系列对应到 dataset 的每一行。
        { type: 'bar', seriesLayoutBy: 'row' },
        { type: 'bar', seriesLayoutBy: 'row' },
        { type: 'bar', seriesLayoutBy: 'row' },
        // 这几个系列会出现在第二个直角坐标系中，每个系列对应到 dataset 的每一列。
        { type: 'bar', xAxisIndex: 1, yAxisIndex: 1 },
        { type: 'bar', xAxisIndex: 1, yAxisIndex: 1 },
        { type: 'bar', xAxisIndex: 1, yAxisIndex: 1 },
        { type: 'bar', xAxisIndex: 1, yAxisIndex: 1 }
      ]
    };
    ```

  - `xAxisIndex: 1, yAxisIndex: 1`：表示图标所在的行和列，默认为00

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230508141937072.png" alt="image-20230508141937072" style="zoom:33%;" />

- `series.encode`映射

  - ```js
    var option = {
      dataset: {
        source: [
          ['score', 'amount', 'product'],
          [89.3, 58212, 'Matcha Latte'],
          [57.1, 78254, 'Milk Tea'],
          [74.4, 41032, 'Cheese Cocoa'],
          [50.1, 12755, 'Cheese Brownie'],
          [89.7, 20145, 'Matcha Cocoa'],
          [68.1, 79146, 'Tea'],
          [19.6, 91852, 'Orange Juice'],
          [10.6, 101852, 'Lemon Juice'],
          [32.7, 20112, 'Walnut Brownie']
        ]
      },
      xAxis: {},
      yAxis: { type: 'category' },
      series: [
        {
          type: 'bar',
          encode: {
            // 将 "amount" 列映射到 X 轴。
            x: 'amount',
            // 将 "product" 列映射到 Y 轴。
            y: 'product'
          }
        }
      ]
    };
    ```

  - 将series中的数据与数据集中的**维度**进行绑定

  - 除了使用维度名外也可以使用序号进行标识（从左测开始为0）

- 存在多个数据集时可以指定要使用的数据集的序号
  - `datasetIndex: 2`（序号按照dataset中声明的顺序从0开始）

#### 数据转化

- 给定一个已有的“数据集”和一个“转换方法”，echarts 能生成一个新的“数据集“

- 通过设置设置 dataset.transform 来实现

  - ```js
    var option = {
      dataset: [
        {
          // 这个 dataset 的 index 是 `0`。
          source: [
    			...
          ]
          // id: 'a'
        },
        {
          // 这个 dataset 的 index 是 `1`。
          // 这个 `transform` 配置，表示，此 dataset 的数据，来自于此 transform 的结果。
          transform: {
            type: 'filter',
            config: { dimension: 'Year', value: 2011 }
          }
          // 我们还可以设置这些可选的属性： `fromDatasetIndex` 或 `fromDatasetId`。
          // 这些属性，指定了，transform 的输入，来自于哪个 dataset。例如，
          // `fromDatasetIndex: 0` 表示输入来自于 index 为 `0` 的 dataset 。又例如，
          // `fromDatasetId: 'a'` 表示输入来自于 `id: 'a'` 的 dataset。
          // 当这些属性都不指定时，默认认为，输入来自于 index 为 `0` 的 dataset 。
        },
        {
          // 这个 dataset 的 index 是 `2`。
          // 同样，这里因为 `fromDatasetIndex` 和 `fromDatasetId` 都没有被指定，
          // 那么输入默认来自于 index 为 `0` 的 dataset 。
          transform: {
            // 这个类型为 "filter" 的 transform 能够遍历并筛选出满足条件的数据项。
            type: 'filter',
            // 每个 transform 如果需要有配置参数的话，都须配置在 `config` 里。
            // 在这个 "filter" transform 中，`config` 用于指定筛选条件。
            // 下面这个筛选条件是：选出维度（ dimension ）'Year' 中值为 2012 的所有
            // 数据项。
            config: { dimension: 'Year', value: 2012 }
          }
        },
        {
          // 这个 dataset 的 index 是 `3`。
          transform: {
            type: 'filter',
            config: { dimension: 'Year', value: 2013 }
          }
        }
      ],
      series: [
        {
          type: 'pie',
          radius: 50,
          center: ['25%', '50%'],
          // 这个饼图系列，引用了 index 为 `1` 的 dataset 。也就是，引用了上述
          // 2011 年那个 "filter" transform 的结果。
          datasetIndex: 1
        },
        {
          type: 'pie',
          radius: 50,
          center: ['50%', '50%'],
          datasetIndex: 2
        },
        {
          type: 'pie',
          radius: 50,
          center: ['75%', '50%'],
          datasetIndex: 3
        }
      ]
    };
    ```

- 直接在其他数据集中添加transform，并使用config配置转化规则

- 可以链式输出

  - 即将第一次转化得到的数据送入继续进行第二次转化

  - ```js
    transform: [
            {
              type: 'filter',
              config: { dimension: 'Product', value: 'Tofu' }
            },
            {
              type: 'sort',
              config: { dimension: 'Year', order: 'desc' }
            }
          ]
    ```

- 一些transform 可能输出多个 data，可以在使用时进行选择

  - 支付顶`fromTransformResult: 1`

  - ```js
    option = {
      dataset: [
        {
          // 这个 dataset 的 index 为 `0`。
          source: [
            // 原始数据
          ]
        },
        {
          // 这个 dataset 的 index 为 `1`。
          transform: {
            type: 'boxplot'
          }
          // 这个 "boxplot" transform 生成了两个数据：
          // result[0]: boxplot series 所需的数据。
          // result[1]: 离群点数据。
          // 当其他 series 或者 dataset 引用这个 dataset 时，他们默认只能得到
          // result[0] 。
          // 如果想要他们得到 result[1] ，需要额外声明如下这样一个 dataset ：
        },
        {
          // 这个 dataset 的 index 为 `2`。
          // 这个额外的 dataset 指定了数据来源于 index 为 `1` 的 dataset。
          fromDatasetIndex: 1,
          // 并且指定了获取 transform result[1] 。
          fromTransformResult: 1
        }
      ],
      xAxis: {
        type: 'category'
      },
      yAxis: {},
      series: [
        {
          name: 'boxplot',
          type: 'boxplot',
          // Reference the data from result[0].
          // 这个 series 引用 index 为 `1` 的 dataset 。
          datasetIndex: 1
        },
        {
          name: 'outlier',
          type: 'scatter',
          // 这个 series 引用 index 为 `2` 的 dataset 。
          // 从而也就得到了上述的 transform result[1] （即离群点数据）
          datasetIndex: 2
        }
      ]
    };
    ```

##### 常用转化器

- filter

  - 过滤具有指定选项的项`config: { dimension: 'Year', '=': 2011 }`

  - 关系比较：`{ dimension: 'Price', '>=': 20, '<': 30 }`

    - 声明在同一个大括号标识and

    - data 里的值，不仅可以是数值（ number ），也可以是“类数值的字符串”（“ numeric string ”），比较过程中会忽略空格和换行

    - 如果我们需要对日期对象（JS `Date`）或者日期字符串（如 '2012-05-12'）进行比较，我们需要手动指定 `parser: 'time'`，例如 `config: { dimension: 3, lt: '2012-05-12', parser: 'time' }`。

      - `parser`表示选择解析器：
        - `parser: 'time'`：把原始值解析成时间戳（ timestamp ）后再做比较。这个解析器的行为，和 `echarts.time.parse` 相同，即，当原始值为时间对象（ JS `Date` 实例），或者是时间戳，或者是描述时间的字符串（例如 `'2012-05-12 03:11:22'` ），都可以被解析为时间戳，然后就可以基于数值大小进行比较。如果原始数据是其他不可解析为时间戳的值，那么会被解析为 NaN。
        - `parser: 'trim'`：如果原始数据是字符串，则把字符串两端的空格（全角半角）和换行符去掉。如果不是字符串，还保持为原始数据。
        - `parser: 'number'`：强制把原始数据转成数值。如果不能转成有意义的数值，那么转成 `NaN`。在大多数场景下，我们并不需要这个解析器，因为按默认策略，“像数值的字符串”就会被转成数值。但是默认策略比较严格，这个解析器比较宽松，如果我们遇到含有尾缀的字符串（例如 `'33%'`, `12px`），我们需要手动指定 `parser: 'number'`，从而去掉尾缀转为数值才能比较。

    - 纯字符串比较也被支持，但是只能用在 `=` 或 `!=` 上

    - `reg` 操作符能提供正则表达式比较。例如， `{ dimension: 'Name', reg: /\s+Müller\s*$/ }` 能在 `'Name'` 维度上选出姓 `'Müller'` 的数据项

    - 条件之间的关系也可以进行显示声明

      - ```js
        transform: {
          type: 'filter',
          config: {
            or: [{
              and: [{
                dimension: 'Price', '>=': 10, '<': 20
              }, {
                dimension: 'Sales', '<': 100
              }, {
                not: { dimension: 'Product', '=': 'Tofu' }
              }]
            }, {
              and: [{
                dimension: 'Price', '>=': 10, '<': 20
              }, {
                dimension: 'Sales', '<': 100
              }, {
                not: { dimension: 'Product', '=': 'Cake' }
              }]
            }]
          }
        }
        ```

- 

- sort

  - 排序规则：

    - 默认按照数值大小排序。其中，“可转为数值的字符串”也被转换成数值，和其他数值一起按大小排序。
    - 对于其他“不能转为数值的字符串”，也能在它们之间按字符串进行排序。这个特性有助于这种场景：把相同标签的数据项排到一起，尤其是当多个维度共同排序时。见下面的例子。

  - ```js
    transform: {
            type: 'sort',
            config: [
              // 对两个维度按声明的优先级分别排序。
              { dimension: 'profession', order: 'desc' },
              { dimension: 'score', order: 'desc' }
            ]
          }
    ```

    

- 第三方转化器（如ecStat）

  - `npm install echarts-stat`

  - 引入`import ecStat from 'echarts-stat'`
  
  - 先注册第三方转化器`echarts.registerTransform(ecStatTransform(ecStat).regression);`
  
  - ```js
    transform: {
            // 引用注册的数据转换器。
            // 注意，每个外部的数据转换器，都有名空间（如 'ecStat:xxx'，'ecStat' 是名空间）。
            // 而内置数据转换器（如 'filter', 'sort'）没有名空间。
            type: 'ecStat:regression',
            config: {
              // 这里是此外部数据转换器所需的参数。
              method: 'exponential'
            }
          }
    ```
  

### 事件与行为

- 在 Apache ECharts 的图表中用户的操作将会触发相应的事件。开发者可以监听这些事件，然后通过回调函数做相应的处理

- ```js
  myChart.on('click', function(params) {
    // 控制台打印数据的名称
    console.log(params.name);
  });
  ```

- 指定监听元素

  - `chart.on(eventName, query, handler);`

    - query可以为字符串表示组件名称，或object类型

      - 使用object指定组件的属性

        - ```js
          {
            ${mainType}Index: number // 组件 index
            ${mainType}Name: string // 组件 name
            ${mainType}Id: string // 组件 id
            dataIndex: number // 数据项 index(如条形图的index)
            name: string // 数据项 name
            dataType: string // 数据项 type，如关系图中的 'node', 'edge'
            element: string // 自定义系列中的 el 的 name
          }
          ```

  - `chart.on('click', 'xAxis.category', function() {});`

#### 鼠标事件

- ECharts 支持常规的鼠标事件类型，包括 `'click'`、 `'dblclick'`、 `'mousedown'`、 `'mousemove'`、 `'mouseup'`、 `'mouseover'`、 `'mouseout'`、 `'globalout'`、 `'contextmenu'` 事件。

- 事件信息

  - ```js
    type EventParams = {
      // 当前点击的图形元素所属的组件名称，
      // 其值如 'series'、'markLine'、'markPoint'、'timeLine' 等。
      componentType: string;
      // 系列类型。值可能为：'line'、'bar'、'pie' 等。当 componentType 为 'series' 时有意义。
      seriesType: string;
      // 系列在传入的 option.series 中的 index。当 componentType 为 'series' 时有意义。
      seriesIndex: number;
      // 系列名称。当 componentType 为 'series' 时有意义。
      seriesName: string;
      // 数据名，类目名
      name: string;
      // 数据在传入的 data 数组中的 index
      dataIndex: number;
      // 传入的原始数据项
      data: Object;
      // sankey、graph 等图表同时含有 nodeData 和 edgeData 两种 data，
      // dataType 的值会是 'node' 或者 'edge'，表示当前点击在 node 还是 edge 上。
      // 其他大部分图表中只有一种 data，dataType 无意义。
      dataType: string;
      // 传入的数据值
      value: number | Array;
      // 数据图形的颜色。当 componentType 为 'series' 时有意义。
      color: string;
    };
    ```

#### 其他事件

- [Documentation - Apache ECharts](https://echarts.apache.org/zh/api.html#events)

### 触发组件的行为

-  [action](https://echarts.apache.org//api.html#action)

-  `myChart.dispatchAction({ type: '' })` 

- 即要求组件执行特定的行为

- 如循环高亮饼图

  - ```js
    setInterval(function() {
      var dataLen = option.series[0].data.length;
      // 取消之前高亮的图形
      myChart.dispatchAction({
        type: 'downplay',
        seriesIndex: 0,
        dataIndex: currentIndex
      });
      currentIndex = (currentIndex + 1) % dataLen;
      // 高亮当前图形
      myChart.dispatchAction({
        type: 'highlight',
        seriesIndex: 0,
        dataIndex: currentIndex
      });
      // 显示 tooltip
      myChart.dispatchAction({
        type: 'showTip',
        seriesIndex: 0,
        dataIndex: currentIndex
      });
    }, 1000);
    ```

- 持续改变选中的条颜色

  - ```js
        weekChart.on('click', function (params) {
            if (params.componentType === 'series' && params.seriesType === 'bar') {
                // 获取被点击的柱子在数据中的索引
                weekIndex.value = params.dataIndex;
                //高亮选中
                // 先将所有柱子的 emphasis 样式清除
                weekChart.dispatchAction({
                    type: 'downplay',
                    seriesIndex: 0
                });
                // 然后设置被点击柱子的 emphasis 样式为红色
                weekChart.dispatchAction({
                    type: 'highlight',
                    seriesIndex: 0,
                    dataIndex: params.dataIndex
                });
            }
        });
    ```

- 

## 补充

### 杂项

- 可以通过设置series的type为none来隐藏不显示某一项

### 异步数据加载

- ```js
  $.get('data.json').done(function(data) {
    // data 的结构:
    // {
    //     categories: ["衬衫","羊毛衫","雪纺衫","裤子","高跟鞋","袜子"],
    //     values: [5, 20, 36, 10, 10, 20]
    // }
    myChart.setOption({
      title: {
        text: '异步数据加载示例'
      },
      tooltip: {},
      legend: {},
      xAxis: {
        data: data.categories
      },
      yAxis: {},
      series: [
        {
          name: '销量',
          type: 'bar',
          data: data.values
        }
      ]
    });
  });
  ```

### loading动画

- `myChart.showLoading();`
- `myChart.hideLoading();`

## 数据的动态更新

- 所有数据的更新都通过 setOption实现，你只需要定时获取数据，setOption填入数据，而不用考虑数据到底产生了哪些变化，ECharts 会找到两组数据之间的差异然后通过合适的动画去表现数据的变化。