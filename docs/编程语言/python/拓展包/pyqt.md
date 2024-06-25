## QT Designer

### 布局管理

- 类型：垂直、水平、网格（栅格）、表单（左列包含标签，右列包含控件）
- 布局方式：
  - 布局管理器：选中控件，右键布局
  - 容器：放入容器中（也可以右键设置布局）
- 属性
  - 绝对布局geometry
    - xy表示控件左上角距离上一级窗口左上角的距离
    - 宽度高度（控件自身）
    - 使用布局管理器时该属性失效
  - 大小
    - mininumSize/maxinumSize最大最小尺寸
    - sizePolicy（需要控件被布局管理器接管）
      - p68
- 分隔
  - 使用横竖弹簧分隔（横弹簧用于横向大距离，纵弹簧用于小距离）
  - 使用横竖分割线

### 其他功能

- 设置伙伴（绑定关系）
  - 选中<img src="../media/friend.png" style="zoom: 67%;" />拖拽标签向输入框
  - 标签text中添加(&a)实现快捷键(按下alt+a自动跳转)
- 编辑信号槽
  - 用<img src="../media/signal.png" style="zoom:67%;" />

- 设置tab顺序
  - 用<img src="../media/tab.png" style="zoom:67%;" />
- QAction：
  - 创建qaction用于放置在菜单栏/工具栏等位置

### 工作流程（pycharm）

- 选择工具qtdesigner创建ui文件

- 是由qtuic将ui文件转化为py文件

- 调用模板：

  - ```python
    import sys
    from PySide6.QtWidgets import QApplication, QMainWindow, QWidget, QDialog
    from untitled import*
    class MyMainWindow(QDialog, Ui_Dialog):#前一项的类型要与后面的ui文件的类型保持一致
        def __init__(self, parent=None):
            super(MyMainWindow, self).__init__(parent)
            self.setupUi(self)#界面初始化
    if __name__ == "__main__":#调用界面（main函数模板）
        app = QApplication(sys.argv)
        myWin = MyMainWindow()
        myWin.show()
        sys.exit(app.exec())
    ```

### 信号槽

- 格式
  - `对象.信号.connect(槽函数)[槽返回值]`如`l.clicked.connect(active)`
  - 解除绑定disconnect
- 使用lambda表达式传递额外参数
  - `.connect(lambda x: f(x, [额外参数]))`

- 自定义信号：
  - `s = Signal(str, int...)`使用Signal创建，括号内填写变量类型
  - 发送信号`emit(信号名)`

- 槽函数：
  - 槽函数可以是任何函数


### 控件使用

- 创建：                                            
  - `l = QLabel(self)`传入self用于绑定          

- label超链接：

  - ```python
    self.label.setText('<a href="http://www.google.com">Google</a>')
    self.label.setOpenExternalLinks(True)
    ```

  - 用html格式记录，并允许跳转