## 概述

vue 是一套用于构建用户界面的前端框架。

### 特性

- 数据驱动视图
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421164324009.png" alt="image-20230421164324009" style="zoom:50%;" />
- 双向数据绑定
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421164410966.png" alt="image-20230421164410966" style="zoom:50%;" />
- mvvm
  - ![image-20230421164542858](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421164542858.png)
- 工作原理
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421164605877.png" alt="image-20230421164605877" style="zoom:50%;" />

### 使用步骤

- 导入 vue.js 的 script 脚本文件
- 在页面中声明一个将要被 vue 所控制的 DOM 区域
-  创建 vm 实例对象（vue 实例对象）
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421165811667.png" alt="image-20230421165811667" style="zoom: 80%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421170058229.png" alt="image-20230421170058229" style="zoom: 67%;" />

### 指令

- `v-text="变量名称"`替换元素标签之间的内容（会覆盖原有的元素）
  - 只能渲染纯文本内容
  - `<p v-text="username">...</p>`
  - `{{}}`解决覆盖的问题，插值表达式
    - `<p>...{{name}}</p>`
  - `v-html`
    - 可以渲染为页面的 HTML 元素

- `v-bind`属性绑定，要为元素的**属性**动态绑定属性值

  - `<... v-bind:属性名=“变量”>`
  - 可以缩写为`:`
  - 除了支持绑定简单的数据值之外，还支持 Javascript 表达式的运算

- `v-on`事件绑定指令

  - `<button v-on:click="addCount[(传参)]"></button>`
  - 简写`@click`
  - 通过 v-on 绑定的事件处理函数，需要在 methods 节点中进行声明：
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421172028798.png" alt="image-20230421172028798" style="zoom: 67%;" />
  - 原生 DOM 对象有 onclick、oninput、onkeyup 等原生事件，替换为 vue 的事件绑定形式后， 分别为：v-on:click、v-on:input、v-on:keyup
  - 事件对象 even:与dom类似，使用vue绑定时也可以收到事件对象event
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/event.png" style="zoom:80%;" />
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421172419119.png" alt="image-20230421172419119" style="zoom: 80%;" />
    - \$event 是 vue 提供的特殊变量，用来表示原生的事件参数对象 event。\$event 可以解决事件参数对象 event  被覆盖的问题。
      - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421172936590.png" alt="image-20230421172936590" style="zoom: 80%;" />
  - 事件修饰符
    - 方便的对事件的触发进行控制
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421173117008.png" alt="image-20230421173117008" style="zoom: 80%;" />
  - 按键修饰符
    - 在监听键盘事件时，我们经常需要判断详细的按键。此时，可以为键盘相关的事件添加按键修饰符
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421173223726.png" alt="image-20230421173223726"  />

- `v-model `双向数据绑定

  - 者在不操作 DOM 的前提下，快速获取表单的数据。
    - 只能配合表单元素一起使用
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421173401398.png" alt="image-20230421173401398" style="zoom: 80%;" />
  - 的修饰符
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421173446744.png" alt="image-20230421173446744" style="zoom:67%;" />

- 条件渲染指令`v-if`和`v-show`

  - 按需控制 DOM 的显示与隐藏
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421173721137.png" alt="image-20230421173721137" style="zoom:50%;" />

  - `v-else` `v-else-if`
    - ![image-20230421173814929](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421173814929.png)
  - 更改变量后可能不会实时刷新，可以获取组件，并强制进行重新加载如`formRef2.value.$forceUpdate();`

- 列表渲染指令

  - 基于一个数组来循环渲染相似的 UI 结构
  - 要使用 item in items 的特殊语法
    - items 是待循环的数组
    - item 是当前的循环
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421174013215.png" alt="image-20230421174013215" style="zoom:80%;" />
  - v-for 指令还支持一个可选的第二个参数，即当前项的索引。
    - `(item,index) in list`

  - key：当列表的数据变化时，默认情况下，vue 会尽可能的复用已存在的 DOM 元素，从而提升渲染的性能。但这种 默认的性能优化策略，会导致有状态的列表无法被正确更新。
    - 需要为每项提供一个唯一的 key 属性
    - ![image-20230421174231511](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421174231511.png)
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421174300027.png" alt="image-20230421174300027" style="zoom:80%;" />

#### 自定义组件

##### 私有自定义指令

- 声明
  - directives节点下声明私有自定义指令
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001318000.png" alt="image-20230422001318000" style="zoom:50%;" />
- 使用时需要加上前缀v
  - 如`v-focus`

##### 全局自定义指令

- 声明
  - 全局共享的自定义指令需要通过“单页面应用程序的实例对象”进行声明
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001511381.png" alt="image-20230422001511381" style="zoom: 50%;" />
- mounted 函数只在元素第一次插入DOM 时被调用，当DOM 更新时mounted 函数不会被触发。updated  函数会在每次DOM 更新完成后被调用。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001806347.png" alt="image-20230422001806347" style="zoom:50%;" />
- 如果mounted 和updated 函数中的逻辑完全相同，则可以简写成如下格式：
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001823762.png" alt="image-20230422001823762" style="zoom:50%;" />
-  指令的参数值
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001840122.png" alt="image-20230422001840122" style="zoom:50%;" />

### 过滤器

- 过滤器（Filters）常用于文本的格式化。
- 过滤器应该被添加在 JavaScript 表达式的尾部，由“管道符”进行调用
- ![image-20230421174608756](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421174608756.png)
- 过滤器可以串联地进行调用`...|...|...`

#### 定义

- 以在 filters 节点中定义过滤器
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421174642356.png" alt="image-20230421174642356" style="zoom:80%;" />
  - 在 filters 节点下定义的过滤器，称为“私有过滤器”，因为它只能在当前 vm 实例所控制的 el 区域内使用。
- 全局过滤器:望在多个 vue 实例之间共享过滤器
  - `Vue.filter('全局过滤器的名字',(str)=>{处理函数})`
- 传参
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421175001590.png" alt="image-20230421175001590" style="zoom:80%;" />
    - 第一个参数保留为管道符前面传入的

## 组件

### vite

- 用于创建vue的SPA（ 单页面应用程序）项目
- 创建：
  - `npm init vite-app 项目名称`
  - `cd 项目名称`
  - `npm inastall`
  - `npm run dev`
    - 令会启动一个开发服务器，该服务器会监听您的源代码更改并自动重新编译和刷新您的应用程序，以便在开发过程中实时查看更改的效果。
- 文件目录
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421201411455.png" alt="image-20230421201411455" style="zoom:50%;" />
    - vue 要做的事情很单纯：通过main.js 把App.vue 渲染到index.html 的指定区域中。
    - App.vue 用来编写待渲染的模板结构
    - index.html 中需要预留一个el 区域
    -  main.js 把App.vue 渲染到了index.html 所预留的区域中

- 过程：
  - 在**App.vue** 中编写模板结构
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421201750908.png" alt="image-20230421201750908" style="zoom:50%;" />
  -  在**index.html** 中预留el 区域
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421201816981.png" alt="image-20230421201816981" style="zoom:50%;" />
  - 在**main.js**中进行渲染
    - 把App.vue 中的模板内容渲染到index.html 页面的el 区域中
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421201954492.png" alt="image-20230421201954492" style="zoom:50%;" />

### 组件化开发

- 根据封装的思想，把页面上可重用的部分封装为组件，从而方便项目的开发和维护。
- vue 中规定组件的后缀名是.vue。之前接触到的App.vue 文件本质 上就是一个vue 的组件。
- vue 中组件的引用原则：先注册后使用

### 组件的构成

- 每个.vue 组件都由3 部分构成
  - template-> 组件的模板结构
  - script-> 组件的JavaScript 行为
  -  style-> 组件的样式
  - 每个组件中必须包含template 模板结构，而script 行为和style 样式是可选的组成部分。
  
- template
  - 在template节点中，支持使用指令语法来辅助渲染dom结构
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421202644564.png" alt="image-20230421202644564" style="zoom:50%;" />
  
- script
  - 组件内的\<script> 节点是可选的，开发者可以在\<script> 节点中封装组件的JavaScript 业务逻辑。
  
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421203203671.png" alt="image-20230421203203671" style="zoom:50%;" />
  
  - 节点：
  
    - name：为当前组件定义一个名称
  
      - `name:'name',`
    - data：定义vue 组件渲染期间需要用到的数据
  
      - 必须定义为函数
  
      - `data`选项用于定义组件的响应式数据。在`data`中定义的数据，当数据发生变化时，Vue会自动更新相关的DOM元素，从而实现响应式更新。
      
      - ```javascript
        data(){
        return {
        	xx:'',
        	...
        	}
        }
        ```
    -  methods：定义组件中的事件处理函数
    
      - ```
        methods:{
        	...处理函数
        }
        ```
    - 以及computed、emits等等
  
- 开发者可以在style\<style> 节点中编写样式美化当前组件的UI 结构
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421203819716.png" alt="image-20230421203819716" style="zoom:50%;" />
  - 默认情况下，写在.vue 组件中的样式会全局生效，因此很容易造成多个组件之间的样式冲突问题
    -  单页面应用程序中，所有组件的DOM 结构，都是基于唯一的index.html 页面进行呈现的每个组件中的样式，都会影响整个index.html 页面中的DOM 元素
    - vue 为style 节点提供了scoped属性，从而防止组件之间的样式冲突问题
      - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421205945804.png" alt="image-20230421205945804" style="zoom:50%;" />
  -  /deep/（vue3中使用:deep()） 样式穿透 
    - 如果给当前组件的style 节点添加了scoped 属性，则当前组件的样式对其子组件是不生效的。如果想让某些样 式对子组件生效，可以使用/deep/ 深度选择器

### 组件注册

#### 全局注册

- 全局注册的组件，可以在全局任何一个组件内使用
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421205037540.png" alt="image-20230421205037540" style="zoom:50%;" />
- 可以把组件的name 属性作为注册后组件的名称
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421205435149.png" alt="image-20230421205435149" style="zoom:50%;" />
- 使用app.component() 方法注册的全局组件，直接以标签的形式进行使用即可
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421205139609.png" alt="image-20230421205139609" style="zoom:50%;" />

#### 局部注册

- 被局部注册的组件，只能在当前注册的范围内使用
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421205207640.png" alt="image-20230421205207640" style="zoom:50%;" />

### props

- props 是组件的自定义属性，组件的使用者可以通过props 把数据传递到子组件内部，供子组件内部进行使 用。
  -  父组件向子组件传递信息![image-20230421211035359](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421211035359.png)
  - 子组件中声明pros获取父组件传递的属性（必须既要在父组件中声明，还要在子组件中声明为props）<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421210500740.png" alt="image-20230421210500740" style="zoom:50%;" />
- v-bind动态绑定
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421211231739.png" alt="image-20230421211231739" style="zoom:50%;" />

#### pros验证

- 在封装组件时对外界传递过来的props 数据进行合法性的校验，从而防止数据不合法的问题。
- 使用数组类型的props 节点的缺点：无法为每个prop 指定具体的数据类型
  - ![image-20230421214138180](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214138180.png)
- 使用对象类型的props 节点，可以对每个prop 进行数据类型的校验（ts语法）
  - 不符合时会在浏览器的调试面板中显示警告信息
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214202935.png" alt="image-20230421214202935" style="zoom:67%;" />

- 基础的类型检查
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214413201.png" alt="image-20230421214413201" style="zoom:33%;" />
- 多个可能的类型，使用数组指定可能的类型
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214452221.png" alt="image-20230421214452221" style="zoom:50%;" />
-  必填项校验
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214529051.png" alt="image-20230421214529051" style="zoom:50%;" />
- 属性默认值
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214623900.png" alt="image-20230421214623900" style="zoom:50%;" />
- 自定义验证函数
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421214711608.png" alt="image-20230421214711608" style="zoom:50%;" />

### 计算属性

- 计算属性本质上就是一个function 函数，它可以实时监听data 中数据的变化，并return 一个计算后的新值， 供组件渲染DOM 时使用
- 写在computed节点下，本质是function函数
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421215315153.png" alt="image-20230421215315153" style="zoom:50%;" />
- 必须当做普通属性使用（使用时只写函数名，不写括号）

### 自定义事件

- 为了让组件的使用者可以监听到组件内状态的变化，此时需要用到组件的自定义事件
- 使用步骤;
  - 在封装组件时：声明自定义事件、触发自定义事件
  - 在使用组件时：监听自定义事件
-  声明自定义事件
  - 必须事先在emits节点中声明
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421215601046.png" alt="image-20230421215601046" style="zoom:50%;" />
- 触发自定义事件
  - `this.$emit('自定义事件的名称'[,可选参数])`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421215631120.png" alt="image-20230421215631120" style="zoom:50%;" />

- 监听自定义事件
  - 以通过v-on的形式监听自定义事件
  - 使用方法与内置事件一致
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421215806610.png" alt="image-20230421215806610" style="zoom:50%;" />

### watch侦听器

- watch 侦听器允许开发者监视数据的变化，从而针对数据的变化做特定的操作。
- 在watch 节点下，定义自己的侦听器
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421221144091.png" alt="image-20230421221144091" style="zoom:50%;" />
  - 如检测值的变化，当值发生变化时向后端发送请求，实时判断值是否合法
  - 可以同时监听多个属性
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421222004752.png" alt="image-20230421222004752" style="zoom: 33%;" />
  - 也可以监听计算属性
    - 这可能相当于同时监听多个不同的属性（由计算属性的依赖决定）
- 默认情况下，组件在初次加载完毕后不会调用watch 侦听器。如果想让watch 侦听器立即被调用，则需要使 用immediate选项。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421221556543.png" alt="image-20230421221556543" style="zoom:50%;" />
- 当watch 侦听的是一个对象，如果对象中的属性值发生了变化，则无法被监听到。
  - 使用`deep:true`
  - 检测对象的单个属性：
    - 将`'对象.属性':{}`代替`'对象':{}`包住hundle回调函数

### 组件的生命周期

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421222811514.png" alt="image-20230421222811514" style="zoom:50%;" />

- vue 框架为组件内置了不同时刻的生命周期函数，生命周期函数会伴随着组件的运行而自动调用。
  - 当组件在内存中被创建完毕之后，会自动调用created函数
  - 当组件被成功的渲染到页面上之后，会自动调用mounted函数
  - 当组件被销毁完毕之后，会自动调用unmounted函数
  - 当组件的data 数据更新之后，vue 会自动重新渲染组件的DOM 结构，从而保证View 视图展示的数据和 Model 数据源保持一致。当组件被重新渲染完毕之后，会自动调用updated生命周期函数。
  
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421223157786.png" alt="image-20230421223157786" style="zoom:50%;" />

- 应用：
  - 在mounted中绑定监听事件（如键盘事件），在beforeunmount中解除绑定事件

- `script setup`在dom没有渲染完就会执行，因此不能再setup里直接获取dom元素

  - ```js
    使用 onmounted绑定事件
    ```

### 组件之间的数据共享

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421230050926.png" alt="image-20230421230050926" style="zoom:50%;" />

#### class与style的绑定

- 经常会遇到**动态操作元素样式**的需求

- vue 允许开发者通过v-bind（单向绑定）属性绑定指令，为元素动态绑定class 属性的值和行内的style 样式
- 可以通过三元表达式，动态的为元素绑定class 的类名。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421212653968.png" alt="image-20230421212653968" style="zoom:50%;" />
- 如果元素需要动态绑定多个class 的类名，此时可以使用数组的语法格式
  - ![image-20230421212719924](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421212719924.png)
- 以对象语法绑定HTML 的class
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421212748656.png" alt="image-20230421212748656" style="zoom:50%;" />
    - 根据值的情况，绑定不同的键作为class
- style
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421213227030.png" alt="image-20230421213227030" style="zoom:50%;" />

#### 组件上的双向绑定（父子关系）

- 外界数据的变化会自动同步到counter 组件中;counter 组件中数据的变化，也会自动同步到外界
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421220019713.png" alt="image-20230421220019713" style="zoom:50%;" />
- v-model可以被用来自定义组件和父组件之间的双向数据绑定，以达到和表单组件类似的效果。
  - 组件需要接收一个名为value的prop，用来接收父组件传递进来的值
  - 组件需要触发一个名为**input**的事件，并且将新的值作为参数传递给该事件
  - 当父组件使用v-model指令来绑定自定义组件的值时，Vue.js会自动将父组件的值传递给组件的value prop，并且监听组件内部input事件的触发，从而实现双向绑定。
  - ![image-20230421220928061](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421220928061.png)

#### 兄弟组件之间的数据共享

- 仍然可以通过`props`和`$emit`方法实现。但是，如果兄弟组件之间的关系比较复杂，或者需要在多个组件之间共享数据，使用`props`和`$emit`方法就会变得比较繁琐。

- 可以借助于第三方的包mitt 来创建eventBus（事件总线）对象，从而实 现兄弟组件之间的数据共享。
  - 事件总线是一个事件广播机制，它可以在任何组件之间传递消息
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421230544521.png" alt="image-20230421230544521" style="zoom:50%;" />
-  安装mitt 依赖包`npm i mitt`
- 创建公共的EventBus 模块
  - 在项目中创建公共的eventBus 模块（js文件）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231000068.png" alt="image-20230421231000068" style="zoom: 67%;" />
- 在数据接收方自定义事件
  - `bus.on('事件名称', 事件处理函数)` 方法注册一个自定义事件
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231106312.png" alt="image-20230421231106312" style="zoom:50%;" />
- 在数据接发送方触发事件
  - `bus.emit('事件名称', 要发送的数据)` 方法触发自定义事件
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231116472.png" alt="image-20230421231116472" style="zoom:50%;" />

#### 后代关系的数据共享

- 是父节点的组件向其子孙组件共享数据。此时组件之间的嵌套关系比较复杂， 可以使用provide（只能由父组件来使用）和inject实现后代关系组件之间的数据共享。

- 父节点通过provide共享数据

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231542879.png" alt="image-20230421231542879" style="zoom:50%;" />

- 子孙节点通过inject 接收数据

  - 子孙节点可以使用inject数组，接收父级节点向下共享的数据。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231642764.png" alt="image-20230421231642764" style="zoom:50%;" />

- > 响应式的数据是指当数据发生变化时，相关的组件会自动更新视图，而无需手动操作。

- 父节点对外共享响应式的数据

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231836567.png" alt="image-20230421231836567" style="zoom:50%;" />

- 子孙节点使用响应式的数据

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421231850555.png" alt="image-20230421231850555" style="zoom:50%;" />

#### 全局数据共享vuex

- vuex 是终极的组件之间的数据共享方案。在企业级的vue 项目开发中，vuex 可以让组件之间的数据共享变得高 效、清晰、且易于维护。

- 安装`npm install vuex@next --save`

- 使用

  - ```js
    import { createStore } from 'vuex'
    const store = createStore({
        state () {
          return {
            //用户信息
            user: {}
          }
        },
        mutations: {
            //记录用户信息
            SET_USERINFO(state, user) {
                state.user = user
        }
      },
        actions: {
            getinfo({ commit }){
                return new Promise((resolve, reject) => {
                    getinfo().then(res => {
                        commit('SET_USERINFO', res)
                        resolve(res)
                    }).catch(err => {
                        reject(err)
                    })
                })
            }
        }
    })
    export default store
    ```

  - 再在main.js引入`app.use(store)`

  - action打包操作，读取成功写入并返回值，否则返回错误

    - 调用`store.dispatch('getinfo')`


- 保存数据`s$tore.commit('修改函数名称', res2)`
- 获取数据`$store.state.属性`
- vuex是在内存中的存储数据，当刷新页面后会进行**重置**，可以通过加载时向服务器发送请求获取数据解决
- tip:


  - html中使用可以直接`$store...`

  - script中使用则要先引入


    - ```js
      import { useStore } from 'vuex'
      const store = useStore()
      ```




### ref引用

- ref 用来辅助开发者在不依赖于jQuery 的情况下，获取DOM 元素或组件的引用。
- 每个vue 的组件实例上，都包含一个\$refs 对象，里面存储着对应的DOM 元素或组件的引用。默认情况下， `this.\$refs` 指向一个空对象
  - 通过给元素添加ref属性来注册引用，可以把元素添加到refs对象中实现访问
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421233753718.png" alt="image-20230421233753718" style="zoom:50%;" />
- ` this.$nextTick(cb)`，会把cb 回调推迟到下一个DOM 更新周期之后执行。通俗的理解是：等组件的 DOM 异步地重新渲染完成后，再执行cb 回调函数。从而能保证cb 回调函数可以操作到最新的DOM 元素
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421234159539.png" alt="image-20230421234159539" style="zoom:50%;" />

### 动态组件

- 动态组件指的是动态切换组件的显示与隐藏。vue 提供了一个内置的\<component>组件，专门用来实现组件的动态渲染

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421234305575.png" alt="image-20230421234305575" style="zoom:50%;" />

- ```vue
  <template>
    <div>
      <button @click="toggleComponent">切换组件</button>
      <component :is="currentComponent"></component>
        <!--动态切换要显示的内容-->
    </div>
  </template>
  
  <script>
  import ComponentA from './ComponentA.vue';
  import ComponentB from './ComponentB.vue';
  
  export default {
    components: {
      ComponentA,
      ComponentB,
    },
    data() {
      return {
        currentComponent: 'ComponentA',
      };
    },
    methods: {
      toggleComponent() {
        this.currentComponent = this.currentComponent === 'ComponentA' ? 'ComponentB' : 'ComponentA';
      },
    },
  };
  </script>
  
  ```

- 默认情况下，切换动态组件时无法保持组件的状态。此时可以使用vue 内置的\<keep-alive>组件保持动态组件的状态。

  - 会缓存动态组件的实例，避免每次切换组件都要重新创建实例。
  - 具体来说，`<keep-alive>`会将其包裹的组件缓存到内存中，如果组件再次被使用，则可以直接从缓存中取出，而不需要重新创建实例和重新渲染组件。这样可以大大提高组件的性能。

### 插槽

- 插槽（Slot）是vue 为组件的封装者提供的能力。允许开发者在封装组件时，把不确定的、希望由用户指定的 部分定义为插槽
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421235058332.png" alt="image-20230421235058332" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421235131722.png" alt="image-20230421235131722" style="zoom:50%;" />
- 如果在封装组件时没有预留任何插槽，则用户提供的任何自定义内容(\<my-com>元素中的内容)都会被丢弃。
- 封装组件时，可以为预留的插槽提供后备内容（默认内容）。如果组件的使用者没有为插槽提供任何 内容，则后备内容会生效。
  - 即`<slot>后备内容<\slot>`
-  具名插槽
  - 如果在封装组件时需要预留多个插槽节点，则需要为每个插槽指定具体的name名称
  - 组件中直接给slot组件添加name属性
  - 使用组件时用`<template v-slot:插槽名称></template>`
    - v-slot可以简写为#
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421235536709.png" alt="image-20230421235536709" style="zoom: 80%;" />

#### 作用域插槽

- 声明作用域插槽
  - `v-slot:default=""`表示作用域插槽
  - 可以通过作用域插槽把表格每一行的数据传递给组件的使用者。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001103672.png" alt="image-20230422001103672" style="zoom:67%;" />
-  使用作用域插槽
  - 声明和使用时的名称不需要相同
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422001130705.png" alt="image-20230422001130705" style="zoom: 67%;" />

- 作用域插槽

  - 为预留的插槽绑定props 数据
  - 作用域插槽允许子组件向父组件暴露具有可复用性的插槽内容，这样父组件就可以使用子组件提供的插槽内容来自定义渲染子组件的部分内容。（数据从子组件传输到父组件）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422000119155.png" alt="image-20230422000119155" style="zoom: 67%;" />
  - ```html
    <el-table-column prop="rate" label="涨跌幅">
      <template #default="{ row }">
        <span :style="{ color: row.rate > 0 ? 'red' : 'green' }">{{ row.rate }}%</span>
      </template>
    </el-table-column>
    ```
  - 

- 解构作用域插槽的Prop

  - 简化数据的接收过程

  - 解构作用域插槽的 Prop 不仅可以用来获取单个属性值，还可以用来获取多个属性值

    - ```vue
      <child-component>
        <template v-slot:default="{ propA, propB }">
          <p>{{ propA }}</p>
          <p>{{ propB }}</p>
        </template>
      </child-component>
      ```

## axios前后端交互（http）

- 安装：`npm install axios`

- 引入`import axios from 'axios'`

- 全局使用

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421232437986.png" alt="image-20230421232437986" style="zoom:50%;" />
  - 之后每个组件中都可以使用`this.$http`来访问axios对象

- 在使用Axios发送HTTP请求时，响应会被封装成一个`response`对象

  - 含以下属性：
    - `data`: 服务器返回的响应数据。
    - `status`: HTTP状态码。
    - `statusText`: HTTP状态消息。
    - `headers`: 响应头。
    - `config`: 请求的配置信息。
    - `request`: 发送请求的XMLHttpRequest对象。

- get：获取数据，请求指定的信息，返回实体对象

  - ```js
    axios.get('/api/users').then((response) => {
      console.log(response.data);
    });
    ```

- post：向指定资源提交数据（例如表单提交或文件上传）

  - ```js
    axios.post('/api/users', {
      name: 'Alice',
      age: 20,
    }).then((response) => {
      console.log(response.data);
    });
    ```

- put：更新数据，从客户端向服务器传送的数据取代指定的文档的内

  - 与post的区别：

    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230421233359578.png" alt="image-20230421233359578" style="zoom:50%;" />

  - ```js
    axios.put('/api/users/1', {
      name: 'Alice',
      age: 25,
    }).then((response) => {
      console.log(response.data);
    });
    ```

- delete：请求服务器删除指定的数据

  - ```js
    axios.delete('/api/users/1').then((response) => {
      console.log(response.data);
    });
    ```

- server.proxy代理解决网络阻止问题
  - 在开发环境中，如果我们的应用程序需要调用远程API，通常需要通过HTTP请求来访问它们。但是，由于CORS（跨源资源共享）策略的限制，浏览器默认情况下禁止跨域请求。这时候我们可以使用 server.proxy 选项来解决跨域请求问题
  
- 拦截器：对请求以及响应添加通用的预处理

  - ```js
    // 添加请求拦截器
    axios.interceptors.request.use(function (config) {
        // 在发送请求之前做些什么
        return config;
      }, function (error) {
        // 对请求错误做些什么
        return Promise.reject(error);
      });
    
    // 添加响应拦截器
    axios.interceptors.response.use(function (response) {
        // 2xx 范围内的状态码都会触发该函数。
        // 对响应数据做点什么
        return response;
      }, function (error) {
        // 超出 2xx 范围的状态码都会触发该函数。
        // 对响应错误做点什么
        return Promise.reject(error);
      });
    ```

  - 如对错误进同一处理，在请求前面添加token头
  
- 带头参数

  - ```js
    return axios.get("/news/index",{
            headers:{
                'Content-Type':'application/x-www-form-urlencoded'
            },
            params: {
                key: "022856a900e4d201e1d865f0866863",
                page: page,
                page_size: 10,
                type: "caijing",
                is_filter: 1
              },
        })
    ```

  - 


## 路由

- SPA 指的是一个web 网站只有唯一的一个HTML 页面，所有组件的展示与切换都在这唯一的一个页面内完成。 此时，不同组件之间的切换需要通过前端路由来实现。
- 是Hash 地址与组件之间的对应关系。
- 工作方式
  - ![image-20230422002044407](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422002044407.png)

### vue-router

#### 基本用法

- 安装`npm i vue-router`
- 定义路由组件
  - 假设项目中有三个vue组件，现在要通过路由来控制他们的展示与切换
  - 使用\<router-link>声明路由链接，\<router-view>声明路由占位符
    - 路由链接：
      - 它提供了一个 HTML 标签来创建链接，使用户可以点击链接跳转到不同的路由页面。
      - `<router-link to="/about">About</router-link>`
    - 路由占位符：
      - 当用户访问某个路由时，Vue Router 会根据当前路由匹配到的组件渲染到 `<router-view></router-view>` 中
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422002814595.png" alt="image-20230422002814595" style="zoom: 67%;" />

- 创建路由模块
  - 在项目中创建router.js 路由模块
  - 从vue-router 中按需导入两个方法
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422002930316.png" alt="image-20230422002930316" style="zoom:50%;" />
  - 导入需要使用路由控制的组件
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422002949692.png" alt="image-20230422002949692" style="zoom:50%;" />
  - 创建路由实例对象
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003003099.png" alt="image-20230422003003099" style="zoom: 50%;" />
  - 向外共享路由实例对象
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003041024.png" alt="image-20230422003041024" style="zoom:50%;" />
  - 在main.js 中导入并挂载路由模块
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003102304.png" alt="image-20230422003102304" style="zoom:50%;" />

- 404匹配
  - `{ path: '/:pathMatch(.*)*', name: 'NotFound', component: NotFound },`
- 

#### 路由重定

- 路由重定向指的是：用户在访问地址A 的时候，强制用户跳转到地址C 
- 通过路由规则的redirect属性，指定一个新的路由地址
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003234311.png" alt="image-20230422003234311" style="zoom:50%;" />

#### 路由高亮

- 将激活的路由链接进行高亮显示
- 被激活的路由链接，默认会应用一个叫做router-link-active的类名。开发者可以使用此类名选择器，为激活 的路由链接设置高亮的样式
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003350822.png" alt="image-20230422003350822" style="zoom:50%;" />

#### 嵌套路由

- 通过路由实现组件的嵌套展示，叫做嵌套路由。
- 声明子路由链接和子路由占位符
  - 在About.vue 组件中，声明tab1 和tab2 的子路由链接以及子路由占位符。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003510627.png" alt="image-20230422003510627" style="zoom: 50%;" />
- 在父路由规则中，通过children属性嵌套声明子路由规则
  - 在router.js 路由模块中，导入需要的组件，并使用children 属性声明子路由规则。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003649634.png" alt="image-20230422003649634" style="zoom:50%;" />

#### 动态路由匹配

- 把Hash 地址中可变的部分定义为参数项，从而提高路由规则的复用性

  - 如<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003825853.png" alt="image-20230422003825853" style="zoom: 50%;" />

  - 通过动态路由匹配的方式渲染出来的组件中，可以使用`$route.params` 对象访问到动态匹配的参数值。

    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422003908374.png" alt="image-20230422003908374" style="zoom:50%;" />

    - 为了简化，可以使用pros传参，即去掉$route.params，直接使用`{{id}}`

#### 编程式导航

- 通过调用API 实现导航的方式，叫做编程式导航。与之对应的，通过点击链接实现导航的方式，叫做声明式导航。
- 普通网页中点击 链接、vue 项目中点击 都属于声明式导航
- 普通网页中调用location.href 跳转到新页面的方式，属于编程式导航
- ` this.$router.push('hash 地址')`跳转到指定Hash 地址，从而展示对应的组件
- `this.$router.go(数值n)` 实现导航历史的前进、后退

#### 命名路由

- 通过name 属性(不可以重复)为路由规则定义名称的方式，叫做命名路由。
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422004201920.png" alt="image-20230422004201920" style="zoom:50%;" />
- 为 标签动态绑定to 属性的值，并通过name 属性指定要跳转到的路由规则。期间还可以用 params 属性指定跳转期间要携带的路由参数。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422004240829.png" alt="image-20230422004240829" style="zoom:50%;" />
- 调用push 函数期间指定一个配置对象，name是要跳转到的路由规则、params是携带的路由参数（同理）

#### 导航守卫

- 导航守卫可以控制路由的访问权限。示意图如下

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422004316407.png" alt="image-20230422004316407" style="zoom:67%;" />

- 声明全局导航守卫

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422004344599.png" alt="image-20230422004344599" style="zoom:50%;" />

  ##### 守卫方法

  - 全局导航守卫的守卫方法中接收3 个形参
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422004439864.png" alt="image-20230422004439864" style="zoom:50%;" />
  -  在守卫方法中如果不声明next 形参，则默认允许用户访问每一个路由！；在守卫方法中如果声明了next 形参，则必须调用next() 函数，否则不允许用户访问任何一个路由！
    - 直接放行：next() 
    - 强制其停留在当前页面：next(false)
    -  强制其跳转到登录页面：next('/login')
  - 如<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230422004612105.png" alt="image-20230422004612105" style="zoom:50%;" />

## 补充

- 点击按钮跳转
  - 在template中使用`el-button type="primary" @click="$router.push('/')">回到首页 </el-button>`

### transition

- 过渡动画

- 如可以用于包住一组`v-if v-else`

  - ```html
    <transition name="fade">
        ...
    </transition>
    ```

- 

### cookie

- 使用vueuse库

- 安装`@vueuse/integrations universal-cookie`

- 引入

  - ```js
    import { useCookies } from '@vueuse/integrations/useCookies';
    const cookie = useCookies();
    ```

- 设置 

  - `cookie.set("名称","值")`

- 获取

  - `cookie.get("名称")`

- 删除

  - `cookie.remove("名称 ")`

### script setup

- `<script setup></script>`
- 在 `setup` 函数中，所有 ES 模块导出都被认为是暴露给上下文的值，并包含在 setup() 返回对象中。
  - 不需要`export default`了

#### 功能

- 自动注册子组件
  - 不需要components
- 可以直接在模板中使用 props 和响应式变量
- 自动处理了响应式变量和 props 的声明和引用，不需要手动导入和使用 `ref`、`reactive` 和 `toRefs` 等 API。

### 几种暴露方式

- `defineExpose`暴露实例，例如提供函数（成员方法）

- `defineProps`提供接口，允许外界输入值（修改）

  - ```js
        const props = defineProps({
            title:String,
            size:{
                type:String,
                default:"45%"
            },
            destroyOnClose:{
                type:Boolean,
                default:false
            },
            confirmText:{
                type:String,
                default:"确定"
            },
        })
    ```

- `defineEmits`定义对外信号事件

  - `  const emit = defineEmits(["submit"])`

### keep-alive

- 减少页面重复加载，提高响应速度

- ```js
  <router-view v-slot="{ Component }">
                      <keep-alive :max="10">
                          <component :is="Component"></component>
                      </keep-alive>
                  </router-view>
  ```

- max表示缓存数目的上限

### transition全局过渡动画

- ```html
  <transition name="fade"></transition>
  ```

- ```css
  <style>
  .fade-enter-from {
      opacity: 0;
  }
  
  .fade-enter-to {
      opacity: 1;
  }
  
  .fade-leave-from {
      opacity: 1;
  }
  
  .fade-leave-to {
      opacity: 0;
  }
  
  .fade-enter-active,
  .fade-leave-active {
      transition: all 0.3s;
  }
  .fade-enter-active{
      transition-delay: 0.3s;
  }
  </style>
  ```

- 要求页面只能有一个div根节点

### 响应式与非响应式

- 以下是响应式对象的特点：
  1. Vue.js 可以追踪它们的变化。
  2. 当响应式对象发生变化时，Vue.js 会自动更新相关 DOM。
  3. 响应式对象应该使用 Vue.js 提供的特定方式创建或初始化。
  4. Vue.js 只会追踪对象的属性，而不是对象本身。
  5. 响应式对象应该是顶层对象，而不是嵌套在其他非响应式对象中。
- 以下是一些不是响应式对象的示例：
  1. 原始类型的值（例如数字、字符串、布尔值等）。
  2. 非顶层对象（例如一个嵌套在其他对象中的对象）。
  3. 通过 Object.freeze() 函数冻结的对象。
  4. 在创建对象后添加的属性。Vue.js 只会追踪已经存在的属性，而不会追踪新添加的属性。如果需要追踪新添加的属性，可以使用 Vue.set() 方法或者修改对象的属性值，触发 Vue.js 监测变化。
- 实现
  - 在`script`中使用data
  - 在`script setup`中使用ref对象实现
  - 或者强制刷新组件，实现伪响应式

## compositon-api

### setup

- 与传统的将 props、data、computed、methods 分类放在export default中相比，新的模式是创建一个setup函数（或直接`script setup`）包含多个功能的不同组成

- setup函数会在 `beforeCreate` 之前被调用（早于dom完成渲染），因此获取dom元素要放在onmonuted中

- ```vue
  <script>
    import { ref, reactive } from 'vue'
  
    export default {
      setup() {
        const count = ref(0)
        const object = reactive({ foo: 'bar' })
  
        // 暴露给模板
        return {
          count,
          object,
        }
      },
    }
  </script>
  ```

- 如果使用`<script setup>`则想到与`default export`中的内容，整个部分都会暴露

- 参数

  - 第一个参数位props，第二个参数为context（上下文对象）

  - ```vue
    export default {
      props: {
        name: String,
      },
      setup(props) {
        console.log(props.name)
      },
    }
    ```
  
  - defineProps
  
    - 用与声明变量类型以及赋初值
  
    - ```js
      const props=defineProps({
          num: {
              type: Number,
              default: 0
          }
      })
      ```
  
    - 访问时也要通过`props`
  
    - 数组、对象必须有默认值，可以初始化为空
  
      - ```js
        const props = defineProps({
            value: {
                type: Array,
                default: function(v) { return }
            }
        })
        ```
  
    - 
  

### 响应式系统

- ref

  - 生成`const count = ref(0)`
  - 在脚本中访问使用`.value`
  - 在模板中使用会自动解套不需要`.value`

- computed

  - 以函数的形式定义，返回一个value不可修改的ref对象

    - ```js
      const count = ref(1)
      const plusOne = computed(() => count.value + 1)
      
      console.log(plusOne.value) // 2
      
      plusOne.value++ // 错误！
      ```

  - 传入get、set函数创建可以读写的

    - ```js
      const count = ref(1)
      const plusOne = computed({
        get: () => count.value + 1,
        set: (val) => {
          count.value = val - 1
        },
      })
      
      plusOne.value = 1
      console.log(count.value) // 0
      ```

- watcheffect

  - 立即执行传入的一个函数，并响应式追踪其依赖，并在其依赖变更时重新运行该函数(当函数的依赖项发生改变时再次执行函数)

    - ```js
      const count = ref(0)
      
      watchEffect(() => console.log(count.value))
      // -> 打印出 0
      
      setTimeout(() => {
        count.value++
        // -> 打印出 1
      }, 100)
      ```

  - 停止侦听，定义停止函数，用于调用

    - ```js
      const stop = watchEffect(() => {
        /* ... */
      })
      
      // 之后
      stop()
      ```

- watch

  - 侦听单个数据源

  - ```js
    watch(count, (count, prevCount) => {
      /* ... */
    })
    ```

  - 侦听多个数据源

  - ```js
    watch([fooRef, barRef], ([foo, bar], [prevFoo, prevBar]) => {
      /* ... */
    })
    ```

- emit

  - ```js
    const emit = defineEmits(["alertSome"])
    function clickButton(){
        //todo
        emit("alertSome",6666)
    }
    ```

### 生命周期

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230509215859488.png" alt="image-20230509215859488" style="zoom: 50%;" />
- 

# vite

### 配置

- 设置路径别名：

  - ```js
    import path from 'path'
    export default defineConfig({
    
      //设置别名
      resolve: {
        alias: {
          '~':path.resolve(__dirname, "src"),
        },
      }
    })
    ```

- 
