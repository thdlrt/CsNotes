## 编译运行

- 分步进行
	- 预处理：`-E` 生成生成 `.i` 文件 `gcc -E demo.c -o demo.i`
	- 编译：`-S` 生成编译之后的 `-S` 文件 `gcc -S demo.i -o demo.S`
	- 汇编：`-C` 生成 `.O` 文件 `gcc -C demo.S -o demo.o`
	- 链接：`gcc demo.o -o demo`

- linux 编译命令
  - `g++ grainrainisgod.cpp -o grainrainisgod -O2 -Wall -fsanitize=address -fsanitize=undefined`
    - 可选重命名 `-o grainrainisgod`
    - `-O2` 开启加速
    - `-Wall` 显示警告
    - `-fsanitize=address` 检测程序的内存错误，比如爆栈等问题
    - `-fsanitize=undefined` 检测程序的未定义行为，比如访问空指针，数组越界访问等问题 (有效检查**RE)**
    - 生成可调试 `-g`（注意不要用 `-O2` 优化可能导致打断点出现问题）
  - 运行 `./a.out`

- 打包静态库 `ar rc libadd_minus.a add_minus.o`
	- 链接时使用创建的静态库 `gcc -o main2 main.o -L./ -ladd_minus`
	- `-L./`：表明库文件位置在当前文件夹。
	-  `-ladd_minus`：表示链接 `libadd_minus.a` 文件，使用 `-l` 参数时,前缀 `lib` 和后缀 `.a` 是需要省略的。

- 打包动态库
	- `gcc multi_div.c -fPIC -shared -o libmulti_div.so`
	- 编译时使用方法与静态库一致  `gcc -c main.c`
	- 可能还需要将动态库添加到文件搜索路径
		- `sudo cp libmulti_div.so /usr/lib`
		- `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/project/make_example-master/chapter0/`

## gdb 调试

-  常用命令
    - 调试 `gdb ./a.out`
    - 断点 `b num` num 为行号
      - 查看断点 ` info b`
    - 启动 `r`
    - 查看源码 `l`
    - 显示变量 `p n`
    - 跟踪 ` watch n`
    - 单步调试 `n`
    - 继续 `c`

### 基本操作

- 要使用 GDB 调试某个程序，该程序编译时必须加上编译选项 **`-g`**，否则该程序是不包含调试信息的；

- `gdb`：进入 gdb 调试，后面可以加上要调试的文件名
  - 如果进入后要重新加入文件，使用 `file` +文件名
- `shell ` 后面可以加上正常的 linux 命令进行操作，如 `shell ls`
- 开启调试过程记录（记录到 txt）`set logging on`
- GDB 调试主要有三种方式：
  1. 直接调试目标程序：gdb ./hello_server
  2. 附加进程 id：gdb attach pid
  3. 调试 core 文件：gdb filename corename
- 退出 `q`

### 调试

| 命令名称    | 命令缩写  | 命令说明                                         |
| ----------- | --------- | ------------------------------------------------ |
| run         | r         | 运行一个待调试的程序                             |
| continue    | c         | 让暂停的程序继续运行                             |
| next        | n         | 运行到下一行                                     |
| step        | s         | 单步执行，遇到函数会进入                         |
| until       | u         | 运行到指定行停下来                               |
| finish      | fi        | 结束当前调用函数，回到上一层调用函数处           |
| return      | return    | 结束当前调用函数并返回指定值，到上一层函数调用处 |
| jump        | j         | 将当前程序执行流跳转到指定行或地址               |
| print       | p         | 打印变量或寄存器值                               |
| backtrace   | bt        | 查看当前线程的调用堆栈                           |
| frame       | f         | 切换到当前调用线程的指定堆栈                     |
| thread      | thread    | 切换到指定线程                                   |
| break       | b         | 添加断点                                         |
| tbreak      | tb        | 添加临时断点                                     |
| delete      | d         | 删除断点                                         |
| enable      | enable    | 启用某个断点                                     |
| disable     | disable   | 禁用某个断点                                     |
| watch       | watch     | 监视某一个变量或内存地址的值是否发生变化         |
| list        | l         | 显示源码                                         |
| info        | i         | 查看断点 / 线程等信息                            |
| ptype       | ptype     | 查看变量类型                                     |
| disassemble | dis       | 查看汇编代码                                     |
| set args    | set args  | 设置程序启动命令行参数                           |
| show args   | show args | 查看设置的命令行参数                             |

- `p` +变量名显示变量内容
  - 可以指定变量类型：`如p (char*)0x5568708b`

- `x /x $eax` 输出寄存器内容（也可以直接接地址）
  - `/s` 表示输出字符串
  - `x $eax+0xc` 带偏移
    - `0x55687134 <_reserved+1028404>: 0x00000000`
    - 表示寄存器指向 0 x 55687134，这个地址的内容是 0 x 00000000

- `backtrace` 命令查看了函数调用栈（运行错误时查找错误位置）
- `info frame` 命令查看了当前帧的信息
- `info registers` 命令查看了栈指针寄存器的当前值。
- 为程序传入输出 `r < in.txt -u 211275022`

#### 断点

- 以地址为断点时加上*，如 `b *0x80494e9`
- `info break` 查看已经打的断点
- `watchpoint ` 与断点的区别是当指定的变量的值发生了变化时才会中断
- disable 断点编号，禁用某个断点，使得断点不会被触发；
- enable 断点编号，启用某个被禁用的断点；
- delete 断点编号，删除某个断点

## 汇编

- 反汇编 `objdump -d x.o >x.s`
- 手写汇编转化为 16 进制命令
  - 编译为可执行文件 `gcc -m32 -c example.S `
  - 反汇编 `\>objdump -d example.o > example.d`
### elf

1. 查看 ELF 文件的头部信息：`readelf -h <filename>`，这将显示 ELF 文件的基本信息，如文件类型、入口地址、段表和节表的偏移等。
2. 查看 ELF 文件的段表信息：`readelf -S <filename>`，这将显示 ELF 文件的段表，包括每个段的名称、偏移、大小、访问权限等。
3. 查看 ELF 文件的节表信息：`readelf -S <filename>`，这将显示 ELF 文件的节表，包括每个节的名称、类型、偏移、大小等。
4. 查看 ELF 文件的符号表信息：`readelf -s <filename>`，这将显示 ELF 文件的符号表，包括全局符号、局部符号、符号地址等。
5. 查看 ELF 文件的动态符号表信息：`readelf -d <filename>`，这将显示 ELF 文件的动态符号表，包括动态符号、动态链接库的依赖关系等。
6. 查看 ELF 文件的重定位信息：`readelf -r <filename>`，这将显示 ELF 文件的重定位表，包括重定位项的类型、偏移、符号信息等。
7. 查看 ELF 文件的动态节信息：`readelf -x <section_name> <filename>`，这将显示指定动态节的内容，如 `.dynamic`、`.plt` 等。

### hexedit

- `hexdump` 查看文件但不需要编辑
- **查看和编辑**十六进制或 ASCII 文件
- 安装 `sudo apt install hexedit -y`
```shell
hexedit [-s | --sector] [-m | --maximize] [-h | --help] [filename]
 
# -s， --sector    格式化显示以包含整个扇区。
# -m， --maximimize    尝试最大化显示。
# -h， --help    显示用法。
```

- 移动
```shell
<,> : 转到文件的开头/结尾
Right: 下一个字符
Left: 前一个字符
Down: 下一行
Up: 前一行
Home: 行的第一个字符
End: 行的最后一个字符
PUp: 向上翻页
PDown: 向下翻页
```

- 剪切粘贴
```shell
Ctrl-Space: set mark
Esc-W: copy
Ctrl-Y: paste
Esc-Y: paste into a file
Esc-I: fill
```

- 其他命令
```shell
F2: 保存
F3: 打开其他文件
F1: 帮助
Ctrl-L: redraw
Ctrl-Z: 暂时停办（推出后使用fg回来，使用jobs 查看 停办的任务）
Ctrl-X:保存并推出
Ctrl-C: 退出不保存
Tab: hex和ascii之间切换
Return: 跳到指定地址（不区分大小写）
Backspace: 撤消前一个修改的字符
Ctrl-U: 撤销所有的修改
Ctrl-S: 向前搜索 16进制值
Ctrl-R: 向后搜索 16进制值
```

## 工具

### Cmake
