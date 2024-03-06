# html

## 基本语法

### 主体框架

```html
<!QOCTYPE html>//声明表示该文档由html5编写
<html>//文档开始
<head>//头部起点，头部元素容器，可以引用脚本、指示浏览器找到样式表、提供源信息
	<title>第一个程序</title>//文档标题
</head>//头部结束
<body>//主体起点，包含文档内容（文本、图像、超链接等）
	<h1>Hello</h1>
	<p>I love FishC!</p>
</body>//主体结束
</html>//文档结束——
```

### 元素类型

#### 行内元素

- 特点
  - 和其他元素（行内元素显示在同一行上）
  - **设置宽度无效**，默认为内容物的宽度
  - **设置高度无效**，但可以通过line-height实现
  - 设置**左右内外边距有效**，设置上下无效
  - 只能内嵌行内元素
    - 链接内不能再放链接但是（a）可以内嵌块级元素

![IMG_20221227_110427](https://thdlrt.oss-cn-beijing.aliyuncs.com/IMG_20221227_110427.jpg)

#### 块级元素

- 特点
  - 每个块级元素独占一行
  - 支持**高度宽度行高以及内外边距等的设置**
  - 宽度默认占父元素的100%
  - 可以内嵌其他元素
    - 文字类元素不能内嵌块级元素，如p，h1内不能放div

![IMG_20221227_110421](https://thdlrt.oss-cn-beijing.aliyuncs.com/IMG_20221227_110421.jpg)

#### 行内块元素

- 特点
  - 和其他元素显示在同一行上
  - 支持高度宽度行高以及内外边距的设置
  - 默认宽度是内容物的宽度
  - 可以内嵌其他元素
- 如img input

### 元素

- `<h1>~<h6>`：不同字号的标题

  - `<h1>text</h1>`

- `<p>`：定义段落（自动在前后创建空白）

  - `<p>text</p>`

- `<span>`：选择区间（可以用于包住一段内容，本身没有任何含义）

- `<img>`：插入图片

  - `<img src="img/1.png" alt="logo" width="256px" height="256px">`
    - src：图片路径(其他参数均可以省缺)
    - alt：图片无法显示时的替代文本

- `<a>`：插入超链接

  - `<a href="https://...">显示的名称</a>`
  - 除了href还有target属性
    - _blank：在新窗口中打开
    - _parent：在父窗口中打开，不存在则在当前窗口打开
    - _self：当前窗口打开（默认）
    - _top：在整个窗口打开
    - framename：指定框架打开

- `<meta>`：设置

  - 写在head里
  - `<meta char set="utf-8">`指定浏览器用utf-8显示文字
    - 源文件中保存为utf-8编码，再用utf-8打开，避免乱码
  - `<meta name="viewport" content=”width=device-width,initial-scal=1.0“>`自适应窗口缩放
  - 描述网站：搜索引擎优化
    - 关键词：`<meta name="keywords" content="">`
    - 描述：`<meta name="description" content="">`
    - 作者：`<meta name="author" content="">`
  - 网页跳转：倒计时跳转网页
    - `<meta http-equiv="refresh" content=5; https://...>`
      - content表示秒数

- `<style>`：定制样式（css样式）

  - 可以实现修改颜色、样式、添加背景等功能

  - 属性：

    - media：指定样式适用的媒体（如打印模式，投影仪模式，以及特定约束条件）
      - `media="print"`打印时的性质
      - `media="screen and (min-width:512px) and (max-with:1024px)"`窗口用于计算机模式且宽度处于一定范围时的性质
    - scoped：作用范围（一般不使用）
    - type：样式类型（默认为css也只有这一种）

  - ```
    <style type="text/css" media="">//参数可省略
    p{
      color: white;//把段落颜色改为白色
    }
    </style>
    ```

- `<link>`链接外部样式表（属性）

  - 可以将style内的内容单独作为一个css文件链接进来
  - `<link rel="" type="text/css" media="" href=""`
    - media与style相同
    - href为链接文件的地址
    - rel属性
    - ![](https://thdlrt.oss-cn-beijing.aliyuncs.com/16717852985051.jpg)

- `<base>`基准位置 

  - 补充
    - ./从当前目录开始
    - ../从上一级目录开始
    - /从根目录开始
  - 只会影响相对路径而不会影响绝对路径
  - 与超链接语法类似：`<base href="基准位置.../" target="打开方式">`

- `<script>`定义/引用脚本（配合js使用）（类比style）

  - 行内脚本
  - 内嵌脚本：`<script type="text/javascript">脚本</script>`
  - 引用外部脚本：`<script type="text/javascript" src="js文件链接"></script>`
  - 执行
    - 正常情况下html解析是单线操作的，遇到js脚本就会暂停文档解析，转而获取并执行js脚本，完成后回到文档解析。（即执行先后与script位置有关系）
    - 延迟执行：（全部解析完再执行脚本）`<script... defer>`添加defer属性
    - 异步执行：（解析与脚本执行同时进行）添加async属性，只对引用脚本起作用
  - `<noscript>...</noscript>`浏览器不支持js时显示的内容

### 常用标签

- 用正确元素做正确的事，从而实现语义化，功能相同，只是更好理解（考虑抓取源代码的爬虫）
- 注释
  - html：`<!-- 注释 -->`
  - css：`/**/`
- `<br>`换行
- `<hr>`水平分割线
- `<pre>`
  - 用pre元素包住会保留文本中的空白、制表符、换行符
  - 有些保留字符不能直接输出，需要使用其实体编号。
    - `“`：&#34
    - `‘`：&#39
    - `&`：&#38
    - `<`：&#60
    - `>`：&#62
    - ` `：&nbsp
- `<code>`
  - 在pre内再使用code，来呈现源代码
- `<var>`：程序变量
- `<kbd>`：用户输入
- `<samp>`：程序输出
- `<q>`：引用，会自动加双引号
- `<blokquote>`：引用多行（可以在里面嵌套<p>），会自动添加缩进
  - 对于具体的效果应该由css来
- `<cite>`：定义作品（如书籍、电影等）的标题
- `<abbr title="">...</abbr>`：定义简称或缩写（可以用title指定全称，鼠标移动到上面时会自动显示）
- `<dfn>`：突出术语
- `<address>...</address>`：定义文档或文章作者及其联系信息
- `<ruby>字<rp>(</rp><rt>拼音</rt><rp>)</rp></ruby>`：注音
  - rt元素标记注音符号（在文字上面显示）
  - 如果浏览器不支持，则会直接显示rp内的和rt内的内容（会在文字后面显示）
- `<bdo dir="rtl">...</bdo>`：从右向左颠倒显示
- 加粗
  - `<strong>`：突出重要文本
  - `<b>`：无语义
- 斜体
  - `<em>`：强调
  - `<i>`：无语义
- 删除线
  - `<del>`：表示删除
  - `<s>`：表示错误
- `<ins>`：下划线
- `<mark>`：高亮显示
- `<sub>`：以下标显示
  - sup上标显示
- `<small>`：缩小显示
- ![Snipaste_2023-01-01_22-47-10](https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2023-01-01_22-47-10.png)

### 结构

#### 列表

- 无序列表

  - ul表示无序列表，li表示项

  - ```
    <ul 属性>
          <li>...</li>
          <li>...</li>
          ...
    </ul>
    ```

- 有序列表

  - ol表示有序列表，li表示项
  - 属性：
    - reversed：反向编号
    - start：指定起始值
    - type：指定标记类型

- 自定义列表

  - 常用于对术语或名词进行解释或描述，列表前没有任何符号

  - 可以多对多

  - ```
    <dl>
      <dt>//条目
      <dd>//描述
    </dl>
    ```

    ![](https://thdlrt.oss-cn-beijing.aliyuncs.com/16717979251060.jpg)

- 可以使用css定义标记样式：list-style-type选择标记，list-style-image自定义图片

- 列表可以嵌套

- 去掉行前面的原点：`list-style: none`

#### 表格

- 基本格式:

```
<table>
    <caption>标题</caption>//可选
    <tr>//表示行
        <th>表头</th>//表头单元格
        ...
    </tr>
    <tr>
        <td>内容</td>//数据单元格
        ...
    </tr>
    ...
</table>
```

- th td支持跨行、跨列显示（合并单元格）

  - 使用关键词colspan rowspan实现
    - 跨行写在最左侧单元格的属性中
    - 跨列写在最上侧的单元格中
  - 如`<td rowspan="3">内容<..>`
  - 还要删除多余单元格

- 边框（css）

  - 如`th{border: 1px solid black;}`(table,th,td分别设置)
  - 合并边框：增加`th{border-collapse: collapse;}`

- 行分割

  - 使用`thead tbody tfoot`把表格分为三部分
  - 从而使用`thead th`等实现更细致的操作（包在tr th的外面）

- 列分割

  - 使用colgroup和col

  - ```
    <colgroup>
          <col style="">
          <col span="2" style...>
    </colgroup>
    ```

#### 表单

- 实现与用户的交互（form标签）

```
    <form action="处理文件(如welcome.php,处理表单数据的服务器程序的url地址，也可以是一个html文件地址)" method="post" target=“_blank”>//target表示新界面打开方式，与超链接类似
        题目：<input type="text" name="name"><br>//type表示变量类型，name表示名称
        ...
        <button type="submit">按钮名称</button>
    </form>     
```

- 提交方式有get和post

  - get会将提交的数据整合到url中，post更常用

- button

  - type属性
    - submit：提交表单内容到服务器，交由脚本处理
    - reset：清空输入框内的内容
    - button：点击后没有效果
  - 用`formmrthod="get"`属性单独设置提交方式

- 自动填充（让浏览器记住用户的选择）

  - 可以直接在form中全局设置也可以单独对每一条设置
    - 添加属性`autocomplete="on"`或者off

- 绑定

  - 用label绑定后点击前面文字就会自动跳转到后面的输入框
    - `<label>题目：<...></label>`
    - `<label for="name">题目</label>...<...id="name">`指定id值
      - 和input的先后顺序可以颠倒

- 分组：用方框划分表单

  - `<fieldset>...<fieldset>`包住
  - 对分区命名：在`<fieldset>`下添加`<legend>文字<legend>`

- 下拉列表（选项）

  - ```
    <label>题目：
    <select name="变量名">
      <option value="选项返回值">选项名称</option>//选项
      ...
    </select>
    </label>
    ```

  - `selected"selected"`默认选中项

  - 分组：`<optgroup label="标题">...</optgroup>` 

  - option中第一项为默认显示

- `oupput`输出

  - 如`<output name="" for="a b"></...>`输出a和b的值

- `textarea`多行文本输入

  - `<textarea name="">段落（默认输入）</textarea>`
  - 尺寸：属性`row col`
  - wrap属性
    - soft：在页面渲染中对文字自动换行，提交的不换行
    - hard：提交的也换行
    - off：渲染不自动换行

- 其他属性（针对单独的一项）

  - 默认值：`value=”“`
  - 自动聚焦：表单加载完成后光标会自动聚焦到指定的input`autofocus`
  - 禁用元素：添加`disabled`(不会提交这一部分的内容)
  - 只读：`readonly`

#### input功能扩展（通过设置type属性实现不同功能）

- text文本框

- password密码模式

- `reset button submit`和按钮的功能一致

  - 通过value的属性设置按钮上显示的文字

- `radio`单选框

  - `<label><input type="radio" name="" value="">男</label>`
  - 多个单选框使用同一个变量名可以实现联动（选项互斥）

- `checkbox`复选框

  - 与单选框类似

- 输入时间日期

  - `tiem`：时间
  - `date`：日期
  - `month`：年月
  - `week`：星期
  - `date time-local`：本地日期和时间

- `search`搜索

- `color`颜色

- `image`图像作为按钮

  - `<input type="image" src="路径" alt="">`
  - 还会自动传递点击点的相对坐标

- `hiden`隐藏不显示

- `file`上传文件

  - 上传文件需要在enctype中指定模式
    - 默认为`application/x-www-form-urlencoded`
    - 应该设置为`multiparty/form-data`
  - 给input添加accept属性限制上传文件的类型
    - 直接输入文件后缀名如`.png`
    - MIME类型描述，如`image/*`限定所有图像文件
  - 限制文件的尺寸
    - 增加一个隐藏的input的元素设置最大大小
    - `input type="hidden" name="MAX_FILE_SIZE" value="大小（字节）"`
  - 增加属性multiple实现多文件上传

- 数字输入

  - `number`数字输入
    - 范围限定：添加属性`min max step`step表示调整幅度
  - `range`滚动条模式
    - `val min max step`val设置初始值

- 邮箱电话网址

  - `email tel url`默认匹配不一定符合需求可以使用正则表达式自定义
  - `<input type="email" name="" pattern="正则表达死">`
    - 在提交表单时进行检查

- 属性

  - `placeholder`
    - 在输入框中给予用户提示
    - 添加属性`placeholder=""`
    - 颜色修改：`input::placeholder{color:pink;}`
  - `required`要求必须填入
  - `size`设置输入框长度
  - `maxlength`限制输入字符的数目
  - `name`inpute元素的名称
  - `value`inpute元素的值（默认值）
  - `checked="checked"`规定该元素默认被选中（用于单选框或复选框）   

- 列表选择

  - ```
    <input...list="id">
    ...
      <datalist id="">
      <option value="">...</option>
    ...
    </datalist>
    ```

### div和语义化布局

- 传统使用div对网页实现分区
  - 如`<div class="名称">内容</div>`
- 新标准凸显网页语义化（使用如`<nav>...</nav>`）
  - header：简介内容
  - nav：导航
  - main：主内容
  - artical：独立的文章内容（与页面其他部分）
  - section：文档中的节
  - aside：侧边栏
  - footer：页脚
  - details：额外细节
  - summary：定义details的标题（总结）
  - 可以嵌套使用，也可以带class关键字

### 嵌入元素

 - 图片

   - 可以实现点击图片不同区域实现分区跳转

     - 用map建立映射，用area定义映射区域以及对应跳转的url，再在img中使用对应的map

     - ```
       <img ...use map"#book">//必须要加个#
       <map name="book">
            <area shape="circle" cords="784,241,163" alt="" href="" target="">//或分区域并跳转到不同地址，shape可以选择circle，poly(多边形)，rect(矩形)；coords设置区域的大小
       ```

     - 使用picture内嵌source，根据条件匹配不同的图片

       - ```
         <picture>
           <source media="min-width: 1024px" srcset="路径">//media设置条件
           ...
           <img...>//浏览器不支持picture时会直接显示img
         </picture>
         ```

     -  插图

        - ```
          <figure>
            <img...>
            <figcaption>插画标题</figcaption>
          </figure>
          ```

 - 视频

   - `<video width="" height="" src="">视频无法播放时显示的文字</video>`

   - 常用MP4格式

   - 播放控件：controls

   - 自动播放：autoplay

   - 静音：muted

   - 视频预加载：preload

     - auto：要求浏览器尽快加载整个视频
     - metadata：只加载视频的元数据
     - none：不加载

   - 视频封面：`poster="封面地址"`

   - 不同条件下播放不同视频

     - 在video内包住多个source

   - 字幕

     - 常用vtt格式文件

       - ```
         00:00:09.250 --> 00:00:11.170//显示的时间区间
         字幕内容
         ...
         ```

     - 使用时在video内增加track

       - `<video><track src="...vtt" srclang="ch(语言)" label="中文字幕" kind="subtitles" default(设置为默认)>...</video>`

- 音频

  - 常用MP3格式
  - `<audio src="" control>`
  - 也有自动播放等属性，与video类似

- 网页

  - `<iframe src="" width="" height="">不支持iframe时显示的内容</iframe>`
  - sandbox属性：限制内嵌网页的权限

- 进度条类型

  - meter：min：最小值 max：最大值 low：较小的值 high：较大的值 optimum：最佳的值 value：默认值；在不同范围显示样式不同
    - `<meter id="" min=""...></meter>`
  - progress：仅有max和value

## 补充

### Canvas 绘图

- Canvas 就是一个画布，主要用于图形表示、图表绘制、游戏制作等。
- 结合js实现图形的绘制[HTML5 简明教程 - HTML5 Canvas API - 蓝桥云课 (lanqiao.cn)](https://www.lanqiao.cn/courses/43/learning/?id=19130&compatibility=true)

### Web Storage 本地存储

- 使用Cookie存储效率均较低，因为cookie总是在服务器和浏览器之间传送，Web Storage的存储空间较大（5-10mb），内容只存储在本地客户端，是持久化的本地存储

#### local storage

- 数据的存储

```javascript
//方法1向本地存储中添加一个名为name,值为"syl"的key-value对象
localStorage.setItem("name", "syl");
//方法2
localStorage["price"] = 1314;
//方法3
localStorage.amount = 520;
```

- 数据的获取`localStorage.getItem(key);`
- 数据的删除

```javascript
localStorage.clear()//全部删除
localStorage.removeItem(key);
```

#### session storage

- 将数据保存在 `session` （会话）对象中，用户在**浏览某个网站时**，从进入网站到关闭浏览器的这段时间，`session` 对象可以用来保存在这段时间内所要求保存的任何数据。是会话级的本地存储，浏览器关闭时数据会被删除

```javascript
<script type="text/javascript">
    if (sessionStorage.pagecount) {
      sessionStorage.pagecount = Number(sessionStorage.pagecount) + 1;
    } else {
      sessionStorage.pagecount = 1;
    }
    document.write("你刷新了本页面 " + sessionStorage.pagecount + " 次");
  </script>
```

# css

## 如何使用

![](https://thdlrt.oss-cn-beijing.aliyuncs.com/16718747989552.jpg)

- 内联样式
  - html元素都有一个style属性，可以直接对其进行赋值
  - `<p style="color red;">`
- 内部样式表
  - 用style在头部定义
- 外部样式表
  - 用link引入
- 优先级：内联>内部>外部

## 书写顺序（规范）

- 布局定位属性：display / position / float / clear / visibility / overflow（建议 display 第一个写，毕竟关系到模式） 
- 自身属性：width / height / margin / padding / border / background 
- 文本属性：color / font / text-  decoration / text-align / vertical-align / white- space / break-word 
- 其他属性（CSS3）：content / cursor / border-radius / box-shadow / text-shadow / background:linear-gradient

## 三大特性

### 层叠性

- 如果样式重复设定并且发生冲突，后面的样式会覆盖前面的样式，即后来者居上

### 继承性

- 子标签会继承父标签的**某些样式**，如文本颜色和字号。
  - text-，font-，line-这些元素开头的可以继承，以及color属性等
- 特殊
  - 行高：
    - 如果父亲定义行高时没有写明单位，则子元素的行高为子元素的文字大小*1.5
    - 如果写明了单位则会直接继承

### 优先性

- 当同一个元素指定多个选择器，就会有优先级的产生。选择器相同，则执行层叠性；选择器不同，则根据选择器权重执行

![Snipaste_2022-12-30_14-20-59](https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2022-12-30_14-20-59.png)

- 数字1越靠左权重越高
  - 对于复合迭代器权重相加，如body h1#myID权重为（1，0，2）
- 再css属性后面加上！important可以使得属性具有最高的优先级
  - `color: pink!important;`
- 特殊
  - a默认样式的优先级高于继承

## 选择器

### 基本选择器

- 通用选择器：`* {...}`多所有html元素操作
- 元素选择器：如`p{}`对一类元素操作
- 类选择器：对具有指定class属性的元素进行操作
  - `.xxx {}//前面一定要加.`
  - `<p class="xxx"> `
    - class属性可以定义多个类名，之间用空格隔开
  - 不同元素的calss属性可以相同
- id选择器：与class相比id属性是唯一的，只能指代单个元素
  - `#xxx {}//前面要加#`

### 复合选择器（由多个选择器复合）

- 交集选择器：
  - `元素选择器.类选择器`｜`元素选择器#id选择器`
- 并集选择器
  - `选择器1, 选择器2, 选择器3`
- 后代选择器
  - `选择器1 选择器2 选择器3`
  - 先匹配选择器1再从匹配元素的后代中找匹配选择器2的元素...
  - **不需要**是直接后代
- 子元素选择器
  - `选择器1 > 选择器2`
  - 只匹配**直接子元素**
- 相邻兄弟选择器
  - `选择器1 + 选择器2`（选择器2才是真正的目标）
  - 匹配具有相同父元素，且紧跟在选择器1元素后面的选择器2元素
- 通用兄弟选择器
  - `选择器1 ～ 选择器2`
  - **不需要紧跟**，具有相同父元素即可

### 伪元素选择器

- `::first-line`
  - 匹配所有文本块（块级元素）的第一行
  - `p::first-line`p元素的第一行
- `::first-letter`
  - 匹配文本块的第一个字符
- `::before`
  - 生成新内容插入到指定位置的前面/后面，使用content（前后是相对元素a的，生成的元素是a的孩子）
    -  before 和 after 创建一个元素，但是属于行内元素（如在所有p标签的文件开始处加上'"<"）
  - 如`a::before {content: "..."}`（a和冒号之间不要有空格，表示给a元素添加伪元素选择器）
  - 也可以添加文本以外的内容如`content: url(...)`
  - content表示插入的内容，必须有该属性
  - `.a:hover::before`：鼠标经过a时对before操作
- `::after`后面
- `::selection`
  - 对用户选中的文本的操作

### 伪类选择器

#### 动态伪类选择器

- 前四项常与超链接（a）联用
  - 可以实现不同状态时的不同样式
- `:link`
  - 未访问过链接
  - 如bg1:link（之间不要有空格）
- `:visited`
  - 访问过链接
- `:hover`
  - 鼠标悬停在链接上方
  - 也常用于div元素
- `:active`
  - 单击链接
- 必须按照l v h a的顺序书写
- `:focus`
  - 比如输入框被选中时，常用于表单元素
- tip：伪选择器可以在冒号前面加元素作为限定，前面也可以是复合选择器如`input#girl:focus` 

#### UI伪类选择器

- 可用|禁用
  - `:enabled `|`disabled`
- 选中
  - `:checked`
- 必填｜可选
  - `:required`|`:optional`
- 默认元素
  - `:default`
- 输入合法性
  - `valid`|`invalid`
- 是否在范围内（如number是否在min与max之间）
  - `in-range`|`out-of-range`
- 是否只读
  - `read-only`|`read-write`

#### 结构伪类选择器

- `:root`：匹配根元素
- `:empty`：匹配没有定义任何内容的元素（如`<p></p>`）
- `:first-child`：所有元素中的第一个子元素
  - `p:first-child`：匹配父元素中第一个子元素p（要求p**必须是**第一个子元素）
- `:last-child`：最后一个子元素
- `:only-child`：唯一子元素（即一个元素是其父元素的唯一子元素）
- `:nth-child()`：第n个
  - 用括号传参数：`p:non-child(3){...}`
  - 除了填入数字外还可以是关键字
    - odd奇数even偶数
  - 还可以填入公式
    - :nth-child(n)：n从0开始每次加一（如果填入n会选择全部子元素）
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2023-01-01_23-22-40.png" alt="Snipaste_2023-01-01_23-22-40" style="zoom: 67%;" />
- `:nth-last-child()`：逆向
- `child`替换为`of-type`：匹配父元素下唯一指定类型的子元素
  - 如`p:first-of-type`作为父元素下第一个p元素的元素（p中的第一个，**但不一定是第一个子元素**）
- nth-child 对父元素里面所有孩子排序选择（序号是固定的） 先找到第n个孩子，然后看看是否和E匹配 ；nth-of-type 对父元素里面指定子元素进行排序选择。 先去匹配E ，然后再根据E 找第n个孩子

#### 其它伪类选择器

- `:target`：匹配锚点(在页面内跳转时执行)
  - 锚点指跳转点：`<p id=target1>text</p>`设置id
  - 用a实现跳转：`<a href="#target1">...</a>`#加id
- `:lang`：匹配设置了lang属性的元素
  - `:lang(zh){...}`需要参数
  - lang指语言，如`lang="zh"`
- `:not`：反向选择器
  - `:not()`可以对任意选择器实现反向匹配

#### 伪类选择器和伪元素选择器的区别

- 伪类选择器是为了已有元素处于某个状态时为其增加样式；伪元素选择器用于创建一些文档数中不存在的元素，并为其添加样式

### 属性选择器

- 针对属性名或属性值来进行匹配
- `[attr]`：匹配定义了attr属性的元素，不考虑值
- `[attr="val"]`：值为val
- `[attr^="val"]`：值以val开头
- `[attr$="val"]`：值以val结尾
- `[attr*="val"]`：值包含val字符串
- `[attr~="val"]`：值为val（可以有多个属性值，只要其中一个为val即可）
- `[attr|="val"]`：由连字符分割，且val位于前面（如：val-xxx）

## 样式属性

### 颜色与背景

- 前景色（文字颜色）：使用color属性设置
  - 使用名称使用颜色：如red blue
  - 使用rgb（红绿蓝）表示：如`rgb(255,0,0)`
  - HEX:将rgb转化为十六进制数（两位十六进制数可以表示0~255）：如`#ff0000`
  - rgba:增加一个参数表示不透明度（0~1表示）
  - 默认为transparent（透明）
- 背景色
  - background-color
- 三种长度单位
  - px：像素
  - em：几个文字的长度
  - %：占元素大小的百分比
- 背景图像：`background-image: url('地址');`
  - 背景图像默认会覆盖背景色
  - 可以指定多个背景图像，之间用逗号分隔即可，在前面的会覆盖在后面的
  - 默认情况下会自动复制覆盖整个界面：参数`background-repeat`
    - repeat（默认）：沿水平竖直同时复制
    - repeat-x repeat-y：单方向复制
    - space：沿水平或竖直方向复制，通过调整间距防止图片被裁切
    - round：沿水平或竖直方向复制，通过调整大小防止图片被裁切
  - `background-position: 10px 50px;`：让图像与元素左侧保持10像素距离，与元素右侧保持50像素距离，x在前y在后
    - 其他参数：
    - （right/center）left top：对齐元素左上角（九宫格位置）
    - left center：对齐元素左侧（方位无顺序）
      - 省略一个方位参数时会默认这个为center
    - left bottom：对齐左下角
    - x% y%（x y）：控制图像相对于元素的具体位置
  - `background-size`：
    - auto（默认）：按照原始尺寸显示
    - x y：设置宽高
    - x% y%：设置宽高占父元素的百分比
    - cover：覆盖全部（可能拉伸或裁剪）
    - cotain：确保图像完整显示
  - `background-attachment`：附着方式
    - scorll：随页面滚动
    - fixed：固定
    - local：随元素中内容滚动
  - `background-origin`：开始绘制的位置
    - padding-box：从内边距左上角
    - border-box：从边框左上角
    - content-box：从内容左上角
  - `background-clip`：显示区域
    - padding-box：显示区域包含内内边距和内容区域
    - border-box：边框、内边距和内容区域
    - content-box：仅内容区域
- 实际上可以直接将所有属性写在background后面（包含背景色，背景图片及其属性）
  - `background: gray url() no-repeat ` 

### 盒子模型

- 外边距（边框与其他元素间的空白区域）-边框-内边距（内容与边框间的空白区域）-内容

![box-model](https://thdlrt.oss-cn-beijing.aliyuncs.com/box-model.gif)

#### 边框

- `border-style`：样式
  - none：无
  - solid：实线
  - dashed：虚线
  - dotted：圆点
  - double：双线
  - groove：3d槽
  - ridge：3d脊
  - inset：3d内凹
  - outset：3d外凸
  - hidden：隐藏
- `border-width`：宽度
  - thin medium thick
  - 具体值如：10px
- `border-color`：颜色
  - 在设置宽度与颜色之前必须先指定边框的样式
- border的属性也支持像背景那样的简化格式
- border-top(right bottom left)-... 实现对四个方向的独立设置
  - 缩写：如对于border-color
    - 输入一个值则四个方向属性相同
    - 输入两个值上下一组，左右一组
    - 输入三个值依次是：上、左右、下
    - 输入四个则    按顺时针顺序赋值
- `border-radius`：圆角边框
  - `border-top-left-radius | border-bottom-right-radius`对四个角单独设置
  - 一个角有两个数据组成`15px 15px`表示圆角边框水平方向半径和竖直方向半径
  - 如果直接`border-radius apx bpx`：表示左上右下为`apx apx  `，右上左下为`bpx bpx`
  - `border-radius apx / bpx`：才表示所有角都为`apx bpx`
  - 一次指定四个圆角`border-radius a1px b1px c1px d1px / a2px b2px c2px d2px `
- 图像边框
  - `border-image-source`：图像来源
  - `border-image-slice`：切分图像
    - 将图像切分为9块，除中间外作为边框的边和角
    - 如图像尺寸为90*90则之应为30
  - `border-image-width`：宽度
  - `border-image-outset`：起始偏移
    - 表示从元素向外扩展多少的位置开始绘制
  - `border-image-repeat`：图像重复方式
    - stretch：拉伸
    - repeat：重复，可能截断图像
    - round：适当拉伸，并重复，不截断图像
    - space：适当保持间距，并重复，不截断图像
  - `border-image`：缩写使用
- `border-collapse: collapse;`合并表格（相邻）边框

#### 内边距、外边距

- padding：内边距

  - 使用：`padding-top right bottom left`：分别设置，或缩写同意设置

- margin：外边距

  - 属性与padding及border一致
  - `margin: 0 auto;`：实现自动居中
    - 必须是块级元素且设置了宽度（不然默认为一整行的宽度）
    - 行内元素/行内块元素居中：给其父元素增加属性`text-align:center`
  - 塌陷
    - 如果相邻的两个块级元素设置了外边距，则会发生塌陷，两元素的间距为两元素外边距中的较大值（而不是和）
    - 嵌套两个块级元素也可能发生两个元素公用外边距而发生塌陷
    - 可以通过分隔BFC实现

- 许多元素可能有默认的内外边距

  - 可以通过通配符选择器清楚

  - ```html
    * {
    	padding: 0;
    	margin: 0;
    }
    ```


  #### 元素尺寸

  - 元素实际尺寸=内容尺寸+（内边距+边框+外边距）*2
    - `boxsizing`属性：
      - `content-box`：指定内容的宽高
      - `padding-box`：指定包含内容和内边距的宽高
      - `border-box`：指定包含边框、内容和内边距的宽高
      - `margin-box`：指定包含外边距、边框、内容和内边距的宽高
  - 设置最大最小尺寸
    - min-width
    - max-width
  - 限制元素尺寸时可能发生溢出（设置大小装不下）
    - overflow
      - auto：自动解决，通常添加滚动条
      - hidden：裁掉溢出的内容
      - scroll：添加滚动条
      - visible：不管是否溢出都显示所有值（默认）
    - resize（overflow不为visible时有效）
      - none：不允许用户调整元素的尺寸（默认）
      - both：允许调整长宽
      - horizontal：只允许宽
      - vertical：只允许高

  #### 轮廓、阴影

  - outline 轮廓
    - 属性
      - outline-style：（与border一致）
      - outline-color
      - outline-width
      - outline-offset：与边框之间的偏移量
    - 轮廓不属于元素尺寸的一部分不会影响原页面的布局
    - 轮廓始终是方的
  - box-shadow：阴影
    - box-shadow-属性：
      - hoffset：阴影的水平偏移量（正数代表向右偏移）
      - voffset：垂直偏移量（正数向下偏移）
      - blur：模糊值
      - spread：阴影延伸半径
      - color
      - inset：设置该值表示内部阴影
    - 缩写如`0 0 0 10PX #248f8f`
      - 可以指定多个阴影之间用逗号分隔
    - 阴影的形状与边框保持一致
  - text-shadow: 文字阴影，属性类似

  ## 布局

  ### 基础操作

  #### 控制元素可见性visibility

  - visible：元素在页面上可见
  - hidden：元素不可见但是占据空间
  - collapse：不可见，不占据空间
  - inherit：继承父对象的可见性（默认）

  #### 改变元素显示类型display

  - 每个元素都有一个display属性，决定元素的显示类型（如行内元素还是块级元素）

    - 可以通过自定义display属性覆盖默认的样式

    - 对于有大小的块级元素通过`text-align: center;`实现文本水平居中，通过`line-height`设置为与height一致来实现垂直居中

    - 属性

      - inline：设置为行内元素
      - block：设置为块级元素（也可以用于显示隐藏的元素）
      - line-block：设置为行内块元素
      - none：隐藏元素（不占位 ，直接移除）
      - 还可以设置为其他样式，如列表项样式等

    - ```css
      .tudou:hover .mask {//鼠标经过土豆盒子时让mask盒子显示出来
         display: block;
       }
      ```

  #### 浮动

  - float
    - 先用标准流的父元素排列上下位置，之后内部子元素采取浮动排列左右位置
    - 可以实现多个块级元素横向排列，比行内块更好，因为行内块无法控制块之间的间距
    - 如果多个盒子都设置了浮动，则它们会按照属性值一行内显示并且顶端对齐排列
      - 一般来说一个元素浮动了，其他的兄弟元素也要浮动

    - 属性
      - none
      - left
      - right
    - 使用flaot会将大部分类型的元素自动转化为块级元素
    - 浮动的元素或脱离正常的文本流，即不再占有原来在文本流中的位置（比如可能下一行的元素会上浮，占据原先的位置）
      - 浮动的盒子只会影响后面的标准流，而不会影响前面的标准流

    - 实现左右排列则直接一个设置为left一个right，且宽度设置为50%（由于可能有内外间距因此要选择合适的大小模式，确保左右分别占据一半的空间）
    - 实现三列排列则left left right即可，由于最左侧已经被占据，第二个left会自动放置在中间

  - 清除浮动 clear（可以用来解决脱离正常文本流的问题）
    - 一个盒子内可能有很多元素，因此盒子的高度难以确定，而如果不显示指出盒子的高度，由于子元素都是浮动的，盒子的高度会默认为零，这就需要清除浮动来解决
      - 如果父盒子本身有高度，则不需要清楚浮动，清除浮动后，父级就会根据浮动的子盒子自动检测高度，父亲有了高度就不会影响下面的标准流的布局了

    - 属性
      - left：清除左侧的浮动
      - right
      - both

    - 用法：
      - 额外标签法：在div最后面加一个具有clear:both属性的空div
      - 给父元素添加`overflow: hidden;`属性

  - 用普通元素对浮动元素标识是没有效果的
    - 如用div包住再设置属性是不会生效的
    - 最好的解决方法是将div创建为一个新的BFC
      - 添加overflow: hidden属性

  #### position定位

  - 先使用position属性设定好工作方式，再通过top、bottom、left、right来实现定位
    - static：正常布局，top等不会生效（默认）
      - 按照标准流特性摆放位置
    - relative（相对定位）：相对于默认位置的重新定位
      - 原来的标准流的位置继续占有，后面的盒子以标准流对待它
    - absulute（绝对定位）：相对于最近一个设置了position属性的值的祖先元素重定位
      - 没有祖先元素或者祖先元素没有定位则以浏览器为基准
      - 绝对定位会失去原先在标准流中的位置，脱离标准流
    - fixed：相对于浏览器可视窗口重定位（不随网页滚动）
      - 贴在版心旁边：让固定定位的盒子left50%走到版心中央，再margin-left版心宽度一半的距离，多走版心宽度的一半位置，正好贴在版心的右侧
    - sticky：结合absolute和fixed（随页面滚动但即将离开页面时会固定住）
      - 一浏览器的可视窗口为参照点移动元素
      - 粘性定位占有原先的位置
      - 需要top/bottom/left/right属性，表示到达一个位置后固定住
  - z-index：解决重合时显示的图层问题
    - 数值越大，图片在层叠中的位置越高（显示在最上面）
  - 也可以用于实现多列布局
  - 通常父亲需要占有位置，使用相对定位；子盒子不需要占有位置，是绝对定位
  - 浮动不会压住标准流的文字，而绝对和相对定位会

  #### BFC块级格式化上下文

  - BFC内部的元素变动不会影响到外部
    - 可以实现阻止文字环绕（使得浮动项和文字不在一个BFC中）
  - BFC内部所有块级元素都是左对齐的（父元素的左侧），在同一个BFC每个块级元素都会独占一行（内外间距存在塌陷）
  - 创建新的BFC
    - float不为none
    - position为absolute或fixed
    - overflow不为visible（常用`overflow: hidden;`创建）

  #### 居中

  - 行内元素：

    - 将父元素的text-align设置为center
    - 将行内元素的line-height设置为其父元素的height属性的值

  - 块级元素

    - margin左右边距设置为auto实现水平居中
    - position设置为absolute，position四个属性设置为0，margin设置为auto，同时实现水平垂直居中
      - 由于祖先中没有设置position属性，因此会根据浏览器实现居中 
      - 法二：先left:50%再margin-left负盒子的一半宽度（垂直居中同理）

  - #### column实现多列布局

    - column-count：列数
    - column-width：列宽度
      - 为列的最小宽度，如果浏览器的宽度不嫩那个满足时就要通过减少列的数目来实现
    - columns：缩写
    - column-gap：列间距
    - column-fill：内容分布方式
      - balance：均匀填充
      - auto：从左到右按顺序填充
    - column-span：指定元素可以横跨多少列
      - all表示可以横跨所有列
    - column-rule-color：列之间的颜色
    - column-rule-style：列之间的样式
    - column-rule-width：列之间的宽度
    - column-rule：缩写（列间距样式）

  ### 经典布局类型

  #### 单列布局

  - 包含上中下三部分

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Title</title>
    <style>
      header, main, footer {
        max-width: 1024px;
        margin: 0 auto;
        text-alogn: center;
      }
      header{
        height: 50px;
        line-height: 50px;
        background-color: pink;
      }
      main{
        height: 200px;
        line-height: 200px;
        background-color: cornsilk;
      }
      footer{
        height: 50px;
        line-height: 50px;
        background-color: lightblue;
      }
    </style>
  </head>
  <body>
    <header>头部</header>
    <main>内容</main>
    <footer>尾部</footer>
  </body>
  </html>
  ```

  #### 两列布局

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Title</title>
    <style>
      .box{
        max-width: 1024px;
        margin: 0 auto;
      }
      .left{
        width: 50%;
        padding: 20px;
        box-sizing:border-box;
        background-color: pink;
        float: left;
      }
      .right{
        width: 50%;
        padding: 20px;
        box-sizing: border-box;
        background-color: lightblue;
        float: right;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="left">
        <p>text1</p>
      </div>
      <div class="right">
        <p>text2</p>
      </div>
    </div>
  </body>
  </html>
  ```

  #### 三列布局

  - 浮动法
    - 左侧向左浮动，右侧向右浮动，中间通过设置margin避开覆盖
  - 绝对定位法
    - 左右设置position：absolute固定于左右两侧，中间通过margin避免覆盖
  - 负外边距法

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Title</title>
    <style>
      .container{
        width: 100%;
        float: left;
      }
      .center{
        height: 500px;
        margin: 0 200px;
        background-color: cornsilk;
      }
      .left{
        width: 200px;
        height: 500px;
        float: left;
        margin-left: -100%;
        background-color: pink;
      }
      .right{
        width: 200px;
        height: 500px;
        float:left;
        margin-left: -200px;
        background-color: lightblue;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="center"></div>
    </div>
    <div class="left"></div>
    <div class="right"></div>
  </body>
  </html>
  ```

  #### 双飞翼布局

  - 与三列布局类似，仅在上下增加header与footer

  #### 圣杯布局

  - 外观与双飞翼接近，只是编写方式不同

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>Title</title>
    <style>
      main{
        padding: 0 200px;
      }
      .center{
        float: left;
        width: 100%;
        height: 500px;
        background-color: cornsilk;
      }
      .left{
        width: 200px;
        height: 500px;
        float: left;
        position: relative;
        margin-left: -100%;
        right: 200px;
        background-color: pink;
      }
      .right{
        width: 200px;
        height: 500px;
        float: left;
        position: relative;
        margin-left: -200px;
        left: 200px;
        background-color: lightblue;
      }
    </style>
  </head>
  <body>
    <main>
      <div class="center"></div>
      <div class="left"></div>
      <div class="right"></div>
    </main>
  </body>
  </html>
  ```

  #### 瀑布流布局

  - 如电商页面常用

  - 使用column划分为三列来完成

  ### 弹性盒布局

  - 可以适应不同名目大小以及不同的设备
  - 由弹性容器与弹性元素共同组成
    - 弹性容器的定义：`display: flex;`表示弹性容器以块级元素存在（会占满一整行）
      - `display: inline-flex`表示弹性容器以行内块的形式存在，相对来说显示的更加灵活，会根据元素数目和大小自动改变
    - 弹性容器的直接子元素会变成弹性元素
    - 块级元素（如div）变为弹性元素会失去一部分的性质：不再独占一行，也不会塌陷
  - 浏览器窗口较小时无法在一行显示所有的元素，会发生溢出
    - flex-wrap属性
      - nowrap：不自动换行（默认)
      - wrap：自动换行
      - wrap-reverse：反向自动换行（垂轴方向反转）
  - flex-direction排列方向
    - row：水平排列（默认）
    - column：垂直排列
    - row-reverse（主轴方向反转）
    - column-reverse
    - flex-flow是wrap和direction的缩写 
  - justify-content主轴上对齐
    - flex-start：弹性元素仅靠主轴起边
    - flex end：终边
    - center：居中
    - space-between：第一个元素仅靠起边最后一个仅靠终边，其他均匀排列
    - space-around：均匀排列，元素间距不折叠
    - space-evenly：均匀排列，间距折叠
  - align-items垂轴上对齐
    - stretch：拉伸以占据整个垂轴
    - flex-start：仅靠垂轴起边
    - flex-end：仅靠垂轴终边
    - center：居中
    - baseline：向基线看起
  - align-self设置单独一个元素在垂轴上的对其
    - 与zlign-items不同的是，self不是在容器中设定，而是在弹性元素中设定
  - align-content多行弹性元素的对齐方式
    - flex-start：弹性元素仅靠主轴起边
    - flex end：终边
    - center：居中
    - space-between：第一个元素仅靠起边最后一个仅靠终边，其他均匀排列
    - space-around：均匀排列，左右两侧没有外边距
    - space-evenly：均匀排列，左右两侧留下外边距
  - order调整显示顺序
    - 所有元素的order默认为0
    - 该属性值越小，相应的元素排列的越靠前
  - flex-shrink压缩比例
    - 每个元素默认值为1，当弹性容器空间不够时所有元素会等比例压缩
    - 设置为零表示该元素不参与压缩
    - 设置为2则表示压缩比例为1的元素的二倍
    - 实际压缩比例收到元素本身性质（存在一个不能再压缩的最小大小）
  - flex-grow放大比例
    - 容器中有多余空间时放大元素
    - 值为0表示不会放大
  - flex-basis初始尺寸
    - 默认为auto
    - 指的是元素在主轴上的（长度）大小
    - grow shrink basis可缩写为flex
  - 弹性元素无法移动
    - 可以通过绝对定位（position：absolute）强制移动元素的位置 

  ### 栅格布局

  - 栅格容器：

    - display属性为：grid或inline-gride

  - 栅格轨道（行和列）

    - `grid-template-columns: 200px 50% 100px`有几个参数表示有几行，参数表示行的宽度
    - `grid-template-rows`
    - fr关键字用于按比例分配剩余空间
      - 如`1fr 2fr`
    - auto关键字让浏览器自己计算所需要的空间
    - min-content表示尽量少占用空间；max-content表示占据较大空间，尽可能让所有文本在一行里显示
    - rpeat(3, 10px)表示重复3个10px与`10px 10px 10px`等价
      - repeat(auto-fill, 200px)让浏览器自己决定单元格的数目，通过增加无内容列来填充剩余空间
      - autofit通过增加每一列的宽度来填充剩余空间
    - minmax(100px, 300px)输入一个区间让浏览器做出选择
    - fit-content(10px)传入一个大小，系统会在指定的值与最小值中选择一个恰当的值

  - `grid-template-areas`定义栅格区域

    - ```html
      grid-template-areas:
      	'nav header header header aside'
      	'nav main mian mian aside'
      	'nav footer footer aside'
      ```

    - 留空区域用一个或多个.表示

    - 缩写grid-template

      - row 写在每一行末尾（引号后面）
      - column写在最后面，与row用/隔开

  - grid-column-gap和grid-row-gap用于定义栅格间距

    - 缩写为grid-gap

  - 栅格对齐（以justify为例表示横向，align表示纵向）

    - `justify-content`栅格布局中栅格元素的对齐方式
      - start center end
      - space-between紧贴起边终边均匀排列
      - space-around均匀、不折叠
      - space-evently均匀、折叠
    - `justify-items`对其栅格元素里的内容，即内容相对于栅格元素自身的对齐
      - start center end
      - baseline基线对其
      - stretch拉伸填充
    - `justify-self`单个元素的对齐（详单于item的单数形式）
    - place-content items self是缩写（先align后justify）

  - 栅格线

    - 可以对栅格线命名，默认为1 2 3...可以一条线有多个名字，之间用括号分隔开
      - `	grid-template-column: [first apple] 1fr [banana] 2fr`
    - 将栅格元素放置到指定的位置
      - `grid-column-start: first; grid-column-end: banana;`以及`grid-row-start  grid-row-end`为元素划分空间起始位置
        - 可以相互覆盖（重叠）
        - 省略结束位置则默认为开始位置的下一条栅格线
      - grid-area缩写`grid-area: grid-column-start / grid-row-start / grid-column-end /  grid-row-end; `

  - 修改重叠区域层级关系

    - z-index提升高度
    - order修改重叠的顺序

  - 放置规则（元素自动填充的规则）

    - grid-auto-flow
      - row按照行优先的顺序填充（默认）
      - column列优先
      - dense紧密填充
      - row dense行优先紧密填充
      - column dense列优先紧密填充
    - grid-auto-columns和grid-auto-rows用于控制在栅格之外的栅格元素的尺寸

  ### 文本属性

  - text-align文本对齐

    - start：使文本对齐书写的起始位置
    - end：对齐结束位置
    - left center right
    - justify使文本两端对齐

  - white-space保留空白字符

    - normal：空白字符被压缩，文本自动换行（默认）
    - nowrap：压缩，不自动换行
    - pre：保留，只在遇到换行符时换行
    - pre-line：压缩，一行排满或遇到换行符时换行
    - pre-wrap：保留，一行排满或遇到换行符时换行

  - 文本方向

    - `direction: rtl;（放到右侧）unicode-bidi: bidi-override;（文字从右向左颠倒显示）`
    - writing-mode
      - horizontal-tb：从左到右流动，从上到下换行
      - vertical-rl：从上到下流动，从右往左换行
      - vertical-lr：从上到下流动，从左到右换行

  - text-indent缩进

    - 表示缩进大小（如2em）
      - em为相对大小，1em为一个文字的大小 

  - 设置文字间距

    - letter-spacing：字母间距
    - word-spacing：单词间距
    - line-height：行高
      - 通常行高不写单位，对于不同字号的文字，具体单位大小有浏览器自行决定

  - vertical-align纵向对齐(可以把属性丢给行内块元素如图片，实现图片与文字对齐)

    - 块级元素没有该属性
    - baseline：与父元素的基线对齐（使用基线对齐内图片下面会保留白边（对应字母基线以下的部分），可以通过改变对齐方式去掉）
    - sub：与下标对齐
    - superp：与上标对齐
    - text-top：元素顶部与父元素字体顶部对齐
    - text-bottom
    - middle
    - top与整行顶部对其
    - bottom

  - text-shadow阴影

    - 四个值分别为水平偏移量、垂直偏移量、（模糊值、颜色）

  - 断词

    - 防止单词长度超出元素宽度，导致文本溢出

    - word-break设置为break-all自动断词

    - 防止溢出

      - white-space设置为nowrap设置为不自动换行（很可能会发生溢出）

      - 单行省略号：添加`white-space: nowrap; overflow: hidden; text-overflow: ellipsis`时会自动防止文本溢出，过长部分显示...（三步操作）

      - 多行省略号：

      - ```css
        overflow: hidden;
        text-overflow: ellipsis;
        /* 弹性伸缩盒子模型显示 */
        display: -webkit-box;
        /* 限制在一个块元素显示的文本的行数 */
        -webkit-line-clamp: 2;
        /* 设置或检索伸缩盒对象的子元素的排列方式 */
        -webkit-box-orient: vertical;
        ```

  - text-decoration装饰文本（添加上划线、删除线、下划线）

    - 是四个属性的缩写：text-decoration-line；text-decoration-thickness；text-decoration-style；text-decoration-color
    - text-decoration-line：（线的位置）
      - none不添加任何线（也可以用于取消超链接自带的下划线）
      - overline添加上划线
      - line-through删除线
      - underline下划线
    - text-decoration-thickness表示粗细
    - text-decoration-style线条样式
      - solid实线
      - double双实线
      - dotted点线
      - dashed虚线
      - wavy波浪线
    - text-decoration-color线条颜色

    - 如`underline 2px wavy red`

  - texttransform大小写转化

    - uppercase：所有字母转化为大写字母
    - lowercase：所有字母转化为小写字母
    - capitalize：所有字母首字母转化为大写字母

  - 设置字体

    - font-family：指定使用的字体
      - 如过字体名称中间有空格，用单引号包住，如`font-family: 'Courier New', cursive`，可以用逗号连接多个字体，浏览器依次选择（选择用户电脑已经安装了的字体）
    - font-size：字号大小
      - xx-small x-small small medium large x-large xx-large
      - 也可以用像素大小表示（谷歌浏览器默认16px）
    - font-weight：字体粗细
      - lighter normal（400） bold（700） bolder 或 100,200,300,400,500,600,700,800,900（无单位）
    - font-style：字体样式
      - italic斜体
      - normal
    - font-variant:
      - small-caps小型大写字母显示
    - font缩写
      - 依次style weight size family

  - 使用web字体，用户访问页面时自动下载

    - ```html
      @font-face{
      	font-family: "字体名";
      	src: url("资源路径");
      }
      ```

    - 之后和普通字体一样正常使用即可，可也防止用户缺少字体而显示失败

  ### 渐变

  - linear gradient线性渐变

    - 需要指定渐变方向（默认为从上到下）、起始颜色、结束颜色：`linear-gradient(direction, red, blue)`
      - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/IMG_20221228_163150.jpg" alt="IMG_20221228_163150" style="zoom: 25%;" />

    - 也可以指定多种颜色，会在渐变中均匀分配
      - 颜色后面添加百分值，定义颜色出现的位置，如blue20%表示接近宽度的20%时显示为蓝色

  - radial gradient径向渐变

    - 中心区域形状（如circle），之后一串颜色（与普通渐变相同）

  ### 过度变换和动画

#### 动画库[animate.css](https://animate.style/)

- `$ npm install animate.css --save`

- `import 'animate.css';`

- 使用

  - 法一`<h1 class="animate__animated animate__动画名称">An animated element</h1>`

  - 法二

    - ```css
      .my-element {
        display: inline-block;
        margin: 0 0.5rem;
      
        animation: 动画名称; /* referring directly to the animation's @keyframe declaration */
        animation-duration: 2s; /* don't forget to set a duration! */
      }
      ```

  - 法三[cdnjs.cloudflare.com/ajax/libs/animate.css/4.1.1/animate.css](https://cdnjs.cloudflare.com/ajax/libs/animate.css/4.1.1/animate.css)直

    - 接复制粘贴to和from

  #### 过渡

  - 属性
    - 常与havor连用
    - transition-property应用过渡的css属性名（属性变化正常设置，与过渡语法无关）
      - all表示多有属性

    - transition-duration过渡的持续时间
    - transition-timing-function过渡效果的速度曲线
      - ease（默认值）：慢->块->慢
      - liner：线性速度
      - ease-in：慢->快
      - ease-out：快->慢
      - ease-in-out：与ease类似，但是中间更快，两端更慢
      - 也可以输入一个贝塞尔曲线如：`cubic-bezier(0.17, 0.67, 0.83, 0.67)`
      - 步进（分几次移动到末尾）：step(5, start)或step(5, end)（没有明显差异）
    - transition-delay过度开始前的延迟时间
    - 缩写transition
      - 多组之间用逗号分隔

  #### 变形transform属性

- 写法：`transform: translateX(100px); `（transform后面可以跟多个属性，先后顺序可能造成影响，如先旋转会改变坐标轴方向，一般把位移属性放在最前面）

  - 旋转
    - rotate()平面旋转（绕z轴垂直于平面旋转）
    - rotateX() rotateY() rotateZ() 表示沿xyz轴旋转
      - 角度单位deg
    - rotate3D(1, 1, 1, 80deg)前三个参数表示沿不同反向的旋转分量，第四个参数表示旋转角度
    - ![Snipaste_2023-01-03_15-32-41](https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2023-01-03_15-32-41.png)
  - 移动
    - translateX() translateY() translateZ()（设置了透视才能看到z轴移动的效果）
    - translate()缩写
    - translate3D()依次写入xyz轴的数据
    - 移动不会影响其他盒子的位置 
    - 使用%依据的是盒子自身的大小
  - 缩放
    - scaleX() scaleY()
    - scale3D() xyz轴
    - scale()缩写
    - 不带单位的数字表示缩放位数
    
  - 倾斜
    - skewX() skewY()
    - skew()
  - 变形原点
    - transform-origin：可以用left center right top center bottom指定顶点或者使用百分百比或长度大小来指定具体位置
  - 3d变形方式
    - transform-style：默认为flat（子元素依附父元素）preserve-3d使子元素具有自己的3d空间（可以处于空间中的不同层）
    - 属性给到父元素上
  - 视域（透视）
    - 只有设置了透视，才能使用3d效果
    - perspective(200px)：参数越小，视角越深（离物体越近畸变越明显），仅为目标元素定义视距
      - perspective: 200px;与函数形式有区别，视距也会应用到子元素上（写在需要透视效果的父元素上）
    - perspective-origin设置视距变形的中心点
    
  - backface-visibility
    - visible表示渲染元素背面
    - hidden不渲染（显示为透明）

  #### 动画

  - 使用@keyframes定义

  ```html
  @keyframes 动画名称{
  	0% {
  		background-color: red;
  	}
  	50%{
  		...
  	}
  	100%{//对于重复的动画状态可以写成20%,45%,100%{}
  		...
  	}	
  }//定义
  div{
  	animation-name: 名称;
  	...
  }
  ```

  - 入过只有两个阶段可以不用百分号，用from和to来表示
  - 属性
    - animation-play-state
      - running和paused（开始暂停播放动画）
    - animation-name 动画名称（指定要使用的动画）
    - animation-duration持续时间
    - animation-delay开始播放前的延迟
    - animation-iteration-count播放次数
      - infinite表示循环播放
    - animation-direction是否反向播放
      - normal（默认）正向播放
      - reverse反向播放
      - alternate奇数次正常播放，偶数次反方向播放
      - alternate-reverse
    - animation-timing-function速度曲线
      - 与过渡一致
    - animation-fill-mode填充模式
      - none结束后和开始前无残留
      - forwards结束后保留最后一帧画面
      - backwards开始前保留最后一帧画面（默认）
      - both开始前和结束后均保留
    - 简写
      - animation：动画名称 持续时间 运动曲线 何时开始 播放次数 是否反方向 动画起始或者结束的状态;

  ### 图像变换

  #### 滤镜

  - blur(2px) 高斯模糊
    - 值越大越模糊
  - brightness()亮度
    - 默认为1，最低为0
  - contrast()对比度
    - 默认为1
  - staurate()饱和度
    - 默认为1
  - grayscale()灰阶
    - 默认为0，1表示完全灰度模式
  - sepia()怀旧
    - 默认为0，取值范围0~1
  - hue-rotate()色相旋转
    - 输入角度
  - invert()颜色反转
    - 默认为0取值范围0~1
    - 输入0.5会得到灰色
  - opacity()透明度
    - 默认为1（不透明），范围0~1
  - drop-shadow()阴影效果
    - 四个参数
  - filter缩写
    - 可以直接在后面加一串滤镜属性
  - SVG滤镜（略）

  #### 混合模式

  - mix-blend-mode属性
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/IMG_20221228_155139.jpg" alt="IMG_20221228_155139" style="zoom: 25%;" />

  #### 裁剪

  - clip-path
    - inset(30px 20px 30px 20px round 10px)指定以四边形内凹的形状裁剪
      - 前四个数据定义四条边的偏移量，用round可以追加圆角设置
    - circle(20px at 20% 50%)圆形裁剪
      - 先定义半径，再用at指定圆心
    - ellipse(40px 2npx at 20% 50%)椭圆裁剪
    - polygon(20px 50px,...)多边形裁剪
      - 指定多个点的坐标
  - 蒙版（略）

  # 补充

  ## 其他特性

  ### css初始化

  - 重设浏览器样式，消除不同浏览器的显示差异

  ### calc计算函数

  - calc() 此CSS函数让你在声明CSS属性值时执行一些计算。
    - 括号里面可以使用 + - * / 来进行计算。
  - `width: calc(100% - 80px);`

  ### 变量

  - 声明：使用两个连字符开头`--brickred: #cd4042`
  - 使用：使用时用var（）括上`color: var(--brickred)`

  ### 精灵图

  - 目的，合并小图片，减少向浏览器的请求次数，提高页面的加载速度
  - 使用方法：
    - 通过移动图片，可以实现局部显示（只显示需要的部分）
      - 通过background-position移动图片，向上向左移动为负值

  ### 字体图标

  - 展示的是图标本质上是字体，占用空间小，放大缩小不会失真，容易更换，用于显示较为简单的图标
  - 使用过程：先下载后引入到html网页中

  - 在阿里网站加入购物车后下载代码，html中有使用方法

  ### css三角

  - 大小为0的盒子在一边增加边框就是一个三角形（四分之一正方形）

    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2023-01-01_20-54-38.png" alt="Snipaste_2023-01-01_20-54-38" style="zoom:33%;" />

  - ```css
    div {
     width: 0;
     height: 0;
     line-height: 0;
     font-size: 0;
     border: 50px solid transparent;
     border-left-color: pink;
     }
    ```

  ### 用户界面

  - cursor属性设置鼠标样式
    - 设置在对象上移动的鼠标指针采用何种系统预定义的光标形状
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2023-01-01_21-02-06.png" alt="Snipaste_2023-01-01_21-02-06" style="zoom:50%;" />
  - 表单轮廓线
    - 去掉选中输入框时的效果`input {outline: none; }`
  - 防止用户拖动调整文本域的大小
    - `textarea{ resize: none;}`

  ## 技巧

  - 自动填充随即文本：
    - lorem默认生成30个单词
    - loremN：生成N个词
    - lorem*N：生成N行
    - loremN*M：填充M行，每行N个词
    - 按tab执行生成

  ### Emmet语法 

  - 使用缩写来提高html和css的编写速度
  - 生成标签 直接输入标签名 按tab键即可 比如 div 然后tab 键， 就可以生成 
    - ！+tab会生成html基本框架
  - 如果想要生成多个相同标签 加上 * 就可以了 比如 div*3 就可以快速生成3个div（也是按tab确认）
  - 如果有父子级关系的标签，可以用 > 比如 ul > li就可以了（会自动生成嵌套关系）
  - 如果有兄弟关系的标签，用 + 就可以了 比如 div+p （生成两行，分别为div和p）
  - 如果生成带有类名或者id名字的， 直接写 .demo 或者 #two tab 键就可以了（默认生成div）
    - `p.one`会生成`<p class="one"></p>`
    - 使用$可以生成名称递增的
      - `div.demo$*5`生成div demo1 demoo2...demo5
  - 如果想要在生成的标签内部写内容可以用 { } 表示
    - div{$}*5可以实现div的内容自增
  - CSS 基本采取简写形式即可，比如 w200 按tab 可以 生成 width: 200px; 比如 lh26px 按tab 可以生成 line-height: 26px;

  - 格式化代码（自动对齐）
    - ctrl+alt+l

  ### ps切图

  - 从psd中获取图片等素材

  - 方法
  
    - 对于单个图片直接右键导出为png，对于多个图层需要先合并图层再导出
  
  - 使用切片工具（在裁剪的选项中），选择区域后导出存储为web所用格式，导出选中的切片
  
- 使用cutterman插件

### 常用模块类名

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/Snipaste_2023-01-02_19-16-57.png" alt="Snipaste_2023-01-02_19-16-57" style="zoom: 50%;" />

## jquery

### 选择器

- `parentTag childTag:contains("specificContent")`：包含选择器（contains sel来获取包含特定内容的子标签的标签。

# 移动端开发

# 补充

### 静态网页与动态网页

#### 静态网页

- 静态网页是指使用 HTML、CSS 和 JavaScript 等语言（前两者通常不被认为是编程语言，而是标记语言和样式表语言）编写的，**不包含服务器端动态内容** 的网页。当用户访问这些网页时，*服务器将其内容原封不动地发送到用户的浏览器，内容不会因用户的不同而改变*。
- 优点
  - 加载速度快：不需要与服务器交互，直接向用户展示内容，节省了加载时间。
  - 易于创建和维护：不需要服务器端编程，只需编写 HTML、CSS 和 JavaScript 代码即可。
  - 安全性高：没有服务器端的交互，降低了安全风险。
- 缺点
  - 功能受限：无法实现复杂的互动功能，如用户登录、评论和实时更新等。
  - 更新困难：当需要更新内容时，必须手动修改HTML代码，这对于大型网站来说可能很麻烦。

#### 动态网页

- 动态网页是指通过服务器端编程语言（如 PHP、Python、Ruby 等）与数据库交互，根据用户请求生成实时内容的网页。动态网页可以实现更丰富的互动功能，如用户登录、评论、购物车等。
- 优点
  - 功能丰富：可以实现复杂的互动功能，提高用户体验。
  - 易于更新：通过数据库更新内容，无需手动修改代码。
  - 个性化体验：可以根据用户的需求和行为，为他们提供定制化的内容。
- 缺点
  - 加载速度慢：服务器需要处理用户请求并生成实时内容，可能导致加载速度较慢。
  - 开发和维护成本高：需要掌握服务器端编程和数据库知识，开发难度较大。

#### 爬虫

- 静态网页是预先编写好的 HTML 文件，它们包含了所有的文本内容、图片和样式信息。当用户请求一个静态网页时，服务器会将整个 HTML 文件发送给客户端，客户端浏览器解析并显示这个文件。在这种情况下，您可以直接请求网页 URL，获取到包含所有数据的 HTML 文件。
- 动态网页则与静态网页有所不同。动态网页的内容通常是由服务器端程序根据用户请求生成的。用户请求一个动态网页时，服务器可能首先发送一个不包含实时数据的 HTML 文件，然后使用 JavaScript 发起额外的请求（例如 Ajax 请求）来获取实时数据。实时数据通常以 JSON 或 XML 格式返回，并在客户端被解析和展示。这种情况下，仅请求网页 URL 可能无法获取到实时数据，因为这些数据是通过额外的请求动态加载的
  - 因此，在爬取这类动态网页时，需要抓包分析实际发起的请求，找到实时数据所在的请求 URL。然后，您可以针对这个 URL 发送请求，获取包含实时数据的 JSON 或 XML 文件，并进行相应的数据解析。
