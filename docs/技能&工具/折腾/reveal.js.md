### 使用md快速创建HTML ppt

#### 使用及部署

- 安装
  - `git clone https://github.com/hakimel/reveal.js.git`
  - 依赖`npm i`
  - 运行`npm start`

- 部署到github
  - 命名为index.html上传到一个新分支，如show
  - 设置page，选择新创建的分支以及.root
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231115175922293.png" alt="image-20231115175922293" style="zoom: 33%;" />

#### 配置及语法

- 播放
  - 按空格键来跳转到下一页
  - 通过按 `?` 问号键来显示帮助
  - `alt + 鼠标点击` 来进行局部放大缩小（在Linux中为 ctrl +单击）
  - 按 Esc 键，进入幻灯片概览
  - 按 b ，暂停幻灯片（页面变黑息屏）
  - 按 s ，进入演讲者备注视图

- 主题选择`$ pandoc slides.md -o slides.html -t revealjs -s -V theme=beige`

  - default：（默认）深灰色背景，白色文字
  - beige：米色背景，深色文字
  - sky：天蓝色背景，白色细文字
  - night：黑色背景，白色粗文字
  - serif：浅色背景，灰色衬线文字
  - simple：白色背景，黑色文字
  - solarized：奶油色背景，深青色文字

- 标头

  - ```
    % 主题：我的一天 //标题
    % Felix       //汇报人
    % 2020-03-13  //时间
    ```

- 分隔页`---`

- 渐进显示列表

  - ```
    ::: incremental
    
    - 列表项1
    - 列表项2
    
    :::
    ```

- 插入停顿`. . .`

- 幻灯片背景

  - 全局视差背景

    - ```
      ---
      title: My Slideshow
      parallaxBackgroundImage: /path/to/my/background_image.png
      parallaxBackgroundSize: 2100px
      ---
      ```

  - 单独的某个幻灯片设置背景

    - `## 这是一个幻灯片级别的标题 {data-background-image="/path/to/special_image.jpg"}`
    - 颜色背景 ： `data-background-color` ，示例 `{data-background-color="#ff0000"}`
    - 图像背景：`data-background-image` ，对于背景图像我们还可以为其添加更多属性，示例：
      `{data-background-image="http://example.com/image.png" data-background-size="100px" data-background-repeat="repeat"}`
    - 视频背景：示例 `{data-background-video="https://s3.amazonaws.com/static.slid.es/site/homepage/v1/homepage-video-editor.mp4,https://s3.amazonaws.com/static.slid.es/site/homepage/v1/homepage-video-editor.webm" data-background-video-loop=true data-background-video-muted=true}`
    - iframe ：嵌入一个网页作为幻灯片背景；iframe位于幻灯片后面的背景层中，因此默认情况下无法与之交互。要使背景具有交互性，可以添加`data-background-interactive`属性。示例：
      `{data-background-iframe="https://slides.com" data-background-interactive=true}`

- 演讲者备注

  - ```
    ::: notes
    
    This is my note.
    
    - It can contain Markdown
    - like this list
    
    :::
    ```

  - 

#### 补充

- 创建html时有很多可选参数`-V theme=sky`

- ```
  // 是否在右下角展示控制条
      controls: true,
  
      // 是否显示演示的进度条
      progress: true,
  
      // 是否显示当前幻灯片的页数
      slideNumber: false,
  
      // 是否将每个幻灯片改变加入到浏览器的历史记录中去
      history: false,
  
      // 是否启用键盘快捷键来导航
      keyboard: true,
  
      // 是否启用幻灯片的概览模式
      overview: true,
  
      // 是否将幻灯片垂直居中
      center: true,
  
      // 是否在触屏设备上启用触摸导航
      touch: true,
  
      // 是否循环演示
      loop: false,
  
      // 是否将演示的方向变成 RTL
      rtl: false,
  
      // 全局开启和关闭碎片
      fragments: true,
  
      // 标识演示文稿是否在嵌入模式中运行，即包含在屏幕的有限部分中的
      embedded: false,
  
      // 当按下键盘上的?问号键时，是否显示帮助
      help: true,
  
      //  两个幻灯片之间自动切换的时间间隔（毫秒），当设置成 0 的时候则禁止自动切换，该值可以被幻灯片上的 ` data-autoslide` 属性覆盖
      autoSlide: 0,
  
      // 当遇到用户输入的时候停止切换
      autoSlideStoppable: true,
  
      // 是否启用通过鼠标滚轮来导航幻灯片
      mouseWheel: false,
  
      //  是否在移动设备上隐藏地址栏
      hideAddressBar: true,
  
      // 是否在一个弹出的 iframe 中打开幻灯片中的链接
      previewLinks: false,
  
      // 切换过渡效果
      transition: 'default', // none/fade/slide/convex/concave/zoom
  
      // 过渡速度
      transitionSpeed: 'default', // default/fast/slow
  
      // 全屏幻灯片背景的过渡效果
      backgroundTransition: 'default', // none/fade/slide/convex/concave/zoom
  
      // 除当前可见的之外的幻灯片数量
      viewDistance: 3,
  
      // 视差背景图片
      parallaxBackgroundImage: '', // e.g. "'https://s3.amazonaws.com/hakim-static/reveal-js/reveal-parallax-1.jpg'"
  
      // 视差背景尺寸
      parallaxBackgroundSize: '', // CSS syntax, e.g. "2100px 900px"
  
      // 移动视差背景（水平和垂直）滑动变化的数量, 例如100
      parallaxBackgroundHorizontal: '',
      parallaxBackgroundVertical: ''
  ```

- 可以构造二维ppt，#1会作为顶级标题，后面的在其下面(上下翻页)，左右翻同时存在

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/v2-32b2a01a805e0c2a7995a6729ecd5256_1440w.webp" alt="img" style="zoom:33%;" />
