- 配置安装：[Set Up a Dev Env - libGDX](https://libgdx.com/wiki/start/setup)

## 基本语法

### 日志输出

- ```java
  // 输出 debug 级别 log 
  Gdx.app.debug("MyTag", "my debug message");
  
  // 输出 info 级别 log 
  Gdx.app.log("MyTag", "my informative message");
  
  // 输出 error 级别 log 
  Gdx.app.error("MyTag", "my error message");
  ```

- 限制输出指定的级别：

  ```java
  Gdx.app.setLogLevel(logLevel);
  ```

  - **Application.LOG_NONE：** 所有级别的 log 都不输出；
  - **Application.LOG_DEBUG：** 输出 debug，info，error 级别的 log （即输出所有级别的 log ）；
  - **Application.LOG_INFO：** 输出 info，error 级别的 log ；
  - **Application.LOG_ERROR：** 只输出 error 级别的 log 。

### 生命周期

- ```java
  public class MainGame implements ApplicationListener {
  
  	@Override
  	public void create() {
  	}
  
  	@Override
  	public void resize(int width, int height) {
  	}
  
  	@Override
  	public void render() {
  	}
  
  	@Override
  	public void pause() {
  	}
  
  	@Override
  	public void resume() {
  	}
  
  	@Override
  	public void dispose() {
  	}
  
  }
  ```

- **create()：** 当应用被创建时调用一次。

- **resize(int width, int height)：** 游戏屏幕尺寸改变并且不处于暂停状态将被调用，在 create() 方法之后也会被调用一次。

- **render()：** ApplicationListener 中的游戏循环渲染方法，每时每刻都在被调用。游戏逻辑的更新通常也是在这个方法中被执行。

- **pause()：** 当游戏界面被新的一个界面覆盖时（例如按下 Home 键回到主界面时被主界面覆盖，来电时被来电界面覆盖），该方法将被调用。通常在这里保存暂停时的游戏状态。

- **resume()：** 被其他界面覆盖后（pause 状态后），重新回到游戏界面时，该方法被调用。

- **dispose()：** 当应用被销毁时调用。

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231211102549475.png" alt="image-20231211102549475" style="zoom:33%;" />

### 文件系统

#### FileHandle

- 3 种存储类型的文件

  - **Internal Files：** 内部文件（只读），所有在 assets 资源文件夹中的文件（图片，音频等文件）属于内部文件，最终将被打包进 jar 包或 APK 文件中。
  - **Local Files：** 本地文件（可读写），用于保存一些轻量级的数据，例如保存游戏状态。Android 平台将保存到应用私有目录。
  - **External Files：** 外部文件（可读写），用于保存大文件，例如游戏截屏图片，从网上下载的文件。Android 平台（AndroidManifest.xml 需要配置外部存储器读写权限）将保存到外部 SD 卡中

- 获取实例

  - ```java
    FileHandle intHandle = Gdx.files.internal("data/myfile.txt");
    FileHandle locHandle = Gdx.files.local("data/myfile.txt");
    FileHandle extHandle = Gdx.files.external("data/myfile.txt");
    ```

- 读文件

  - ```java
    FileHandle file = Gdx.files.internal("myfile.txt");
    String text = file.readString();
    ```

- 写文件

  - ```java
    FileHandle file = Gdx.files.local("myfile.txt");
    file.writeString("My god, it's full of stars", false);
    ```

### 键值对存储Preferences

- 获取实例

  - `Preferences prefs = Gdx.app.getPreferences("MyPreferences");`

- 读写数据

  - ```java
    prefs.putString("name", "Donald Duck");
    String name = prefs.getString("name", "No name stored");
    
    prefs.putBoolean("soundOn", true);
    prefs.putInteger("highscore", 10);
    ```

- 保存修改

  - `prefs.flush();`

### 图象渲染

#### 纹理Texture

- 负责解码一个图片文件并加载到 GPU 内存

- 创建

  - ```java
    Texture(FileHandle file)
    Texture(String internalPath)//使用 assets 资源文件夹中的文件的相对路径名创建纹理
    ```

- 常用方法

  - ```java
    int getWidth()//获取纹理的宽度
    int getHeight()//获取纹理的高度
    void dispose()//释放纹理资源
    ```

#### 纹理区域TextureRegion

- 表示 Texture（纹理）的一部分矩形区域，可以用来绘制纹理中的一部分显示在屏幕上

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231211110305782.png" alt="image-20231211110305782" style="zoom:33%;" />

- ```java
  region = new TextureRegion(texture, 0, 0, 128, 128);
  ```

#### 精灵Sprite

- 比 TextureRegion 要强大的多，封装得更完善，除了表示一张图片外，还附加拥有许多属性，例如 在屏幕中的位置/坐标（绘制起点），缩放比，旋转角度，透明度/颜色 等

- ```java
  sprite = new Sprite(texture);
  
  // 设置精灵的位置（左下角绘制起点）
  sprite.setPosition(64, 128);
  
  // 设置 旋转 和 缩放 的 起点（参考点/旋转点/旋转中心）为图片的左下角, 默认为 Sprite（图片）宽高的一半, 即图片的中心点
  sprite.setOrigin(0, 0);
  
  // 设置精灵的旋转角度, 单位为度, 逆时针方向为正
  sprite.setRotation(15.0F);
  
  // 设置精灵的 X 和 Y 轴方向的缩放比, 均缩小为原来的 1/2
  sprite.setScale(0.5F, 0.5F);
  
  // 设置精灵在水平方向取镜像, 竖直方不取镜像
  sprite.flip(true, false);
  sprite.draw(batch);
  ```

#### 纹理画布SpriteBatch

- 主要用于将纹理**绘制**到屏幕上

- SpriteBatch 将对所有绘制的纹理进行批处理并经过优化后发送到 GPU。SpriteBatch 绘制的坐标原点为屏幕左下角

- ```java
  batch = new SpriteBatch();
  public void render() {
      Gdx.gl.glClearColor(1, 0, 0, 1);
      Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
  
      // 绘制开始
      batch.begin();
  
      // 在这里进行各种纹理的绘制
      batch.draw(...);
      ...
          batch.draw(...);
  
      // 绘制结束
      batch.end();
  }
  
  @Override
  public void dispose() {
      // 当应用退出时释放资源
      if (batch != null) {
          batch.dispose();
      }
  }
  ```

### 内存中的图片pixmap

- **Pixmap**:

  - `Pixmap` 是一个关于原始图像数据的高级封装。它代表了一个在内存中的图像，你可以**直接对其进行像素级的操作**，如绘制点、线、矩形、圆形，或者修改单个像素的颜色。
  - `Pixmap` 存储在RAM（随机存取存储器）中，因此它的操作是在CPU上进行的。
  - `Pixmap` 通常用于图像处理或动态图像生成。

- **Texture**:

  - `Texture` 代表了一个上传到GPU（图形处理单元）的图像，用于渲染。
  - 与 `Pixmap` 不同，`Texture` 不能直接用于像素级的操作，因为它存储在显存中，由GPU控制。
  - `Texture` 通常用于游戏中的图像渲染，如渲染角色、背景等。

- ixmap 需要加载为 Texture （纹理）才能绘制到屏幕上

- 在 Pixmap 上绘制图形时的坐标原点为 Pixmap 的左上角，X轴正方向水平向右，Y轴正方向竖直向下。

- ```java
  // 创建一个宽高都为 256, 像素点颜色值格式为 RGBA8888(每个像素颜色值占 4 个字节) 的 Pixmap
  pixmap = new Pixmap(256, 256, Pixmap.Format.RGBA8888);
  
  // 设置绘图颜色为白色
  pixmap.setColor(1, 1, 1, 1);
  // 将整个 pixmap 填充为当前设置的颜色
  pixmap.fill();
  
  // 设置绘图颜色为红色
  pixmap.setColor(1, 0, 0, 1);
  // 画一个空心圆
  pixmap.drawCircle(64, 64, 32);
  
  // 设置绘图颜色为绿色
  pixmap.setColor(Color.GREEN);
  // 画一条线段, 线段两点为 (0, 0) 到 (256, 128)
  pixmap.drawLine(0, 0, 256, 128);
  
  // 设置绘图颜色为蓝色
  pixmap.setColor(Color.BLUE);
  // 画一个矩形, 矩形左上角坐标(128, 128), 宽高均为64
  pixmap.drawRectangle(128, 128, 64, 64);
  
  // 设置绘图颜色为黄色
  pixmap.setColor(Color.YELLOW);
  // 填充一个三角形, 三点(0, 256), (0, 128), (128, 128)
  pixmap.fillTriangle(0, 256, 0, 128, 128, 128);
  
  // pixmap 处理完成后转换成纹理
  texture = new Texture(pixmap);
  ```

## 高级

### 游戏开发框架

- MVC模型
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231211110821961.png" alt="image-20231211110821961" style="zoom:33%;" />
- 场景、舞台、演员
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231211110954167.png" alt="image-20231211110954167" style="zoom:33%;" />
  - **场景**（Screen）： 一个场景可以理解为**一个游戏界面**，类似 Android 中的 Activity，一个游戏由多个场景（界面）组成，通常包括开始界面、游戏 / 关卡界面、帮助界面等。
  - **舞台**（Stage）： 一个舞台可以理解为场景中的**一个图层**，类似 Android 中 FrameLayout / RelativeLayout，一个场景可以包括一个或多个舞台（图层），例如一个“游戏关卡舞台”和一个“结束游戏舞台”，正在游戏时隐藏“结束游戏舞台”，游戏结束时显示“结束游戏舞台”。
  - **演员**（Actor）： 演员表示游戏中的**最基本元素**，类似 Android 中的 TextView / ImageView / Button，一个舞台中包含多个演员，例如 背景图片，游戏人物，怪物，地板，障碍物等。

#### 演员Actor

- 一个演员实例拥有位置（position），矩形尺寸（rectangular size），缩放和旋转的支点（origin），缩放比（scale），旋转角度（rotation），在舞台中的绘制顺序（origin），颜色 / 透明度（color）等属性。

  - 位置（position）属性表示的是在没有旋转也没有缩放时的左下角，缩放和旋转也都围绕该点进行
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231211111730105.png" alt="image-20231211111730105" style="zoom:33%;" />

- 演员类（Actor）直接继承自 Object 类，Actor 类封装了位置、尺寸、缩放比、旋转角度等属性，但没有纹理（Texture）属性，Actor 作为显示在游戏画面上的最基本节点，而 Texture 作为图片的基本表现形式，因此 Actor 类不能直接拿来使用，我们需要**自定义一个 Actor 的子类**，并封装 Texture，然后在绘制的时候根据 Actor 类封装的各种属性将 Texture 经过变换绘制到屏幕上。

- ```java
  package com.libgdx.test;
  
  import com.badlogic.gdx.graphics.g2d.Batch;
  import com.badlogic.gdx.graphics.g2d.TextureRegion;
  import com.badlogic.gdx.scenes.scene2d.Actor;
  
  /**
   * 自定义演员, 重写 act() 和 draw() 这两个方法
   */
  public class MyActor extends Actor {
  
      // 用于展示该演员的纹理区域
      private TextureRegion region;
  
      public MyActor(TextureRegion region) {
          super();
          this.region = region;
  
          // 将演员的宽高设置为纹理区域的宽高（必须设置, 否则宽高默认都为 0, 绘制后看不到）
          setSize(this.region.getRegionWidth(), this.region.getRegionHeight());
      }
  
      public TextureRegion getRegion() {
          return region;
      }
  
      public void setRegion(TextureRegion region) {
          this.region = region;
          // 重新设置纹理区域后, 需要重新设置宽高
          setSize(this.region.getRegionWidth(), this.region.getRegionHeight());
      }
  
      /**
  	 * 演员的逻辑处理
  	 * 
  	 * @param delta
  	 *		表示从渲染上一帧开始到现在渲染当前帧的时间间隔, 或者称为渲染的 时间步 / 时间差。单位: 秒
  	 */
      @Override
      public void act(float delta) {
          super.act(delta);
          // 现在这里一般没有什么逻辑要处理
      }
  
      /**
  	 * 绘制演员
  	 * 
  	 * @param batch
  	 * 		纹理画布, 用于绘制演员封装的纹理。SpriteBatch 就是实现了 Batch 接口
  	 * 
  	 * @param parentAlpha 
  	 * 		父节点的透明度, 处理透明度和演员的颜色属性有关, 稍微复杂, 这里暂时先不处理
  	 */
      @Override
      public void draw(Batch batch, float parentAlpha) {
          super.draw(batch, parentAlpha);
  
          // 如果 region 为 null 或者 演员不可见, 则直接不绘制
          if (region == null || !isVisible()) {
              return;
          }
  
          /* 这里选择一个较为复杂的绘制方法进行绘制
  		batch.draw(
  				region, 
  				x, y, 
  				originX, originY, 
  				width, height, 
  				scaleX, scaleY, 
  				rotation
  		);*/
  
          /*
  		 * 绘制纹理区域
  		 * 将演员中的 位置(position, 即 X, Y 坐标), 缩放和旋转支点(origin), 宽高尺寸, 缩放比, 旋转角度 应用到绘制中,
  		 * 最终 batch 会将综合结果绘制到屏幕上
  		 */
          batch.draw(
              region, 
              getX(), getY(), 
              getOriginX(), getOriginY(), 
              getWidth(), getHeight(), 
              getScaleX(), getScaleY(), 
              getRotation()
          );
      }
  
  }
  //在主程序中使用演员
  actor.act(Gdx.graphics.getDeltaTime());
  batch.begin();
  // 绘制演员（这里暂且先直接绘制, 位置相对于屏幕左下角）
  actor.draw(batch, 1.0F);
  batch.end();
  ```

#### 演员组

- 演员组类（Group）表示的是一组演员，可以包含多个不同层次演员，将多个演员添加到组中作为演员的父节点对多个演员统一管理
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231211113856898.png" alt="image-20231211113856898" style="zoom:50%;" />
- void addActor(Actor actor)： 将演员作为子节点添加到组中。
- void addActorAfter(Actor actorAfter, Actor actor)： 在已在组中的演员 actorAfter 的索引位置后面添加演员 actor。绘制时 actorAfter 先绘制，actor 后绘制。
- void addActorBefore(Actor actorBefore, Actor actor)： 在已在组中的演员 actorBefore 的索引位置前面添加演员 actor。绘制时 actor 先绘制，actorBefore 后绘制。
- void addActorAt(int index, Actor actor)： 在指定索引位置添加一个演员（索引越大先后绘制，即越显示在屏幕前面）。
- boolean removeActor(Actor actor)： 移除组中的一个演员。
- boolean swapActor(Actor first, Actor second)： 交换组中两个演员的位置。
- boolean swapActor(int first, int second)： 根据索引交换组中两个演员的位置。
- void clearChildren()： 移除组中所有演员。
- void clear()： 移除组中所有演员，组的所有动作和监听。
- SnapshotArray<Actor> getChildren()： 获取组中所有的演员。

#### 舞台**Stage**

- float getWidth()： 获取舞台的宽度

- float getHeight()： 获取舞台的高度

- void act(float delta)： 更新舞台逻辑，并批处理舞台中的演员（自动逐个调用演员的 act() 方法更新演员逻辑）

- void draw()： 绘制舞台，并批处理舞台中的演员（自动逐个调用演员的 draw() 方法绘制演员）

- void dispose() : 释放舞台中的所有资源

- boolean addListener(EventListener listener)： 添加事件监听到舞台

- boolean removeListener(EventListener listener)： 移除监听器

- void addActor(Actor actor)： 增加一个演员到舞台中

- void clear()： 移除舞台中的所有演员

- `Array<Actor>` getActors()： 获取舞台中的所有演员

- Group getRoot()： 获取舞台中维护所有演员的演员组

- 舞台类中有增加演员的方法，但没有**移除单个演员**的方法，如果需要移除某个演员，需要调用 stage.getRoot() 方法先获取到舞台的 Group 对象，然后调用 Group 对象的 group.removeActor(actor) 方法。

- ```java
  private Stage stage;
  
  	@Override
  	public void create() {
  		// 创建纹理, badlogic.jpg 图片的宽高为 256 * 256
          texture = new Texture(Gdx.files.internal("badlogic.jpg"));
          // 创建演员, 位置默认为为 (0, 0), 在舞台左下角
          actor = new MyActor(new TextureRegion(texture));
          
          // 使用默认的构造方法创建舞台, 宽高默认为屏幕宽高
          stage = new Stage();
          
          // 将 演员 添加到舞台中, 由舞台去更新演员的逻辑和绘制
          stage.addActor(actor);
  	}
  
  	@Override
  	public void render() {
  		// 黑色清屏
  		Gdx.gl.glClearColor(0, 0, 0, 1);
  		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
  		
  		/*
  		 * 舞台自己维护了纹理画布（SpriteBatch）, 并且在绘制前后自动分别调用了 begin() 和 end() 方法,
  		 * 所以渲染舞台时, 只需要调用舞台的 act() 和 draw() 方法即可
  		 */
  		
  		// 更新舞台逻辑，并批处理舞台中的演员（自动逐个调用演员的 act() 方法更新演员逻辑）
  		stage.act();
  		
  		// 绘制舞台，并批处理舞台中的演员（自动逐个调用演员的 draw() 方法绘制演员）
  		stage.draw();
  	}
  
  	@Override
  	public void dispose() {
  		// 释放纹理资源
  		if (texture != null) {
  			texture.dispose();
  		}
  		// 释放舞台资源
  		if (stage != null) {
  			stage.dispose();
  		}
  	}
  ```

##### 事件处理

-  直接判断事件的输入
  - Gdx.input.isTouched()： 屏幕当前是否被触摸
  - Gdx.input.justTouched()： 屏幕刚刚是否被触摸
  - Gdx.input.isKeyPressed(int keyCode)： 指定按键当前是否处于按下状态
  - Gdx.input.isKeyJustPressed(int keyCode)： 指定按键刚刚是否处于按下状态

- InputProcessor 是输入处理器接口，一个 InputProcess 实例被用来接收输入（触屏/鼠标点击，键盘按键）。而舞台类（Stage）正好是实现了 InputProcess 接口，因此游戏的输入事件监听通常把一个 Stage 对象注册到 Input 中进行接收输入并根据输入分发事件。
- EventListener 是事件监听器接口，一般输入处理器（InputProcessor）接收到后，将输入转换成不同的事件（Event），然后回调相应事件监听器的方法通知监听者。
  - **InputListener**： 输入监听器，将输入事件分的更加细致，包括多个回调方法，例如：
    - keyDown()： 键盘按键按下时被调用（键盘按键事件分为“按下”和“弹起”两个动作）
    - keyUp()： 键盘按键弹起时被调用
    - touchDown()： 触摸屏幕，手指/鼠标按下时被调用（触摸事件可分为手指/鼠标“按下”，“拖动”，“抬起”三个动作）
    - touchDragged()： 触摸屏幕，手指/鼠标按下后在屏幕上拖动时被调用
    - touchUp()： 触摸屏幕，手指/鼠标按下后抬起时被调用
  - **ClickListener**： 点击监听器，通常用于舞台/演员被点击的事件监听。“点击”的定义：**按下 并 抬起后 视为“点击”**。
    - clicked()： 当注册监听的对象（舞台/演员）被点击时调用

- 自定义事件处理

  - ```java
    private class MyInputListener extends InputListener {
        /**
             * 当有键盘按键被按下时调用, 参数 keycode 是被按下的按键的键值, 
             * 所有键盘按键的键值常量定义在 com.badlogic.gdx.Input.Keys 类中
             */
        @Override
        public boolean keyDown(InputEvent event, int keycode) {
            switch (keycode) {
                case Input.Keys.UP: {
                    Gdx.app.log(TAG, "被按下的按键: 方向上键");
                    break;
                }
                case Input.Keys.DOWN: {
                    Gdx.app.log(TAG, "被按下的按键: 方向下键 ");
                    break;
                }
                case Input.Keys.A: {
                    Gdx.app.log(TAG, "被按下的按键: A键");
                    break;
                }
                case Input.Keys.ENTER: {
                    Gdx.app.log(TAG, "被按下的按键: 回车键");
                    break;
                }
                default: {
                    Gdx.app.log(TAG, "其他按键, KeyCode: " + keycode);
                    break;
                }
            }
            return false;
        }
    
        /**
             * 手指/鼠标 按下时调用
             * 
             * @param x 
             *      按下时的 X 轴坐标, 相对于被触摸对象（监听器注册者）的左下角
             * 
             * @param y 
             * 		按下时的 Y 轴坐标, 相对于被触摸对象（监听器注册者）的左下角
             * 
             * @param pointer 
             *      按下手指的ID, 用于多点触控时辨别按下的是第几个手指, 
             *      一般情况下第一只手指按下时 pointer 为 0, 手指未抬起前又有一只手指按下, 则后按下的手指 pointer 为 1。
             *      同一只手指的 按下（touchDown）, 拖动（touchDragged）, 抬起（touchUp）属于同一次序列动作（pointer 值相同）,
             *      pointer 的值在 按下 时被确定, 之后这只手指产生的的 拖动 和 抬起 动作将会把该已确定的 pointer 值传递给其事件方法
             *      touchDragged() 和 touchUp() 方法。 
             * 
             * @return
             *      返回值为 boolean 类型, 用于告诉上一级当前对象（演员/舞台）是否需要处理该次事件。 <br/><br/>
             * 
             *      返回 true: 表示当前对象需要处理该次事件, 则之后这只手指产生的 拖动（touchDragged）和 抬起（touchUp）事件
             *          也会传递到当前对象。<br/><br/>
             * 
             *      返回 false: 表示当前对象不处理该次事件, 既然不处理, 则之后这只手指产生的 拖动（touchDragged）和 抬起（touchUp）事件 
             *          也将不会再传到到当前对象。<br/><br/>
             *      
             *      PS: 当前对象是否处理一只手指的触摸事件（按下, 拖动, 抬起）只在 按下时（touchDown）确定, 
             *          所以之后的 touchDragged() 和 touchUp() 方法中就不再判断, 因此返回类型为 void。
             */
        @Override
        public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
            Gdx.app.log(TAG, "touchDown: " + x + ", " + y + "; pointer: " + pointer);
            return true;
        }
    
        /**
             * 手指/鼠标 按下后拖动时调用
             */
        @Override
        public void touchDragged(InputEvent event, float x, float y, int pointer) {
            Gdx.app.log(TAG, "touchDragged: " + x + ", " + y + "; pointer: " + pointer);
        }
    
        /**
             * 手指/鼠标 抬起时调用
             */
        @Override
        public void touchUp(InputEvent event, float x, float y, int pointer, int button) {
            Gdx.app.log(TAG, "touchUp: " + x + ", " + y + "; pointer: " + pointer);
        }
    }
    
    /**
         * 点击 监听器（只包括 手指点击 或 鼠标点击）
         */
    private class MyClickListener extends ClickListener {
    
        /**
        	 * 对象（演员/舞台）被点击时调用
        	 * 
        	 * @param x 
        	 * 		点击时（手指抬起时）的 X 轴坐标, 相对于被点击对象（监听器注册者）的左下角
        	 * 
        	 * @param y 
        	 * 		点击时（手指抬起时）的 Y 轴坐标, 相对于被点击对象（监听器注册者）的左下角
        	 */
        @Override
        public void clicked(InputEvent event, float x, float y) {
            // 获取响应这个点击事件的演员
            Actor actor = event.getListenerActor();
    
            Gdx.app.log(TAG, "被点击: " + x + ", " + y + "; Actor: " + actor.getClass().getSimpleName());
        }
    }
    
    }
    ```

- 绑定

  - ```java
    // 首先必须注册输入处理器（stage）, 将输入的处理设置给 舞台（Stage 实现了 InputProcessor 接口）
    // 这样舞台才能接收到输入事件, 分发给相应的演员 或 自己处理。
    Gdx.input.setInputProcessor(stage);
    
    // 给舞台添加输入监听器（包括触屏, 鼠标点击, 键盘按键 的输入）
    stage.addListener(new MyInputListener());
    
    // 给演员添加一个 点击 监听器（只包括 手指点击 或 鼠标点击）
    actor.addListener(new MyClickListener());
    
    // 只有需要监听输入的舞台/演员才需要添加监听器
    // 如果要移除指定监听器, 可以调用相应的 removeListener(listener) 方法
    ```

#### 场景Screen

- 一个场景可以理解为一个游戏界面，类似 Android 中的 Activity，一个游戏由多个场景（界面）组成，通常包括开始界面、游戏/关卡界面、帮助界面等。一个场景中可以包含一个或多个舞台。

- 需要自定义场景类实现 Screen 接口，并结合 com.badlogic.gdx.Game 类进行使用，Game 是一个抽象类，直接继承自 Object，并实现了 ApplicationListener 接口（即属于游戏主程序的入口类），**Game 可以看做是 Screen 的父节点或游戏框架的最顶层节点**，可以将 Screen 添加到 Game 中，Game 负责管理 Screen 和其生命周期方法的调用。

- 实现screen接口

  - 也可以**继承ScreenAdapter**，只重写需要的方法

  - ```java
    /**
     * 当该场景被设置到 Game 中成为 Game 的当前场景时被调用
     */
    public void show();
    
    public void resize(int width, int height);
    
    /**
     * 当该场景需要被渲染时被调用
     */
    public void render(float delta);
    
    public void pause();
    
    public void resume();
    
    /**
     * 当有另一个场景被设置为 Game 的当前场景时（即该场景被覆盖/移出当前场景）被调用
     */
    public void hide();
    
    /**
     * 当场景需要被释放所有资源时调用,
     * 注意: 该方法不会自动被调用, 在需要释放场景的所有资源时手动进行调用
     */
    public void dispose();
    ```

- 场景切换

  - ```java
    package com.libgdx.test;
    		
    import com.badlogic.gdx.Game;
    	
    /**
     * 游戏主程序的启动入口类, 要使用场景需要将 MainGame 改为继承 Game 抽象类
     */
    public class MainGame extends Game {
    
    	// 视口世界的宽高统使用 480 * 800, 并统一使用伸展视口（StretchViewport）
    	public static final float WORLD_WIDTH = 480;
    	public static final float WORLD_HEIGHT = 800;
    	
    	// 开始场景
    	private StartScreen startScreen;
    	
    	// 主游戏场景
    	private GameScreen gameScreen;
    
    	@Override
    	public void create() {
    		// 创建开始场景
    		startScreen = new StartScreen(this);
    		
    		// 创建主游戏场景
    		gameScreen = new GameScreen();
    		
    		// 设置当前场景为开始场景
    		setScreen(startScreen);
    	}
    	
    	/**
    	 * 开始场景展示完毕后调用该方法切换到主游戏场景
    	 */
    	public void showGameScreen() {
    		// 设置当前场景为主游戏场景
    		setScreen(gameScreen);
    		
    		if (startScreen != null) {
    			// 由于 StartScreen 只有在游戏启动时展示一下, 之后都不需要展示,
    			// 所以启动完 GameScreen 后手动调用 StartScreen 的 dispose() 方法销毁开始场景。
    			startScreen.dispose();
    			
    			// 场景销毁后, 场景变量值空, 防止二次调用 dispose() 方法
    			startScreen = null;
    		}
    	}
    	
    	@Override
    	public void dispose() {
    		super.dispose(); // super.dispose() 不能删除, 在父类中还有其他操作（调用当前场景的 hide 方法）
    		
    		// 游戏程序退出时, 手动销毁还没有被销毁的场景
    		if (startScreen != null) {
    			startScreen.dispose();
    			startScreen = null;
    		}
    		if (gameScreen != null) {
    			gameScreen.dispose();
    			gameScreen = null;
    		}
    	}
    
    }
    ```

#### 动作Action

- 动作（Action）是附加在演员身上的在指定时间内随着时间推移而被执行的一些任务逻辑。
- 特效类动作
  - **MoveToAction**： 将演员从当前位置移动到指定的位置
  - **RotateToAction**： 将演员从当前角度旋转到指定的角度
  - **ScaleToAction**： 将演员从当前的缩放值过渡到指定的缩放值
  - **SizeToAction**： 将演员从当前尺寸（宽高）过渡到指定尺寸（宽高）
  - **AlphaAction**： 将演员的透明度从当前 alpha 值过渡到指定的 alpha 值
  - **MoveByAction**： 演员在当前位置基础上移动指定的距离
  - **RotateByAction**： 演员在当前角度值的基础上旋转指定的角度
  - **ScaleByAction**： 演员在当前缩放值的基础上进行再次缩放
  - **SizeByAction**： 演员在当前尺寸基础上增加指定的尺寸
- 控制类动作
  - **SequenceAction**： 顺序动作，包含一个或多个动作，这些动作按顺序依次执行。
  - **ParallelAction**： 并行动作，包含一个或多个动作，这些动作一起同时执行。
  - **RepeatAction**： 重复动作，包含一个动作，重复执行这个被包含的动作。
  - **DelayAction**： 延时动作，一般添加到顺序动作的动作序列中使用。例如按顺序执行完某一动作后，执行一个延时动作（延时指定时间），然后再继续执行下一个动作。
  - **AfterAction**： 包含一个动作，该动作和其他动作一起添加到演员身上，等到演员身上的其他所有动作都执行完后，执行该 AfterAction 所包含的动作。
  - **RunnableAction**： 包含一个 Runnable 实例，可以在指定时机执行自己的代码。例如将一个 RunnableAction 添加到顺序动作的末尾，则可在顺序动作执行完成时执行自己的 Runnable 中 run() 方法内的代码。

- ```java
  actor.setPosition(0, 0);
  // 获取一个 MoveTo 动作, 3 秒内移动到 (150, 300) 的位置
  MoveToAction action = Actions.moveTo(150, 300, 3.0F);
  // 将动作附加在演员身上, 执行动作
  actor.addAction(action);
  
  MoveByAction action = Actions.moveBy(100, -200, 2.0F);
  // 将动作附近在演员身上, 执行动作
  actor.addAction(action);
  
  // 移动动作
      MoveToAction moveTo = Actions.moveTo(150, 500, 3.0F);
  // 缩放动作
  ScaleToAction scaleTo = Actions.scaleTo(1.0F, 1.0F, 3.0F);
  // 旋转动作
  RotateByAction rotateBy = Actions.rotateBy(360.0F, 3.0F);
  // 并行动作, 包含 moveTo, scaleTo, rotateBy
  ParallelAction parallelAction = Actions.parallel(moveTo, scaleTo, rotateBy);
  // 执行并行动作
  actor.addAction(parallelAction);
  ```

#### 动画Animation

- ```java
  //walkFrames为纹理序列
  walkAnimation = new Animation(0.05F, walkFrames);
  walkAnimation.setPlayMode(Animation.PlayMode.LOOP);
  //绘制动画
  public void render() {
      // 黑色清屏
      Gdx.gl.glClearColor(0, 0, 0, 1);
      Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
  
      // 累加时间步（stateTime 也可表示游戏的运行时间）
      stateTime += Gdx.graphics.getDeltaTime();
  
      // 根据当前 播放模式 获取当前关键帧, 就是在 stateTime 这个时刻应该播放哪一帧
      currentFrame = walkAnimation.getKeyFrame(stateTime);
  
      batch.begin();
  
      // 绘制当前关键帧
      batch.draw(currentFrame, 50, 100);
  
      batch.end();
  }
  ```

#### 视口Viewport

- 

### 系统控件

- 系统控件本身也是一个（封装好的）演员，演员所拥有的特性（各种属性，附加 Action，添加到舞台管理等），系统控件也均拥有

#### 图片

- ```java
  private Image image;
  image = new Image(new TextureRegion(texture));
  
  // 设置 image 的相关属性
  image.setPosition(100, 200);
  image.setScale(0.5F, 1.0F);
  image.setRotation(-5);
  
  // 添加 image 到舞台
  stage.addActor(image);
  ```

#### 标签

- 由于标签是用来展示文字的，所以使用标签首先要有位图字体（BitmapFont）来 提供字符显示 

  - 使用 hiero 制作得到png和fnt文件，放在assets文件下
  - 要包含所有输入的字符图形

- ```java
  // 标签控件
  private Label label;
  // 位图字体
  private BitmapFont bitmapFont;
  /*
  		 * 第 1 步: 创建 BitmapFont
  		 */
  // 读取 bitmapfont.fnt 文件创建位图字体
  bitmapFont = new BitmapFont(Gdx.files.internal("font/bitmapfont.fnt"));
  
  /*
  		 * 第 2 步: 创建 LabelStyle
  		 */
  // 要创建 Label 首先要创建一个 Label 的样式, 用于指明 Label 所使用的位图字体, 背景图片, 颜色等
  Label.LabelStyle style = new Label.LabelStyle();
  
  // 指定 Label 的背景, 可用纹理区域 textureRegion（在这里背景我就不再设置）
  // style.background = new TextureRegionDrawable(textureRegion);
  
  // 指定 Label 所使用的位图字体
  style.font = bitmapFont;
  
  // 指定 Label 字体的 RGBA 颜色, 在这里我设置为红色
  style.fontColor = new Color(1, 0, 0, 1);
  
  /*
  		 * 第 3 步: 创建 Label
  		 */
  // 根据 Label 的样式创建 Label, 第一个参数表示显示的文本（要显示的文本字符必须在 BitmapFont 中存在）
  label = new Label("Hello Label", style);
  
  // 也可以通过方法设置或获取文本
  // label.setText("Hello");
  // String text = label.getText().toString();
  
  // 设置 Label 的显示位置
  label.setPosition(50, 400);
  
  // 可以通过设置字体的缩放比来控制字体显示的大小
  label.setFontScale(1.5f);
  
  /*
  		 * 第 4 步: 添加到舞台
  		 */
  // 添加 label 到舞台
  stage.addActor(label);
  ```

#### 按钮

- 一个按钮一般可分为两种状态，按下状态和弹起状态，可以使用两张图片分别来表示。

- ```java
  /*
  		 * 第 1 步: 创建 弹起 和 按下 两种状态的纹理
  		 */
  upTexture = new Texture(Gdx.files.internal("button_1.png"));
  downTexture = new Texture(Gdx.files.internal("button_2.png"));
  
  /*
  		 * 第 2 步: 创建 ButtonStyle
  		 */
  Button.ButtonStyle style = new Button.ButtonStyle();
  
  // 设置 style 的 弹起 和 按下 状态的纹理区域
  style.up = new TextureRegionDrawable(new TextureRegion(upTexture));
  style.down = new TextureRegionDrawable(new TextureRegion(downTexture));
  
  /*
  		 * 第 3 步: 创建 Button
  		 */
  button = new Button(style);
  
  // 设置按钮的位置
  button.setPosition(100, 200);
  
  // 给按钮添加点击监听器
  button.addListener(new ClickListener() {
      @Override
      public void clicked(InputEvent event, float x, float y) {
          Gdx.app.log(TAG, "按钮被点击了");
      }
  });
  
  /*
  		 * 第 4 步: 添加 button 到舞台
  		 */
  stage.addActor(button);
  ```

#### 复选框

- ```java
  /*
  		 * 第 1 步: 创建复选框 选中 和 未选中 两种状态的纹理, 以及创建位图字体（用于显示复选框的文本）
  		 */
  checkboxOnTexture = new Texture(Gdx.files.internal("checkbox_on.png"));
  checkboxOffTexture = new Texture(Gdx.files.internal("checkbox_off.png"));
  
  bitmapFont = new BitmapFont();
  
  /*
  		 * 第 2 步: 创建 CheckBoxStyle
  		 */
  CheckBox.CheckBoxStyle style = new CheckBox.CheckBoxStyle();
  
  // 设置 style 的 选中 和 未选中 状态的纹理区域
  style.checkboxOn = new TextureRegionDrawable(new TextureRegion(checkboxOnTexture));
  style.checkboxOff = new TextureRegionDrawable(new TextureRegion(checkboxOffTexture));
  
  // 设置复选框文本的位图字体
  style.font = bitmapFont;
  
  // 也可以设置复选框文本的字体颜色（RGBA）
  // style.fontColor = new Color(1, 0, 0, 1);
  
  /*
  		 * 第 3 步: 创建 CheckBox
  		 */
  checkBox = new CheckBox("Hello", style);
  
  // 设置复选框的位置
  checkBox.setPosition(100, 200);
  
  // 可以手动设置复选框的选中状/未选中态
  // checkBox.setChecked(true);
  
  // 设置复选框的（选中/未选中）状态改变监听器
  checkBox.addListener(new ChangeListener() {
      @Override
      public void changed(ChangeEvent event, Actor actor) {
          Gdx.app.log(TAG, "复选框是否被选中: " + checkBox.isChecked());
      }
  });
  
  /*
  		 * 第 4 步: 添加 checkBox 到舞台
  		 */
  stage.addActor(checkBox);
  ```

#### 文本框

- 文本框主要用于提供给用户输入文字，获取用户输出

- ```java
  /*
  		 * 第 1 步: 创建文本框背景纹理, 光标纹理, 以及创建位图字体（用于显示文本框中的文本）
  		 * 
  		 * 为了方便演示, 这里创建纹理不再用图片来创建, 而是使用 Pixmap 来创建
  		 */
  bgTexture = createBackgroundTexture();
  cursorTexture = createCursorTexture();
  
  // 为了方便演示, 这里直接使用 gdx.jar 中自带的字体文件创建位图字体（只要在 BitmapFont 中包含有的字符才能够被输入）
  bitmapFont = new BitmapFont();
  
  // gdx.jar 中自带的字体比较小, 这里放大一下
  bitmapFont.getData().setScale(2.0F);
  
  /*
  		 * 第 2 步: 创建 TextFieldStyle
  		 */
  TextField.TextFieldStyle style = new TextField.TextFieldStyle();
  
  // 设置背景纹理区域
  style.background = new TextureRegionDrawable(new TextureRegion(bgTexture));
  
  // 设置光标纹理区域
  style.cursor = new TextureRegionDrawable(new TextureRegion(cursorTexture));
  
  // 设置文本框显示文本的字体来源
  style.font = bitmapFont;
  
  // 设置文本框字体颜色为白色
  style.fontColor = new Color(1, 1, 1, 1);
  
  /*
  		 * 第 3 步: 创建 TextField
  		 */
  usernameTextField = new TextField("", style);
  passwordTextField = new TextField("", style);
  
  // 设置文本框的宽高
  usernameTextField.setSize(TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT);
  passwordTextField.setSize(TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT);
  
  // 设置文本框的位置
  usernameTextField.setPosition(90, 500);
  passwordTextField.setPosition(90, 430);
  
  // 文本框中的文字居中对齐
  usernameTextField.setAlignment(Align.center);
  passwordTextField.setAlignment(Align.center);
  
  // 用于显示密码的文本框, 需要将文本框设置为密码模式
  passwordTextField.setPasswordMode(true);
  // 显示密码时用 * 号代替密码字符
  passwordTextField.setPasswordCharacter('*');
  
  /*
  		 * 第 4 步: 添加 TextField 到舞台
  		 */
  stage.addActor(usernameTextField);
  stage.addActor(passwordTextField);
  ```

### 高级工具

#### 音频

- Music：适合用来表示长时间的音乐（例如背景音乐），Music 支持暂停、恢复、循环播放等操作。

- Sound：一个 Sound 实例表示一个简短的音频剪辑，可以并行播放无数次，Sound 会把整个音效都加载到内存中，所以只能加载一些较小的音频文件

- ```java
  Music music = Gdx.audio.newMusic(FileHandle);
  Sound sound = Gdx.audio.newSound(FileHandle);
  ```

- 把音频文件也放在assets下面

- ```java
  // 加载背景音乐, 创建 Music 实例
  music = Gdx.audio.newMusic(Gdx.files.internal("mymusic.ogg"));
  
  // 背景音乐设置循环播放
  music.setLooping(true);
  
  // 设置音量, 值范围 0.0 ~ 1.0
  // music.setVolume(float volume);
  
  // 手动暂停播放, 暂停播放后调用 play() 将从暂停位置开始继续播放
  // music.pause();
  
  // 手动停止播放, 停止播放后调用 play() 将从头开始播放
  // music.stop();
  
  // 手动播放音乐, 这里游戏启动时开始播放背景音乐
  music.play();
  
  // 加载音效, 创建 Sound 实例
  sound = Gdx.audio.newSound(Gdx.files.internal("mysound.ogg"));
  sound.play();
  ```

- 

#### 资源管理器

- 资源管理器（AssetManager）主要负责统一加载和管理 纹理（Texture）、纹理图集（TextureAtlas）、位图字体（BitmapFont）、音乐（Music）、音效（Sound） 等 assets 文件夹中的资源。

- ```java
  // 创建资源管理器
  manager = new AssetManager();
  
  // 加载资源
  manager.load(BADLOGIC, Texture.class);
  manager.load(LOGO, Texture.class);
  
  // 阻塞线程, 等待资源加载完毕
  manager.finishLoading();
  
  //检查是否加载完成
  boolean texIsLoaded = manager.isLoaded("data/mytexture.png");
  boolean fontIsLoaded = manager.isLoaded("data/myfont.fnt");
  
  // 加载完毕后获取资源实例
  badlogicTexture = manager.get(BADLOGIC, Texture.class);
  logoTexture = manager.get(LOGO, Texture.class);
  ```

#### 碰撞检测Rectangle

- 在程序中通常先获取到主角/地板/障碍物/子弹/怪物的包围矩形 Rectangle，然后在通过 Rectangle 中的方法进行碰撞关系判断。

- 构造方法

  - ```java
    // 默认构造方法, 坐标宽高全为 0
    public Rectangle();
    
    // 通过指定的 左下角坐标点 和 宽高 创建矩形对象
    public Rectangle(float x, float y, float width, float height);
    ```

- 碰撞检测

  - ```java
    // 矩形是否包含指定的点（指定的点是否在矩形中）
    boolean contains(float x, float y)
    boolean	contains(Vector2 point)
    
    // 矩形是否包含指定的矩形（otherRect 矩形是否完全在 this 矩形内）
    boolean	contains(Rectangle otherRect)；
    
    // 判断两个矩形是否相同（坐标和宽高是否都相等）
    boolean	equals(Object obj) 
    
    // 矩形是否和指定的矩形有重叠部分（是否有碰撞）
    boolean overlaps(Rectangle otherRect);
    
    // 矩形是否包含指定的点（指定的点是否在矩形中）
    boolean contains(float x, float y)
    boolean	contains(Vector2 point)
    
    // 矩形是否包含指定的矩形（otherRect 矩形是否完全在 this 矩形内）
    boolean	contains(Rectangle otherRect)；
    
    // 判断两个矩形是否相同（坐标和宽高是否都相等）
    boolean	equals(Object obj) 
    
    // 矩形是否和指定的矩形有重叠部分（是否有碰撞）
    boolean overlaps(Rectangle otherRect);
    ```

#### 网络

- Net 接口提供了跨平台执行网络操作的方法，比如简单的 HTTP get 和 post 请求，TCP 服务端/客户端 socket 通信。