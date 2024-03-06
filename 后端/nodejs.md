## 概述

- node.js是基于浏览器v8引擎的js运行环境
- 是js的后端运行环境，不提供web api ，bom、dom
- 在命令行中运行`node + 文件路径`

## nvm

- nodejs版本管理器
- `nvm install`版本号，可安装指定版本的nodejs
- `nvm ls `查看已经安装的所有nodejs版本
- `nvm use `版本号，即可切换到指定版本
- `nvm uninstall `版本号，卸载指定版本
- `nvm on`： 启用node.js版本管理。
- `nvm off`： 禁用node.js版本管理(不卸载任何东西)

## 内置api

### fs文件系统

- 引入`const fs = require('fs')`

#### 读取文件

- `fs.readFile(path[,options],callback)`
  - 参数1： 必选参数，字符串，表示文件的路径
  - 参数2： 可选参数，表示以什么编码格式来读取文件。
  - 参数 3 ： 必选参数，文件读取完成后，通过回调函数拿到读取的结果。
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421130942977.png" alt="image-20230421130942977" style="zoom:33%;" />
  - 读取成功时err=None

#### 写入文件

- `fs.writeFile(path,data[,options],callback)`
  - 参数1：必选参数，需要指定一个文件路径的字符串，表示文件的存放路径。
  - 参数2：必选参数，表示要写入的内容。
  - 参数3：可选参数，表示以什么格式写入文件内容，默认值是 utf8。
  - 参数4：必选参数，文件写入完成后的回调函数。
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421131651804.png" alt="image-20230421131651804" style="zoom:50%;" />

### path路径

- 导入`const path = require('path')`
- `__dirname` 可以用来动态获取当前文件所属目录的绝对路径
- `__filename `可以用来动态获取当前文件的绝对路径，包含当前文件

#### 拼接路径

- 把多个路径片段拼接为完整的路径字符串：

- `path.join([...paths])`
  - ...paths <string> 路径片段的序列
  - 返回值: <string>
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421132305291.png" alt="image-20230421132305291" style="zoom:50%;" />

#### 获取路径中的文件名

- 文件名`path.basename() `
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421132604546.png" alt="image-20230421132604546" style="zoom:50%;" />
- 扩展名`path.extname() `

### http模块

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421133647264.png" alt="image-20230421133647264" style="zoom:50%;" />

- 引入`const http = require('http')`
- 实例`const server = http.createServer()`
- 绑定request事件
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421133941879.png" alt="image-20230421133941879" style="zoom:50%;" />
  - req对象:访问与客户端相关的数据或属性
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421134224007.png" alt="image-20230421134224007" style="zoom:50%;" />
  - res对象：访问与服务器相关的数据或属性
    - 使用`res,end()`将内容返还给客户端
      - 向客户端发送中文内容的时候，会出现乱码问题，此时，需要手动设置内容的编码格式
    - ![image-20230421134342782](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421134342782.png)
- 启动服务器,指定监听的端口
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421134034651.png" alt="image-20230421134034651" style="zoom:50%;" />

- 根据不同的 url 响应不同的 html 内容
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421134504660.png" alt="image-20230421134504660" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421134512389.png" alt="image-20230421134512389" style="zoom:50%;" />
  - 通常把文件的实际存放路径，作为每个资源的请求 url 地址，这样就可以把url作为文件路径，读取文件之后返回内容

## 模块化

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421134745731.png" alt="image-20230421134745731" style="zoom:50%;" />
- 加载模块`const .. = require('..')`
  - 加载内置、第三方模块时直接写包名，加载自定义模块时写文件的相对路径，如`./custom.js`
  - 模块在第一次加载后会被缓存。 这也意味着多次调用 require() 不会导致模块的代码被执行多次。
  - 使用 require() 加载自定义模块时，**必须指定以 ./ 或 ../ 开头**的路径标识符。在加载自定义模块时，如果没有指定 ./ 或 ../ 这样的路径标识符，则 node 会把它当作**内置模块或第三方模块**进行加载。
    - Node.js 会从当前模块的父目录开始，尝试从 /node_modules 文件夹中加载第三方模块。如果没有找到对应的第三方模块，则移动到再上一层父目录中，进行加载，直到文件系统的根目录
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421141256841.png" alt="image-20230421141256841" style="zoom:50%;" />

### module 对象

- 每个js模块都有一个module 对象，存储了和当前模块有关的信息，也可以用于向外共享模块作用域中的成员
-  module.exports 对象：将模块内的成员共享出去，供外界使用
  - 通过require获取到的就是模块的exports对象
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421135121840.png" alt="image-20230421135121840" style="zoom:50%;" />

### npm与包

- npm, Inc. 公司提供了一个包管理工具，我们可以使用这个包管理工具。

#### 操作

- 在项目中安装包`npm i 包名[@版本号]`
- 卸载包`npm uninstall 包名`
- 初次装包完成后，在项目文件夹下多一个叫做 node_modules 的文件夹和 package-lock.json 的配置文件。
  - node_modules 文件夹用来存放所有已安装到项目中的包。require() 导入第三方包时，就是从这个目录中查找并加载包
  - package-lock.json 配置文件用来记录 node_modules 目录下的每一个包的下载信息，例如包的名字、版本号、下载地址等。
- 在项目根目录中必须提供一个叫做 package.json 的包管理配置文件。用来记录与项目有关的一些配置信息。
  - 功能
    - 项目的名称、版本号、描述等
    - 项目中都用到了哪些包
    - 哪些包只在开发期间会用到
    - 那些包在开发和部署时都需要用到
  - 便于剔除 node_modules 目录之后，在团队成员之间共享项目的源代码。从而减少体积
    - 把 node_modules 文件夹，添加到 .gitignore 忽略文件中。
  - 创建package.json
    - `npm init -y`
    - 使用install安装包时会自动把包的名称和版本号记录到json
    - 卸载包时会自动删除
    - 使用`npm i`按照json文件中的记录一键安装所有的包
    - 安装包的信息存储在json众多的dependencies 节点
    - 如果某些包只在项目开发阶段会用到，在项目上线之后不会用到，则建议把这些包记录到 devDependencies 节点中
      - 安装时末尾加上`-D`
- 下载源

#### 包的分类

##### 项目包

- 被安装到项目的 node_modules 目录中的包，都是项目包。
-  开发依赖包（被记录到 devDependencies 节点中的包，只在开发期间会用到） 
- 核心依赖包（被记录到 dependencies 节点中的包，在开发期间和项目上线之后都会用到）

##### 全局包

- 在执行 npm install 命令时，如果提供了 -g 参数，则会把包安装为全局包。全局包会被安装到 C:\Users\用户目录\AppData\Roaming\npm\node_modules 目录下。
- 只有工具性质的包，才有全局安装的必要性。因为它们提供了好用的终端命令。

### 包的结构与开发

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421140928583.png" alt="image-20230421140928583" style="zoom:50%;" />
-  <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421141023677.png" alt="image-20230421141023677" style="zoom:50%;" />
- 把不同功能写在不同的js文件中，都导入到index中。最后在 index.js 中，使用 module.exports 把对应的方法共享出去

## express（待补充）