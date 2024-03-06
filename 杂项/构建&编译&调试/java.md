### 编译运行

- 编译javac
	- `javac -cp ./commons-lang3-3.10.jar -d . -encoding UTF-8 Hello.java ./util/Common.java`
	- -cp 指定查找用户类文件和注释处理程序的位置
	- -d 指定放置生成的类文件(.class)的位置
	- -encoding 指定源文件使用的字符编码。
	- -ea 开启断言

- 运行 java
	- `java name`

- 反编译 javap
	- `javap -v com/demo/Hello.class`
	- -v 显示详细信息