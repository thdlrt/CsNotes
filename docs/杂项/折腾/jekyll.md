

### 安装

- [Jekyll • 简单静态博客网站生成器](http://jekyllcn.com/docs/themes/)

- 依赖环境

  - 安装[Ruby](https://link.zhihu.com/?target=https%3A//rubyinstaller.org/downloads/)
  - 安装[RubyGems](https://link.zhihu.com/?target=https%3A//rubygems.org/pages/download)
    - 解压压缩文件到本地。在 CMD 命令窗口执行`ruby setup.rb`

- jekyll安装

  - ```shell
    gem install jekyll   #安装jekyll  
    jekyll -v    #查看jekyll版本号
    ```

- 初始化仓库`jekyll new name`
- 本地预览`bundle exec jekyll serve`
- 修改`_config.yml`来设置网页的基本配置信息
- 编译

  - 保存到`_site`文件夹


### 配置

- gemfile中存储插件等依赖信息
  - 修改之后使用bundle install自动进行安装 

- _draft草稿
  - 将md文件放入_draft文件夹，文章不会直接渲染到网站上 
  - 查看`jekyll serve --draft`
- _include定义组件 
  - 如重复使用的head和foot
  - 使用`{% include header.html color="可选传参" %}`
    - 传递的参数通过`{{include.color}}`访问

- _data存储静态数据(yml json csv)
  - 如使用`people.yml`即`{{ site.data.people }}`


#### _config全局配置

- 头信息默认值defaults

  - 为全站文章指定相同的配置信息（如页面布局）

  - ```yml
    defaults:
      -scope:
          path: ""
          type: "posts"
        values:
          layout: "my-site"
      -scope:
          path: "projects"
          type: "pages" # 以前的 `page`， 在 Jekyll 2.2 里。
        values:
          layout: "project" # 覆盖之前的默认布局
          author: "Mr. Hyde"
    ```
    
  - 优先级低于具体文章中的内容

  - scope指定应用范围，values指定默认文件头

- 头信息

  - ```
    ---
    layout: article
    title: Page - Sidebar
    aside:
      toc: true
    sidebar:
      nav: layouts
    ---
    ```

  - 用---包围

### _layouts自定义布局

- 使用html编写页面模板，嵌入响应式变量（类似vue`{{ content }}`）

- 嵌套包装（如一个布局为wrapper）

  - ```
    Wrapper <br>
    {{ content }}
    <br> Wrapper
    ```

- 循环`{% for post in site.posts %} {% endfor %}`

- 条件`{% if condition %} {% else if condition %} {% else %} {% endif %} `

#### 特殊变量

- content：md的全部内容
- 访问头部定义的数据(如author属性)
  - layout表示访问当前配置文件中的文件
    - layout.author
  - page表示访问前端文件（如md）中的内容 
  - site访问_config的全局配置

### 静态文件

- 如pdf png css等，存储在assets文件中
- 在`site.static_files`

### 页面

- 对于常规的博客内容，以`年-月-日-标题.MARKUP`的格式存储在`_post`文件夹
  - 标题中的空格使用_代替

- 对于主页、关于等页面通常以html存储在根目录下

### 主题

- [Jekyll Themes](http://jekyllthemes.org/)

#### Text

- 头部导航栏在 *data/navigation.yml* 文件的 `header` 项定义，它是一个包含标题和 URL 项的数组：

- 侧边栏导航栏

  - 要想在某篇文章或页面中使用侧边栏导航栏，首先你需要在 *data/navigation.yml* 中定义一个导航栏。

    ```
    docs-en:
      - title:      Start
        children:
          - title:  Quick Start
            url:    /docs/en/quick-start
          - title:  Structure
            url:    /docs/en/structure
          ...
      - title:      Customization
        children:
          - title:  Configuration
            url:    /docs/en/configuration
          - title:  Navigation
            url:    /docs/en/navigation
          ...
    ```

    然后在头信息中将定义的导航作为这篇文章或页面的侧边栏导航栏：

    ```
    sidebar:
      nav: docs-en
    ```

- 常用配置参数

- 文章全部在`_post`文件夹，文件格式为`年-月-日-标题.md`

- 文章头部用于设置参数

  - ```
    ---
    layout: article
    title: Document - Writing Posts
    tags:[]//标签
    mathjax: true
    article_header:
      type: cover
      image:
        src: /screenshot.jpg
    ---
    ```
    
  - permalink指定固定 url地址，如`/xxx/xxx` 

  - 可以使用`:layout`来引用变量

- 扩展

  - 支持网易云、b站、幻灯片等

- 布局排版

  - [Samples - TeXt Theme (kitian616.github.io)](https://kitian616.github.io/jekyll-TeXt-theme/samples.html)

- layout 布局参数

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230712204934462.png" alt="image-20230712204934462" style="zoom:33%;" />
