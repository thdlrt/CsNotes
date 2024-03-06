- 硬件描述语言，描述方式设计电路
## 基本语法
### 模块结构
- 对大型的数字电路进行分割，分割为大小不一的小模块
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240227193809.png)
- 模块名和端口定义：定义模块名称和模块的端口
- 参数定义：类似定义常亮，便于对数值进行统一的管理
	- `parameter name=x`
- 接口定义：对模块的端口做进一步的说明，端口可以为输入端口、输出端口或双向端口
- 信号说明：
	- reg 寄存器信号
	- wire 线信号
- 功能定义：逻辑功能的定义
	- assign 声明语句描述两输入与门如  `assign a = b & c`
	- 用 always 块
	- 模块例化（例化：使用定义的模块）
### 信号类型
- 通常在 **always** 设计的信号都定义为 reg，其他信号定义为 wire
#### wire
- 对结构化器件之间的物理线的建模
- 定义 `wire [msb,lsb] wire1,wire2,...,wireN;`
	-  如 `wire [7:0] cnt0 ;` 表示定义一个位宽为 8 位的线型信号
	- msb lsb 定义类位宽范围，必须为常数值
- 缺省信号类型时默认为 wire
- 省却信号范围时默认为一位
#### reg
- 用于表示存储单元，如触发器、ROM 等（也不一定表示存储单元，有时就表示一个变量）
- `reg a,b,c;` 同时定义多个信号
### 功能描述
#### 程序语句
- assign
	- 连续赋值语句，将一个变量的值不间断地赋值给另一变量，相当于将两个变量**连线**在一起
	- `assign a=b; assign a=0;`
	- 可以带有组合逻辑 `assign end=add&&cnt==2-1;`
- always
	- 条件循环语句，通过对一个称为敏感变量表的事件驱动来实现，敏感事件的条件满足时就执行一次程序语句
	- 在@后跟着事件
	- \*表示任意信号 (对下面语句块有影响的语句，对于下面的例子就是 a b d sel)
```verilog
always @(a or b or d)begin
	if(sel==0)
		c = a + b;
	else
		c = a + d;
end
```
- 当信号 a 或 b 或 d 发生变化时，就执行一次下面语句（类似一个锁存器）
- `@(posedge clk)` 时钟上升沿 negedg 下降沿，用于构建时序逻辑电路

- 敏感列表中的一些次有特殊含义：
	- clk 表示始终
	- rst_n 表示复位信号

- = 表示阻塞赋值（组合逻辑器件）；<=表示非注册赋值（时序逻辑器件）
### 数字进制

- 数字表示格式 `<位宽>'<基数><数值>` 如 `4'b1011`
	- 位宽表示二进制位数
	- x 表示不定态、z 表示高阻态（二进制表示时的可选参数）
	- bdoh: 2、10、8、16 进制，默认为 10 进制
	- 当数值的位数比位宽小时在前面自动补 0；数值位数比位宽大时从低位截断

- 不定态 x
	- 为 0/1 均可，如 din== `4'b10x0`
	- 实际电路中不存在不定态，只是用于语法层面
- 高阻态 z
	- 表示设计者不驱动这个信号，用于三态门
	- 三态门的写使能无效时为高阻 `assign data=(wr_en==1)?wr_data:1'bz;`
### 运算符
- 算术运算符
	- 尽量避免使用/和%，会使用大量门电路，效率较差
	- 信号位宽
		- 最终结果取决于 `=` 左边的信号位宽，保存低位丢弃高位（或者前面补 0）

- 关系运算符
	- 如果参与比较的有 x,z 则结果为 x
	- 同样长度不同时短的前面加 0

-  逻辑运算符
	- && || !
	- 逻辑运算符的结果只有 0/1 两种，通常输入为两个 1 位宽的数；对于有多位的操作数，若操作数中每一位**都是 0** 则为逻辑 0 值，若操作数中有 1 则为逻辑 1 值

- 位运算
	- ~&|^
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228155352.png)
	- 单目运算： 每一位之间进行运算
		- `C=&A` 等价于 `C=A[3]&A[2]&[1]&A[0]` 即是否每一位全是 1
		- `C=|A` 类似，可以用于判断是否为 0
		- ~是翻转每一位
	- 双目运算：长度较小的操作数在左侧添 0 补位

- 使用 begin end 表示代码块（类似{}）
- 条件运算符（作用上类似于多路选择器）
	- if () else if () else
- 选择语句
```verilog
always@(*)begin
	case(S)
2'b00 : C=D0;
2'b01 : C=D1;
default : C=D3;
	endcase
end
```
- 三目运算符同样支持

- 拼接运算符
	- 将大括号内的信号按位置一对一连接
	- 如 `B={A[2],A[3],A[0]}`
	- ![image.png|246](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228161254.png)

### 时序逻辑电路相关

- 同步复位：时钟上升沿复位才生效
- 异步复位：复位立即有效（or）不需要等待时钟信号

- 阻塞赋值：=
	- 一个 begin end 内的多行赋值语句按顺序逐行执行
	- 组合逻辑都是用阻塞赋值
- 非阻塞赋值：<=
	- 多行赋值语句在同一时间**同时执行**（也就是说后面行会用前面的旧值）
	- 时序逻辑都是用非阻塞赋值

- 不允许使用敏感列表检测上升下降沿，因为无论名称是什么填入之后都变成时钟，相当于创建多个不同的时钟信号
#### 时序逻辑和相关硬件
- D 触发器：
	- FPGA 中只使用 D 触发器
	- ![image.png|300](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228162859.png)
	- 当 rst_n 低电平（复位有效）时 q 处于低电平，否则根据 d 在 clk 到来时进行赋值
```verilog
always @(posedge clk or negedge res_n)begin
	if(rst_n==1'b0)begin
		q<=0;
	end
	else begin
		q<=d;
	end
end
```
## VIVADO 的使用
- 使用 vscode 作为编译器，textedit 设置为 `cmd /S /k "code -g [file name]:[line number]" `

## 例子
### 异或电路的设计

- **电路设计文件** designsources
```verilog
module my_xor(
    input A,
    input B,
    output F
    );
    assign F=~A&B|A&~B;
endmodule
```

- **仿真测试文件** simulation sources
```verilog
`timescale 1ns / 1ps
module my_xor_tb();
wire f; //输出变量要声明为 wire 类型的，这里 wire 不可缺省
reg a,b; //输入变量声明为 reg 类型的
my_xor s0(.A(a),.B(b),.F(f));
initial begin
begin a = 1'b0; b = 1'b0; end
#200 begin a = 1'b0; b = 1'b1; end
#200 begin a = 1'b1; b = 1'b0; end
#200 begin a = 1'b1; b = 1'b1; end
#200 begin a = 1'b0; b = 1'b0; end
end
endmodule
```
- “\`timescale 1ns / 1ps”，说明测试程序的时间单位为 1ns 且时间精度为1 ps
- `my_xor s0(.A(a),.B(b),.f(F));` 表示实例化模块，并将模块的端口与变量绑定
- ![|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228204116.png)

- **设计综合**：把项目设计文件进行逻辑优化，并将 RTL 代码映射到 FPGA 器件的原语，生成网表文
件。
-  ![image.png|525](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228204217.png)
- ![image.png|525](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228204426.png)

- **创建约束文件**， FPGA 芯片没有输入输出设备，必须使用外部的输入输出设备。contrains
- Vivado 中的约束类型分成两类，一类是物理约束，一类是时序约束。
	- 物理约束是指 FPGA 引脚分配和引脚电平的大小，假设把输入端口 A、B 分别连接到 Nexys A 7-100 T 实验板上的拨动开关 SW 0 和 SW 1 上，输出端口 F 连接到 LED 指示灯 LD 0 上。输入和输出引脚的工作电压都为 3.3V。
	- ![image.png|525](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228205330.png)
	- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228205344.png)
- 有两种方法可以添加引脚约束文件：一是可以直接新建 XDC 的约束文件，手动输入约束语句；
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228205613.png)
- 二是可利用 Vivado 中 IO planning 功能。
	- 图形界面操作 ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228210146.png)

-  完成约束文件建立后，在导航窗口中选择执行 Implementation。Implementation 主要包含布局布线两个过程，布局主要将综合后的基本单元放到 FPGA 中合适的位置，而布线则是将这些基本单元连接起来。
- 选择 Generate Bitstream，单击 OK，则**生成二进制流文件**；

- 使用开发板**验证配置**
	- 在流程导航窗口中执行 Open Hardware Manager 菜单命令或者在 bit 文件生成完成页面中选择 Open Hardware Manager 选项，点击 OK 按钮，进入硬件编程管理页面。单击 Open Target，选择 Auto Connect，建立和实验开发板之间的连接
	- 下载 bit 文件。在目标的 FPGA 器件 xc 7 a 100 t 上用鼠标右击，选择 Program Device…菜单或者在流程导航窗口中的 Open Hardware Manager 中点击 Program Device 菜单，将弹出芯片编程文件确认对话框，指定所需的 bit 文件路径，
	- 点击 Program 按钮，将 bit 文件下载到开发板卡上的 FPGA 中，下载结束后，在 FPGA 芯片名称后面显示“Programmed”

- 封装 IP 核
	- IP 核用于 ASIC 或 FPGA 中的预先设计好的电路功能模块，类似编程语言中的**函数库**，设计人员可以直接调用。
	- 



