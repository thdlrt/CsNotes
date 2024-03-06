- 可以通过编程改变内部结构，可编程集成电路
- ![image.png|225](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240227185615.png)
	- 由查找表 lut 构成，可以改变特定输入下的输出，即转化为不同的门电路

- 综合器：将代码解释为电路
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240227192254.png)
- 仿真：在烧录到 FPGA 之前进行仿真验证，需要编写测试文件，描述仿真对象的输入情况，检查输出是否符合预期
- 可综合设计：语言描述的程序映射到实际硬件电路中的结构是**能实现**的
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240227193220.png)
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240227193430.png)
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240227193500.png)

### FPGA 开发流程

- 前端完成程序编写、语法分析和逻辑实现，在通过编译后，进行激励仿真，对设计的逻辑功能进行验证，完成功能仿真；分成模块设计、HDL 编写、激励输入、功能仿真等阶段。后端通常分成设计综合、器件实现和装配验证等阶段，涉及到具体的 FPGA 器件，在功能仿真通过后，可以进行设计综合和布局布线；将逻辑功能映射到实际物理器件上，生成网表文件 Netlist 和二进制 bit 文件；针对物理器件的实际延时和物理性能，分析最终器件是否能满足设计要求；最后将二进制 bit 文件写入 FPGA 中，在实际 FPGA 器件上进行验证。
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240228194514.png)

