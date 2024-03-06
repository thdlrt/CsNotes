## Logisim基本使用

### 基本组件

#### 线路库

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231003153627287.png" alt="image-20231003153627287" style="zoom: 50%;" />
  - Splitter分线器：将多位线路进行拆分或合并。
  - Pin引脚：电路的输入或输出引脚。
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231003214538234.png" alt="image-20231003214538234" style="zoom:33%;" />
  - Probe探针：监控电路中指定位置的具体值，类似输出引脚，连接线颜色为灰色，用于线路调试。
  - Tunnel隧道：类似于多层印刷电路板的过孔，通过相同的标识符将没有线路相连的两个或多个点逻辑连通，有助于电路设计整洁美观。
  - Pull Resistor上/下拉电阻：用于处理连接点的不确定值（浮动值）。
  - Clock时钟：时钟信号源，可以在simulate菜单下设置为固定频率连续输出，也可设置为单步输出，多用于时序电路。
  -  Programmable Generator：可编程信号发生器，4个输出状态。
  - Constant常量：数值属性固定的值。
  - Power电源：特殊的常量，值为1
  - Ground接地：特殊的常量，值为0。
  - Transistor晶体管：有PMOS、NMOS晶体管两种类型。
  - Transmission Gate传输门：
  - Bit Extender位扩展器：可扩展或截断数据位宽，扩展时刻选择0、1、符号位或额外输入位扩展。

#### 输入输出库

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231003153918780.png" alt="image-20231003153918780" style="zoom:50%;" />
  - Button按钮：模拟一个按钮，未按下输出0，鼠标左键按下输出1，释放鼠标按钮后输出0
  - Switch开关：通过鼠标点击，开关处于不同位置来设置是否导通或截止。
  - Dip Switch一组拨档开关：选择不同位置持续输出0或1。
  - Slider连续数值输出：可通过鼠标平滑移动连续输出n位数二进制数。
  - Joystick操纵杆：鼠标拖动中间按钮，输出x、y两个坐标。
  - Keyboard键盘：允许电路读取从键盘输入的ASCII键值。
  - Buzzer蜂鸣器：发出有输入定义的频率声音
  - LED指示灯：根据灯的亮和灭显示其输入值是1还是0。
  - RGB LED彩色指示灯：根据三个1位R、G、B输入值来显示指示灯的色彩，全0黑色，全1白色。
  - Digital Oscilloscope数字示波器：显示输入信号的波形。
  - 7-Segment Display七段数码管：8个1位输入值分别对应7个线段和1个小数点。
  - Hex Digit Display十六进制数码管：一个4位输入对应数值，一个1位输入对应小数点。
  - LED Matrix LED矩阵：通过一个像素点阵来显示符号。有行模式、列模式、行列模式三种不同引脚模式。
  - TTY字符终端：一个简单的字符显示终端，接收可显示的ASCII码。

### 基本操作

- 子电路
  - 封装<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231003213009902.png" alt="image-20231003213009902" style="zoom:33%;" />
    - 点击右侧按钮封装
    - 点击加号用于创建新电路
    - 封装后的电路只能在本文件使用，如果需要在其它电路使用需要导入
    - 直接加载文件即可<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231003213149574.png" alt="image-20231003213149574" style="zoom:33%;" />
- 自动分析&构建电路
  - 设置变量名称<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231004003506916.png" alt="image-20231004003506916" style="zoom:33%;" />
  - 获取&设置真值表<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231004003533614.png" alt="image-20231004003533614" style="zoom:33%;" />
  - 通过表达式设置<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231004003551980.png" alt="image-20231004003551980" style="zoom:33%;" />
  - 通过卡诺图设置<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231004003631995.png" alt="image-20231004003631995" style="zoom:33%;" />
  - 可以通过以上多种方式分析&构建电路

### 杂项

- 线路不同颜色的含义
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231003154514846.png" alt="image-20231003154514846" style="zoom:33%;" />
- 选择Project菜单下的Analyze Circuit子菜单，弹出组合电路分析对话框，
  可以显示输入信号、输出信号、真值表、表达式和最小项列表。
- 在本地进行实验：
  - 电路文件上本质上是xml文件，可以通过直接复制文件代码间接实现文件互传

#### 快捷键

- 单步执行`ctrl+i`