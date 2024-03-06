# linux

## 基础

### [vim](vim.md)

### 基础概念

- 命令格式 command \[-options] \[parameter]
  - command 命令本身
  - -options 命令的一些选项，控制行为细节
    - 可以组合使用，如：-l -a 或-la 或-al 均可
  - parameter 命令的参数，多用于指向目标
- linux 系统终端默认会加载 HOME 目录为当前的工作目录
  - HOME 目录：每个 Linux 系统的个人账户目录（/home/用户名）
  - /home/用户名/~

- 在 shell 中执行命令时实际上是在执行一段 shell 可以解释执行的简短代码。对于不是 shell 了解的编程关键字，shell 会**去环境变量寻找**，搜索目标程序，然后根据路径执行程序。

```bash
missing:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
missing:~$ which echo(获得程序位置)
/bin/echo
missing:~$ /bin/echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
```

- | 管道符，将管道左边命令的结果作为右边命令的输入
  - 比如 cat text 01. txt | grep xxx 等价于 grep xxx text 01. txt
  - 如查找文件 ls xx | grep xx
  - 嵌套使用 xx|xx|xx|... 依次向右传递

- 查看指令的使用方法 `man xx
- `history` 输出输入的命令的历史记录
- `tree` 显示文件目录工具 `

### [[杂项/linux与shell/linux/文件系统]]

### [[权限管理]]

### [[进程管理]]

### [[网络]]

## 杂项

### [[环境配置]]

### 软件安装

#### yum-centos

- `yum [-y] [install | remove | search] 软件名称`
  - -y自动确认
- yum需要root权限以及联网
#### apt-ubuntu

- 仅将yum换成apt
#### systemctl软件（服务）启动&关闭控制

- `systemctl start | stop |status | enable | disable 服务名`
  - 启动 | 关闭 | 查看状态 | 开启开机自启 | 关闭开机自启
- 有些第三方软件不会自动集成进来，需要手动添加

### 环境变量

- `env`查看系统中记录的环境变量，以键值对的形式进行存储
  - 可以通过 `${键}` 获取对应的值（大括号可以在没有歧义时省去）

- 设置
  - **临时**设置`export 变量名=变量值`
  - 永久：（把export命令写入指定的文件）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230316235914735.png" alt="image-20230316235914735" style="zoom:40%;" />
    - `source 配置文件路径`

- 把程序所在的地址/文件夹写入PATH路径可以实现在**任意位置都可执行程序**。
  - PATH包含了一系列不同的路径，之间用:分隔。

### 压缩解压

- 常用格式`.tar .gz`
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230316221954382.png" alt="image-20230316221954382" style="zoom: 67%;" />
  - 常用
    - 压缩：`-(z)cvf name.tar（-f的压缩后的文件名称） name1.txt...(选择要压缩的文件)`
    - 解压：`-(z)xvf name.tar(要解压的文件) -C /...（指定解压目的地）`
    - -z一般在最前面，-f必须在最后面，-C单独写(不写默认为当前目录)
- zip
  - 压缩：`zip [-r] 目标名称 要压缩文件`
    - -r表示包含文件夹
  - 解压：`unzip 要解压的文件 [-d 解压目的地址]`

### 软连接（快捷方式）

- `ln -s 参数1 参数2`
  - 参数1：被链接的（源文件）
  - 参数2：链接目的地（快捷方式）
### [[Shell编程]]

#### 调试及性能分析

- [调试及性能分析 · the missing semester of your cs education (missing-semester-cn.github.io)](https://missing-semester-cn.github.io/2020/debugging-profiling/)

## 杂项

### 快捷键

- `ctrl+c` 终止程序运行/放弃输入这条命令，重新换行进行输入
- `ctrl+d` 退出登录（相当于 exit）/退出某些程序的特定界面
- `ctrl+l` **清空终端**相当于 clear
- `!+前缀` 搜索最近的匹配前缀的命令并执行
- `ctrl+r` **搜索历史命令**
  - 回车直接执行
  - 左右方向键获取命令
-  **光标移动**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230316203548007.png" alt="image-20230316203548007" style="zoom:50%;" />

### 系统时间/时区

- `date [-d] [+格式化字符串]` 查看系统时间
  - -d: 按照给定的字符串显示日期，一般用于日期计算
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230316215420462.png" alt="image-20230316215420462" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230316215012764.png" alt="image-20230316215012764" style="zoom:50%;" />
    - 可以自由组合，如 `date +%Y-%m-%d"`
- ntp 时间自动校准
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230316215702020.png" alt="image-20230316215702020" style="zoom:50%;" />