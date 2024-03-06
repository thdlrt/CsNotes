# vscode

### copilot

- 接受内联代码建议 Tab
- 关闭内联代码建议 Esc
- 显示下一个建议 Alt + ]
- 显示上一个建议 Alt + [
- 触发建议 Alt + \
- 在右侧窗口中显示十个建议 Ctrl + Enter

### ssh远程连接

- [配置vscode 远程开发+ 免密登录 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/222452460)
- X11配置[ vscode 通过 X11/Xming 转发显示远程 GUI 窗口_vscode x11_blainet的博客-CSDN博客](https://blog.csdn.net/qq_40750972/article/details/123963536?spm=1001.2101.3001.6650.12&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-12-123963536-blog-120041495.pc_relevant_3mothn_strategy_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-12-123963536-blog-120041495.pc_relevant_3mothn_strategy_recovery&utm_relevant_index=17)

# ide

## 常用快捷键

### vs

- tip：

  - ctrl是强制功能键

  - shift有给项目增加功能

- Ctrl+F: 查找 

  - F3 下一个
  - Shift+F3: 查找上一个

- 注释

  - Ctrl+K,C: 注释选定内容
  - Ctrl+K,U: 取消选定注释内容

- 调试

  - F5: 启动调试
  - Ctrl+F5: 开始执行(不调试)
  - Shift+F5: 停止调试
  - Ctrl+Shift+F5: 重启调试
  - F9: 启用/关闭断点
  - Ctrl+F9: 停止断点
  - Ctrl+Shift+F9: 删除全部断点
  - F10: 逐过程
  - Ctrl+F10: 运行到光标处
  - F11: 逐语句

- 编辑快捷键

  - Ctrl+Shift+V: 剪贴板循环（剪贴记录）
  - Ctrl+U: 全部变为小写
  - Ctrl+Shift+U: 全部变为大写
  - 查找
    - F12: 转到所调用过程或变量的定义（声明和实现间跳转）
    - Alt+F12: 查找符号(列出所有查找结果)
    - shift+f12:查找所有引用（讲光标放在单词上， 然后按Shift + F12）
  - Ctrl+Shift+L: 删除当前行
  - Ctrl+单击: 选中当前点击的整个单词
  - Ctrl+左右箭头键:一次可以移动一个单词

### QT

- Ctrl + I 选中的文字自动缩进
- Ctrl + / 注释行和取消注释行

- 【F2】 声明和定义之间切换 

- 【F4】 头文件和源文件之间切换

- 查找
  - 【Ctrl + Shift + F】 弹出查找对话框
  - 【Ctrl + F】 查找当前文档 
  - 【F3】 查找下一个
  - 【Shift + F3】 查找上一个

### idea

- 搜索：两次shif

  - 查找可以进行的ide操作ctrl+shift+a
  - 查找类ctrl+n
  - 文件中查找ctrl+shift+f
  - 替换ctrl+shift+r

- 文件中查找ctrl+f

  - enter下一个
  - shift enter上一个

- 高亮选中匹配：ctrl+shift+F7

- 显示上下文操作alt+enter

- 补全

  - ctrl+tab调出补全
  - enter补全（如果后面有则是插入）tab补全（替换）
  - ctrl+shift+enter完整补全/语句补全（如for）
  - ctrl+shift+space类型匹配补全
  - 后缀补全，如在括号后.补全if

- ctrl+w选中单词，再按扩大选中范围（一句，再加引号）

  - ctrl+shift+w收缩
  - 很灵活，比如一下选中if，再按一下选中if块

- 每行//注释：ctrl+/

  - /**/注释：ctrl+shift+/

- 复制行：ctrl+D

  - 删除行：ctrl+Y

- Shift+上下：向上移动一行光标**并选中**范围

- alt+上下：移动到上一个方法

- alt+shift+上下：剪切移动行

- ctrl+shift+上下：剪切并移动整个方法

- ctrl+-=收起打开方法

  - 加shift对整个文件修改

- 包装（如try catch）：ctrl+alt+t

  - 解包：ctrl shift delete

- 多选

  - alt+j选中光标处符号
    - 再按选中下一个
  - alt+shift+j取消上一个
  - ctrl+alt+shift+j选中文件中所有匹配项

- 重命名：shift+F6

- 提取变量ctrl+alt+v将变量提取为一个新变量

  - ```java
    int i1 = i + 1;
    if (array[i] > array[i1]) {
        int temp = array[i];
        array[i] = array[i1];
        array[i1] = temp;
    }
    ```

  - 提取方法ctrl+shift+alt+v
  - 打开重构菜单ctrl+alt+shift+t

- 右键有本地历史记录，用于查看修改记录

  - 最近打开的文件ctrl+e
  - 同时看到代码ctrl+shift+e

- ctrl+l格式化代码（没有选中就全格式化）

  - ctrl+alt+shift+l显示格式化设置

- 查看方法签名（参数）ctrl+p

  - 查看文档ctrl+q
  - 查看定义（代码）ctrl+shift+i

- 转到下一个警告F2

  - ctrl+F2打开说明

- ctrl+b转到声明/查看使用
  - 查找实现ctrl+alt+b
  - ctrl+u基类方法
- 视图
  - 查看方法层次ctrl+shift+h
  - 查看类视图ctrl+h
- 调试
  - 如果修改只影响纯方法可以热交换，只按ctrl+F9
  - 重置帧：点击栈帧顶层的返回

- git
  - 搜索克隆打开面板克隆仓库
  - 右下角查看、控制分支
  - 右上控制推送等操作<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123012726596.png" alt="image-20231123012726596" style="zoom:50%;" />
  - 提交设置
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123012903804.png" alt="image-20231123012903804" style="zoom:33%;" />
  - alt+9打开提交视图，选中一个提交可以查看
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123013047754.png" alt="image-20231123013047754" style="zoom:33%;" />
    - alt m修正提交
  - 