---
url: https://git.nju.edu.cn/thdlrt/njucs-baoyan/-/blob/main/%E4%BD%BF%E7%94%A8VSCode%E7%BC%96%E5%86%99C++%E5%8D%95%E6%96%87%E4%BB%B6%E7%A8%8B%E5%BA%8F(Windows%E7%B3%BB%E7%BB%9F).md?ref_type=heads
title: 使用 VSCode 编写 C++ 单文件程序 (Windows 系统).md · main · 田 昊东 / NJUCS-BAOYAN · GitLab
date: 2024-05-27 21:19:08
tag: 
summary: 南京大学代码托管服务
---
相同内容也在某人的个人博客上发布 [无耻引流](https://triccsr.github.io/fe9a715b/)

## [](#update-on-20240506)Update on 2024.05.06

某人去了基础实验楼乙区 124 机房，发现 124 里的电脑换成了 i7-13700，还装了 clion、pycharm 和 intellij idea，版本 2024.1。某人测试后发现在 VSCode 中使用 clion 的编译器不会出现 task.json 和 launch.json 的问题。

本文的测试环境是 Dev C++，仅供参考，但配置起来大差不差。

新配的电脑的注意事项：

*   开机慢，会在一个只有一行白字的黑屏界面卡很久
*   然后会出现一个系统菜单，选择 Visual Studio 选项（不出意外是第一个）

## [](#%E8%83%8C%E6%99%AF)背景

南京大学硕士夏令营机试开始之前，某人打开 124 机房的古董电脑上的 vscode，简单写了个 hello world，结果发现 VSCode 对着`#include <bits/stdc++>`报错 "header not found"。(解决方法见下文)

机试开始，某人想调试代码，却发现 gdb 不太好使。

一切都结束之后，某人翻经验贴仓库，发现有相似问题的不只某人一个。

## [](#%E5%89%8D%E7%BD%AE%E6%9D%A1%E4%BB%B6)前置条件

*   电脑上有 MinGW
*   电脑上有 Visual Studio Code
*   vscode 上有 Microsoft 官方的 C/C++ 插件

## [](#%E6%B5%8B%E8%AF%95%E7%8E%AF%E5%A2%83)测试环境

*   Win11 22H2
*   Visual Studio Code 1.83.0
*   DevC++ 5.11 自带的 MinGW，其中 g++ 版本为 4.9.2，gdb 版本为 7.8.1（为了模拟 124 古董机器的编译器）

## [](#%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95)使用方法

新建文件夹，用 vscode 打开，之后的所有操作都在该窗口中进行。

### [](#cc-configuration)C/C++ Configuration

按 F1 键，显示搜索框，输入 C/C++，选择`C/C++: Edit Configurations(UI)`，将会出现新页面 C/C++ Configurations，同时. vscode 文件夹下出现新文件 c_cpp_properties.json。

以下内容需要修改：

使用 C/C++ Configurations 页面编辑时，不能打开 c_cpp_properties.json 文件，否则进行的编辑将不被保存。

[![](https://triccsr.github.io/fe9a715b/image-1.png)](https://triccsr.github.io/fe9a715b/image-1.png)

这个是编译器路径，更改方式有如下两种：

1.  点击右侧箭头，打开下拉菜单，选择 MinGW 的 g++（适用于 g++ 在 PATH 中的情况）** upd. on 2024.5.6：如果电脑上有 clion 则选择 clion 的 g++ **
2.  直接输入 g++ 的路径，注意不要带引号

VSCode 的编译器寻找顺序为 MSVC -> GCC on WSL -> MinGW, 所以当电脑上有 MSVC 时默认编译器路径是 MSVC 路径，这是 124 机房电脑的 vscode 不认识`#include <bits/stdc++>`的原因。

[![](https://triccsr.github.io/fe9a715b/image-3.png)](https://triccsr.github.io/fe9a715b/image-3.png)

在框中输入编译器参数，每行一个。

某人一般使用:

```
-Wall
-Wextra
-Wconversion
-Wshadow
-std=c++11
```

其中`-Wconversion`是类型转换警告，`-Wshadow`是变量重名覆盖警告（某人经常犯变量重名错误，因此习惯加上），`-std=c++11`为 c++ 版本。

[![](https://triccsr.github.io/fe9a715b/image-4.png)](https://triccsr.github.io/fe9a715b/image-4.png)

这个选择 windows-gcc-x64。

[![](https://triccsr.github.io/fe9a715b/image-5.png)](https://triccsr.github.io/fe9a715b/image-5.png)

这个是 c 和 c++ 的版本，按需选择。

我用上述编译器版本测试，即使在 C++ standard 中选择了 c++11，在编译带 c++11 特性的代码时仍报错，解决方案是在编译参数中加上`-std=c++11`

### [](#%E7%BC%96%E5%86%99%E4%BB%A3%E7%A0%81)编写代码

没啥说的，在自己创建的文件夹里新建 c/c++ 文件写就完了。

### [](#%E8%BF%90%E8%A1%8C%E8%B0%83%E8%AF%95)运行 / 调试

现在. vscode 文件夹下只有 c_cpp_properties.json 一个文件。

#### [](#tasksjson%E5%BF%85%E9%9C%80)tasks.json(必需)

**将 vscode 页面切换到想要运行的代码文件**，右上角如图所示：

[![](https://triccsr.github.io/fe9a715b/image-6.png)](https://triccsr.github.io/fe9a715b/image-6.png)

点击下拉菜单，选择 debug 或 run

[![](https://triccsr.github.io/fe9a715b/image-8.png)](https://triccsr.github.io/fe9a715b/image-8.png)

会出现一个菜单

[![](https://triccsr.github.io/fe9a715b/image-7.png)](https://triccsr.github.io/fe9a715b/image-7.png)

选择想要的编译器路径，选择完后. vscode 文件夹下应出现 tasks.json。

然后就**有可能**可以正常运行或调试程序了。**upd on 2024.5.6 某人测试若使用 clion 的编译器可以正常运行或调试程序**

正常情况下 vscode 会自动新建两个 terminal，一个用于编译，一个用于运行。

使用快捷键 ctrl+j 打开 panel，下面这个终端是编译用的，与我们无关：

[![](https://triccsr.github.io/fe9a715b/image-12.png)](https://triccsr.github.io/fe9a715b/image-12.png)

下面这个终端是运行程序的，我们在这里输入数据：

[![](https://triccsr.github.io/fe9a715b/image-13.png)](https://triccsr.github.io/fe9a715b/image-13.png)

注意到 panel 里面还有一个 debug console，调试时我们可以在里面输入式子。

如果还不能正常使用，请看下节 launch.json。

#### [](#launchjson%E9%9D%9E%E5%BF%85%E9%9C%80)launch.json(非必需)

我使用 DevC++ 自带的 gdb7.8.1 测试时，用 vscode 的集成终端无法输入数据，换成 gdb13.2 则没有此问题。解决方法是在 launch.json 中把`"externalConsole"`由`false`改为`true`，使用外部终端。 但这样外部终端会一闪而过看不见输出，解决方法：

*   在代码的`main`函数的`return 0;`前面加上`system("pause");`，**在 OJ 提交时去掉这行**。
*   运行程序时选择 debug c/c++ file 按钮，设置断点

##### [](#%E8%87%AA%E5%8A%A8%E9%85%8D%E7%BD%AE)自动配置

点击右上角的齿轮图标，顶部会出现一个菜单

[![](https://triccsr.github.io/fe9a715b/image-11.png)](https://triccsr.github.io/fe9a715b/image-11.png)

选择第一个 Recently Used Task，.vscode 下将会自动生成一个 launch.json

##### [](#%E6%89%8B%E5%8A%A8%E9%85%8D%E7%BD%AE)手动配置

**页面切换至 c/c++ 代码文件**，点击侧边栏的 Run and Debug，点击 create a launch.json file。

[![](https://triccsr.github.io/fe9a715b/image-14.png)](https://triccsr.github.io/fe9a715b/image-14.png)

在弹出的菜单中选择 C++(GDB/LLDB)，然后将生成一个新文件 launch.json。初始如图所示：

[![](https://triccsr.github.io/fe9a715b/image-15.png)](https://triccsr.github.io/fe9a715b/image-15.png)

如果生成的 launch.json 不是空白的而是有了内容，则不用更改文件。

否则，点击右下角的 Add Configuration，选择 C/C++: (gdb) Launch。

然后将插入以下内容：

[![](https://triccsr.github.io/fe9a715b/image-16.png)](https://triccsr.github.io/fe9a715b/image-16.png)

其中 "program" 和 "miDebuggerPath" 是一定要改的。打开 tasks.json，看到 args 的 - o 后面有一行`"${fileDirname}\\${fileBasenameNoExtension}.exe"`，把 program 后面的内容改成这个。"miDebuggerPath" 就是 gdb 的路径，注意在 windows 下要使用双反斜杠，最后形如这样：

```
"program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
"miDebuggerPath": "C:\\Program Files (x86)\\Dev-Cpp\\MinGW64\\bin\\gdb.exe",
```

配置完之后再点击右上角的 run/debug 按钮，不出意外应该可以正常运行。

## [](#%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99)参考资料

[Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)

[C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp)

[Debug C++ in Visual Studio Code](https://code.visualstudio.com/docs/cpp/cpp-debug)