## 游戏系统

### 分辨率及适配

- 当屏幕分辨率与设计分辨率不同时会出现适配问题

#### widget

- 对节点实现自动定位
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402160751707.png" alt="image-20230402160751707" style="zoom:50%;" />

### 运行原理

##### 生命期回调

- `onLoad` 回调会在**节点**首次激活时触发，比如所在的场景被载入，或者所在节点被激活的情况下。通常我们会在 `onLoad` 阶段去做一些初始化相关的操作。（类似于构造函数的作用）
- `onEnable`当**组件**的 `enabled` 属性从 `false` 变为 `true` 时，或者所在**节点**的 `active` 属性从 `false` 变为 `true` 时，会激活 `onEnable` 回调。倘若**节点**第一次被创建且 `enabled` 为 `true`，则会在 `onLoad` 之后，`start` 之前被调用。
  - 当组件的 `enabled` 属性从 `true` 变为 `false` 时，或者所在节点的 `active` 属性从 `true` 变为 `false` 时，会激活 `onDisable` 回调。
  - 当组件或者所在节点调用了 `destroy()`，则会调用 `onDestroy` 回调，并在当帧结束时统一回收组件。
- `start` 回调函数会在**组件**第一次激活前，也就是**第一次执行 `update` 之前**触发。`start` 通常用于初始化一些中间状态的数据，这些数据可能在 update 时会发生改变，并且被频繁的 enable 和 disable。
  - `update (dt)`dt参数表示距离上一次调用过去的时间

- 游戏开发的一个关键点是在每一帧渲染前更新物体的行为，状态和方位。这些更新操作通常都放在 `update` 回调中。
  - `update` 会在所有动画更新前执行，但如果我们要在动效（如动画、粒子、物理等）更新之后才进行一些额外操作，或者希望在所有组件的 `update` 都执行完之后才进行其它操作，那就需要用到 `lateUpdate` 回调。

##### 事件冒泡

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230323095515662.png" alt="image-20230323095515662" style="zoom:50%;" />
  - 子节点受到事件出发后会对父节点发送相同的事件（逐级处理）
- 可以阻止事件的传递  `e.stopPropagation()`则此事件到此为止，不会继续后面的传递

### 内置对象

#### cc.game

1. `cc.game.run(scene, onLaunched)`：启动游戏引擎并加载指定的场景。`scene` 参数为要加载的场景对象，`onLaunched` 参数为可选的回调函数，在游戏引擎启动后调用。
2. `cc.game.pause()`：暂停游戏的运行，通常用于处理游戏暂停的逻辑。
3. `cc.game.resume()`：恢复游戏的运行，通常用于处理游戏继续运行的逻辑。
4. `cc.game.restart()`：重新启动游戏，即重新加载当前场景，通常用于处理游戏重新开始的逻辑。
5. `cc.game.end()`：结束游戏的运行，即退出游戏，通常用于处理游戏退出的逻辑。
6. `cc.game.step()`：手动执行一帧的游戏逻辑，通常用于特定的需求，如帧同步、测试等。
   - 一旦手动调用了step，再之后的过程中不会再由系统自动进行调用
   - step会调用游戏进行更新（比如会调用update函数）
7. `cc.game.setFrameRate(frameRate)`：设置游戏帧率，即每秒渲染的帧数。
8. `cc.game.getFrameRate()`：获取当前游戏的帧率设置。
9. `cc.game.getDeltaTime()`：获取上一帧与当前帧之间的时间间隔，单位为秒。
10. `cc.game.setFrameRate(frameRate)`：设置游戏帧率，即每秒渲染的帧数。
11. `cc.game.getFrameRate()`：获取当前游戏的帧率设置。
12. `cc.game.getFrameRate()`：获取当前游戏的帧率设置。

#### cc.sys

`cc.sys` 是 Cocos Creator 引擎中的一个全局对象，用于访问和处理与平台相关的功能和属性。它提供了一些方法和属性，可以获取和操作有关平台、设备和浏览器环境的信息。

- `cc.sys.platform`: 获取当前平台的名称，可能的取值有 `"browser"`（浏览器）、`"windows"`（Windows 平台）、`"mac"`（Mac 平台）、`"android"`（Android 平台）、`"ios"`（iOS 平台）等。
- `cc.sys.isMobile`: 判断当前平台是否是移动平台（Android 或 iOS）。
- `cc.sys.isNative`: 判断当前平台是否是原生平台（Windows、Mac、Android 或 iOS）。
- `cc.sys.isBrowser`: 判断当前平台是否是浏览器平台。
- `cc.sys.os`: 获取当前操作系统的名称，可能的取值有 `"Windows"`、`"Mac OS X"`、`"Android"`、`"iOS"` 等。
- `cc.sys.browserType`: 获取当前浏览器的类型，可能的取值有 `"Chrome"`、`"Firefox"`、`"Safari"`、`"Opera"` 等。
- `cc.sys.localStorage`用于访问浏览器缓存

#### cc.director

`cc.director` 是 Cocos Creator 中的导演（Director）对象，它是游戏场景管理和游戏逻辑控制的核心之一。它提供了许多方法和事件，用于控制游戏的运行和切换场景。

- `cc.director.loadScene(sceneName)`：加载指定名称的场景。
- `cc.director.runSceneImmediate(scene)`：立即运行指定的场景。
- `cc.director.pause()`：暂停游戏逻辑更新。
  - 是停止update的调用（而game的pause是停止整个游戏逻辑的运行和界面渲染）
- `cc.director.resume()`：恢复游戏逻辑更新。
- `cc.director.getDeltaTime()`：获取上一帧和当前帧之间的时间间隔（Δt）。
- `cc.director.getTotalTime()`：获取游戏运行的总时间。
- `cc.director.setAnimationInterval(1/60);`设置帧率（update调用频率）及绑定更新函数

### 预制体

- 可以用于动态创建节点（如子弹）

#### 创建

- 正常创建一个节点，对其进行设置
- 将调好的节点拖到资源管理器，创建prefab文件，创建预制体资源

#### 使用

- `let bulletNode ==cc.instantiate(xxx);`

#### 对象池

- 在需要频繁的创建销毁节点时使用，可以提高程序的运行效率

- 创建：`nodePool=cc.NodePool()`

- 判断是否为空`==null`（取出的节点为null）

- 初始化，向对象池中加入节点备用

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402170910927.png" alt="image-20230402170910927" style="zoom:50%;" />

- 取出节点：`Nodepool.get()`

- 放回节点：`Nodepool.put(node)`

- 判断节点是否启用`cc.isValid(node)`

- 模板;

  - ```typescript
    createEnemy(){
            let node = this.enemyPool.get();
            if(node == null)
                node = cc.instantiate(this.enemyPrefab);
            return node;
        }
        destroyEnemy( node : cc.Node){
            this.enemyPool.put( node );
        }
    ```

### 碰撞系统

#### 添加碰撞体Colider 

-  添加碰撞组件
- 用绿色框表示

#### 碰撞检测

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402172618216.png" alt="image-20230402172618216" style="zoom:50%;" />
  - 最后一行表示显示碰撞框（用于调试）
- 回调事件
  - 发生：`onCollisionEnter(other,self)`
  - 进行中：`onCollisionStay(other,self)`
  - 分开：`onCollisionExit(other,self)`
  - other，self都是组件，是组件之间的碰撞
  - 事件发生时会自动进行调用  
- 碰撞事件处理
  - 只有碰撞双方才会收到信息

#### 碰撞组

- 继续身份标识，有些设备之间的碰撞不需要处理
- 醒目->项目设置->分组管理
- 添加组并设置哪些组之间的碰撞需要被记录
- 用group参数对节点分组
- 用tag可以保存信息，用于判断碰撞对方的属性`other.tag==xx`

### 坐标系

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230322173852203.png" alt="image-20230322173852203" style="zoom:50%;" />
  - 用于坐标对象点
- 坐标系变化（本地坐标系<->世界坐标系）
  - convertToNodeSpace，获得的坐标相对于参照物的坐标。
  - convertToWorldSpace，获得的坐标是参照物所在的坐标系中的坐标，即转换到参照物的世界坐标。
  - convertToNodeSpaceAR，获得的坐标相对于参照物的坐标（此时坐标系的原点在参照物的**锚点**）。
  - convertToWorldSpaceAR，获得的坐标是参照物所在的坐标系中的坐标，即转换到参照物的世界坐标（此时坐标系的原点在参照物的**锚点**）。


#### 方位角

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230322231806429.png" alt="image-20230322231806429" style="zoom:33%;" />
- 获得点的方位（一个二维向量，分别表示cos和sin）
  - 输入为二维向量坐标，进行标准化处理
  - `pos.normalize()`
- `a.signAngle(b)`：获取ab两个向量之间的夹角（a-b可能为正也可能为负）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230322235631929.png" alt="image-20230322235631929" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230322235647089.png" alt="image-20230322235647089" style="zoom:33%;" />

### [缓动系统](https://docs.cocos.com/creator/manual/zh/tween/tween-example.html)

- `cc.tween(node).to(1（持续时间）,{position:cc.v3(250,-120,0),[其他属性变化（可以添加多个，同时进行）],[easing:'表示动画曲线']})[.to(这样是先后进行)].[call(回调函数，在动画完成后调用)][.then(其他缓动的名称，设置为并发执行)].start();`

  - to表示绝对值计算，by表示使用相对值计算

  - 表示创建长度为1s的缓动动画

  - 相当于：

    - ```typescript
      // 创建一个 cc.Tween 类型的对象
      let tween = cc.tween ( node );  
      // tween.to()的返回值就是tween对象自身 
      tween = tween. to(1, { position : cc.v3(250, -120, 0) } ) ;   
      // 开始动作
      tween.start();
      
      ```

#### 动画实现

- 在`update`中更新和调整动画，这个函数每秒钟会被调用60次
- 设置帧率`cc.game.setFrameRate(n);`
  - 这是一个全局设置，一般挂在根节点Canvas节点下

### 动画编辑器

#### 步骤

- 给组件添加animation组件（其他组件中）
- 新创建animation clip类型资源，把资源拖到节点的animation组件
  - 可以添加多个片段
  - play on load自动播放
- 开始编辑<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230407222823482.png" alt="image-20230407222823482" style="zoom: 33%;" />
- 选择片段进行编辑<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230407222927118.png" alt="image-20230407222927118" style="zoom:33%;" />
- 编辑关键帧
  - 设置帧率<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230407223031559.png" alt="image-20230407223031559" style="zoom:50%;" />
  - 右键拖动时间轴
  - 滚轮缩放
  - 在属性列表中设置属性
  - 然后为属性插入关键帧
  - 在不同关键帧通过属性面板改变检点的属性
  - 设置播放模式<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230407231730555.png" alt="image-20230407231730555" style="zoom:33%;" />

- 可以用于播放gif（图片组）
  - 关键帧选择spriteframe属性
  - 直接选中所有图片拖入进来会自动创建关键帧
- 不规则路径（贝塞尔曲线）
  - 单机画面上的运动路径添加控制点，编辑路径

#### api

- 先获取动画组件`let anima=this.getComponent(cc.Animation)`
- 播放指定的动画`anima.play("动画名称")`

### 图像绘制（待补充）

### 计时器

- 启动定时器  

  - `this. schedule(callback, interval)  `
  - `this. schedule(callback, interval, repeat, delay)`
    -  callback , 计时器回调  
      - 注意传入回调函数时不要带小括号
    -  interval , 每次时间间隔
    -   repeat , 重复多少次  delay 
    -  多少秒后还时启动

- 停止定时器  `comp.unschedule(callback )`（传入回调函数）

- 全部关闭`this.unscheduleAllCallbacks();`

- 注意：回调函数中的this指向组件

   - 可以使用箭头函数代替,，来让this指向节点

   - `function(){}`->`()=>{}`

- 一次性计时器：

   - ```typescript
       this.scheduleOnce(function() {
           // 这里的 this 指向 component
           this.doSomething();
       }, 2);
      ```

   - 仅在2s后执行一次回调函数

- ```typescript
  this.count = 0;
  this.callback = function () {
      if (this.count == 5) {
          // 在第六次执行回调时取消这个计时器
          this.unschedule(this.callback);
      }
      this.doSomething();
      this.count++;
  }
  this.schedule(this.callback, 1);
  ```

### 多媒体

#### 资源加载

- 之间在属性面板中指定属于静态加载

- 使用`cc.resources.load`进行动态加载

  - `cc.resources.load( path, type, onComplete)`

    - 待加载的资源**必须放在resources目录下**
      - 例如，icon/汽车 指的是 assets/resources/icon/汽车
    - 路径不能加后缀名

  - 第3个参数：onComplete指定回调方法，当资源加载完毕时调用`function( err, assets ) {}`

    - 若err == null ，表示资源加载成功，assets即为加载得到的资源对象
    - 若err!=null ，表示资源加载出错，err即为出错的原因。

  - ```typescript
     onClicked(){
            let self = this;    // 这是JS中的闭包语法(否则闭包函数内访问不到this，或者也可以使用箭头函数来解决)
            cc.resources.load("icon/汽车", cc.SpriteFrame, function (err, assets) {
                self.node.getComponent(cc.Sprite).spriteFrame = <cc.SpriteFrame> assets;(尖括号代表强制类型转化)
            });
    }
    
    ```

- 一次加载多个资源
  - 指定多个资源路径cc.resources.load ( paths, callback(err, assets){  … })其中，paths类型 [cc.String],  assets类型 [cc.Asset]
  - 指定一个资源目录cc.resources.loadDir(path , callback(err,assets){  … })其中，path是一个文件夹路径，assets是[cc.Asset]

#### 图片

##### 显示gif

- 需要先提取为图片再使用脚本循环播放

  - ```typescript
     @property( [ cc.SpriteFrame ] )
        frames : cc.SpriteFrame[]  = new Array();
      
        sprite : cc.Sprite = null; // Sprite组件(用于控制图片的显示)
        index : number = 0;   // 当前显示第N张图片
        interval : number = 0.1; // 定时器的间隔
      
        onLoad () {
            this.sprite = this.getComponent(cc.Sprite);
        }
      
        start () {
            this.schedule(this.onTimer, this.interval);
        }
      
        onTimer(){
            if(this.frames.length ==0) return;
      
            this.sprite.spriteFrame = this.frames[this.index];
      
            // 下一帧
            this.index ++;
            if(this.index >= this.frames.length)
                this.index = 0;
        }
        // update (dt) {}
      
        onDestroy(){
            this.unschedule(this.onTimer);
        }
    ```

- 要设置关闭自动缩放

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230323001011540.png" alt="image-20230323001011540" style="zoom:33%;" />

- 或使用图集*Atlas（类似css中雪碧图）
  - 待补充

#### 音效

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402161748160.png" alt="image-20230402161748160" style="zoom:50%;" />

#### audiosource组件

- 背景音乐通常使用
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402162218848.png" alt="image-20230402162218848" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402162247856.png" alt="image-20230402162247856" style="zoom:50%;" />

#### audioEngine

- 播放提示音以及配音
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402163346466.png" alt="image-20230402163346466" style="zoom:50%;" />
  - clip是cc.AudioClip类型
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402163538288.png" alt="image-20230402163538288" style="zoom:50%;" />

### 多场景设计

- 游戏的入口称为初始场景（导出时在构建发布中设置）
- 场景scene，一个场景代表一个画面

#### 资源加载

- 每个资源都有一个独立的uuid
- 资源只有被引用了才会进行加载

- 预加载

  - `cc.director.preloadScene(sceneName,onProgress,onLoaded)`

    - 分别表示加载的场景、回调表示加载进度、回调表示加载完成

  - ```typescript
    cc.director.preloadScene('新手村', 
                function(count, total, item){//count表示加载完成的数目、total表示总数
                    cc.log('预加载场景: ' + count + '/' + total );
                },
                function(error: Error){
                    if(error!=null){     cc.log(error.message);}
                    cc.log('预加载完成!');            
                }
            );
    ```

- 可以使用内置的进度条组件来显示加载的进度

#### api

- 场景切换`cc.director.loadScene('要切换的场景名称';)`
  - 名称即可，不需要写路径

#### 场景间数据传输（常驻节点）

### 物理系统（待补充）



## API

### 游戏运行控制

- 退出游戏`cc.game.end();`
- 暂停游戏`cc.director.pause();`
- 回复游戏`cc.director.resume();`

### 节点

#### 获取节点

- 当前节点：`this.node:cc.Node`
  - 这就是通过组件来获取节点（每个组件都有一个.node类型成员）

- 父节点：`this.node.parent`
- 子节点：`this.node.children:cc.Node[]`
- 查找（子）节点：`cc.find("路径",[子节点名称])`历经就是在层级管理器中现实的（如Canvas/佩奇）
  - 找不到时返回null

#### 全局对象

- 有的对象应该作为整个游戏的全局变量（如玩家得分），这时就应该使用全局对象
- 一般创建一个一级节点其他，在下面挂载全局初始化节点（用于存储全局变量）（通常添加static修饰）
- 将其他脚本中的节点/组件引入到该节点中（在onload中赋值）

#### 销毁节点

- `node.destroy()`

### 组件

#### 获取组件

- `node.getComponent(组件)`

  - 内置：`cc.Lable`

  - 自定义：`"自定义组件名称"`

    - 可以获取别的组件（脚本），调用其方法

    - 应用：通过修改Sprite的属性修改节点的图片

    - 创建图片帧属性，用于对其赋值

      - ```typescript
        let sprite = this.node.getComponent(cc.Sprite);
                if(this.face==true)
                {
                    sprite.spriteFrame = this.face1;
                    this.face=false;
                }
                else
                {
                    sprite.spriteFrame = this.face2;
                    this.face=true;
                }
        ```

#### 创建组件

- `x.addComponent(cc.Sprite);`为x节点新创建一个新脚本组件，并返回

  - 也可以输入一个具体的已经创建的脚本进行引入

    - ```typescript
      //先引入
      import BulletScript from "./BulletScript";
      let script = bullet.addComponent('BulletScript');
      ```

  - 可以由此对其他脚本进行操控

- ```typescript
    let bullet:cc.Node=new cc.Node();
    let sprite:cc.Sprite=bullet.addComponent(cc.Sprite);
    sprite.spriteFrame=this.bulletIcon;
    bullet.parent=this.node;
  ```

  - 动态创建（子弹）节点，并创建脚本挂载



#### 内置组件

##### 进度条

- 

##### widget

- 

##### block input event

- 用于阻止输入事件（也可以使用阻止冒泡）
- 添加组件后会自动阻止触摸事件透传

##### button

- 使一个节点具有按钮的功能
- transition设置点击、悬浮时按钮的样式（行为）
- clickevent表示按钮被点击时，指定节点、脚本来处理
  - 交给节点->组件->函数处理
  - Click Event属性用户添加的每一个事件由节点引用，组件名称和一个响应函数组成。详情见下方的 **Button 点击事件** 部分。
- 

##### label

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402153908233.png" alt="image-20230402153908233" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402154147313.png" alt="image-20230402154147313" style="zoom:50%;" />

##### sprite

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402154332930.png" alt="image-20230402154332930" style="zoom:50%;" />
- trime type设置是否自动裁切空白区域
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402154536045.png" alt="image-20230402154536045" style="zoom:50%;" />

##### mask

- 遮罩、蒙版：限制子节点的可渲染区域
- 自定义形状
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230402155602929.png" alt="image-20230402155602929" style="zoom:67%;" />

### 调试

- 输出到控制台`cc.log()`

### 属性

#### 属性的定义

- `@property(“数据类型”)`:写在属性定义的上一行，属性就会出现在属性面板，使用基本数据类型时可以省略数据类型
  - 脚本将属性显示在属性面板上，可以很方便的调节属性而不需要改变代码，使得代码可以满足不同的需求，很好的实现复用

#### 属性的使用

- 基本属性类型：`string number boolean bigint`
- 引用类型：`cc.Node节点 cc.SpriteFrame图片帧 cc.AudioClip音频`

#### 常用节点属性

- 位置`setPosition(x,y)`
  - 可以传入二/三维向量`cc.v3(0,0,0)`
  - `getPosition()`
  - `cc.Vec2.distance(p1,p2)`传入两个二维向量计算距离
- `angle`设置方向（要转化为角度值）
- 缩放`setSCale()`
  - 也可以传入向量（只不过代表的是缩放倍数）
- 节点禁用启用：active属性
- 显示层级设置`zIndex`
  - 数值越大越xian'shi


### 事件

- 通常在onload中绑定事件
  - `this.node.on("事件名称",处理函数,this)`

#### 键盘事件

- 不属于某个单个节点，是属于系统的事件(全局事件)

- `cc.systemEvent.on('keydown',处理函数,this)`

  - 不是`this.node.on()`

- 示例

  - ```typescript
     onKeyDown(evt:cc.Event.EventKeyboard){
            switch(evt.keyCode){
                case cc.macro.KEY.a:
                    this.node.x-=10;
                    break;
                case cc.macro.KEY.d:
                    this.node.x+=10;
                    break;
                case cc.macro.KEY.w:
                    this.node.y+=10;
                    break;
                case cc.macro.KEY.s:
                    this.node.y-=10;
                    break;
            }
        }
    ```

- 

#### 鼠标（触摸）事件

- 使用touch系列（兼容）

- 单击`this.node.on('mousedown',this.move,this);`(`touchdown`)
- 移动`mousemove`(`touchmove`)
- 抬起`mouseup`(`touchup`)

- `touchcancel`触摸取消（终止），相当于按下了esc

- ```typescript
    this.node.on('touchstart', this.onTouchStart,this);
   onTouchStart(e:cc.Event.EventTouch){}
   ```
  
   - `e.getLocaction()`获取坐标的二维向量

## 补充

### http

- 使用XMLHttpResquest对象

### 脚本的引入

1. **通过 `getComponent` 获取脚本：** `getComponent` 是 Cocos Creator 提供的方法之一，用于在运行时获取指定节点上的组件实例。使用 `getComponent` 方法可以在运行时**动态**获取组件，并通过组件**实例**调用其方法或访问其属性。这种方式适用于**动态场景**，需要根据游戏逻辑获取组件并进行操作。

   示例：

   ```
   const myScript = node.getComponent(MyScript);
   
   // 调用脚本组件的方法
   myScript.myMethod();
   
   // 访问脚本组件的属性
   const value = myScript.myProperty;
   ```

   这种方式是基于游戏对象（节点）的实例获取组件，适用于运行时动态操作。

2. **通过 `import` 导入脚本：** 在 Cocos Creator 中，你可以使用 `import` 语句直接导入脚本文件，并将其**作为一个模块**来使用。通过导入脚本，你可以使用脚本中的方法、类、变量等，并在代码的其他部分进行调用和使用。这种方式适用于在代码的不同部分需要共享脚本中的功能或数据。

   示例：

   ```
   import MyScript from 'MyScript';
   
   // 创建脚本实例
   const myScript = new MyScript();
   
   // 调用脚本的方法
   myScript.myMethod();
   
   // 访问脚本的属性
   const value = myScript.myProperty;
   ```

   这种方式是基于模块的导入，适用于静态的、在多个代码文件中共享脚本功能和数据的情况。

总体来说，`getComponent` 适用于运行时动态获取组件实例并进行操作，而通过 `import` 导入脚本适用于代码的其他部分需要共享脚本功能或数据的情况。选择使用哪种方式取决于你的具体需求和场景。