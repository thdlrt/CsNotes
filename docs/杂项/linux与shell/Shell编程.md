
### 基础

- 扩展名为`sh`
- `#!/bin/zsh`头文件指定要使用的终端程序
  - 或者运行时指定 `/bin/zsh test.sh`

#### 输入输出

- 使用`echo`输出
  - 使用`-e`启用转义字符`echo -e "OK! \n"`
  - 显式不换行`echo -e "OK! \c"`(默认echo会自动添加换行符)
  - 输出命令执行结果，使用\`，如显示时间echo \`date\`

- 格式化输出printf
  - **%s %c %d %f** 都是格式替代符，**％s** 输出一个字符串，**％d** 整型输出，**％c** 输出一个字符，**％f** 输出实数，以小数形式输出。
  - **%-10s** 指一个宽度为 10 个字符（**-** 表示左对齐，没有则表示右对齐），任何字符都会被显示在 10 个字符宽的字符内，如果不足则自动以空格填充，超过也会将内容全部显示出来。
  - **%-4.2f** 指格式化为小数，其中 **.2** 指保留2位小数。
  - 转义字符
  - ![image-20231229154411516](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231229154411516.png)
```bash
printf "%-10s %-8s %-4s\n" 姓名 性别 体重kg  
printf "%-10s %-8s %-4.2f\n" 郭靖 男 66.1234
printf "%-10s %-8s %-4.2f\n" 杨过 男 48.6543
printf "%-10s %-8s %-4.2f\n" 郭芙 女 47.9876
姓名     性别   体重kg
郭靖     男      66.12
杨过     男      48.65
郭芙     女      47.99
```

- 读取
```bash
read name 
echo "$name It is a test"
```

- 重定向
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20231229170250.png)

- 默认情况下，command > file 将 **stdout** 重定向到 file，command < file 将 **stdin** 重定向到 file。
- 如果希望 stderr 重定向到 file，可以这样写：`command 2>file`

- 如果希望执行某个命令，但又**不希望在屏幕上显示输出结果**，那么可以将输出重定向到 /dev/null：`$ command > /dev/null`

### 变量与参数

- 定义变量，如`foo=bar`，服务器重启之后就会失效
  - 注意**不能有空格**
  - 将命令的输出保存到变量`foo=$(pwd)`
    - `$(pwd)`将输出转化为了一个**临时变量**
    - 如`for file in $(ls /etc)`
  - `<( CMD )` 会执行 `CMD` 并将结果**输出到一个临时文件中**，并将 `<( CMD )` **替换成临时文件名**。
    -  `diff <(ls foo) <(ls bar)` 会显示文件夹 `foo` 和 `bar` 中文件的区别。
- 定义为只读变量

```bash
myUrl="https://www.google.com"
readonly myUrl
myUrl="https://www.runoob.com"
```

- 删除变量`unset variable_name`

- 使用变量时添加`$`作为前缀`echo "I am good at ${skill}Script"`

  - 注意只有读取时使用`$`，对于赋值即使是**二次赋值也不使用**`$`

- 使用双引号或单引号来表示字符串，其中双引号会进行转化（如将**变量替换为值**），而单引号是**原始字符串**

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231223000025278.png" alt="image-20231223000025278" style="zoom:33%;" />
  - 字符串拼接

```bash
  your_name="runoob"
  # 使用双引号拼接
  greeting="hello, "$your_name" !"
  greeting_1="hello, ${your_name} !"
  echo $greeting  $greeting_1
  
  # 使用单引号拼接
  greeting_2='hello, '$your_name' !'
  greeting_3='hello, ${your_name} !'
  echo $greeting_2  $greeting_3
  ```

  - 获取字符串长度`${#name}`
  - 截取字符串`${string:1:4}`从第二个字符开始截取4个子符

- 数组`my_array=(1 2 3 4 5)`，只支持一维数组，元素使用空格分隔
  - 可以直接使用下标进行访问
  - 获取数组中所有元素`${my_array[@]}`
  - 获取长度`${#my_array[@]}`
  - 关联数组（使用`-A`参数表示关联数组）
  - 获取管理那数组的所有键`${!site[*]}`

```bash
declare -A associative_array
associative_array["name"]="John"
associative_array["age"]=30
```

- 注释`#`
  - 多行

```bash
: <<'COMMENT'
这是注释的部分。
可以有多行内容。
COMMENT

:<<'
注释内容...
注释内容...
注释内容...
'

:<<!
注释内容...
注释内容...
注释内容...
!
```

#### 特殊变量

- `$0` - 脚本名
- `$1` 到 `$9` - **脚本的参数**。 `$1` 是第一个参数，依此类推。

- `$@` - 所有参数，"\$1"\"\$2" … "\$n" 的形式输出所有参数。

- `$*`以单字符串显示所有向脚本传递的参数,以"\$1 \$2 … \$n"的形式输出所有参数。

- `$#` - 参数个数

- `$?` - 前一个命令的**返回值**
  - 对于无返回值的成功返回0，失败返回1
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231223001614316.png" alt="image-20231223001614316" style="zoom:33%;" />

- `$$` - 当前脚本的进程识别码

- `!!` - 完整的**上一条命令**，包括参数。常见应用：当你因为权限不足执行命令失败时，可以使用 `sudo !!`再尝试一次。

- `$_` - 上一条命令的**最后一个参数**。如果你正在使用的是交互式 shell，你可以通过按下 `Esc` 之后键入 . 来获取这个值。

#### 函数

- 定义函数
```shell
mcd () {
    mkdir -p "$1"
    cd "$1"
}
#执行函数
mcd
```

- 带有返回值的版本
```bash
funWithReturn(){  
    echo "这个函数会对输入的两个数字进行相加运算..."  
    echo "输入第一个数字: "  
    read aNum  
    echo "输入第二个数字: "  
    read anotherNum  
    echo "两个数字分别为 $aNum 和 $anotherNum !"  
    return $(($aNum+$anotherNum))  
}  
funWithReturn  
echo "输入的两个数字之和为 $? !"
```

- 同样使用 `$1` 等获取参数
### 流程控制

- 条件语句
```shell
if [[ "$variable" = "value" ]]; 
then
    echo "变量等于值"
elif condition
then

else
    echo "变量不等于值"
fi
```
- 也可以使用 test 产生条件 `if test $[num1] -eq $[num2]`

- case语句
```shell
case "$variable" in
    pattern1)
        # 如果变量匹配pattern1，执行这里的代码
        ;;
    pattern2)
        # 如果变量匹配pattern2，执行这里的代码
        ;;
    *)
        # 如果没有匹配的条件，执行这里的代码
        ;;
esac
```

- 循环语句
```shell
for var in item1 item2 ... itemN
do
    command1
    command2
    ...
    commandN
done

for item in list; do
    # 循环体中的代码
done

count=1
while [ $count -le 5 ]; do
    echo "计数：$count"
    count=$((count+1))
done

until [ condition ]; do# 条件为假时重复执行一段代码
    # 循环体中的代码
done
```

- break 命令允许跳出所有循环
```bash
#!/bin/bash  
while :  
do  
    echo -n "输入 1 到 5 之间的数字:"  
    read aNum  
    case $aNum in  
        1|2|3|4|5) echo "你输入的数字为 $aNum!"  
        ;;  
        *) echo "你输入的数字不是 1 到 5 之间的! 游戏结束"  
            break  
        ;;  
    esac  
done
```
- continue
### 运算

- 算数运算符
  - bash原生不支持数学运算，使用expr命令进行
  - \`expr x + y\`表示加法（注意不是dan引号），注意一定要有空格
  - ![image-20231229152850136](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231229152850136.png)
  - 乘法要使用`\*`
  
- 关系运算符
  - 字符串连接`result="$str1.$str2"`
  - 比较
```shell
-gt # 大于
-lt # 小于
-ge # 大于等于
-le # 小于等于
```
- `-e`：检查**文件是否存在**。如果文件存在，则返回真，否则返回假。
- `-f`：检查文件是否是**一个普通文件**。如果是普通文件，则返回真，否则返回假。
- `-d`：检查文件是否是**一个目录**。如果是目录，则返回真，否则返回假。
- `-r`：检查文件是否可读。如果文件可读，则返回真，否则返回假。
- `-w`：检查文件是否可写。如果文件可写，则返回真，否则返回假。
- `-x`：检查文件是否可执行。如果文件可执行，则返回真，否则返回假。
- `-s`：检查文件是否为空。如果文件不为空，则返回真，否则返回假。
- `[ "$a" -gt "$b" ]`
- 或者 `(( a > b ))`
- 或者 ` if test $[num1] -eq $[num2]`

- 布尔运算符
  - ![image-20231229153104488](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231229153104488.png)

- 逻辑运算符
```shell
false || echo "Oops, fail"
# Oops, fail
true || echo "Will not be printed"
#
true && echo "Things went well"
# Things went well
false && echo "Will not be printed"
#
false ; echo "This will always run"
# This will always run
```

- 字符运算符
  - ![image-20231229153212942](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231229153212942.png)
- 文件运算符
  - ![image-20231229153424107](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231229153424107.png)
  - ![image-20231229153403526](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231229153403526.png)

### 补充

- 执行脚本`source mcd`就将方法加载到了终端作用域，之后可以直接使用`mcd xxx`执行

- 例子
```shell
echo "Starting program at $(date)" # date会被替换成日期和时间

echo "Running program $0 with $# arguments with pid $$"

for file in "$@"; do
    grep foobar "$file" > /dev/null 2> /dev/null
    # 如果模式没有找到，则grep退出状态为 1
    # 我们将标准输出流和标准错误流重定向到Null，因为我们并不关心这些信息
    if [[ $? -ne 0 ]]; then
        echo "File $file does not have any foobar, adding one"
        echo "# foobar" >> "$file"
    fi
done
```

- 通配符
  - `ls *.sh`筛选文件类型
  - `ls project?`
```shell
convert image.{png,jpg}
# 会展开为
convert image.png image.jpg

cp /path/to/project/{foo,bar,baz}.sh /newpath
# 会展开为
cp /path/to/project/foo.sh /path/to/project/bar.sh /path/to/project/baz.sh /newpath
# 下面命令会创建foo/a, foo/b, ... foo/h, bar/a, bar/b, ... bar/h这些文件(一个语句多个大括号使用笛卡尔积组合)
touch {foo,bar}/{a..h}
```

- 其他语言编写脚本（不能作为函数）
```shell
#!/usr/local/bin/python
import sys
for arg in reversed(sys.argv[1:]):
    print(arg)
```
- 函数只能与shell使用相同的语言，脚本可以使用任意语言。因此在脚本中包含 `shebang` 是很重要的。
- 函数仅在定义时被加载，脚本会在每次被执行时加载。这让函数的加载比脚本略快一些，但每次修改函数定义，都要重新加载一次。
- 函数会在当前的shell环境中执行，脚本会在单独的进程中执行。因此，函数可以对环境变量进行更改，比如改变当前工作目录，脚本则不行。脚本需要使用 [`export`](https://man7.org/linux/man-pages/man1/export.1p.html) 将环境变量导出，并将值传递给环境变量。
- 与其他程序语言一样，函数可以提高代码模块性、代码复用性并创建清晰性的结构。shell 脚本中往往也会包含它们自己的函数定义。

#### 文件包含

- shell 脚本调用外部脚本
```bash
. filename
#或
source filename
```

#### 工具

- 脚本静态代码分析工具 [shellcheck](https://github.com/koalaman/shellcheck)
  - 识别并提供关于 Shell 脚本中的语法错误、安全漏洞、代码风格问题和一般性问题的有用建议。
  - `shellcheck your_script.sh`

### 数据处理

- `sed` 基于文本编辑器 `ed` 构建的”流编辑器” 
  - 利用一些简短的命令来**修改文件**，而不是直接操作文件的内容
  - 替换文件的内容 `| sed 's/.*Disconnected from //'`
    - `s/REGEX/SUBSTITUTION/`, 其中 `REGEX` 部分是我们需要使用的正则表达式，而 `SUBSTITUTION` 是用于替换匹配结果的文本。

- 统计数目
  - `wc` 默认单词数目 `-l` 统计行

- `| sort | uniq -c`
  - `sort` 会对其输入数据进行排序。`uniq -c` 会把连续出现的行折叠为一行并使用出现次数作为前缀。

- awk：强大的**文本处理编程语言**
  - `awk '{print $2}'` 输出介个后的序列中的第二个字符串
  - `| awk '$1 == 1 && $2 ~ /^c[^ ]*e$/ { print $2 }' | wc -l`
    - 为 `awk` 指定了一个匹配模式串（也就是 `{...}` 前面的那部分内容）。该匹配要求文本的第一部分需要等于 1（这部分刚好是 `uniq -c` 得到的计数值），然后其第二部分必须满足给定的一个正则表达式。代码块中的内容则表示打印用户名。然后我们使用 `wc -l` 统计输出结果的行数。

- 数学计算 `bc -l`
  - `| paste -sd+ | bc -l` 解析输入为加法表达式，之后进行计算
  - 使用 R 语言进行统计 `R --slave -e 'x <- scan(file="stdin", quiet=TRUE); summary(x)'`
  - 使用 `gnuplot` =绘制图表
    - `gnuplot -p -e 'set boxwidth 0.5; plot "-" using 1:xtic(2) with boxes'`