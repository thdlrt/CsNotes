## 概述

- Webpack是一个现代的静态模块打包工具，它可以处理JavaScript、CSS、HTML、图片等多种文件，并将它们打包成适合在浏览器中运行的静态资源。

### 基本用法

- 安装`npm install webpack webpack-cli -D`
- 项目中配置   
  -  在项目根目录中，创建名为webpack.config.js的webpack 配置文件
    - webpack.config.js 是 webpack 的配置文件。webpack 在真正开始打包构建之前，会先读取这个配置文件， 从而基于给定的配置，对项目进行打包。
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421155001572.png" alt="image-20230421155001572" style="zoom:50%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421155109496.png" alt="image-20230421155109496" style="zoom:50%;" />
  -  在package.json 的scripts 节点下，新增dev 脚本
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421155025320.png" alt="image-20230421155025320" style="zoom:50%;" />
  -  在终端中运行`npm run dev `命令，启动webpack 进行项目的打包构建
  - 在webpack 中有如下的默认约定： 
    - 默认的打包入口文件为src-> index.js 
    - 默认的输出文件路径为dist -> main.js
    - 在webpack.config.js 配置文件中，通过entry 节点指定打包的入口。通过output 节点指定打包的出口。
      - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421155322893.png" alt="image-20230421155322893" style="zoom:50%;" />

## 插件与扩展(待补充)

###  webpack-dev-server

- 每当修改了源代码，webpack 会自动进行项目的打包和构建
- 安装`npm install webpack-dev-server -D`
- 配置：
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421161838837.png" alt="image-20230421161838837" style="zoom:50%;" />

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421161924647.png" alt="image-20230421161924647" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421162140973.png" alt="image-20230421162140973" style="zoom:50%;" />

###  html-webpack-plugin

- webpack 中的HTML 插件（类似于一个模板引擎插件）可以通过此插件自定制index.html 页面的内容
- 安装`npm install html-webpack-plugin -D`

## loader

- 在实际开发过程中，webpack 默认只能打包处理以 .js 后缀名结尾的模块。其他非 .js 后缀名结尾的模块， webpack 默认处理不了，需要调用 loader 加载器才可以正常打包。
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421162911327.png" alt="image-20230421162911327" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421163109480.png" alt="image-20230421163109480" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421163136367.png" alt="image-20230421163136367" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421163207698.png" alt="image-20230421163207698" style="zoom:50%;" />
- js高级语法
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421163256775.png" alt="image-20230421163256775" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421163308090.png" alt="image-20230421163308090" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421163318808.png" alt="image-20230421163318808" style="zoom:50%;" />

## 打包发布（待补充）

