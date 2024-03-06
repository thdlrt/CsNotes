参考：[android_interview/android/basis/broadcastreceiver.md at master · LRH1993/android_interview (github.com)](https://github.com/LRH1993/android_interview/blob/master/android/basis/broadcastreceiver.md)

##  概述

### 工程结构

- Android- Manifest.xml配置文件

  - ```xml
    <application
            android:allowBackup="true"
            android:dataExtractionRules="@xml/data_extraction_rules"
            android:fullBackupContent="@xml/backup_rules"
            android:icon="@mipmap/ic_launcher"
            android:label="@string/app_name"
            android:roundIcon="@mipmap/ic_launcher_round"
            android:supportsRtl="true"
            android:theme="@style/Theme.BaiduDemo"
            tools:targetApi="31">
    ```

    - 基本配置信息

  - ```xml
    <activity android:name=".lesson2.LessonTwoActivity"
    android:exported="true">
       <intent-filter>
           <action android:name="android.intent.action.MAIN" />
           <category android:name="android.intent.category.LAUNCHER" />
       </intent-filter>
    </activity>
    ```

    - 对MainActivity进⾏注册，并表⽰MainActivity是这个项⽬的主Activity，在⼿机上点击应⽤图标，⾸先启动的就是这个Activity。(必须要设置一个主activity)

- activity：

  - ```
    class LessonTwoActivity : AppCompatActivity() {
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
        }
    }
    ```

    - 项⽬中所有⾃定义的Activity都必须继承它或者它的⼦类才能拥有Activity的特性，该文件中存储程序的逻辑
    - 在res/layout文件夹中以xml的格式设置布局（上面的activity_main）
      - 在activity中引用ui配置`setContentView(R.layout.first_layout)`

- res文件结构

  - drawable⽤来放图⽚
  - mipmap放应⽤图标
  - values放字符串、样式、颜⾊等配置
  - layout⽤来放布局⽂件的
  - 引用方式`R.文件类型.app_name`或`@文件类型/app_name`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230717204404071.png" alt="image-20230717204404071" style="zoom:33%;" />

- gradle

### 日志调试

- 分类
  - Log.v()。⽤于打印那些最为琐碎的、意义最⼩的⽇志信息。对应级
    别verbose，是Android⽇志⾥⾯级别最低的⼀种。
  - Log.d()。⽤于打印⼀些调试信息，这些信息对你调试程序和分析问
    题应该是有帮助的。对应级别debug，⽐verbose⾼⼀级。
  - Log.i()。⽤于打印⼀些⽐较重要的数据，这些数据应该是你⾮常想
    看到的、可以帮你分析⽤户⾏为的数据。对应级别info，⽐debug⾼⼀
    级。
  - Log.w()。⽤于打印⼀些警告信息，提⽰程序在这个地⽅可能会有潜
    在的⻛险，最好去修复⼀下这些出现警告的地⽅。对应级别warn，⽐
    info⾼⼀级。
  - Log.e()。⽤于打印程序中的错误信息，⽐如程序进⼊了catch语句
    中。当有错误信息打印出来的时候，⼀般代表你的程序出现严重问题
    了，必须尽快修复。对应级别error，⽐warn⾼⼀级。

-  `Log.v("tag","msg")`
- 

## activity视图

- 重写成员`ctrl+o`
- 销毁，调用`finish()`
- 为activity设置主题（如对话框）`android:theme="@style/Theme.AppCompat.Dialog"`

### View视图

- 每个`Activity`都包含一个用户界面，这个用户界面是由一个或多个`View`对象组成的。

  - **用户输入控件**：例如按钮（Button）、复选框（CheckBox）、单选按钮（RadioButton）、下拉列表（Spinner）、滑动条（SeekBar）等。
  - **文本和图像**：例如文本视图（TextView）、图像视图（ImageView）、图像按钮（ImageButton）等。
  - **布局**：这些是特殊的`View`，称为`ViewGroup`，它们包含其他的`View`或`ViewGroup`，并管理它们的布局。例如线性布局（LinearLayout）、相对布局（RelativeLayout）、帧布局（FrameLayout）、约束布局（ConstraintLayout）等。
  - **其他特殊的`View`**：例如进度条（ProgressBar）、滑动面板（ScrollView）、列表视图（ListView）、网格视图（GridView）、卡片视图（CardView）等

- 使用 view判断触发的组件（响应事件）

  - ```kotlin
    override fun onClick(v: View?) {
            when (v) {
                binding.send -> {
                    val content = binding.inputText.text.toString()
                    if (content.isNotEmpty()) {
                        val msg = Msg(content, Msg.TYPE_SENT)
                        msgList.add(msg)
                        adapter?.notifyItemInserted(msgList.size - 1)
    // 当有新消息时,刷新RecyclerView中的显⽰
                        binding.recyclerView.scrollToPosition(msgList.size - 1)
    // 将RecyclerView定位到最后⼀⾏
                        binding.inputText.setText("") // 清空输⼊框中的内容
                    }
                }
            }
        }
    ```

- 可以将layout界面转化为view对象进一步操作

  - `val view = LayoutInflater.from(parent.context).inflate(R.layout.fruit_item, parent, false)`

### Intent交互

#### activity切换

- 显式Intent

  - `Intent(ContextpackageContext, Class<?> cls)`
    - 第⼀个参数Context要求提供⼀个启动Activity的**上下⽂**；第⼆个参数Class⽤于指定想要启动的⽬标Activity,以构建出Intent的“意图”
    - 再使用`startActivity(intent)`执行切换
  - 返回时  只需要销毁新的activity即可返回上一个activity

- 隐式Intent

  - 并不明确指出想要启动哪⼀个Activity，⽽是指定了⼀系列更为抽象的action和category等信息，然后交由系统去分析这个Intent，并帮我们找出合适的Activity去启动。

  - 在`AndroidManifest.xml`配置activity可以响应的内容

    - ```xml
      <activity android:name=".SecondActivity" >
      	<intent-filter>
      		<action
      android:name="com.example.activitytest.ACTION_START" />
      		<category android:name="android.intent.category.DEFAULT" />
      	</intent-filter>
      </activity>
      ```

    - 指明了当前Activity可以响应com.example.activitytest.ACTION_START这个action

    - 可以设置多个响应

    - 作为默认activity

      - ```xml
        <intent-filter>
             <action android:name="android.intent.action.MAIN" />
             <category android:name="android.intent.category.LAUNCHER" />
        </intent-filter>
        ```

  - 只有`<action>`和`<category>`中的内容同时匹配Intent中指定的action和category
    时，这个Activity才能响应该Intent。

  - ```kotlin
    button1.setOnClickListener {
        val intent = Intent("com.example.activitytest.ACTION_START")
        intent.addCategory("com.example.activitytest.MY_CATEGORY")
        startActivity(intent)
    }
    ```

    - 在调⽤startActivity()⽅法的时候会⾃动将`android.intent.category.DEFAULT`添加到Intent中（如果不手动指定）

  - 我们还可以在`<intent-filter>`标签中再配置⼀个`<data>`标签，⽤于更精确地指定当前Activity能够响应的数据。

    - android:scheme。⽤于指定数据的协议部分，如上例中的https部分。
    - android:host。⽤于指定数据的主机名部分，如上例中的www.baidu.com部分。
    - android:port。⽤于指定数据的端⼝部分，⼀般紧随在主机名之后。
    - android:path。⽤于指定主机名和端⼝之后的部分，如⼀段⽹址中跟在域名之后的内容。
    - android:mimeType。⽤于指定可以处理的数据类型，允许使⽤通配符的⽅式进⾏指定。

  - 当有多个可相应的activity时会交由用户选择

- 向下一个activity传递数据

  - 以键值对的形式传递数据

  - 在发送之前添加`intent.putExtra("extra_data", data)`

  - 获取数据`val extraData = intent.getStringExtra("extra_data")`

    - getStringExtra()、getIntExtra()、getBooleanExtra()

  - 参数接口（规范数据传输）

    - ```kotlin
      class SecondActivity : BaseActivity() {
          ...
          companion object {
              fun actionStart(context: Context, data1: String, data2:String) {
                  val intent = Intent(context,SecondActivity::class.java)
                  intent.putExtra("param1", data1)
                  intent.putExtra("param2", data2)
                  context.startActivity(intent)
              }
          }
      }
      //使用apply的写法
      val intent = Intent(context, SecondActivity::class.java).apply {
          putExtra("param1", "data1")
          putExtra("param2", "data2")
      }
      context.startActivity(intent)
      //启动方式
      button1.setOnClickListener {
          SecondActivity.actionStart(this, "data1", "data2")
      }
      ```
  
- 向上一个activity返回数据

  - 在前一个activity中使用`startActivityForResult(intent, 1)`开启跳转（1为唯一的请求码）

  - 在后一个activity中

    - ```kotlin
      button2.setOnClickListener {
          val intent = Intent()
          intent.putExtra("data_return", "Hello FirstActivity")//附加数据
          setResult(RESULT_OK, intent)//传回附带参数的intent
          finish()
      }
      ```

  - 由于我们是使⽤startActivityForResult()⽅法来启动SecondActivity的，在SecondActivity被销毁之后会**回调**上⼀个Activity的onActivityResult()⽅法，因此我们需要在FirstActivity中**重写**这个⽅法来得到返回的数据

    - ```kotlin
      override fun onActivityResult(requestCode: Int, resultCode: Int,
      data: Intent?) {
      	super.onActivityResult(requestCode, resultCode, data)
      		when (requestCode) {
      			1 -> if (resultCode == RESULT_OK) {//对应的请求码
      				val returnedData = data?.getStringExtra("data_return")
      			Log.d("FirstActivity", "returned data is
      $returnedData")
      		}
      	}
      }
      ```

    - onActivityResult()⽅法带有3个参数：第⼀个参数requestCode，即我们在启动Activity时传⼊的请求码；第⼆个参数resultCode，即我们在返回数据时传⼊的处理结果；第三个参数data，即携带着返回数据的Intent。

  - 不过如果用户没有通过button2返回而是直接左划back不会传回数据，因此也要对back进行重写

    - ```kotlin
      override fun onBackPressed() {
          val intent = Intent()
          intent.putExtra("data_return", "Hello FirstActivity")
          setResult(RESULT_OK, intent)
          finish()
      }
      ```

#### 内置action

- 调用系统浏览器打开网页

  - ```kotlin
    button1.setOnClickListener {
        val intent = Intent(Intent.ACTION_VIEW)
        intent.data = Uri.parse("https://www.baidu.com")
        startActivity(intent)
    }
    ```

- 调用系统拨号

  - ```kotlin
    button1.setOnClickListener {
        val intent = Intent(Intent.ACTION_DIAL)
        intent.data = Uri.parse("tel:10086")
        startActivity(intent)
    }
    ```

### 生命周期

- ⽣命周期中最多可能会有4种状态

  - 运⾏状态：当⼀个Activity位于返回栈的栈顶时，Activity就处于运⾏状态。

  - 暂停状态：当⼀个Activity不再处于栈顶位置，但仍然可⻅时，Activity就进⼊了暂停状态。（如被弹窗挡住一部分）
  - 停⽌状态：当⼀个Activity不再处于栈顶位置，并且完全不可⻅的时候，就进⼊了停⽌状态。
  - 销毁状态：⼀个Activity从返回栈中移除后就变成了销毁状态。

- 生命周期回调

  - onCreate()：Activity第⼀次被创建的时候调⽤。完成Activity的初始化操作，⽐如加载布局、绑定事件等。
    - ⼀般情况下，⼀个Activity会在onCreate()⽅法中完成各种初始化操作，⽽在onDestroy()⽅法中完成释放内存的操作。
  - onStart()。这个⽅法在Activity由**不可⻅变为可⻅**的时候调⽤。
    - Activity在onStart()⽅法和onStop()⽅法之间所经历的就是可⻅⽣存期。可以通过这两个⽅法合理地管理那些对⽤户可⻅的资源。
  - onResume()。这个⽅法在Activity准备好和⽤户进⾏交互的时候调⽤。此时的Activity⼀定位于返回栈的栈顶，并且处于运⾏状态。
    - Activity在onResume()⽅法和onPause()⽅法之间所经历的就是前台⽣存期
  - onPause()。这个⽅法在系统准备去启动或者恢复另⼀个Activity的时候调⽤。
  - onStop()。这个⽅法在Activity**完全不可⻅**的时候调⽤。
    - 不应执行太耗时的操作
    - 从`A Activity`打开`B Activity`
      分别执行`A onPause()、B onCreate()、B onStart()、B onResume()、A onStop()`方法。
    - 关闭`B Activity`
      分别执行`B onPause()、A onRestart()、A onStart()、A onResume()、B onStop()、B onDestroy()`方法。
  - onDestroy()。这个⽅法在Activity**被销毁之前**调⽤，之后Activity的状态将变为销毁状态。
  - onRestart()。这个⽅法在Activity由停⽌状态变为运⾏状态之前调⽤，也就是Activity被重新启动了。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230716234506110.png" alt="image-20230716234506110" style="zoom: 50%;" />

- 当一个activity被回收时会丢失其中暂存的数据，需要进行缓存，从而在重新创建时恢复

  - onSaveInstanceState()回调⽅法，这个⽅法可以保证在Activity被
    回收之前⼀定会被调⽤，因此我们可以通过这个⽅法来进行缓存

  - ```kotlin
    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        val tempData = "Something you just typed"
        outState.putString("data_key", tempData)
    }
    ```

  - 创建时其实就有一个 Bundle数据，从中取出数据即可

    - ```kotlin
      override fun onCreate(savedInstanceState: Bundle?) {
          super.onCreate(savedInstanceState)
          Log.d(tag, "onCreate")
          setContentView(R.layout.activity_main)
          if (savedInstanceState != null) {
              val tempData = savedInstanceState.getString("data_key")
              Log.d(tag, "tempData is $tempData")
          }
          ...
      }
      ```

##### 特殊情况的生命周期

- 横竖屏切换
  - 在Activity由于异常情况下终止时，系统会调用**onSaveInstanceState**来保存当前Activity的状态。这个方法的调用是在**onStop之前**，它和onPause没有既定的时序关系，该方法只在Activity被异常终止的情况下调用。当异常终止的Activity被**重建**以后，系统会调用**onRestoreInstanceState**，并且把Activity销毁时onSaveInstanceState方法所保存的Bundle对象参数同时传递给onRestoreInstanceState和onCreate方法。
    - <img src="https://camo.githubusercontent.com/2a3ceb59c3e7851daea9a0dff4e669eb261ae0dfbaa6eca22dc1fcce37545a50/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d323364393034373166613766313264322e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom: 80%;" />
  - 横竖屏切换的生命周期：onPause()->onSaveInstanceState()-> onStop()->onDestroy()->onCreate()->onStart()->onRestoreInstanceState->onResume()
- 由于资源不足Activity被杀死
  - 优先级分类：
    -  前台Activity——正在和用户交互的Activity，优先级最高。
    - 可见但非前台Activity——比如Activity中弹出了一个对话框，导致Activity可见但是位于后台无法和用户交互。
    - 后台Activity——已经被暂停的Activity，比如执行了onStop，优先级最低。

##### 数据加载时机

- **数据大小**：如果数据量很大或者加载数据需要较长时间，应考虑在**后台线程**（例如使用 `AsyncTask`、`Coroutine` 或 `RxJava`）中加载数据，以避免UI线程阻塞，从而保证流畅的用户体验。
- **数据更新频率**：对于经常变化的数据，你可能需要在 `onResume()` 或者其它适当的生命周期方法中重新加载或更新。而对于不经常变化的数据，只需要在 `onCreate()` 中加载一次即可。

#### 控制类

- 可以重写基类，并改让其他activity继承该类 而不是原始基类来实现对activity的处理

- 重写基类

  - ```kotlin
    open class BaseActivity : AppCompatActivity() {
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            Log.d("BaseActivity", javaClass.simpleName)
            ActivityCollector.addActivity(this)
        }
        override fun onDestroy() {
            super.onDestroy()
            ActivityCollector.removeActivity(this)
        }
    }
    ```

  - javaClass表示获取当前实例的对象

- 添加activity控制类，维护activity，集中控制（实现关闭全部activity等）

  - 可以在控制类中做许多事，如绑定全局事件等等
  
  - ```kotlin
    object ActivityCollector {
        private val activities = ArrayList<Activity>()
        fun addActivity(activity: Activity) {
            activities.add(activity)
        }
        fun removeActivity(activity: Activity) {
            activities.remove(activity)
        }
        fun finishAll() {
            for (activity in activities) {
                if (!activity.isFinishing) {
                    activity.finish()
                }
            }
            activities.clear()
        }
    }
    ```
  

### 启动模式

- 通过给`<activity>`标签指定android:launchMode属性来选择启动模式

- 在5.0之后跨应用调用时新启动的Activity就会放入一个新创的栈

- standard
  - Activity默认的启动模式
  - 对于使⽤standard模式的Activity，系统不会在乎这个Activity是否已经在返回栈中存在，每次启动都会创建⼀个该Activity的新实例。
  - 即可以创建一个activity的多个实例
- singleTop栈顶复用
  - 在启动Activity时如果发现返回栈的**栈顶**已经是该Activity，则认为可以直接使⽤它，不会再创建新的Activity实例
  - 但是并不代表每个activity只会有一个，只是保证顶层只有一个
  - 在通知栏点击收到的通知，然后需要启动一个Activity，这个Activity就可以用singleTop，否则每次点击都会新建一个Activity。
- singleTask栈内复用
  - 当Activity的启动模式指定为singleTask，每次启动该Activity时，系统⾸先会在返回栈中检查是否存在该Activity的实例，如果发现已经存在则直接使⽤该实例，并把在这个Activity之上的所有其他Activity统统**出栈**，如果没有发现就会创建⼀个新的Activity实例。
  - 可以手动指定要进入的栈，每个Activity都有taskAffinity属性，这个属性**指出了它希望进入的Task**。如果Activity指定的栈**不存在，则创建一个栈**，并把创建的Activity压入栈内。如果Activity指定的栈存在，如果其中没有该Activity实例，则会创建Activity并压入栈顶，如果其中有该Activity实例，则把该Activity实例之上的Activity杀死清除出栈，重用并让该Activity实例处在栈顶，然后调用onNewIntent()方法。
  - 当我们第一次进入主界面之后，主界面位于栈底，以后不管我们打开了多少个Activity，只要我们再次回到主界面，都应该使用将主界面Activity**上所有的Activity移除**的方式来让主界面Activity处于栈顶，而不是往栈顶新加一个主界面Activity的实例，通过这种方式能够保证退出应用时所有的Activity都能报销毁。
- singleInstance单例
  - 会启⽤⼀个新的返回栈来管理这个Activity，不管是哪个应⽤程序来访问这个Activity，都共⽤同⼀个返回栈，也就解决了共享Activity实例的问题。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230717101257718.png" alt="image-20230717101257718" style="zoom:33%;" />
  - 打开该Activity时，**直接创建一个新的任务栈**，并创建该Activity实例放入新栈中。一旦该模式的Activity实例已经存在于某个栈中，任何应用再激活该Activity时都会重用该栈中的实例。

#### 前台栈和后台栈的交互

- 假如目前有两个任务栈。前台任务栈为AB，后台任务栈为CD，这里假设CD的启动模式均为singleTask,现在请求启动D，那么**这个后台的任务栈都会被切换到前台**
  - <img src="https://camo.githubusercontent.com/796afbc8136b4404ce0a3b7361ce25dfecbcf604e5d1ada5097551b1e0152fc7/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d346165623139343762626132376534342e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />
  - <img src="https://camo.githubusercontent.com/2a1accaf4f4fe23931a9023d30ae0aa64560f2269a72dfdab1663f73505acb28/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d663265616631303035636466316231642e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />

### 组件获取

- 获取ui组件`val button1: Button = findViewById(R.id.button1)`
  - 必须显示声明类型

#### 视图绑定

- 在build.gradle中引入

  - ```kotlin
    android {
        viewBinding {
            enabled = true
        }
        dataBinding{
            enabled = true
        }
    }
    ```

- 为某个模块启用视图绑定功能后，系统会为该模块中包含的每个 XML 布局文件生成一个绑定类,对于不想进行试图绑定的布局添加属性

  - ```kotlin
    <LinearLayout tools:viewBindingIgnore="true" >
    </LinearLayout>
    ```

- 系统会通过以下方式生成绑定类的名称：将 XML 文件的名称转换为驼峰式大小写，并在末尾添加“Binding”一词。
  - result_profile.xml->ResultProfileBinding

- activity中使用

  - ```kotlin
     private lateinit var binding: ResultProfileBinding
      
        override fun onCreate(savedInstanceState: Bundle) {
            super.onCreate(savedInstanceState)
            binding = ResultProfileBinding.inflate(layoutInflater)
            val view = binding.root
            setContentView(view)
        }
    ```

    - 调用生成的绑定类中包含的静态 `inflate()` 方法。此操作会创建该绑定类的实例以供 Activity 使用。
    - 通过调用 `getRoot()` 方法或使用 [Kotlin 属性语法](https://kotlinlang.org/docs/reference/properties.html#declaring-properties)获取对根视图的引用。
    - 将根视图传递到 [`setContentView()`](https://developer.android.google.cn/reference/kotlin/android/app/Activity?hl=zh-cn#setcontentview_1)，使其成为屏幕上的活动视图。

### 数据绑定

### 响应

- 信号绑定

  - ```kotlin
    button1.setOnClickListener {
                Toast.makeText(this, "You clicked Button 1",
                    Toast.LENGTH_SHORT).show()
            }
    ```

### 交互

- 消息气泡提示`Toast.makeText(this, "You clicked Button 1",Toast.LENGTH_SHORT).show()`

## Service服务

- Service的运⾏不依赖于任何⽤户界⾯，即使程序被切换到后台，或者⽤户打开了另外⼀个应⽤程序，Service仍然能够保持正常运⾏。Service并不是运⾏在⼀个独⽴的进程当中的，⽽是依赖于创建Service时所在的应⽤程序进程。需要在Service的内部⼿动创建⼦线程，并在这⾥执⾏具体的任务

### 服务分类

- 运行地点：
  - 本地服务：依附在主进程，随主进程的终止而终止，如音乐播放器等不需要常驻的服务
  - 远程服务：独立进程，如跨应用服务（天气查询），硬件通讯等
- 运行类型：
  - 前台服务：通知栏有显示，如音乐播放器
  - 后台服务：不会在通知栏显示，如日期同步、邮件同步
- 使用方式：
  - startService启动：启动服务作为后台任务，不进行通信，使用stopService停止
  - bindService启动：要进行通信的服务，使用unbindService停止
  - 同时使用：同时使用两种停止

### 生命周期

- <img src="https://camo.githubusercontent.com/64b60032e7d886a21adf8de58ebd4ed92d710933380fda2693a2ce93bb14eb7e/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d383536313461646462626563376130632e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom: 80%;" />
- **OnCreate()**：系统在service第一次创建时执行此方法，来执行**只运行一次的**初始化工作。如果service已经运行，这个方法不会被调用。
- **onStartCommand()**：每次客户端调用startService()方法启动该Service都会回调该方法（**多次调用**）。一旦这个方法执行，service就启动并且在后台长期运行。通过调用stopSelf()或stopService()来停止服务。
- **OnBind()**：当组件调用bindService()想要绑定到service时(比如想要执行进程间通讯)系统调用此方法（**一次调用**，一旦绑定后，下次再调用bindService()不会回调该方法）。在你的实现中，你必须提供一个返回一个**IBinder来以使客户端能够使用它与service通讯**，你必须总是实现这个方法，但是如果你不允许绑定，那么你应返回null。（可以通过返回的IBinder来获取Service对象）
- **OnUnbind()**：当前组件调用unbindService()，想要解除与service的绑定时系统调用此方法
- **OnDestory()**:系统在service不再被使用并要销毁时调用此方法。
- 1：第一次 startService 会触发 onCreate 和 onStartCommand，以后在服务运行过程中，每次 startService 都**只会触发 onStartCommand**；不论 startService 多少次，stopService **一次就会停止服务**
- 2：如果一个Service在某个Activity中被调用bindService方法启动，不论bindService被调用几次，Service的onCreate方法只会执行一次（onBind也是），同时onStartCommand方法始终不会调用。Service会一直运行，除非调用u**nbindService来解除绑定**、**断开连接或调用该Service的Context不存在**
- 混合型：当一个Service在被启动(startService)的同时又被绑定(bindService)，该Service将会一直在后台运行，并且不管调用几次，onCreate方法始终只会调用一次，**onStartCommand的调用次数与startService调用的次数一致**（使用bindService方法不会调用onStartCommand）。同时，**调用unBindService将不会停止Service，必须调用stopService或Service自身的stopSelf来停止服务。**（同时也应该解绑）

#### 使用选择

- 如果你只是想要启动一个后台服务长期进行某项任务那么使用 startService 便可以了。
- 如果你想要**与正在运行的 Service 取得联系**，那么有两种方法，一种是使用 broadcast ，另外是使用 bindService ，前者的缺点是如果交流较为频繁，容易造成性能上的问题，并且 BroadcastReceiver 本身执行代码的时间是很短的
- 混合启动方式提供了 Service 的灵活性和稳定性，比如音乐播放器中需要bind绑定，便于在任务栏实时观看，又需要在不断开连接下能自由启动停止服务。

### 多线程编程

- 创建线程

  - ```kotlin
    class MyThread : Thread() {
        override fun run() {
            // 编写具体的逻辑
        }
    }
    ```

- 运行线程

  - `MyThread().start()`

- 更为简洁的方法

  - ```kotlin
    thread {
    // 编写具体的逻辑
    }
    runOnUiThread{// 在这⾥进⾏UI操作
     	...
    }
    ```

#### AsyncTask

- 在一个进程中频繁地创建和销毁线程，显然不是高效的做法。正确的做法是采用线程池，一个**线程池**中会缓存一定数量的线程，通过线程池就可以避免因为频繁创建和销毁线程所带来的系统开销。
- syncTask是一个抽象类，它是由Android封装的一个轻量级异步类
  - AsyncTask的内部封装了**两个线程池**(SerialExecutor和THREAD_POOL_EXECUTOR)和**一个Handler**(InternalHandler)。
  - 其中SerialExecutor线程池用于任务的排队，让需要执行的多个耗时任务，按顺序排列，THREAD_POOL_EXECUTOR线程池才真正地执行任务，InternalHandler用于从工作线程切换到主线程
- 异步任务的实例必须在**UI线程**中创建，即AsyncTask对象必须在UI线程中创建。
- 一个任务实例**只能执行一次**，如果执行第二次将会抛出异常。

- 泛型参数`public abstract class AsyncTask<Params, Progress, Result>`

  - Params。在执⾏AsyncTask时**需要传⼊的参数**，可⽤于在后台任务中使⽤。
  - Progress。在后台任务执⾏时，如果需要在界⾯上**显⽰当前的进度**，则使⽤这⾥指定的泛型作为进度单位。
  - Result。当任务执⾏完毕后，如果需要对结果进⾏返回，则使⽤这⾥指定的泛型作为**返回值类型**。
  - 如`class DownloadTask : AsyncTask<Unit, Int, Boolean>() {...}`
    - 第⼀个泛型参数指定为Unit，表⽰在执⾏AsyncTask的时候不需要传⼊参数给后台任务。第⼆个泛型参数指定为Int，表⽰使⽤整型数据来作为进度显⽰单位。第三个泛型参数指定为Boolean，则表⽰使⽤布尔型数据来反馈执⾏结果。

- 重写方法

  - `onPreExecute()`在后台任务开始执⾏之前调⽤，⽤于进⾏⼀些界⾯上的**初始化操作**，⽐如显⽰⼀个进度条对话框等。
  -  `doInBackground(Params...)`这个⽅法中的所有代码都会在**⼦线程**中运⾏，我们应该在这⾥去处理所有的**耗时任务**。任务⼀旦完成，就可以通过return语句将任务的执⾏结果返回，如果AsyncTask的第三个泛型参数指定的是Unit，就可以不返回任务执⾏结果。注意，在这个⽅法中是不可以进⾏UI操作的,可以调⽤publishProgress (Progress...)⽅法来完成。
  - `onProgressUpdate(Progress...)`，通过`publishProgress(Progress...)`调用，**在这个⽅法中可以对UI进⾏操作**(在主线程中进行)
  - `onPostExecute(Result)`当后台任务执⾏完毕并通过return语句进⾏返回时，这个⽅法就很快会被调⽤。返回的数据会作为参数传递到此⽅法中。

- ```kotlin
  class DownloadTask : AsyncTask<Unit, Int, Boolean>() {
      override fun onPreExecute() {
          progressDialog.show() // 显⽰进度对话框
      }
      override fun doInBackground(vararg params: Unit?) = try {
          while (true) {
              val downloadPercent = doDownload() // 这是⼀个虚构的⽅法
              publishProgress(downloadPercent)
              if (downloadPercent >= 100) {
                  break
              }
          }
          true
      } catch (e: Exception) {
          false
      }
      override fun onProgressUpdate(vararg values: Int?) {
          // 在这⾥更新下载进度
          progressDialog.setMessage("Downloaded ${values[0]}%")
      }
      override fun onPostExecute(result: Boolean) {
          progressDialog.dismiss()// 关闭进度对话框
          // 在这⾥提⽰下载结果
          if (result) {
              Toast.makeText(context, "Download succeeded", Toast.LENGTH_SHORT).show()
          } else {
              Toast.makeText(context, " Download failed", Toast.LENGTH_SHORT).show()
          }
      }
  }
  
  //启动任务
  DownloadTask().execute()
  ```

#### HandlerThread

- andlerThread是Google帮我们封装好的，可以用来执行多个耗时操作，而不需要多次开启线程，里面是采用Handler和Looper实现的。（替代线程池）

- 使用

  - 实例`HandlerThread handlerThread = new HandlerThread("myHandlerThread");`

  - 启动`handlerThread.start();`

  - 与Handler绑定

    - ```java
      mThreadHandler = new Handler(mHandlerThread.getLooper()) {
          @Override
          public void handleMessage(Message msg) {
              checkForUpdate();
              if(isUpdate){
                  mThreadHandler.sendEmptyMessage(MSG_UPDATE_INFO);
              }
          }
      };
      ```

- 实例

  - ```java
    public class MyActivity extends AppCompatActivity {
    
        private HandlerThread handlerThread;
        private Handler handler;
        private OkHttpClient httpClient;
    
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);
    
            httpClient = new OkHttpClient();
    
            // 创建和启动 HandlerThread
            handlerThread = new HandlerThread("HttpHandlerThread");
            handlerThread.start();
    
            // 使用 HandlerThread 的 Looper 创建 Handler
            handler = new Handler(handlerThread.getLooper());
            
            // 每隔一秒发送 HTTP 请求
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    sendHttpRequest();
                    handler.postDelayed(this, 1000);  // 循环发送
                }
            }, 1000);
        }
    
        private void sendHttpRequest() {
            Request request = new Request.Builder()
                    .url("https://example.com/api/data")
                    .build();
    
            httpClient.newCall(request).enqueue(new Callback() {
                @Override
                public void onFailure(Call call, IOException e) {
                    e.printStackTrace();
                }
    
                @Override
                public void onResponse(Call call, Response response) throws IOException {
                    if (response.isSuccessful()) {
                        String responseBody = response.body().string();
                        // 处理返回的数据
                    }
                }
            });
        }
    
        @Override
        protected void onDestroy() {
            super.onDestroy();
            handler.removeCallbacksAndMessages(null);  // 移除所有回调和消息
            handlerThread.quitSafely();  // 安全地结束 HandlerThread
        }
    }
    
    ```

### Service基本使用

- 需要注册

  - ```kotlin
    <service
    android:name=".MyService"
    android:enabled="true"
    android:exported="true">
    ```

- 重写方法

  - `onBind()`：用于联系activity与service，实现除了启动/关闭之外的更多交互

    - ```kotlin
      private val mBinder = DownloadBinder()
      class DownloadBinder : Binder() {
          fun startDownload() {
              Log.d("MyService", "startDownload executed")
          }
          fun getProgress(): Int {
              Log.d("MyService", "getProgress executed")
              return 0
          }
      }
      override fun onBind(intent: Intent): IBinder {
          return mBinder
      }
      ```

    - 当⼀个Activity和Service绑定了之后，就可以调⽤该Service⾥的Binder提供的⽅法了。

  - `onCreate`：在Service创建的时候调⽤

  - `onStartCommand`：在每次Service启动的时候调⽤

  - `onDestroy`：在Service销毁的时候调⽤

- 内部结束`stopSelf()`

- 启动：

  - ```kotlin
    val intent = Intent(this, MyService::class.java)
    startService(intent) // 启动Service
    ```

  - 只有第一次启动时会同时调用onCreate和onStartCommand，之后只会调用onStartCommand

- 终止：

  - ```kotlin
    val intent = Intent(this, MyService::class.java)
    stopService(intent) // 停⽌Service
    ```

- ```kotlin
  class MainActivity : AppCompatActivity() {
      lateinit var downloadBinder: MyService.DownloadBinder
      private val connection = object : ServiceConnection {
          override fun onServiceConnected(name: ComponentName, service: IBinder) {
              downloadBinder = service as MyService.DownloadBinder
              downloadBinder.startDownload()
              downloadBinder.getProgress()
          }
          override fun onServiceDisconnected(name: ComponentName) {
          }
      }
      override fun onCreate(savedInstanceState: Bundle?) {
          ...
          bindServiceBtn.setOnClickListener {
              val intent = Intent(this, MyService::class.java)
              bindService(intent, connection, Context.BIND_AUTO_CREATE) // 绑定Service
          }
          unbindServiceBtn.setOnClickListener {
              unbindService(connection) // 解绑Service
          }
      }
  }
  ```

#### 前台service

- 会有⼀个正在运⾏的图标在系统的状态栏显⽰，避免后台被系统自动关闭

- 对onCreate进行修改

  - ```kotlin
    override fun onCreate() {
        super.onCreate()
        Log.d("MyService", "onCreate executed")
        val manager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel("my_service", "前台Service通知", NotificationManager.IMPORTANCE_DEFAULT)
            manager.createNotificationChannel(channel)
        }
        val intent = Intent(this, MainActivity::class.java)
        val pi = PendingIntent.getActivity(this, 0, intent, 0)
        val notification = NotificationCompat.Builder(this, "my_service")
        .setContentTitle("This is content title")
        .setContentText("This is content text")
        .setSmallIcon(R.drawable.small_icon)
        .setLargeIcon(BitmapFactory.decodeResource(resources, R.drawable.large_icon))
        .setContentIntent(pi)
        .build()
        startForeground(1, notification)
    }
    ```

#### 多线程

- Service中的代码都是默认运⾏在主线程当中的，需要创建子线程来执行一些操作

- 在`onStartCommand`内创建线程

  - ```kotlin
    thread {
    // 处理具体的逻辑
    stopSelf()//关闭线程
    }
    ```

### IntentService

- `IntentService` 是 Android 提供的一个特殊的 `Service` 子类，设计用于执行后台任务。当它接收一个启动请求时（通常是通过一个 `Intent`），它会将该 `Intent` 添加到工作队列，然后依次处理每个 `Intent`。`IntentService` 运行在一个单独的工作线程中，因此它可以执行长时间的操作，而不会影响主线程。用于**依次处理**后台任务。

- 使用

  - **创建一个继承自 `IntentService` 的子类**：

    - ```kotlin
      class MyIntentService : IntentService("MyIntentService") {
          override fun onHandleIntent(intent: Intent?) {
              // 执行任务，例如下载文件、上传数据等
          }
      }
      ```

  - **启动服务**：你可以像启动普通的 `Service` 那样启动 `IntentService`。

    - ```kotlin
      val intent = Intent(this, MyIntentService::class.java)
      startService(intent)
      ```

## BroadcastReceiver广播机制

- 标准⼴播是⼀种完全异步执⾏的⼴播，在⼴播发出之后，所有的BroadcastReceiver⼏乎会在**同⼀时刻**收到这条⼴播消息，因此它们之间没有任何先后顺序可⾔。
- 有序⼴播则是⼀种同步执⾏的⼴播，在⼴播发出之后，同⼀时刻只会有⼀个BroadcastReceiver能够收到这条⼴播消息，当这个BroadcastReceiver中的逻辑执⾏完毕后，⼴播才会继续传递。（顺序传递）

### 实现原理

- 使用设计模式中的观察者模式
- <img src="https://camo.githubusercontent.com/02d7f9103dbf61f95d4896cc111700240c140e527d01f5384486380c87368c3c/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d303839366261386439313535313430652e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />
- 广播接收者 通过 `Binder`机制在 `AMS` 注册
- 广播发送者 通过 `Binder` 机制向 `AMS` 发送广播
- `AMS` 根据 广播发送者 要求，在已注册列表中，寻找合适的广播接收者
- `AMS`将广播发送到合适的广播接收者相应的消息循环队列中；
- 广播接收者通过 消息循环 拿到此广播，并回调 `onReceive()`

<img src="https://camo.githubusercontent.com/abe7d72b051318e58e429c8987d4c227ccaec2a5170dc000f098dd8cf54aa02a/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d376339666636353665626431623938312e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />

### 注册

- 注册BroadcastReceiver，接受指定类型的广播

- 动态注册

  - 动态广播最好在Activity的onResume()注册、onPause()注销。注意内存泄漏以及重复注册注销。

  - 新建⼀个类，让它继承⾃BroadcastReceiver，并重写⽗类的onReceive()⽅法就⾏了。这样当有⼴播到来时，onReceive()⽅法就会得到执⾏，具体的逻辑就可以在这个⽅法中处理。

  - 此外创建事件过滤器并将**指定的事件**与事件响应函数绑定

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        lateinit var timeChangeReceiver: TimeChangeReceiver
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            //创建事件过滤器，并添加事件类型
            val intentFilter = IntentFilter()
            intentFilter.addAction("android.intent.action.TIME_TICK")
            //创建并 绑定事件处理函数
            timeChangeReceiver = TimeChangeReceiver()
            registerReceiver(timeChangeReceiver, intentFilter)
        }
        override fun onDestroy() {
            super.onDestroy()
            //销毁时必须解除绑定
            unregisterReceiver(timeChangeReceiver)
        }
        inner class TimeChangeReceiver : BroadcastReceiver() {
            //事件处理
            override fun onReceive(context: Context, intent: Intent) {
                Toast.makeText(context, "Time has changed",Toast.LENGTH_SHORT).show()
            }
        }
    }
    ```

- 静态注册

  - 让程序在**未启动的情况**下也能接收⼴播

  - 以收到开机信号`android.intent.action.BOOT_COMPLETED`为例（开机自启）

  - 设置响应函数的方法相同

    - ```kotlin
      class BootCompleteReceiver : BroadcastReceiver() {
          override fun onReceive(context: Context, intent: Intent) {
              Toast.makeText(context, "Boot Complete",Toast.LENGTH_LONG).show()
          }
      }
      ```

  - AndroidManifest.xml⽂件中注册

    - 使用内置方法创建时会自动注册：右击com.example.broadcasttest包→New→Other→Broadcast Receiver

      - Exported属性表⽰是否允许这个BroadcastReceiver接收本程序以外的⼴播

    - ```xml
      <manifest xmlns:android="http://schemas.android.com/apk/res/android"
                package="com.example.broadcasttest">
          <uses-permissionandroid:name="android.permission.RECEIVE_BOOT_COMPLETED" />
          <application
                       android:allowBackup="true"
                       android:icon="@mipmap/ic_launcher"
                       android:label="@string/app_name"
                       android:roundIcon="@mipmap/ic_launcher_round"
                       android:supportsRtl="true"
                       android:theme="@style/AppTheme">
              ...
              <receiver
                        android:name=".BootCompleteReceiver"
                        android:enabled="true"
                        android:exported="true">
                  <intent-filter>
                      <actionandroid:name="android.intent.action.BOOT_COMPLETED" />
                  </intent-filter>
              </receiver>
          </application>
      </manifest>
      ```

    - 使用android:name来记录响应的action

    - 接收系统的开机⼴播就是需要进⾏权限声明的，使⽤`<uses-permission>`标签声明了android.permission.RECEIVE_BOOT_COMPLETED权限。

- 通常事件绑定和取消都是在`onCreate()和onDestroy()`中进行的，但是如果希望只有最上层的activity响应事件（如在控制类中的全局事件处理会被每个activity继承，造成重复响应）

  - 可以在`onResume()和onPause()`中处理来解决


### 发送广播

- 通过intent对象发送广播

- 标准广播

  - ```kotlin
    val intent = Intent("com.example.broadcasttest.MY_BROADCAST")
    intent.setPackage(packageName)
    sendBroadcast(intent)
    ```

  - 传⼊要发送的广播的值并设置目标应用（当前的）包名，最后执行发送

  - 安卓8.0之后无法通过隐式注册接收不指定目标应用程序的广播 

- 有序广播

  - 发送`sendOrderedBroadcast(intent, null)`

  - 设定BroadcastReceiver的先后顺序：通过android:priority属性给BroadcastReceiver设置了优先级，优先级⽐较⾼的BroadcastReceiver就可以先收到⼴播(数值越大优先级越高)

  - 优先级高的接收器可以阻断信号的继续传播

    - ```kotlin
      class MyBroadcastReceiver : BroadcastReceiver() {
          override fun onReceive(context: Context, intent: Intent) {
              Toast.makeText(context, "received in MyBroadcastReceiver",Toast.LENGTH_SHORT).show()
              abortBroadcast()//终止传递
          }
      }
      ```
      
  
- 系统广播
  - 系统内置，如监听网络变化，飞行模式开关等
  - 只需要在注册广播接收者时定义相关的action即可
- 应用内广播
  - App应用内广播可理解为一种局部广播，广播的发送者和接收者都同属于一个App。
  - 相比于全局广播（普通广播），App应用内广播优势体现在：安全性高 & 效率高

## 数据与存储

### 持久化存储

#### ⽂件存储

- 写入文件 ：openFileOutput()⽤于将数据存储到指定的⽂件中

  - 指定存储文件的名称（`/data/data/<package name>/files/`目录下）和写入方式（MODE_PRIVATE和MODE_APPEND覆盖、附加）

  - ```kotlin
    fun save(inputText: String) {
        try {
            val output = openFileOutput("data", Context.MODE_PRIVATE)
            val writer = BufferedWriter(OutputStreamWriter(output))
            writer.use {
                it.write(inputText)
            }//Lambda表达式中的代码全部执⾏完之后⾃动将外层的流关闭
        } catch (e: IOException) {//可选
            e.printStackTrace()
        }
    }
    ```

- 读取文件：`openFileInput()`

  - 读取`/data/data/<package name>/files/`目录下的文件

  - ```kotlin
    fun load(): String {
        val content = StringBuilder()
        try {
            val input = openFileInput("data")
            val reader = BufferedReader(InputStreamReader(input))
            reader.use {
                reader.forEachLine {
                    content.append(it)
                }
            }
        } catch (e: IOException) {
            e.printStackTrace()
        }
        return content.toString()
    }
    ```

#### SharedPreferences存储

- 使⽤键值对的⽅式来存储数据

- 获取SharedPreferences对象

  - Context类中的getSharedPreferences()⽅法
    - 第⼀个参数⽤于指定SharedPreferences⽂件的名称，如果指定的⽂件不存在则会创建⼀个（`/data/data/<package name>/shared_prefs/`目录下），
    - 第⼆个参数⽤于指定操作模式，⽬前只有默认的MODE_PRIVATE这⼀种模式可选（只有当前的应⽤程序才可以对这个SharedPreferences⽂件进⾏读写）
  - Activity类中的getPreferences()⽅法
    - 只有当前的应⽤程序才可以对这个SharedPreferences⽂件进⾏读写

- 存储数据

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            saveButton.setOnClickListener {
                val editor = getSharedPreferences("data",Context.MODE_PRIVATE).edit()
                editor.putString("name", "Tom")//添加数据
                editor.putInt("age", 28)
                editor.putBoolean("married", false)
                editor.apply()//提交更改
            }
        }
    }
    ```

  - 化简

    - ```kotlin
      getSharedPreferences("data", Context.MODE_PRIVATE).edit {
          putString("name", "Tom")
          putInt("age", 28)
          putBoolean("married", false)
      }
      ```

- 读取数据

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            ...
            restoreButton.setOnClickListener {
                val prefs = getSharedPreferences("data",Context.MODE_PRIVATE)
                val name = prefs.getString("name", "")
                val age = prefs.getInt("age", 0)
                val married = prefs.getBoolean("married", false)
                Log.d("MainActivity", "name is $name")
                Log.d("MainActivity", "age is $age")
                Log.d("MainActivity", "married is $married")
            }
        }
    }
    ```

  - 第⼀个参数是键，传⼊存储数据时使⽤的键就可以得到相应的值了。

  - 第⼆个参数是默认值，即表⽰当传⼊的键找不到对应的值时会以什么样的**默认值**进⾏返回。

#### SQLite数据库存储

- 使用`SQLiteOpenHelper`创建数据库
  - SQLiteOpenHelper中有两个抽象⽅法：onCreate()和onUpgrade()。我们必须在⾃⼰的帮助类⾥重写这两个⽅法，然后分别在这两个⽅法中实现**创建和更新**数据库的逻辑。
  - 构建出SQLiteOpenHelper的实例之后使用getReadableDatabase()和getWritableDatabase()。（`data/data/<package name>/databases/`）这两个⽅法都可以创建或打开⼀个现有的数据库（如果数据库已存在则直接打开，否则要创建⼀个新的数据库），并返回⼀个可对数据库**进⾏读写操作的对象**。
    - 当数据库不可写⼊的时候（如磁盘空间已满），getReadableDatabase()⽅法返回的对象将以只读的⽅式打开数据库，⽽getWritableDatabase()⽅法则将出现异常。

- 数据类型：integer表⽰整型，real表⽰浮点型，text表⽰⽂本类型，blob表⽰⼆进制类型

  - ```sql
    create table Book (
    id integer primary key autoincrement,
    author text,
    price real,
    pages integer,
    name text)
    ```

  - primarykey将id列设为主键

  - autoincrement关键字表⽰id列是⾃增⻓的

- ```kotlin
  class MyDatabaseHelper(val context: Context, name: String, version:Int) :
  SQLiteOpenHelper(context, name, null, version) {
      private val createBook = "create table Book (" +
      " id integer primary key autoincrement," +
      "author text," +
      "price real," +
      "pages integer," +
      "name text)"
      override fun onCreate(db: SQLiteDatabase) {
          //完成一些初始化如建表等工作
          db.execSQL(createBook)//执行SQL语句
          Toast.makeText(context, "Create succeeded",Toast.LENGTH_SHORT).show()
      }
      override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int,newVersion: Int) {
      }
  }
  
  //创建
  val dbHelper = MyDatabaseHelper(this, "BookStore.db", 1)
  dbHelper.writableDatabase
  ```

- 升级数据库：由于只会在不存在数据库时调用create创建，而已经存在时不会创建只会返回已经存在的对象，需要删除原先的文件

  - 删除表再重新调用创建

    - ```kotlin
      override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
          db.execSQL("drop table if exists Book")
          db.execSQL("drop table if exists Category")
          onCreate(db)
      }
      ```

  - 创建版本号大于1的对象即可调用升级函数`val dbHelper = MyDatabaseHelper(this, "BookStore.db", 2)`

  - 但是这种方法会丢失原先数据库的数据，改进：

    - ```kotlin
      class MyDatabaseHelper(val context: Context, name: String, version:Int):
      SQLiteOpenHelper(context, name, null, version) {
          private val createBook = "create table Book (" +
          " id integer primary key autoincrement," +
          "author text," +
          "price real," +
          "pages integer," +
          "name text)"
          private val createCategory = "create table Category (" +
          "id integer primary key autoincrement," +
          "category_name text," +
          "category_code integer)"
          override fun onCreate(db: SQLiteDatabase) {
              db.execSQL(createBook)
              db.execSQL(createCategory)
          }
          override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
              if (oldVersion <= 1) {
                  db.execSQL(createCategory)
              }
          }
      }
      ```

    - 这样当⽤户直接安装第2版的程序时，就会进⼊onCreate()⽅法，将**两张表⼀起创建**。⽽当⽤户使⽤第2版的程序覆盖安装第1版的程序时，就会进⼊升级数据库的操作中，此时由于Book表已经存在了，因此**只需要创建⼀张**Category表即可。

  - 针对不同旧版本升级来的用户进行分类讨论，进行更新

- 使用Database Navigator插件编辑创建的db数据库文件

  - 打开DB Browser
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230719112327513.png" alt="image-20230719112327513" style="zoom:33%;" />
  - 导入文件<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230719112344700.png" alt="image-20230719112344700" style="zoom:33%;" />

##### 数据操作

- 借助`SQLiteDatabase`对象对数据库进行操作

- 添加数据insert

  - 第⼀个参数是表名；第⼆个参数⽤于在未指定添加数据的情况下给某些可为空的列⾃动赋值NULL（⼀般我们⽤不到这个功能，直接传⼊null即可）；第三个参数是⼀个ContentValues对象

  - ```kotlin
    val db = dbHelper.writableDatabase
    val values1 = ContentValues().apply {
        // 开始组装第⼀条数据
        put("name", "The Da Vinci Code")
        put("author", "Dan Brown")
        put("pages", 454)
        put("price", 16.96)
    }
    db.insert("Book", null, values1) // 插⼊第⼀条数据
    val values2 = ContentValues().apply {
        // 开始组装第⼆条数据
        put("name", "The Lost Symbol")
        put("author", "Dan Brown")
        put("pages", 510)
        put("price", 19.95)
    }
    db.insert("Book", null, values2) // 插⼊第⼆条数据
    ```

  - 快速构建数据集

    - ```kotlin
      val values = contentValuesOf("name" to "Game of Thrones", "author" to
      "George Martin",
      "pages" to 720, "price" to 20.85)
      ```

- 更新数据update

  - 第⼀个参数是表名；第⼆个参数是ContentValues；第三、第四个参数⽤于约束更新某⼀⾏或某⼏⾏中的数据，不指定的话默认会更新所有⾏。

  - ```kotlin
    val db = dbHelper.writableDatabase
    val values = ContentValues()
    values.put("price", 10.99)//要修改的字段
    db.update("Book", values, "name = ?", arrayOf("The Da VinciCode"))
    ```

  - 为了减少SQL注入攻击 ，使用参数化查询(变量?和具体值分开)当存在多个?时，只需要让后面的数组有对应数目的项即可

  - 相当于`where`筛选

- 删除数据 delete

  - 第⼀个参数是表名；第⼆、第三个参数⽤于约束删除某⼀⾏或某⼏⾏的数据，不指定的话默认会删除所有⾏。

  - ```kotlin
    val db = dbHelper.writableDatabase
    db.delete("Book", "pages > ?", arrayOf("500"))
    ```

- 查询数据 query

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230719115355143.png" alt="image-20230719115355143" style="zoom:50%;" />

  - 调⽤query()⽅法后会返回⼀个Cursor对象，查询到的所有数据都将从这个对象中取出。

  - ```kotlin
    val db = dbHelper.writableDatabase
    // 查询Book表中所有的数据
    val cursor = db.query("Book", null, null, null, null, null, null)
    if (cursor.moveToFirst()) {
    //将数据的指针移动到第⼀⾏的位置,准备开始遍历
        do {
            // 遍历Cursor对象，取出数据并打印
            val name =cursor.getString(cursor.getColumnIndex("name"))
            val author =cursor.getString(cursor.getColumnIndex("author"))
            val pages =cursor.getInt(cursor.getColumnIndex("pages"))
            val price =cursor.getDouble(cursor.getColumnIndex("price"))
            Log.d("MainActivity", "book name is $name")
            Log.d("MainActivity", "book author is $author")
            Log.d("MainActivity", "book pages is $pages")
            Log.d("MainActivity", "book price is $price")
        } while (cursor.moveToNext())
    }
    cursor.close()//关闭
    ```

    - 通过Cursor的getColumnIndex()⽅法获取某⼀列在表中对应的位置索引，然后将这个索引传⼊相应的取值⽅法中，就可以得到从数据库中读取到的数据了。

- 使用SQL操作

  - ```kotlin
    db.execSQL("insert into Book (name, author, pages, price) values(?, ?,?, ?)",
    arrayOf("The Da Vinci Code", "Dan Brown", "454", "16.96")
    )
    
    val cursor = db.rawQuery("select * from Book", null)
    ```

##### 事务

- ```kotlin
  val db = dbHelper.writableDatabase
  db.beginTransaction() // 开启事务
  try {
      db.delete("Book", null, null)
      /*
      if (true) {
          // ⼿动抛出⼀个异常，让事务失败
          throw NullPointerException()
      }
      */
      val values = ContentValues().apply {
          put("name", "Game of Thrones")
          put("author", "George Martin")
          put("pages", 720)
          put("price", 20.85)
      }
      db.insert("Book", null, values)
      db.setTransactionSuccessful() // 事务已经执⾏成功
  } catch (e: Exception) {
      e.printStackTrace()
  } finally {
      db.endTransaction() // 结束事务
  }
  ```

  - 先调⽤SQLiteDatabase的beginTransaction()⽅法**开启⼀个事务**，然后在⼀个**异常捕获的代码块**中执⾏具体的数据库操作，当所有的操作都完成之后，调⽤setTransactionSuccessful()表⽰事务**已经执⾏成功了**，最后在finally代码块中调⽤endTransaction()**结束事务**。

### ContentProvider跨应用数据交互

- <img src="https://camo.githubusercontent.com/3d97174ca9577d6a8cbcbc93785bb752951c254264bcd2eae023517c2b84285c/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d336334333339633566316434613066642e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:33%;" />

- 可以选择将一部分数据共享给其他应用，而一些数据不共享

- ContentProvider主要以表格的形式组织数据

#### 运行时权限

- 用户不需要在安装软件的时候⼀次性授权所有申请的权限，⽽是可以在软件的使⽤过程中再对某⼀项权限申请进⾏授权

- Android现在将常⽤的权限⼤致归成了两类，⼀类是普通权限，⼀类是危险权限。普通权限系统会⾃动帮我们进⾏授权；危险权限必须由⽤户⼿动授权才可以，否则程序就⽆法使⽤相应的功能

- android6后除了AndroidManifest.xml中静态注册权限，对于一些危险权限还要再运行时进行动态申请

- 危险权限

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230719133127690.png" alt="image-20230719133127690" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230719133138561.png" alt="image-20230719133138561" style="zoom:33%;" />

- ```kotlin
  class MainActivity : AppCompatActivity() {
      override fun onCreate(savedInstanceState: Bundle?) {
          super.onCreate(savedInstanceState)
          setContentView(R.layout.activity_main)
          makeCall.setOnClickListener {
              //首先检查是否具有权限，没有权限则需要申请
              if (ContextCompat.checkSelfPermission(this,  Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                  //请求权限
                  ActivityCompat.requestPermissions(this,  arrayOf(Manifest.permission.CALL_PHONE), 1)
              } else {
                  call()
              }
          }
      }
      //处理权限请求结果的回调
      override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
          super.onRequestPermissionsResult(requestCode, permissions, grantResults)
          when (requestCode) {
              //根据请求码进行处理
              1 -> {
                  //检查授权结果
                  if (grantResults.isNotEmpty() &&
                      grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                      call()
                  } else {
                      Toast.makeText(this, "You denied the permission",Toast.LENGTH_SHORT).show()
                  }
              }
          }
      }
      private fun call() {
          try {
              val intent = Intent(Intent.ACTION_CALL)
              intent.data = Uri.parse("tel:10086")
              startActivity(intent)
          } catch (e: SecurityException) {
              e.printStackTrace()
          }
      }
  }
  ```

#### 统一资源标识符URI

- 唯一标识 ContentProvider & 其中的数据
- <img src="https://camo.githubusercontent.com/56b7f3d1be49a53d21d31463a616686e872bc1c2096fc6c3c92557a78b9e8955/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d393630313961323035346562323763662e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />
- 

#### 访问其他程序中的数据

- 如果⼀个应⽤程序通过ContentProvider对其数据提供了外部访问接⼝，那么任何其他的应⽤程序都可以对这部分数据进⾏访问，一切操作都通过`contentResolver`对象来进行

- 通过Uri作为路径对数据进行访问，通常使用包名+表名的组合，如`content://com.example.app.provider/table1`

  - 还需要将字符串解析为Uri对象`val uri = Uri.parse("content://com.example.app.provider/table1")`

- 数据获取query

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230719135451770.png" alt="image-20230719135451770" style="zoom:33%;" />
  - 操作与SQLite类似，也是获取cursor对象，只是把表名换为Uri

- 对于危险权限（如获取通讯录等）都需要先申请获取权限之后 再进行操作

  - ```kotlin
    rivate fun readContacts() {
        // 查询联系⼈数据
        contentResolver.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null, null, null, null)?.apply {
            while (moveToNext()) {
                // 获取联系⼈姓名
                val displayName = getString(getColumnIndex(
                    ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME))
                // 获取联系⼈⼿机号
                val number = getString(getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER))
                contactsList.add("$displayName\n$number")
            }
            adapter.notifyDataSetChanged()
            close()
        }
    }
    ```

#### 创建ContentProvider

- 将需要共享的数据共享给其他程序，**进程**间共享数据的本质是：添加、删除、获取 & 修改（更新）数据

- ```kotlin
  class MyProvider : ContentProvider() {
      override fun onCreate(): Boolean {
          return false//初始化成功/失败
      }
      override fun query(uri: Uri, projection: Array<String>?, selection: String?, selectionArgs: Array<String>?, sortOrder: String?): Cursor? {
          return null//Cursor格式返回结果
      }
      override fun insert(uri: Uri, values: ContentValues?): Uri? {
          return null//返回⼀个⽤于表⽰这条新记录的URI
      }
      override fun update(uri: Uri, values: ContentValues?, selection: String?, selectionArgs: Array<String>?): Int {
          return 0//受影响的⾏数将作为返回值返回
      }
      override fun delete(uri: Uri, selection: String?, selectionArgs: Array<String>?): Int {
          return 0//被删除的⾏数将作为返回值返回
      }
      override fun getType(uri: Uri): String? {
          return null
      }
  }
  ```

  - 需要重写全部的6个抽象方法

- 可以在这个内容URI的后⾯加上⼀个id`content://com.example.app.provider/table1/1`表示要找id为1的数据

  - 通配符：*表⽰匹配任意⻓度的任意字符；#表⽰匹配任意⻓度的数字。

- 借助UriMatcher这个类就可以轻松地实现匹配内容URI的功能

  - `UriMatcher`可以用来帮助`ContentProvider`确定请求的数据属于哪种类型，或者来自哪个数据表或数据集。这样，`ContentProvider`可以根据不同的URI提供不同的数据或执行不同的操作。`UriMatcher`不直接限定或控制对外共享的文件，但它可以通过帮助`ContentProvider`理解请求来间接实现这一点。

  - 首先放入**要共享的数据的Uri**，使用addURI()分别把authority、path和⼀个⾃定义代码传进去

  - 调⽤UriMatcher的match()⽅法时，就可以将⼀个Uri对象传⼊，返回值是某个能够匹配这个Uri对象所对应的⾃定义代码，利⽤这个代码，我们就可以**判断**出调⽤⽅期望访问的是**哪张表**中的数据。

  - 外部应用只能通过UriMatcher来访问数据，这就保证了数据的安全

  - ```kotlin
    class DatabaseProvider : ContentProvider() {
        private val bookDir = 0
        private val bookItem = 1
        private val categoryDir = 2
        private val categoryItem = 3
        private val authority = "com.example.databasetest.provider"
        private var dbHelper: MyDatabaseHelper? = null
        private val uriMatcher by lazy {
            val matcher = UriMatcher(UriMatcher.NO_MATCH)
            matcher.addURI(authority, "book", bookDir)
            matcher.addURI(authority, "book/#", bookItem)
            matcher.addURI(authority, "category", categoryDir)
            matcher.addURI(authority, "category/#", categoryItem)
            matcher
        }
        override fun onCreate() = context?.let {
            dbHelper = MyDatabaseHelper(it, "BookStore.db", 2)
            true
        } ?: false
        override fun query(uri: Uri, projection: Array<String>?, selection: String?, selectionArgs: Array<String>?, sortOrder: String?) = dbHelper?.let {
            // 查询数据
            val db = it.readableDatabase
            val cursor = when (uriMatcher.match(uri)) {
                bookDir -> db.query("Book", projection, selection, selectionArgs, null, null, sortOrder)
                bookItem -> {
                    val bookId = uri.pathSegments[1]
                    db.query("Book", projection, "id = ?", arrayOf(bookId), null, null, sortOrder)
                }
                categoryDir -> db.query("Category", projection, selection, selectionArgs, null, null, sortOrder)
                categoryItem -> {
                    val categoryId = uri.pathSegments[1]
                    db.query("Category", projection, "id = ?", arrayOf(categoryId), null, null, sortOrder)
                }
                else -> null
            }
            cursor
        }
        override fun insert(uri: Uri, values: ContentValues?) =
        dbHelper?.let {
            // 添加数据
            val db = it.writableDatabase
            val uriReturn = when (uriMatcher.match(uri)) {
                bookDir, bookItem -> {
                    val newBookId = db.insert("Book", null, values)
                    Uri.parse("content://$authority/book/$newBookId")
                }
                categoryDir, categoryItem -> {
                    val newCategoryId = db.insert("Category", null, values)
                    Uri.parse("content://$authority/category/$newCategoryId")
                }
                else -> null
            }
            uriReturn
        }
        override fun update(uri: Uri, values: ContentValues?,
                            selection: String?,
                            selectionArgs: Array<String>?) = dbHelper?.let {
            // 更新数据
            val db = it.writableDatabase
            val updatedRows = when (uriMatcher.match(uri)) {
                bookDir -> db.update("Book", values, selection, selectionArgs)
                bookItem -> {
                    val bookId = uri.pathSegments[1]
                    db.update("Book", values, "id = ?", arrayOf(bookId))
                }
                categoryDir -> db.update("Category", values, selection, selectionArgs)
                categoryItem -> {
                    val categoryId = uri.pathSegments[1]
                    db.update("Category", values, "id = ?", arrayOf(categoryId))
                }
                else -> 0
            }
            updatedRows
        } ?: 0
        override fun delete(uri: Uri, selection: String?, selectionArgs: Array<String>?) = dbHelper?.let {
            // 删除数据
            val db = it.writableDatabase
            val deletedRows = when (uriMatcher.match(uri)) {
                bookDir -> db.delete("Book", selection, selectionArgs)
                bookItem -> {
                    val bookId = uri.pathSegments[1]
                    db.delete("Book", "id = ?", arrayOf(bookId))
                }
                categoryDir -> db.delete("Category", selection, selectionArgs)
                categoryItem -> {
                    val categoryId = uri.pathSegments[1]
                    db.delete("Category", "id = ?", arrayOf(categoryId))
                }
                else -> 0
            }
            deletedRows
        } ?: 0
        override fun getType(uri: Uri) = when (uriMatcher.match(uri)) {
            bookDir -> "vnd.android.cursor.dir/vnd.com.example.databasetest.provider.book"
            bookItem -> "vnd.android.cursor.item/vnd.com.example.databasetest.provider.book"
            categoryDir -> "vnd.android.cursor.dir/vnd.com.example.databasetest.provider.category"
            categoryItem -> "vnd.android.cursor.item/vnd.com.example.databasetest.provider.category"
            else -> null
        }
    }
    ```

- getType()获取uri对应的**MIME类型**

  - MIME 类型有助于接收数据的应用程序了解如何处理这些数据。

  - MIME格式

    - **MIME类型组成** 每种`MIME`类型 由2部分组成 = 类型 + 子类型

    - ```
      text / html
      // 类型 = text、子类型 = html
      
      text/css
      text/xml
      application/pdf
      ```

    - 必须以vnd开头。

    - 如果内容URI以路径结尾，则后接android.cursor.dir/；如果内容URI以id结尾，则后接android.cursor.item/。

    - 最后接上`vnd.<authority>.<path>`。

  - 如
    - ```kotlin
      class UserProvider : ContentProvider() {
      
          // ... 其他实现细节 ...
      
          override fun getType(uri: Uri): String? {
              return when (uriMatcher.match(uri)) {
                  USERS -> "vnd.android.cursor.dir/vnd.com.example.app.provider.users"
                  USER_ID -> "vnd.android.cursor.item/vnd.com.example.app.provider.user"
                  else -> throw IllegalArgumentException("Unsupported URI: $uri")
              }
          }
      }
      
      // 在外部类或对象中：
      val USERS = 1
      val USER_ID = 2
      val uriMatcher = UriMatcher(UriMatcher.NO_MATCH).apply {
          addURI("com.example.app.provider", "users", USERS)
          addURI("com.example.app.provider", "users/#", USER_ID)
      }
      
      ```

- ContentProvider⼀定要在AndroidManifest.xml⽂件中注册才可以使⽤

  - ```xml
    <provider
              android:name=".DatabaseProvider"
              android:authorities="com.example.databasetest.provider"
              android:enabled="true"
              android:exported="true">
    </provider>
    ```

- 数据的获取

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        var bookId: String? = null
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            addData.setOnClickListener {
                // 添加数据
                val uri =  Uri.parse("content://com.example.databasetest.provider/book")
                val values = contentValuesOf("name" to "A Clash of Kings", "author" to "George Martin", "pages" to 1040, "price" to 22.85)
                val newUri = contentResolver.insert(uri, values)
                bookId = newUri?.pathSegments?.get(1)
            }
            queryData.setOnClickListener {
                // 查询数据
                val uri = Uri.parse("content://com.example.databasetest.provider/book")
                contentResolver.query(uri, null, null, null, null)?.apply {
                    while (moveToNext()) {
                        val name = getString(getColumnIndex("name"))
                        val author = getString(getColumnIndex("author"))
                        val pages = getInt(getColumnIndex("pages"))
                        val price = getDouble(getColumnIndex("price"))
                        Log.d("MainActivity", "book name is $name")
                        Log.d("MainActivity", "book author is $author")
                        Log.d("MainActivity", "book pages is $pages")
                        Log.d("MainActivity", "book price is $price")
                    }
                    close()
                }
            }
            updateData.setOnClickListener {
                // 更新数据
                bookId?.let {
                    val uri = Uri.parse("content://com.example.databasetest.provider/book/$it")
                    val values = contentValuesOf("name" to "A Storm of Swords", "pages" to 1216, "price" to 24.05)
                    contentResolver.update(uri, values, null, null)
                }
            }
            deleteData.setOnClickListener {
                // 删除数据
                bookId?.let {
                    val uri =  Uri.parse("content://com.example.databasetest.provider/book/$it")
                    contentResolver.delete(uri, null, null)
                }
            }
        }
    }
    ```

#### ContentResolver类

- 统一管理不同 `ContentProvider`间的操作

  - 通过 `URI` 即可操作 不同的`ContentProvider` 中的数据
  - 外部进程通过 `ContentResolver`类 从而与`ContentProvider`类进行交互

- `ContentResolver` 作为一个客户端，用于与 `ContentProvider` 交互。当应用程序需要访问 `ContentProvider` 中的数据时，它不是直接与 `ContentProvider` 交互，而是通过 `ContentResolver`。

- 通过Uri绑定Provider进行数据交互

  - 

  - ```kotlin
    // 使用ContentResolver前，需要先获取ContentResolver
    // 可通过在所有继承Context的类中 通过调用getContentResolver()来获得ContentResolver
    ContentResolver resolver =  getContentResolver(); 
    
    // 设置ContentProvider的URI
    Uri uri = Uri.parse("content://cn.scu.myprovider/user"); 
    
    // 根据URI 操作 ContentProvider中的数据
    // 此处是获取ContentProvider中 user表的所有记录 
    Cursor cursor = resolver.query(uri, null, null, null, "userid desc");
    ```

#### 工具类

- ContentUris

  - 操作 `URI`

  - ```kotlin
    // withAppendedId（）作用：向URI追加一个id
    Uri uri = Uri.parse("content://cn.scu.myprovider/user") 
    Uri resultUri = ContentUris.withAppendedId(uri, 7);  
    // 最终生成后的Uri为：content://cn.scu.myprovider/user/7
    
    // parseId（）作用：从URL中获取ID
    Uri uri = Uri.parse("content://cn.scu.myprovider/user/7") 
    long personid = ContentUris.parseId(uri); 
    //获取的结果为:7
    ```

- UriMatcher

  - 在`ContentProvider` 中注册`URI`

  - 根据 `URI` 匹配 `ContentProvider` 中对应的数据表

  - ```kotlin
    // 步骤1：初始化UriMatcher对象
    UriMatcher matcher = new UriMatcher(UriMatcher.NO_MATCH);
    //常量UriMatcher.NO_MATCH  = 不匹配任何路径的返回码
    // 即初始化时不匹配任何东西
    
    // 步骤2：在ContentProvider 中注册URI（addURI（））
    int URI_CODE_a = 1；
    int URI_CODE_b = 2；
    matcher.addURI("cn.scu.myprovider", "user1", URI_CODE_a);
    matcher.addURI("cn.scu.myprovider", "user2", URI_CODE_b);
    // 若URI资源路径 = content://cn.scu.myprovider/user1 ，则返回注册码URI_CODE_a
    // 若URI资源路径 = content://cn.scu.myprovider/user2 ，则返回注册码URI_CODE_b
    
    // 步骤3：根据URI 匹配 URI_CODE，从而匹配ContentProvider中相应的资源（match（））
    
    @Override
    public String getType (Uri uri){
        Uri uri = Uri.parse(" content://cn.scu.myprovider/user1");
    
        switch (matcher.match(uri)) {
            // 根据URI匹配的返回码是URI_CODE_a
            // 即matcher.match(uri) == URI_CODE_a
            case URI_CODE_a:
                return tableNameUser1;
            // 如果根据URI匹配的返回码是URI_CODE_a，则返回ContentProvider中的名为tableNameUser1的表
            case URI_CODE_b:
                return tableNameUser2;
            // 如果根据URI匹配的返回码是URI_CODE_b，则返回ContentProvider中的名为tableNameUser2的表
        }
    }
    ```

- ContentObserver

  - 观察 Uri引起ContentProvider 中的数据变化 & 通知外界（即访问该数据访问者）

  - ```kotlin
    // 步骤1：注册内容观察者ContentObserver
    getContentResolver().registerContentObserver（uri）；
    // 通过ContentResolver类进行注册，并指定需要观察的URI
    
    // 步骤2：当该URI的ContentProvider数据发生变化时，通知外界（即访问该ContentProvider数据的访问者）
    public class UserContentProvider extends ContentProvider {
        public Uri insert(Uri uri, ContentValues values) {
            db.insert("user", "userid", values);
            getContext().getContentResolver().notifyChange(uri, null);
            // 通知访问者
        }
    }
    
    // 步骤3：解除观察者
    getContentResolver().unregisterContentObserver（uri）；
    // 同样需要通过ContentResolver类进行解除
    ```

### 缓存LruCache

- (最近最少使用)

- LruCache是个泛型类，主要算法原理是把最近使用的对象用强引用（即我们平常使用的对象引用方式）存储在 LinkedHashMap 中。当缓存满时，把最近最少使用的对象从内存中移除，并提供了get和put方法来完成缓存的获取和添加操作。**用于在内存中缓存对象的简单工具类。**

- 当处理例如图像这样的大数据时，频繁地将其加载和回收会导致性能问题，尤其是在滚动视图中。使用 `LruCache` 可以在内存中高效地缓存这些数据，从而提供更流畅的用户体验。

- 使用

  - ```kotlin
    int maxMemory = (int) (Runtime.getRuntime().totalMemory() / 1024);
    int cacheSize = maxMemory / 8;
    mMemoryCache = new LruCache<String, Bitmap>(cacheSize) {
        @Override
        protected int sizeOf(String key, Bitmap value) {
            return value.getRowBytes() * value.getHeight() / 1024;
        }
    };
    
    // 将一个 Bitmap 放入缓存
    lruCache.put("someKey", someBitmap)
    
    // 从缓存中获取一个 Bitmap
    val cachedBitmap = lruCache.get("someKey")
    
    ```

  - 设置LruCache缓存的大小，一般为当前进程可用容量的1/8。

  - 重写sizeOf方法，计算出要缓存的每张图片的大小。

## Context

- **Android应用模型是基于组件的应用设计模式，组件的运行要有一个完整的Android工程环境**，在这个环境下，Activity、Service等系统组件才能够正常工作，而这些组件并不能采用普通的Java对象创建方式，new一下就能创建实例了，而是要有它们各自的上**下文环境，也就是Context。**
- Context提供了关于应用**环境全局信息**的接口。**它是一个抽象类，它的执行被Android系统所提供**。
- <img src="https://camo.githubusercontent.com/f13f4e36dff25e4779267e1673708d89b1e3cf1c6af1766989cce8381170fb58/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f313138373233372d316234633063643331666430313933662e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:50%;" />
  - Context数量=Activity数量+Service数量+1（Application）
- 功能：弹出Toast、启动Activity、启动Service、发送广播、操作数据库等等
  - <img src="https://camo.githubusercontent.com/cb4b5eeeaf7c3c75d4857f966bfe3c4a0626b34c01fd67a5548191eef7ddaf0e/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f313138373233372d666233326230663939326461343738312e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom: 67%;" />
  - 即：凡是跟UI相关的，都应该使用Activity做为Context来处理；其他的一些操作，Service,Activity,Application等实例都可以

### 获取Context对象

- View.getContext,返回当前View对象的Context对象，通常是当前正在展示的Activity对象。
- Activity.getApplicationContext,获取当前Activity所在的(应用)进程的Context对象，通常我们使用Context对象时，要优先考虑这个全局的进程Context。
- Activity.this 返回当前的Activity实例，如果是UI控件需要使用Activity作为Context对象，但是默认的Toast实际上使用ApplicationContext也可以。

### Context使用的注意事项

#### 内存泄漏

- 让一些生命周期较长的对象（如静态对象）持有activity的引用，导致activity迟迟不能被GC
- 一般Context造成的内存泄漏，几乎都是当Context销毁的时候，却因为被引用导致销毁失败，而Application的Context对象可以理解为随着进程存在的。因此当Application的Context能搞定的情况下，并且生命周期长的对象，**优先使用Application的**Context。
  - 不要让生**命周期长于Activity的对象**持有到Activity的引用。
  - 尽量不要在Activity中使用非静态内部类，因为非静态内部类会隐式持有外部类实例的引用，如果使用静态内部类，将外部实例引用作为弱引用持有。

## Fragment

- 更好的适配不同大小的屏幕和设备，Fragment是⼀种可以嵌⼊在Activity当中的UI⽚段，它能让程序更加合理和充分地利⽤⼤屏幕的空间，因⽽在平板上应⽤得⾮常⼴泛

- 也可以对布局进行抽离，简化代码，便于复用

- 如使用Fragment实现左右分屏

  - 分别为左侧和右侧编写xml布局配置

  - 创建类

    - ```kotlin
      class LeftFragment : Fragment() {
          override fun onCreateView(inflater: LayoutInflater, container:
                                    ViewGroup?,savedInstanceState: Bundle?): View? {
              return inflater.inflate(R.layout.left_fragment, container,false)
          }
      }
      ```

  - 使用方式

    - ```xml
      <fragment
      android:id="@+id/leftFrag"
      android:name="com.example.fragmenttest.LeftFragment"//指定类
      android:layout_width="0dp"
      android:layout_height="match_parent"
       android:layout_weight="1" />
      ```

- 动态添加

  - 由于这⾥仅需要在布局⾥放⼊⼀个Fragment，不需要任何定位，因此⾮常适合使⽤FrameLayout。

  - 将一个Fragment放入布局

    - ```kotlin
      replaceFragment(RightFragment())
      private fun replaceFragment(fragment: Fragment) {
          val fragmentManager = supportFragmentManager
          val transaction = fragmentManager.beginTransaction()
          transaction.replace(R.id.rightLayout, fragment)
          transaction.addToBackStack(null)//将事务添加到事务被添加到回退栈后，方便用户点击back时返回
          transaction.commit()
      }
      ```

    - 创建待添加Fragment的实例

    - 获取FragmentManager，在Activity中可以直接调⽤getSupportFragmentManager()⽅法获取。

    - 开启⼀个事务，通过调⽤beginTransaction()⽅法开启。

    - 向容器内添加或替换Fragment，⼀般使⽤replace()⽅法实现，需要传⼊容器的id和待添加的Fragment实例。

    - 提交事务，调⽤commit()⽅法来完成

- Fragment与Activity之间的交互

  - 获取fragment`val fragment = supportFragmentManager.findFragmentById(R.id.leftFrag) as LeftFragment`
  - 获取activity`val mainActivity = activity as MainActivity`(getActivity())
  - fragment之间通信，通过 获取activity间接进行
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724173426747.png" alt="image-20230724173426747" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724173615157.png" alt="image-20230724173615157" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724173010289.png" alt="image-20230724173010289" style="zoom:33%;" />

### 生命周期

- 状态
  - 运⾏状态：当⼀个Fragment所关联的Activity正处于运⾏状态时，该Fragment也处于运⾏状态。
  - 暂停状态：当⼀个Activity进⼊暂停状态时（由于另⼀个未占满屏幕的Activity：被添加到了栈顶），与它相关联的Fragment就会进⼊暂停状态。
  - 停⽌状态：当⼀个Activity进⼊停⽌状态时，与它相关联的Fragment就会进⼊停⽌状态，或者通过调⽤FragmentTransaction的remove()、replace()⽅法将Fragment从Activity中移除，但在事务提交之前调⽤了addToBackStack()⽅法（**操作可以回退**），这时的Fragment也会进⼊停⽌状态。
  - 销毁状态：当Activity被销毁时，与它相关联的Fragment就会进⼊销毁状态。或者通过调⽤FragmentTransaction的remove()、replace()⽅法将Fragment从Activity中移除，但在事务提交之前并没有调⽤addToBackStack()⽅法，这时的Fragment也会进⼊销毁状态。
- 生命周期回调
  - onAttach()：当Fragment和Activity建⽴关联时调⽤。
  - onCreateView()：为Fragment创建视图（加载布局）时调⽤。
  - onActivityCreated()：确保与Fragment相关联的Activity已经创建完毕时调⽤。
  - onDestroyView()：当与Fragment关联的视图被移除时调⽤。
  - onDetach()：当Fragment和Activity解除关联时调⽤。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230717203711104.png" alt="image-20230717203711104" style="zoom:33%;" />

### 响应式布局

- 在不同文件中给出不同的界面配置方案

  - 如`layout/activity_main`和`layout-large/ activity_main`

- 更为具体的限定

  - `layout-sw600dp`
  - 当程序运⾏在屏幕宽度**⼤于等于**600 dp的设备上时，会加载layout-sw600dp/activity_main布局，当程序运⾏在屏幕宽度⼩于600dp的设备上时，则仍然加载默认的layout/activity_main布局。

- 通过重写生命周期函数进行判断来实现自适应布局

  - 检查当前的布局中是否存在一个特定的视图组件判断状态

  - ```kotlin
    override fun onActivityCreated(savedInstanceState: Bundle?) {
        super.onActivityCreated(savedInstanceState)
        isTwoPane = activity?.findViewById<View>(R.id.newsContentLayout) != null
    }
    ```

  - 从而activity会根据启用的layout自动判断状态

### 回退栈

- ragment的回退栈是用来保存每一次Fragment事务发生的变化 如果你将Fragment任务添加到回退栈，当用户点击后退按钮时，将看到上一次的保存的Fragment。一旦Fragment完全从后退栈中弹出，用户再次点击后退键，则退出当前Activity
- 使用remove操作时，如果被移除的Fragment没有添加到回退栈（回退栈后面会详细说），这个Fragment实例将会被销毁（在replace操作很常用）

## 消息机制

### 模型

- Message：是在线程之间传递的消息，它可以在内部携带少量的信息，⽤于在不同线程之间传递数据。

- Handler：主要是⽤于发送和处理消息的。

- MessageQueue：消息队列，主要⽤于存放所有通过Handler发送的消息，等待被处理。(数据结构上是单链表)

- Looper：MessageQueue的管家，发现MessageQueue中存在⼀条消息时，就会将它取出，并传递到Handler的handleMessage()⽅法中

- <img src="https://camo.githubusercontent.com/9104023c0d03d0ab0656fa27121f95ae5e67a8f7e3b016bdf2dab798c313b025/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d623332393562363761326230343737662e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231011141831891.png" alt="image-20231011141831891" style="zoom: 50%;" />

  - 每个线程中只能存在一个Looper，但每个线程中可以有多个Handler

- 所有消息发送都调用

  - ```java
     public boolean sendMessageAtTime(Message msg, long uptimeMillis) {
           //其中mQueue是消息队列，从Looper中获取的
            MessageQueue queue = mQueue;
            if (queue == null) {
                RuntimeException e = new RuntimeException(
                        this + " sendMessageAtTime() called with no mQueue");
                Log.w("Looper", e.getMessage(), e);
                return false;
            }
            //调用enqueueMessage方法
            return enqueueMessage(queue, msg, uptimeMillis);
        }
         private boolean enqueueMessage(MessageQueue queue, Message msg, long uptimeMillis) {
            msg.target = this;
            if (mAsynchronous) {
                msg.setAsynchronous(true);
            }
            //调用MessageQueue的enqueueMessage方法
            return queue.enqueueMessage(msg, uptimeMillis);
        }
    ```

  - 本质就是把消息放入队列

## 事件分发机制

- 当一个事件发生后，系统需要将这个事件传递给一个具体的View去处理。**这个事件传递的过程就是分发过程。**
- 一个点击事件产生后，传递顺序是：Activity（Window） -> ViewGroup -> View -> ViewGroup -> Activity（Window）
  - 这里的父子关系不是指继承上的关系，而是视图上的包含关系
- 事件列：如一个点击事件实际上包含down move up等一系列的事件

### 事件函数

- dispatchTouchEvent
  - 分发事件
  - true：消费事件，不再向下传递；后续事件会**分发到该View**
  - false：不消费事件，事件停止传递；事件传给父控件的onTouchEvent处理，但**当前view仍接受此事件的其他事件**
- onInterceptTouchEvent
  - 拦截事件，仅在 `ViewGroup`（如 `LinearLayout`、`RelativeLayout` 等）中存在。
  - true：拦截事件，事件不再向下传递；自己处理，调用onTouchEvent，**同一事件列的其他事件都直接由该View处理**，在**同一个事件列中该方法不会被再次调用**，之后会直接给对应的onTouchEvent
  - false：不拦截事件，事件继续往下传递，调用父类的dispatchTouchEvent，此View**仍然接受**此事件列的其他事件
- onTouchEvent
  - 处理事件
  - true：自己处理时间不再向下传递，**后续事件序列直接由其处理**
  - false：不处理事件，上传给父控件onTouchEvent处理，**不再接受**此事件的其他事件
- 调用过程
  - 当一个触摸事件发生时，`dispatchTouchEvent` 被首先调用。
  - 在 `ViewGroup` 中，`onInterceptTouchEvent` 决定是否拦截这个事件。
  - 如果 `ViewGroup` 拦截了事件，那么 `onTouchEvent` 会被调用；否则，事件将被分发到子视图。
- <img src="https://camo.githubusercontent.com/1a1b199c244d959e5f2a3b16734469453f8dd99c5ce0a5bf2c951a9ecc8a2067/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d616138343136666336643265356563642e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />

- ```java
  / 点击事件产生后，会直接调用dispatchTouchEvent（）方法
  public boolean dispatchTouchEvent(MotionEvent ev) {
  
      //代表是否消耗事件
      boolean consume = false;
  
  
      if (onInterceptTouchEvent(ev)) {
      //如果onInterceptTouchEvent()返回true则代表当前View拦截了点击事件
      //则该点击事件则会交给当前View进行处理
      //即调用onTouchEvent (）方法去处理点击事件
        consume = onTouchEvent (ev) ;
  
      } else {
        //如果onInterceptTouchEvent()返回false则代表当前View不拦截点击事件
        //则该点击事件则会继续传递给它的子元素
        //子元素的dispatchTouchEvent（）就会被调用，重复上述过程
        //直到点击事件被最终处理为止
        consume = child.dispatchTouchEvent (ev) ;
      }
  
      return consume;
     }
  ```

#### 实例

- <img src="https://camo.githubusercontent.com/ecd908684ad3f517399bab2b55cb46bf004fa643de78f6e6844c069ce22d4220/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d656361633632343738313661336462312e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:50%;" />

- 默认的事件传递过程
  - <img src="https://camo.githubusercontent.com/b2b1799a1633b84dcca3c256a2db56ac1fdaf894ca9b7745692205f8a0375f09/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d363932323966643461383034633066382e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />
- 处理事件，如c的onTouchEvent()返回true
  - <img src="https://camo.githubusercontent.com/d73c302ec266fb6d6b5829ba7940b2e6d953d7eac75a88d4a3d01e7cc8f1c42c/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d323632393062306433333337303835332e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:50%;" />
- 拦截down事件
  - 假设ViewGroup B希望处理这个点击事件，即B覆写了onInterceptTouchEvent()返回true、onTouchEvent()返回true。
  - 后续事件将直接传递给B的onTouchEvent()处理；后续事件将不会再传递给B的onInterceptTouchEvent方法，该方法一旦返回一次true，就再也不会被调用了。
  - <img src="https://camo.githubusercontent.com/df628f7eb3985fb35a19e5978e418cdc1c133589a347f1ce93dc6e311c74d63e/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f3934343336352d643861636433356433613530653039312e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />
- 假设ViewGroup B没有拦截DOWN事件（还是View C来处理DOWN事件），但它拦截了接下来的MOVE事件。
  - 由于DOWN事件传递到C的onTouchEvent方法，返回了true。在后续到来的MOVE事件，B的onInterceptTouchEvent方法返回true拦截该MOVE事件，**但该事件并没有传递给B**；这个MOVE事件将会被系统变成一个CANCEL事件传递给C的onTouchEvent方法

## 网络开发

### http

- 使用`HttpURLConnection`

- ```kotlin
  private fun sendRequestWithHttpURLConnection() {
      // 开启线程发起⽹络请求
      thread {
          var connection: HttpURLConnection? = null
          try {
              val response = StringBuilder()
              val url = URL("https://www.baidu.com")
              connection = url.openConnection() as HttpURLConnection
              connection.connectTimeout = 8000
              connection.requestMethod = "POST"
              connection.readTimeout = 8000
              //设置附带的url参数
              val output = DataOutputStream(connection.outputStream)
  			output.writeBytes("username=admin&password=123456")
              val input = connection.inputStream
              // 下⾯对获取到的输⼊流进⾏读取
              val reader = BufferedReader(InputStreamReader(input))
              reader.use {
                  reader.forEachLine {
                      response.append(it)
                  }
              }
              showResponse(response.toString())
          } catch (e: Exception) {
              e.printStackTrace()
          } finally {
              connection?.disconnect()
          }
      }
  }
  ```

- 使用OkHttp

  - 添加依赖`implementation 'com.squareup.okhttp3:okhttp:4.1.0'`

  - ```kotlin
    val client = OkHttpClient()
    val request = Request.Builder()
    .url("https://www.baidu.com")
    .build()
    val response = client.newCall(request).execute()
    val responseData = response.body?.string()
    ```

  - post表单

    - ```kotlin
      val requestBody = FormBody.Builder()
      .add("username", "admin")
      .add("password", "123456")
      .build()
      
      val request = Request.Builder()
      .url("https://www.baidu.com")
      .post(requestBody)
      .build()
      ```

#### Json解析

- GSON库

  - 引入`implementation 'com.google.code.gson:gson:2.8.5'`

  - 可以将⼀段JSON格式的字符串⾃动映射成⼀个对象

  - 解析

    - ```kotlin
      val gson = Gson()
      val person = gson.fromJson(jsonData, Person::class.java)
      ```

#### 网络请求回调

- 打包一个类来处理

  - ```kotlin
    object HttpUtil {
        ...
        fun sendOkHttpRequest(address: String, callback:okhttp3.Callback) {
            val client = OkHttpClient()
            val request = Request.Builder()
            .url(address)
            .build()
            client.newCall(request).enqueue(callback)
        }
    }
    //重写回调
    HttpUtil.sendOkHttpRequest(address, object : Callback {
        override fun onResponse(call: Call, response: Response) {
            // 得到服务器返回的具体内容
            val responseData = response.body?.string()
        }
        override fun onFailure(call: Call, e: IOException) {
            // 在这⾥对异常情况进⾏处理
        }
    })
    ```

#### Retrofit库

- 可以配置好⼀个根路径，然后在指定服务器接⼝地址时只需要使⽤相对路径即可，这样就不⽤每次都指定完整的URL地址了

- 完全不⽤关⼼⽹络通信的细节，只需要在接⼝⽂件中声明⼀系列⽅法和返回值。Retrofit会⾃动向对应的服务器接⼝发起请求，并将响应的数据解析成返回值声明的类型

- 还会将服务器返回的JSON数据⾃动解析成对象

- 依赖与前面几个底层方法的封装实现

- ```
  implementation 'com.squareup.retrofit2:converter-gson:2.6.1'
  implementation 'com.squareup.retrofit2:retrofit:2.6.1'
  ```

- ```kotlin
  interface AppService {//请求接口定义
      @GET("get_data.json")//标记一个方法是一个 HTTP GET 请求，以及http相对地址
      fun getAppData(): Call<List<App>>//接口方法，用于获取应用数据的列表。数据类型为List<App>(ResponseBody表示不关心返回数据的类型，不对数据进行解析，如delete模式的http)
      @POST("users")
      fun createUser(@Body user: User): Call<User>
  }
  
  val retrofit = Retrofit.Builder()//创建 Retrofit 实例
  .baseUrl("http://10.0.2.2/")
  .addConverterFactory(GsonConverterFactory.create())
  .build()
  val appService =  retrofit.create(AppService::class.java)//传入接口
  appService.getAppData().enqueue(object : Callback<List<App>> {
      override fun onResponse(call: Call<List<App>>, response: Response<List<App>>) {//发送请求，重写回调处理函数
          val list = response.body()
          if (list != null) {
              for (app in list) {
                  Log.d("MainActivity", "id is ${app.id}")
                  Log.d("MainActivity", "name is ${app.name}")
                  Log.d("MainActivity", "version is ${app.version}")
              }
          }
      }
      override fun onFailure(call: Call<List<App>>, t: Throwable) {
          t.printStackTrace()
      }
  })
  }
  ```
  
  - `enqueue` 是 Retrofit 库中 `Call` 对象的一个方法，它用于**异步执行**网络请求。当你调用 `enqueue` 方法时，Retrofit 会在后台线程中执行网络请求，而不会阻塞当前线程。
  
- 处理复杂的接⼝地址类型

  - 有变量的地址`http://example.com/<page>/get_data.json`

    - ```kotlin
      interface ExampleService {
          @GET("{page}/get_data.json")
          fun getData(@Path("page") page: Int): Call<Data>
      }
      ```

  - 使用url参数的地址`http://example.com/get_data.json?u=<user>&t=<token>`

    - ```kotlin
      interface ExampleService {
          @GET("get_data.json")
          fun getData(@Query("u") user: String, @Query("t") token:String): Call<Data>
      }
      ```
    
  - 使⽤@GET、@POST、@PUT、@PATCH、@DELETE注解，发出相应类型的请求了。

  - post请求（数据放到请求体）

    - ```kotlin
      POST http://example.com/data/create
      {"id": 1, "content": "The description for this data."}
      
      interface ExampleService {
          @Headers("User-Agent: okhttp", "Cache-Control: max-age=0")//可选请求头（静态）
          @POST("data/create")
          fun createData(@Body data: Data, @Header("Cache-Control") cacheControl: String)): Call<ResponseBody>
      }
      ```

    - 使用`@Body`注解，会⾃动将Data对象中的数据转换成JSON格式的⽂本，并放到HTTP请求的body部分

    - 使⽤@Header注解,表示请求头信息

- 打包单例类，方便使用

  - ```kotlin
    object ServiceCreator {
        private const val BASE_URL = "http://10.0.2.2/"
        private val retrofit = Retrofit.Builder()
        .baseUrl(BASE_URL)
        .addConverterFactory(GsonConverterFactory.create())
        .build()
        fun <T> create(serviceClass: Class<T>): T = retrofit.create(serviceClass)
    }
    
    val appService = ServiceCreator.create(AppService::class.java)
    ```

  - 

## UI开发

### 组件

#### 通用属性

- 组件id

  - 每个组件具有的唯一标识符

  - ```xml
    <Button
        android:id="@+id/add_item"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Add Item" />
    ```

- 宽高
  - `android:layout_width`和`android:layout_height`
  - match_parent表⽰让当前控件的⼤⼩和⽗布局的⼤⼩⼀样，也就是由⽗布局来决定当前控件的⼤⼩。
  - wrap_content表⽰让当前控件的⼤⼩能够刚好包含住⾥⾯的内容，也就是由控件内容决定当前控件的⼤⼩。
  - 固定值表⽰表⽰给控件指定⼀个固定的尺⼨，单位⼀般⽤dp，这是⼀种屏幕密度⽆关的尺⼨单位，可以保证在不同分辨率的⼿机上显⽰效果尽可能地⼀致
  - 一个属性设置为0表示根据比例自动计算
- 对齐方式
  - `android:gravity`
  - top、bottom、start、end、center等，可以⽤“|”来同时指定多个值
    - 支持水平垂直方向分别指定`center_vertical|center_horizontal`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724141046022.png" alt="image-20230724141046022" style="zoom:33%;" />
- 文字样式
  - `android:textColor`属性可以指定⽂字的颜⾊
  - `android:textSize`属性可以指定⽂字的⼤⼩

- 可见性控制
  - `android:visibility`
    - `visible`：可见
    - `invisible`：不可见
    - `gone`：不可见并且不占用屏幕空间
  - activity中设置：使⽤的是setVisibility()⽅法，允许传⼊View.VISIBLE、View.INVISIBLE和View.GONE这3种值
    - 使用`getVisibility()`获取显示状态
- 背景填充`android:background`
  - 可以使用颜色或图片填充
- 设置外边距`android:layout_margin`
  - `android:padding`
- 隐藏系统自带的任务栏`supportActionBar?.hide()`

#### 自定义控件

- 在`/layout`中创建布局

- 在其他xml布局中引用`<include layout="@layout/name" />`

- 打包控件功能与响应（除布局之外的其他内容）

  - ```kotlin
    class TitleLayout(context: Context, attrs: AttributeSet) :
    LinearLayout(context, attrs) {
        init {
            LayoutInflater.from(context).inflate(R.layout.title, this)
            titleBack.setOnClickListener {
                val activity = context as Activity
                activity.finish()
            }
            titleEdit.setOnClickListener {
                Toast.makeText(context, "You clicked Edit button",
                               Toast.LENGTH_SHORT).show()
            }
        }
    }
    ```

  - 通过LayoutInflater的from()⽅法可以构建出⼀个LayoutInflater对象，然后调⽤inflate()⽅法就可以动态加载⼀个布局⽂件。

- 使用方式

  - ```xml
    <com.example.uicustomviews.TitleLayout
    android:layout_width="match_parent"
    android:layout_height="wrap_content" />
    ```

  - 

#### TextView

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724160154545.png" alt="image-20230724160154545" style="zoom:33%;" />

- 文字标签

  - ```kotlin
    <TextView
    android:id="@+id/textView"
    android:layout_width="match_parent"
    android:layout_height="wrap_content"
    android:gravity="center"
    android:textColor="#00ff00"
    android:textSize="24sp"
    android:text="This is TextView"/>
    ```

- 最大显示行数`android:maxLines`
- `android:ellipsize`⽤于设定当⽂本内容超出控件宽度时⽂本的缩略⽅式
- Autolink自动识别跳转

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724160447220.png" alt="image-20230724160447220" style="zoom:33%;" />


#### WebView

- 显示网页

- ```xml
  <WebView
  android:id="@+id/webView"
  android:layout_width="match_parent"
  android:layout_height="match_parent" />
  //声明网络权限
  <uses-permission android:name="android.permission.INTERNET" />
  ```

- ```kotlin
  webView.settings.javaScriptEnabled=true
  webView.webViewClient = WebViewClient()
  webView.loadUrl("https://www.baidu.com")
  ```

- 

#### Button

-  默认会将按钮上的英文全部转化为大写

  - 关闭`android:textAllCaps="false"`

- 事件响应

  - 函数式API的⽅式来注册监听器

  - ```kotlin
    button.setOnClickListener {
    // 在此处添加逻辑
    }
    ```

  - 实现接⼝的⽅式来进⾏注册

    - 注册`button.setOnClickListener(this)`

    - 重写

      - ```kotlin
        override fun onClick(v: View?) {
            when (v?.id) {
                R.id.button -> {
                    // 在此处添加逻辑
                }
            }
        }
        ```

#### EditText

- 文字输入框
- 提示文字`android:hint="Type something here`
- 最大输入行数（超出后改为滚动）`android:maxLines="2"`
- 隐式调用gettext获取输入内容`editText.text.toString()`

#### ImageView

- 用于显示图片
- 资源url`android:src="@drawable/img_1"`
  - 在activity中设置`imageView.setImageResource(R.drawable.img_2)`

#### ProgressBar

- 进度条，默认为圆形加载动画

- 水平进度条

  - ```kotlin
    style="android:attr/progressBarStyleHorizontal"
    android:max="100"
    ```

  - activity中设置进度`progressBar.progress = progressBar.progress + 10`

#### AlertDialog

- 对话框是置顶于所有界⾯元素之上的，能够屏蔽其他控件的交互能⼒，因此AlertDialog⼀般⽤于提⽰⼀些⾮常重要的内容或者警告信息。

- 直接在activity中创建并使用

  - ```kotlin
    AlertDialog.Builder(this).apply {
        setTitle("This is Dialog")
        setMessage("Something important.")
        setCancelable(false)
        setPositiveButton("OK") { dialog, which ->
                                }
        setNegativeButton("Cancel") { dialog, which ->
                                    }
        show()
    }
    ```

#### ListView

- layout引入

  - ```xml
    <ListView
    android:id="@+id/listView"
    android:layout_width="match_parent"
    android:layout_height="match_parent" />
    ```

- 数据传入

  - ```kotlin
    val adapter = ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,data)
    listView.adapter = adapter
    ```

  - （data为list）设置当传入数据类型，当前activity，目标组件以及数据集合，最后将生成的适配器应用到具体组件

- 界面定制

  - 自定义实体类作为ListView的适配类型

  - 为ListView的子项设定布局

  - 创建自定义适配器，重写`getview`

    - ```kotlin
      class FruitAdapter(activity: Activity, val resourceId: Int, data:List<Fruit>) :
      ArrayAdapter<Fruit>(activity, resourceId, data) {
          override fun getView(position: Int, convertView: View?, parent:ViewGroup): View {
              if (convertView == null) {
                  view = LayoutInflater.from(context).inflate(resourceId,parent, false)//判断是否存在缓存，避免重复加载提高效率
              } else {
                  view = convertView
              }//将xml布局转化为视图对象
              val fruitImage: ImageView =view.findViewById(R.id.fruitImage)
              val fruitName: TextView = view.findViewById(R.id.fruitName)
              val fruit = getItem(position) // 获取当前项的Fruit实例
              if (fruit != null) {
                  fruitImage.setImageResource(fruit.imageId)
                  fruitName.text = fruit.name
              }
              return view
          }
      }
      ```

    - FruitAdapter定义了⼀个主构造函数，⽤于将Activity的实例、ListView⼦项布局的id和数据源传递进来。另外⼜重写了getView()⽅法，这个⽅法在每个⼦项被滚动到屏幕内的时候会被调⽤。

  - 在主activity中装配

    - ```kotlin
      class MainActivity : AppCompatActivity() {
          private val fruitList = ArrayList<Fruit>()
          override fun onCreate(savedInstanceState: Bundle?) {
              super.onCreate(savedInstanceState)
              setContentView(R.layout.activity_main)
              initFruits() // 初始化⽔果数据
              val adapter = FruitAdapter(this, R.layout.fruit_item,fruitList)//使用重载的适配器
              listView.adapter = adapter
          }
          private fun initFruits() {//初始化data
              repeat(2) {
       ...           fruitList.add(Fruit("Apple",R.drawable.apple_pic))
              }
      }
      ```

- 点击事件

  - ```kotlin
    listView.setOnItemClickListener { parent, view, position,id ->
        val fruit = fruitList[position]
        Toast.makeText(this, fruit.name,Toast.LENGTH_SHORT).show()
                                    }
    }
    ```

#### RecyclerView（新）

- 可以实现横向、纵向滚动以及瀑布流布局

- 向`app/build.gradle`添加依赖

  - `implementation 'androidx.recyclerview:recyclerview:1.3.0'`

- layout引入

  - ```xml
    <androidx.recyclerview.widget.RecyclerView 
    android:id="@+id/recyclerView" 
    android:layout_width="match_parent" 
                                               android:layout_height="match_parent" />
    ```
  
- 适配器配置

  - ```kotlin
    class FruitAdapter(val fruitList: List<Fruit>) :RecyclerView.Adapter<FruitAdapter.ViewHolder>() {
        inner class ViewHolder(view: View) :RecyclerView.ViewHolder(view) {
            val fruitImage: ImageView =view.findViewById(R.id.fruitImage)
            val fruitName: TextView = view.findViewById(R.id.fruitName)
        }
        override fun onCreateViewHolder(parent: ViewGroup, viewType:Int): ViewHolder {
            val view = LayoutInflater.from(parent.context).inflate(R.layout.fruit_item, parent, false)
            return ViewHolder(view)
        }
        override fun onBindViewHolder(holder: ViewHolder, position:Int) {
            val fruit = fruitList[position]
            holder.fruitImage.setImageResource(fruit.imageId)
            holder.fruitName.text = fruit.name
        }
        override fun getItemCount() = fruitList.size
    }
    ```

  - **`onCreateViewHolder`**：当RecyclerView需要新的ViewHolder来显示一个列表项时，它会调用`onCreateViewHolder`方法。这通常发生在初次加载RecyclerView，或者在用户滚动屏幕，使得新的列表项需要显示在屏幕上时。（使用LayoutInflater动态加载）

  - **`onBindViewHolder`**：当RecyclerView需要用数据来填充一个列表项的内容时，它会调用`onBindViewHolder`方法。这通常发生在初次加载RecyclerView，或者在用户滚动屏幕，使得已经存在的ViewHolder需要被重新绑定到新的数据时。

  - **`getItemCount`**：RecyclerView在需要知道有多少个列表项时会调用`getItemCount`方法。这通常在初始化RecyclerView，以及数据源发生变化时发生。此方法的返回值决定了RecyclerView可以滚动的长度，以及在滚动到底部时何时开始加载更多数据（如果实现了这个功能的话）。activity中使用

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        private val fruitList = ArrayList<Fruit>()
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            initFruits() // 初始化⽔果数据
            val layoutManager = LinearLayoutManager(this)
            //RecyclerView的一个布局管理器
            recyclerView.layoutManager = layoutManager
            //配置布局管理器
            val adapter = FruitAdapter(fruitList)
            recyclerView.adapter = adapter
            //数据生成
        }
    }
    ```

- 当有多种类型子项在一个列表中，可以考虑重写

  - ```kotlin
    override fun getItemViewType(position: Int): Int {
            val msg = msgList[position]
            return msg.type
        }
    ```

- 此外同样还有fruit类的定义及layout的生成需要配置

- 点击事件

  - 所有的点击事件都由具体的View去注册

  - 在适配器onCreateViewHolder中直接注册事件

  - ```kotlin
    val viewHolder = ViewHolder(view)
    viewHolder.itemView.setOnClickListener {
        val position = viewHolder.adapterPosition
        val fruit = fruitList[position]
        Toast.makeText(parent.context, "you clicked view${fruit.name}",
                       Toast.LENGTH_SHORT).show()
    }
    viewHolder.fruitImage.setOnClickListener {
        val position = viewHolder.adapterPosition
        val fruit = fruitList[position]
        Toast.makeText(parent.context, "you clicked image${fruit.name}",
                       Toast.LENGTH_SHORT).show()
    }
    ```

  - 可以针对不同组件做出不同的 响应

- 更新数据

  - `adapter?.notifyItemInserted(List.size - 1)`告诉适配器（`adapter`）有一项新的数据被插入到了数据集的最后一位，要更新视图 
  - `binding.recyclerView.scrollToPosition(msgList.size - 1)`：这行代码使`RecyclerView`**滚动**到数据集的最后一位（`msgList.size - 1`）。这样，用户就可以立即看到新添加的消息。

##### 布局管理器

- 除了LinearLayoutManager之外，RecyclerView还给我们提供了GridLayoutManager可以⽤于实现⽹格布局，StaggeredGridLayoutManager可以⽤于实现瀑布流布局。
  - 瀑布流布局的宽度应该是根据布局的列数来⾃动适配的，⽽不是⼀个固定值。因此需要将宽度设置为match_parent

- 横向滚动

  - 对布局管理器增加配置

  - ```kotlin
    val recyclerView: RecyclerView = findViewById(R.id.my_recycler_view)
    recyclerView.layoutManager = LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false)
    ```

  - 

- 瀑布流

  - ```kotlin
    val layoutManager = StaggeredGridLayoutManager(3,
    StaggeredGridLayoutManager.VERTICAL)
    recyclerView.layoutManager = layoutManager
    ```

  - 配置瀑布流的行数以及 滑动方向

#### 其他

- 利用view生成分割线

  - ```xml
    <View
    android:layout_width="match_parent"
    android:layout_height="1dp"
    android:background="#000" />
    ```

- 

### 菜单

- 在`res/menu`中设置菜单的样式

  - ```xml
    <?xml version="1.0" encoding="utf-8"?>
    <menu xmlns:android="http://schemas.android.com/apk/res/android">
        <item
            android:id="@+id/add_item"
            android:title="Add"/>
        <item
            android:id="@+id/remove_item"
            android:title="Remove"/>
    </menu>
    ```

- 在activity中创建菜单

  - ```kotlin
    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
            menuInflater.inflate(R.menu.main, menu)
            return true
        }
    ```

- 菜单响应

  - ```kotlin
    override fun onOptionsItemSelected(item: MenuItem): Boolean {
            when (item.itemId) {
                R.id.add_item -> Toast.makeText(this, "You clicked Add",
                    Toast.LENGTH_SHORT).show()
                R.id.remove_item -> Toast.makeText(this, "You clicked Remove",
                    Toast.LENGTH_SHORT).show()
            }
            return true
        }
    ```

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230716220319661.png" alt="image-20230716220319661" style="zoom:33%;" />

### 布局

#### LinearLayout线性布局

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724111511937.png" alt="image-20230724111511937" style="zoom:33%;" />

- 控件在特定方向上线性排列

  - ```xml
    <LinearLayout
                  xmlns:android="http://schemas.android.com/apk/res/android"
                  android:orientation="vertical"
                  android:layout_width="match_parent"
                  android:layout_height="match_parent">
        <TextView
                  android:id="@+id/textView"
                  android:layout_width="match_parent"
                  android:layout_height="wrap_content"
                  android:text="This is TextView"/>
    </LinearLayout>
    ```

- 指定排列方式`android:orientation`水平排列/垂直排列

  - 如果LinearLayout的排列⽅向horizontal，内部的控件就绝对不能将宽度指定为match_parent，否则，单独⼀个控件就会将整个⽔平⽅向占满，其他的控件就没有可放置的位置了。同样的道理，如果LinearLayout的排列⽅向是vertical，内部的控件就不能将⾼度指定为match_parent。

- 指定布局中空间的对齐方式`android:layout_gravity`（此属性写在控件中）

  - 当排列方式是垂直时只能指定水平对齐方式，反之同理

- 使用比例控制控件在布局中的显示

  - ```xml
    <EditText
              android:id="@+id/input_message"
              android:layout_width="0dp"
              android:layout_height="wrap_content"
              android:layout_weight="1"
              android:hint="Type something"
              />
    <Button
            android:id="@+id/send"
            android:layout_width="0dp"
            android:layout_height="wrap_content"
            android:layout_weight="1"
            android:text="Send"
            />
    ```

  - 可以混用，如一个占据尽可能大的空间，另一个使用wrap_content

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230717141353417.png" alt="image-20230717141353417" style="zoom:33%;" />

#### ConstraintLayout约束布局

- 创建具有复杂关系的界面，减少嵌套层次，提高性能
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724112212503.png" alt="image-20230724112212503" style="zoom:33%;" />
  - 指向其他组件/parent
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724112243620.png" alt="image-20230724112243620" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724113020539.png" alt="image-20230724113020539" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724112754846.png" alt="image-20230724112754846" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724112909297.png" alt="image-20230724112909297" style="zoom:50%;" />

#### RelativeLayout相对布局

- 可以通过相对定位的⽅式让控件出现在布局的任何位置

- ```
  android:layout_alignParentLeft、
  android:layout_alignParentTop、
  android:layout_alignParentRight、
  android:layout_alignParentBottom、
  android:layout_centerInParent
  ```

  - 通过true进行选择相对于布局的位置

- 相对其他控件位置布局

  - ```
    android:layout_above
    android: layout_below
    android:layout_toLeftOf
    android:layout_toRightOf
    ```

  - 赋值为如@id/button3指定对象

  - 边缘对齐

    - ```
      android:layout_alignLeft
      android:layout_alignRight
      android:layout_alignTop
      android:layout_alignBottom
      ```

#### FrameLayout帧布局

- 同样使用`layout_gravity`来控制空间的布局，但是位于相同位置的空间会重叠
- 内部的子视图默认都会定位在屏幕的左上角

### 多媒体

#### 通知

- 通知渠道：每条通知都要属于⼀个对应的渠道。每个应⽤程序都可以⾃由地创建当前应⽤拥有哪些通知渠道，但是这些通知渠道的控制权是掌握在⽤户⼿上的。

- 创建通知渠道：

  - 获取通知管理器`val manager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager`

  - 创建通知渠道（createNotificationChannel()⽅法都是Android 8.0系统中新增的API，因此我们在使⽤的时候还需要进⾏版本判断才可以）

    - ```kotlin
      if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
          val channel = NotificationChannel(channelId, channelName, importance)
          manager.createNotificationChannel(channel)
      }
      ```

    - 渠道ID可以随便定义，只要保证全局唯⼀性就可以

    - 渠道名称是给⽤户看的，需要可以清楚地表达这个渠道的⽤途

    - 通知的重要等级主要有IMPORTANCE_HIGH、IMPORTANCE_DEFAULT、IMPORTANCE_LOW、IMPORTANCE_MIN

- 创建通知

  - ```kotlin
    val notification = NotificationCompat.Builder(context, channelId)
    .setContentTitle("This is content title")
    .setContentText("This is content text")
    .setSmallIcon(R.drawable.small_icon)
    .setLargeIcon(BitmapFactory.decodeResource(getResources(),R.drawable.large_icon))
    .build()//构建完成 
    manager.notify(1, notification)//发送
    ```

- 发送通知`manager.notify(1, notification)`

  - 第⼀个参数是id，要保证为每个通知指定的id都是不同的；第⼆个参数则是Notification对象，这⾥直接将我们刚刚创建好的Notification对象传⼊即可。

- 响应通知`PendingIntent`使通知可以被点击

  - PendingIntent倾向于在某个合适的时机执⾏某个动作
  - 先`val intent = Intent(this,NotificationActivity::class.java)`构建intent操作（跳转activity）`val pi = PendingIntent.getActivity(this, 0, intent, 0)`然后初始化notificationCompat中添加`.setContentIntent(pi)`进行绑定，实现点击通知后跳转到指定的activity

- 关闭通知

  - 再添加`.setAutoCancel(true)`当点击这个通知的时候，通知会⾃动取消
  - 根据id手动关闭通知`manager.notify(1, notification)`

- 高级样式

  - 完整显示大段通知

    - ```kotlin
      .setStyle(NotificationCompat.BigTextStyle().bigText("Learn
      how to build
      notifications, send and sync data, and use voice actions.
      Get the official
      Android IDE and developer tools to build apps for
      Android."))
      ```

  - 放置图片

    - ```kotlin
      .setStyle(NotificationCompat.BigPictureStyle().bigPicture(
      BitmapFactory.decodeResource(resources,
      R.drawable.big_image)))
      ```

#### 摄像头与相册

- 拍照

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        val takePhoto = 1
        lateinit var imageUri: Uri
        lateinit var outputImage: File
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            takePhotoBtn.setOnClickListener {
                // 创建File对象，⽤于存储拍照后的图⽚
                outputImage = File(externalCacheDir, "output_image.jpg")
                //getExternalCacheDir()⽅法可以得到当前应⽤缓存数据的位置(/sdcard/Android/data/<packagename>/cache)
                if (outputImage.exists()) {
                    outputImage.delete()
                }
                outputImage.createNewFile()
                imageUri = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
                    //对于高版本使用更为安全的方法，使用ContentProvider进行数据共享
                    FileProvider.getUriForFile(this, "com.example.cameraalbumtest.fileprovider", outputImage)
                } else {
                    Uri.fromFile(outputImage)
                }
                // 启动相机程序
                val intent = Intent("android.media.action.IMAGE_CAPTURE")
                intent.putExtra(MediaStore.EXTRA_OUTPUT, imageUri)
                startActivityForResult(intent, takePhoto)
            }
        }
        override fun onActivityResult(requestCode: Int, resultCode:Int, data: Intent?) {
            super.onActivityResult(requestCode, resultCode, data)
            when (requestCode) {
                takePhoto -> {
                    if (resultCode == Activity.RESULT_OK) {
                        // 将拍摄的照⽚显⽰出来
                        val bitmap = BitmapFactory.decodeStream(contentResolver.openInputStream(imageUri))
                        imageView.setImageBitmap(rotateIfRequired(bitmap))
                    }
                }
            }
        }
        //纠正画面旋转的问题
        private fun rotateIfRequired(bitmap: Bitmap): Bitmap {
            val exif = ExifInterface(outputImage.path)
            val orientation =
            exif.getAttributeInt(ExifInterface.TAG_ORIENTATION,
                                 ExifInterface.ORIENTATION_NORMAL)
            return when (orientation) {
                ExifInterface.ORIENTATION_ROTATE_90 ->
                rotateBitmap(bitmap, 90)
                ExifInterface.ORIENTATION_ROTATE_180 ->
                rotateBitmap(bitmap, 180)
                ExifInterface.ORIENTATION_ROTATE_270 ->
                rotateBitmap(bitmap, 270)
                else -> bitmap
            }
        }
        private fun rotateBitmap(bitmap: Bitmap, degree: Int): Bitmap {
            val matrix = Matrix()
            matrix.postRotate(degree.toFloat())
            val rotatedBitmap = Bitmap.createBitmap(bitmap, 0, 0,nbitmap.width, bitmap.height, matrix, true)
            bitmap.recycle() // 将不再需要的Bitmap对象回收
            return rotatedBitmap
        }
    }
    ```

  - 还需要对ContentProvider进行注册(AndroidManifest.xml)

    - ```xml
      <provider
      	android:name="androidx.core.content.FileProvider"
      	android:authorities="com.example.cameraalbumtest.fileprovider"
      	android:exported="false"
      	android:grantUriPermissions="true">
          //配置文件路径策略
      	<meta-data
      	 android:name="android.support.FILE_PROVIDER_PATHS" android:resource="@xml/file_paths" />
      </provider>
      ```

    - ndroid:authorities属性的值必须和刚才FileProvider.getUriForFile()⽅法中的第⼆个
      参数⼀致从相册选择图片

  - 创建⼀个file_paths.xml⽂件

    - ```xml
      <?xml version="1.0" encoding="utf-8"?>
      <paths xmlns:android="http://schemas.android.com/apk/res/android">
      <external-path name="my_images" path="/" />
      </paths>
      ```

- 从相册选择文件

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        ...
        val fromAlbum = 2
        override fun onCreate(savedInstanceState: Bundle?) {
            ...
            fromAlbumBtn.setOnClickListener {
                // 打开⽂件选择器
                val intent = Intent(Intent.ACTION_OPEN_DOCUMENT)
                intent.addCategory(Intent.CATEGORY_OPENABLE)
                // 指定只显⽰图⽚
                intent.type = "image/*"
                startActivityForResult(intent, fromAlbum)
            }
        }
        //对结束的子activity进行处理
        override fun onActivityResult(requestCode: Int, resultCode:Int, data: Intent?) {
            super.onActivityResult(requestCode, resultCode, data)
            when (requestCode) {
                ...
                fromAlbum -> {
                    if (resultCode == Activity.RESULT_OK && data != null) {
                        data.data?.let { uri ->
                        // 将选择的图⽚显⽰
                         val bitmap = getBitmapFromUri(uri)
                         imageView.setImageBitmap(bitmap)
                        }
                    }
                }
            }
        }
        private fun getBitmapFromUri(uri: Uri) = contentResolver
        .openFileDescriptor(uri, "r")?.use {
            BitmapFactory.decodeFileDescriptor(it.fileDescriptor)
        }
        ...
    }
    ```

#### 播放多媒体⽂件

- 资源位置
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230721225220406.png" alt="image-20230721225220406" style="zoom:33%;" />
  - 借助AssetManager这个类提供的接⼝对assets⽬录下的⽂件进⾏读取

##### 播放音频

- 使用MediaPlayer

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230721224800050.png" alt="image-20230721224800050" style="zoom:33%;" />

    <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230721224822607.png" alt="image-20230721224822607" style="zoom:33%;" />

- 流程

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        private val mediaPlayer = MediaPlayer()//实例化对象
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            initMediaPlayer()
            play.setOnClickListener {
                if (!mediaPlayer.isPlaying) {
                    mediaPlayer.start() // 开始播放
                }
            }
            pause.setOnClickListener {
                if (mediaPlayer.isPlaying) {
                    mediaPlayer.pause() // 暂停播放
                }
            }
            stop.setOnClickListener {
                if (mediaPlayer.isPlaying) {
                    mediaPlayer.reset() // 停⽌播放
                    initMediaPlayer()
                }
            }
        }
        private fun initMediaPlayer() {
            //通过AssetManager打开文件
            val assetManager = assets
            val fd = assetManager.openFd("music.mp3")
            mediaPlayer.setDataSource(fd.fileDescriptor, fd.startOffset, fd.length)
            mediaPlayer.prepare()
        }
        override fun onDestroy() {
            super.onDestroy()
            mediaPlayer.stop()
            mediaPlayer.release()
        }
    }
    ```

##### 播放视频

- VideoView

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230721225459930.png" alt="image-20230721225459930" style="zoom:33%;" />

    <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230721225515805.png" alt="image-20230721225515805" style="zoom:33%;" />

- 不⽀持直接播放assets⽬录下的视频资源，res⽬录下创建⼀个raw⽬录进行播放

  - ```kotlin
    class MainActivity : AppCompatActivity() {
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            val uri = Uri.parse("android.resource://$packageName/${R.raw.video}")
            videoView.setVideoURI(uri)
            play.setOnClickListener {
                if (!videoView.isPlaying) {
                    videoView.start() // 开始播放
                }
            }
            pause.setOnClickListener {
                if (videoView.isPlaying) {
                    videoView.pause() // 暂停播放
                }
            }
            replay.setOnClickListener {
                if (videoView.isPlaying) {
                    videoView.resume() // 重新播放
                }
            }
        }
        override fun onDestroy() {
            super.onDestroy()
            videoView.suspend()
        }
    }
    ```

  - 

### Material Desig ui设计

#### Toolbar

-  创建的项目中默认包含了actionbar（`res/values/styles.xml`中``<style name="AppTheme" parent="Theme.AppCompat.Light.DarkActionBar">`

  - 去掉默认actionbar：使用主题`Theme.AppCompat.Light.NoActionBar`
  
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230723164841144.png" style="zoom:33%;" />

- ```xml
  <FrameLayout
  xmlns:android="http://schemas.android.com/apk/res/android"
  xmlns:app="http://schemas.android.com/apk/res-auto"
  android:layout_width="match_parent"
  android:layout_height="match_parent">
  <androidx.appcompat.widget.Toolbar
  android:id="@+id/toolbar"
  android:layout_width="match_parent"
  android:layout_height="?attr/actionBarSize"
  android:background="@color/colorPrimary"
  android:theme="@style/ThemeOverlay.AppCompat.Dark.ActionBar"为Toolbar指定主题
  app:popupTheme="@style/ThemeOverlay.AppCompat.Light" />为弹出菜单指定
  </FrameLayout>
  ```

  - 声明名空间

    - ```kotlin
      xmlns:android="http://schemas.android.com/apk/res/android"
      xmlns:app="http://schemas.android.com/apk/res-auto"
      ```


  - 传入实例`setSupportActionBar(toolbar)`

- 内容：

  - activity中`android:label`属性

  - 添加按钮：`res/menu/toolbar.xml`(Menu resource file)

  - ```xml
    <menu xmlns:android="http://schemas.android.com/apk/res/android" xmlns:app="http://schemas.android.com/apk/res-auto">
        <item
              android:id="@+id/backup"
              android:icon="@drawable/ic_backup"
              android:title="Backup"
              app:showAsAction="always" />//永远显示
        <item
              android:id="@+id/delete"
              android:icon="@drawable/ic_delete"
              android:title="Delete"
              app:showAsAction="ifRoom" />//空间足够时显示在toolbar否则在菜单
        <item
              android:id="@+id/settings"
              android:icon="@drawable/ic_settings"
              android:title="Settings"
              app:showAsAction="never" />//显示在菜单中
    </menu>
    ```

  - Toolbar中的action按钮只会显⽰图标，菜单中的action按钮只会显⽰⽂字

  - 加载及响应

    - ```kotlin
      class MainActivity : AppCompatActivity() {
          ...
          //加载布局
          override fun onCreateOptionsMenu(menu: Menu?): Boolean {
              menuInflater.inflate(R.menu.toolbar, menu)
              return true
          }
          //点击响应
          override fun onOptionsItemSelected(item: MenuItem): Boolean {
              when (item.itemId) {
                  R.id.backup -> Toast.makeText(this, "You clicked Backup",
                                                Toast.LENGTH_SHORT).show()
                  R.id.delete -> Toast.makeText(this, "You clicked Delete",
                                                Toast.LENGTH_SHORT).show()
                  R.id.settings -> Toast.makeText(this, "You clicked Settings",
                                                  Toast.LENGTH_SHORT).show()
              }
              return true
          }
      }
      ```


#### DrawerLayout

- ⼀个布局，在布局中允许放⼊两个直接⼦控件：第⼀个⼦控件是主屏幕中显⽰的内容，第⼆个⼦控件是滑动菜单中显⽰的内容。

- ```xml
  <androidx.drawerlayout.widget.DrawerLayout
  xmlns:android="http://schemas.android.com/apk/res/android"
  xmlns:app="http://schemas.android.com/apk/res-auto"
  android:id="@+id/drawerLayout"
  android:layout_width="match_parent"
  android:layout_height="match_parent">
  //主屏幕中显示的内容
  <FrameLayout
  android:layout_width="match_parent"
  android:layout_height="match_parent">
  <androidx.appcompat.widget.Toolbar
  android:id="@+id/toolbar"
  android:layout_width="match_parent"
  android:layout_height="?attr/actionBarSize"
  android:background="@color/colorPrimary"
  android:theme="@style/ThemeOverlay.AppCompat.Dark.ActionBar"
  app:popupTheme="@style/ThemeOverlay.AppCompat.Light" />
  </FrameLayout>
  //抽屉内容
  <TextView
  android:layout_width="match_parent"
  android:layout_height="match_parent"
  android:layout_gravity="start"//指定抽屉的位置（left左，right右，start自动）
  android:background="#FFF"
  android:text="This is menu"
  android:textSize="30sp" />
  </androidx.drawerlayout.widget.DrawerLayout>
  ```

- 通过按钮控制滑动

  - ```kotlin
    //内置添加
    supportActionBar?.let {
        it.setDisplayHomeAsUpEnabled(true)
        it.setHomeAsUpIndicator(R.drawable.ic_menu)
    }
    
    //响应绑定
    when (item.itemId) {
        android.R.id.home ->
        drawerLayout.openDrawer(GravityCompat.START)
        ...
    }
    ```

  - 

#### NavigationView

- 美化滑动窗口

- ```
  implementation 'com.google.android.material:material:1.1.0'
  implementation 'de.hdodenhof:circleimageview:3.0.1'
  ```

  - 引⼊了Material库之后,需要将res/values/styles.xml⽂件中AppTheme的parent主题改成
    Theme.MaterialComponents.Light.NoActionBar，否则在使⽤接下来的⼀些控件时可能会遇到崩溃问题。

- ```xml
  <menu xmlns:android="http://schemas.android.com/apk/res/android">
      <group android:checkableBehavior="single">//菜单项只能单选
          <item
                android:id="@+id/navCall"
                android:icon="@drawable/nav_call"
                android:title="Call" />
          <item
                android:id="@+id/navFriends"
                android:icon="@drawable/nav_friends"
                android:title="Friends" />
          <item
                android:id="@+id/navLocation"
                android:icon="@drawable/nav_location"
                android:title="Location" />
          <item
                android:id="@+id/navMail"
                android:icon="@drawable/nav_mail"
                android:title="Mail" />
          <item
                android:id="@+id/navTask"
                android:icon="@drawable/nav_task"
                android:title="Tasks" />
      </group>
  </menu>
  ```

- ```xml
  <RelativeLayout
  xmlns:android="http://schemas.android.com/apk/res/android"
  android:layout_width="match_parent"
  android:layout_height="180dp"
  android:padding="10dp"
  android:background="@color/colorPrimary">
  <de.hdodenhof.circleimageview.CircleImageView //显示圆形头像
  android:id="@+id/iconImage"
  android:layout_width="70dp"
  android:layout_height="70dp"
  android:src="@drawable/nav_icon"
  android:layout_centerInParent="true" />
  <TextView
  android:id="@+id/mailText"
  android:layout_width="wrap_content"
  android:layout_height="wrap_content"
  android:layout_alignParentBottom="true"
  android:text="tonygreendev@gmail.com"
  android:textColor="#FFF"
  android:textSize="14sp" />
  <TextView
  android:id="@+id/userText"
  android:layout_width="wrap_content"
  android:layout_height="wrap_content"
  android:layout_above="@id/mailText"
  android:text="Tony Green"
  android:textColor="#FFF"
  android:textSize="14sp" />
  </RelativeLayout>
  ```

- 使用

  - ```xml
    <com.google.android.material.navigation.NavigationView
    android:id="@+id/navView"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:layout_gravity="start"
    app:menu="@menu/nav_menu"
    app:headerLayout="@layout/nav_header"/>
    ```

- 响应

  - ```kotlin
    navView.setNavigationItemSelectedListener {
        drawerLayout.closeDrawers()
        true
    }
    ```

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230723175248022.png" alt="image-20230723175248022" style="zoom:33%;" />

#### FloatingActionButton

- 用于实现悬浮按钮

- ```xml
  <com.google.android.material.floatingactionbutton.FloatingActionBut
  ton
  android:id="@+id/fab"
  android:layout_width="wrap_content"
  android:layout_height="wrap_content"
  android:layout_gravity="bottom|end"//指定位置
  android:layout_margin="16dp"
  android:src="@drawable/ic_done" />
  ```

- 和普通按钮一样使用setOnClickListener()⽅法来设置按钮的点击事件

#### Snackbar

- 带有交互功能的toast

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230723180555410.png" alt="image-20230723180555410" style="zoom:33%;" />

- ```kotlin
  Snackbar.make(view, "Data deleted",
  Snackbar.LENGTH_SHORT)//显示内容   显示时长
  .setAction("按钮name") {
  //动作响应
  }
  .show()
  ```

  - make()⽅法的第⼀个参数需要传⼊⼀个View，只要是当前界⾯布局的任意⼀个View都可以

#### CoordinatorLayout

- CoordinatorLayout本⾝就是⼀个加强版的FrameLayout
- 直接替换标签即可，可以监听子组件，自适应变化（如上图不会挡住悬浮按钮）

#### MaterialCardView

- 实现卡片式布局

- ```xml
  <com.google.android.material.card.MaterialCardView
  android:layout_width="match_parent"
  android:layout_height="wrap_content"
  app:cardCornerRadius="4dp"//圆角弧度
  app:elevation="5dp">//高度，控制投影效果
  <TextView
  android:id="@+id/infoText"
  android:layout_width="match_parent"
  android:layout_height="wrap_content"/>
  </com.google.android.material.card.MaterialCardView>
  ```

  - 卡片内容夹在标签内部

#### Glide

- 加载图片时对图片进行压缩等一系列处理
- `Glide.with(context).load(url).into(ImageView)`

#### AppBarLayout

- CoordinatorLayout就是⼀个加强版的FrameLayout，那么FrameLayout中的所有控件在不进⾏明确定位的情况下，默认都会摆放在布局的左上⾓，从⽽产⽣了遮挡的现象
- 将Toolbar嵌套到AppBarLayout中；改日下面的如给RecyclerView指定⼀个布局⾏为
  - `app:layout_behavior="@string/appbar_scrolling_view_behavior"`
- 滚动时行为(AppBarLayout)，app:layout_scrollFlags属性
  - scroll|enterAlways|snap：
    - scroll表⽰当RecyclerView向上滚动的时候，Toolbar会跟着⼀起向上滚动并实现隐藏；enterAlways表⽰当RecyclerView向下滚动的时候，Toolbar会跟着⼀起向下滚动并重新显⽰；snap表⽰当Toolbar还没有完全隐藏或显⽰的时候，会根据当前滚动的距离，⾃动选择是隐藏还是显⽰。

#### SwipeRefreshLayout

- 把想要实现**下拉刷新功能**的控件放置到SwipeRefreshLayout中，就可以迅速让
  这个控件⽀持下拉刷新。

- `implementation "androidx.swiperefreshlayout:swiperefreshlayout:1.0.0"`

- 响应

  - ```kotlin
    swipeRefresh.setColorSchemeResources(R.color.colorPrimary)//下拉颜色
    swipeRefresh.setOnRefreshListener {
        refreshFruits(adapter)//刷新时操作
    }
    ```

#### CollapsingToolbarLayout

- 可折叠式标题栏，不仅仅是展⽰⼀个标题栏，⽽且能够实现⾮常华丽的效果。只能作为AppBarLayout的直接⼦布局来使⽤

- ```xml
  <androidx.coordinatorlayout.widget.CoordinatorLayout
  xmlns:android="http://schemas.android.com/apk/res/android"
  xmlns:app="http://schemas.android.com/apk/res-auto"
  android:layout_width="match_parent"
  android:layout_height="match_parent">
  <com.google.android.material.appbar.AppBarLayout
  android:id="@+id/appBar"
  android:layout_width="match_parent"
  android:layout_height="250dp">
  <com.google.android.material.appbar.CollapsingToolbarLayout
  	android:id="@+id/collapsingToolbar"
  	android:layout_width="match_parent"
  	android:layout_height="match_parent"
  	android:theme="@style/ThemeOverlay.AppCompat.Dark.ActionBar"
  	app:contentScrim="@color/colorPrimary"
  	app:layout_scrollFlags="scroll|exitUntilCollapsed">
  	<ImageView
  		android:id="@+id/fruitImageView"
  		android:layout_width="match_parent"
  		android:layout_height="match_parent"
  		android:scaleType="centerCrop"
  		app:layout_collapseMode="parallax" />//折叠过程中的折叠模式
  	<androidx.appcompat.widget.Toolbar
  		android:id="@+id/toolbar"
  		android:layout_width="match_parent"
  		android:layout_height="?attr/actionBarSize"
  		app:layout_collapseMode="pin" />
  </com.google.android.material.appbar.CollapsingToolbarLayout>
  </com.google.android.material.appbar.AppBarLayout>
      //下面内容
  <androidx.core.widget.NestedScrollView
  	android:layout_width="match_parent"
  	android:layout_height="match_parent"
  		app:layout_behavior="@string/appbar_scrolling_view_behavior">
      <LinearLayout
  		android:orientation="vertical"
  		android:layout_width="match_parent"
  		android:layout_height="wrap_content">
          <com.google.android.material.card.MaterialCardView
  			android:layout_width="match_parent"
  			android:layout_height="wrap_content"
  			android:layout_marginBottom="15dp"
  			android:layout_marginLeft="15dp"
  			android:layout_marginRight="15dp"
  			android:layout_marginTop="35dp"
  			app:cardCornerRadius="4dp">
  		<TextView
  			android:id="@+id/fruitContentText"
  			android:layout_width="wrap_content"
  			android:layout_height="wrap_content"
  			android:layout_margin="10dp" />
  		</com.google.android.material.card.MaterialCardView>
  	</LinearLayout>
  </androidx.core.widget.NestedScrollView>
  <com.google.android.material.floatingactionbutton.FloatingActionButton
  	android:layout_width="wrap_content"
  	android:layout_height="wrap_content"
  	android:layout_margin="16dp"
  	android:src="@drawable/ic_comment"
  	app:layout_anchor="@id/appBar"//锚点，这样悬浮按钮就会出现在⽔果标题栏的区域内
  	app:layout_anchorGravity="bottom|end" />
  </androidx.coordinatorlayout.widget.CoordinatorLayout>
  ```

  - app:contentScrim属性⽤于指定CollapsingToolbarLayout在趋于折叠状态以及折叠之后的背景⾊
  - scroll表⽰CollapsingToolbarLayout会随着⽔果内容详情的滚动⼀起滚动，exitUntilCollapsed表⽰当CollapsingToolbarLayout随着滚动完成折叠之后就保留在界⾯上，不再移出屏幕。

- ```kotlin
  class FruitActivity : AppCompatActivity() {
      companion object {
          const val FRUIT_NAME = "fruit_name"
          const val FRUIT_IMAGE_ID = "fruit_image_id"
      }
      override fun onCreate(savedInstanceState: Bundle?) {
          super.onCreate(savedInstanceState)
          setContentView(R.layout.activity_fruit)
          val fruitName = intent.getStringExtra(FRUIT_NAME) ?: ""
          val fruitImageId = intent.getIntExtra(FRUIT_IMAGE_ID, 0)
          setSupportActionBar(toolbar)
          supportActionBar?.setDisplayHomeAsUpEnabled(true)
          collapsingToolbar.title = fruitName
          Glide.with(this).load(fruitImageId).into(fruitImageView)
          fruitContentText.text = generateFruitContent(fruitName)
      }
      override fun onOptionsItemSelected(item: MenuItem): Boolean {
          when (item.itemId) {
              android.R.id.home -> {
                  finish()
                  return true
              }
          }
          return super.onOptionsItemSelected(item)
      }
      private fun generateFruitContent(fruitName: String) = fruitName.repeat(500)
  }
  ```

- 

### 动画 

#### 帧动画

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724164239290.png" alt="image-20230724164239290" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724164315079.png" alt="image-20230724164315079" style="zoom:33%;" />

#### 补间动画

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724164445294.png" alt="image-20230724164445294" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724164456222.png" alt="image-20230724164456222" style="zoom:33%;" /><img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724164519610.png" style="zoom:33%;" />

- 回调函数
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724164957060.png" alt="image-20230724164957060" style="zoom:33%;" />

#### 属性动画

- 原理
  - 属性动画的运行机制是通过**不断地对值进行操作**来实现的，而初始值和结束值之间的动画过渡就是由ValueAnimator这个类来负责计算的。它的内部使用一种时间循环的机制来计算值与值之间的动画过渡，我们只需要将初始值和结束值提供给ValueAnimator，并且告诉它动画所需运行的时长，那么ValueAnimator就会自动帮我们完成从初始值平滑地过渡到结束值这样的效果。除此之外，ValueAnimator还负责管理动画的播放次数、播放模式、以及对动画设置监听器等。

- 区别
  - **补间动画**：
    - 主要通过改变视图的绘制来实现动画效果，例如平移、缩放、旋转和透明度。
    - **不会改变视图的实际属性或位置。**
  - **属性动画**：
    - **可以改变视图的实际属性和位置**，为动画提供了更多的可能性。
    - 更为强大和灵活，可以对任意对象的属性进行动画操作，不仅仅是视图。

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724165352706.png" alt="image-20230724165352706" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724165431213.png" alt="image-20230724165431213" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230724165451876.png" alt="image-20230724165451876" style="zoom:33%;" />

### 视图结构

- Window、Activity、DecorView以及ViewRoot之间的关系
- Activity并**不负责视图控制**，它只是**控制生命周期和处理事件**。一个Activity包含了一个Window，**Window才是真正代表一个窗口**。
- **Window是视图的承载器**，内部持有一个 DecorView，而这个**DecorView才是 view 的根布局**。Window是一个抽象类，实际在Activity中持有的是其子类PhoneWindow。PhoneWindow中有个内部类DecorView，通过创建DecorView来加载Activity中设置的布局`R.layout.activity_main`。
- DecorView是**FrameLayout的子类**，它可以被认为是Android视图树的**根节点视图**。
- ViewRoot对应**ViewRootImpl类，它是连接WindowManagerService和DecorView的纽带**，View的**三大流程**（测量（measure），布局（layout），绘制（draw））均通过ViewRoot来完成。RootView继承了Handler类，可以**接收事件并分发**，Android的所有触屏事件、按键事件、界面刷新等事件都是通过ViewRoot进行分发的。
- <img src="https://camo.githubusercontent.com/e33fc83f97381f8c6174f28e3964cf9fd79757714fa4a7296dcdd51007b23258/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d653737336162326362383361643231342e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:50%;" />

#### View的测量布局及绘制

- View的绘制是**从上往下**一层层迭代下来的。DecorView-->ViewGroup（--->ViewGroup）-->View ，按照这个流程从上往下，依次**measure(测量),layout(布局),draw(绘制)**。
  - <img src="https://camo.githubusercontent.com/7fad924f63e074fa4311a7eef9f7cef877685ede0d272ae36d02d2d4fc989651/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d613761636536663932323163396437392e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />


##### Measure测量

- 调用measure()方法，进行一些逻辑处理，然后调用onMeasure()方法，在其中调用setMeasuredDimension()设定View的宽高信息，完成View的测量操作。

- ```java
  public final void measure(int widthMeasureSpec, int heightMeasureSpec) {
  }
  
  protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
          setMeasuredDimension(getDefaultSize(getSuggestedMinimumWidth(), widthMeasureSpec),
                  getDefaultSize(getSuggestedMinimumHeight(), heightMeasureSpec));
      }
  ```

- widthMeasureSpec, heightMeasureSpec的确定

  - <img src="https://camo.githubusercontent.com/f3ae0d7d42fab0b57316a9a379c5bd7253e95535c04abd35266bc7806d375057/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d643362663039303561656238373139622e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom: 80%;" />
  - Mode模式
    - UNSPECIFIED ：不对View进行任何限制，要多大给多大，一般用于系统内部
    - EXACTLY：对应LayoutParams中的match_parent和具体数值这两种模式。检测到View所需要的精确大小，这时候View的最终大小就是SpecSize所指定的值，
    - AT_MOST ：对应LayoutParams中的wrap_content。View的大小不能大于父容器的大小。
    - <img src="https://camo.githubusercontent.com/6140b113581f69dd02314dd2e27d730227f387c5d4b925e80fa56fed4beb217b/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d653366323063363636326566666237622e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />
  - size
    - 对于DecorView，其确定是通过屏幕的大小，和自身的布局参数LayoutParams。
    - 对于其他View（包括ViewGroup），其确定是通过父布局的MeasureSpec和自身的布局参数LayoutParams。
  - MeasureSpec的指定也是从顶层布局开始一层层往下去，**父布局影响子布局**。

- 当子View的LayoutParams的布局格式是wrap_content，可以看到子View的大小是父View的剩余尺寸，和设置成match_parent时，子View的大小没有区别。为了显示区别，一般在自定义View时，需要重写onMeasure方法，处理wrap_content时的情况，进行特别指定。（即父wrapcontent子mathparent）

  - 自定义控件通常需要重写onMeasure来实现wrap_content

  - ```java
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        //获得宽度的模式
        int wSpecMode = MeasureSpec.getMode(widthMeasureSpec);
        //获得宽度的大小
        int wSpecSize = MeasureSpec.getSize(widthMeasureSpec);
        //获得高度的模式
        int hSpecMode = MeasureSpec.getMode(heightMeasureSpec);
        //获得高度的大小
        int hSpecSize = MeasureSpec.getSize(heightMeasureSpec);
        //默认值
        int result = 100;
    
        //当控件高和宽 为 wrap_content
        if (wSpecMode == MeasureSpec.AT_MOST && hSpecMode == MeasureSpec.AT_MOST) {
            setMeasuredDimension(result,result );
            //当宽为 wrap_content 
        } else if (wSpecMode == MeasureSpec.AT_MOST) {
            setMeasuredDimension(result, hSpecSize);
            //当高为 wrap_content 
        } else if (hSpecMode == MeasureSpec.AT_MOST) {
                setMeasuredDimension(wSpecSize, result);
        }
    }
    ```

- <img src="https://camo.githubusercontent.com/566d361b93040921e3d595bea8d8517736f6ba8a193623b8084ab7c997bc5571/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d643161353732393434323866663636382e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom: 80%;" />

##### layout布局

- View的布局主要通过确定上下左右四个点来确定的

- 其中布局也是自上而下，不同的是ViewGroup**先在layout()中确定自己的布局**，然后在**onLayout()方法中再调用子View的layout()方法**，让子View布局。在Measure过程中，ViewGroup一般是**先测量子View的大小**，**然后再确定自身的大小**。

- **onLayout**用于对**子对象**进行布局，对于自定义的ViewGroup必须实现这个方法

  - ```java
    protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
        }
    ```

- <img src="https://camo.githubusercontent.com/6eac7dfc45afb5cf12e764fa07b53b47aaf3647c3bc48575d8bfcb285578ed65/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d386165666163343262333931323533392e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />

##### deaw绘制

- 顺序
  - 绘制背景 background.draw(canvas)
  - 绘制自己（onDraw）
  - 绘制Children(dispatchDraw)
  - 绘制装饰（onDrawScrollBars）
- 在ViewGroup中，实现了 dispatchDraw()方法，而在单一子View中不需要实现该方法。自定义View一般要重写**onDraw()**方法，在其中绘制不同的样式。
- <img src="https://camo.githubusercontent.com/d04e94186bcc562c7ebad76c26ac5e665a98bc9a46c19b963dbc5ea696b56975/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d353934663662336364653837363263372e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:80%;" />

##### 重写

- **onMeasure()方法**：单一View，一般重写此方法，针对wrap_content情况，规定View默认的大小值，避免于match_parent情况一致。ViewGroup，若不重写，就会执行和单子View中相同逻辑，不会测量子View。一般会重写onMeasure()方法，循环测量子View。
- **onLayout()方法:**单一View，不需要实现该方法。ViewGroup必须实现，该方法是个抽象方法，实现该方法，来对子View进行布局。
- **onDraw()方法：**无论单一View，或者ViewGroup都需要实现该方法，因其是个空方法

## 拓展

### 安卓虚拟机Dalvik

- Dalvik是Google公司自己设计用于Android平台的Java虚拟机
- 专有的DEX可执行文件格式，体积更小，执行速度更快；
- 提供了对象生命周期管理，堆栈管理，线程管理，安全和异常管理以及垃圾回收等重要功能；
- 所有的Android程序都运行在Android系统进程里，**每个进程对应着一个Dalvik虚拟机实例**。

#### 与JAVA虚拟机的区别

- **Java虚拟机基于栈架构**，程序在运行时虚拟机需要频繁的从栈上读取或写入数据，这个过程需要更多的指令分派与内存访问次数，会耗费不少CPU时间，对于像手机设备资源有限的设备来说，这是相当大的一笔开销。**Dalvik虚拟机基于寄存器架构**。数据的访问通过寄存器间直接传递，这样的访问方式比基于栈方式要快很多。

- Java虚拟机通过解码class文件中的内容来运行程序。而Dalvik虚拟机运行的是Dalvik字节码，所有的Dalvik字节码由Java字节码转换而来，并被打包到一个DEX（Dalvik Executable）可执行文件中。Dalvik虚拟机通过解释DEX文件来执行这些字节码。**Dalvik可执行文件体积小。Android SDK中有一个叫dx的工具负责将Java字节码转换为Dalvik字节码。**
  - dx工具对Java类文件重新排列，**消除其中的冗余信息**，重新组合形成一个**常量池**，所有的类文件共享同一个常量池。由于dx工具对常量池的压缩，使得相同的字符串，常量在DEX文件中只出现一次，从而减小了文件的体积。
- <img src="https://camo.githubusercontent.com/02dc9a97ea7fb9db49bb1835e9afdfe501cb9cfa7397bc14e2a1db4481c063b0/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d396465616461333235303862386565352e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom: 67%;" />
- <img src="https://camo.githubusercontent.com/29a9dbcbbb33a640b4a276fb9628fe7138a8a3c211344313bc179b0174928f01/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d366233353133356633663461333561392e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:67%;" />
- <img src="https://camo.githubusercontent.com/b45e41b651b66a0d380e87d8cf67320cadf2f33c8110db2e7efacbd5f2f08b1e/687474703a2f2f75706c6f61642d696d616765732e6a69616e7368752e696f2f75706c6f61645f696d616765732f333938353536332d346461336465353736653661303435642e706e673f696d6167654d6f6772322f6175746f2d6f7269656e742f7374726970253743696d61676556696577322f322f772f31323430" alt="img" style="zoom:67%;" />
  - 一个应用首先经过DX工具将class文件转换成Dalvik虚拟机可以执行的**dex文件**，然后由**类加载器**加载原生类和Java类，接着由解释器根据指令集对**Dalvik字节码进行解释**、执行。最后，根据dvm_arch参数选择编译的目标机体系结构。

#### APK编译打包流程

- Java编译器对工程本身的java代码进行编译，这些java代码有三个来源：app的**源代码**，由资源文件生成的**R文件(**aapt工具)，以及有aidl文件生成的**java接口文件**(aidl工具)。**产出为.class文件**。

- .class文件和依赖的三方库文件通过dex工具生成Delvik虚拟机可执行的**.dex文件**，包含了所有的class信息，包括项目自身的class和依赖的class。产出为.dex文件。

- apkbuilder工具将.dex文件和编译后的资源文件**生成未经签名对齐的apk文件**。这里编译后的资源文件包括两部分，一是由aapt编译产生的编译后的资源文件，二是依赖的三方库里的资源文件。产出为未经签名的.apk文件。

  4.分别由Jarsigner和zipalign对apk文件进行**签名和对齐，生成最终的apk文件。**

  总结为：**编译-->DEX-->打包-->签名和对齐**

#### ART虚拟机

- ART代表Android Runtime，Dalvik是依靠一个Just-In-Time (JIT)编译器去解释字节码。开发者编译后的应用代码需要通过**一个解释器**在用户的设备上运行，这一机制并不高效，但让应用能更容易在不同硬件和架构上运行。ART则完全改变了这套做法，在应用安装时就**预编译字节码到机器语言**，这一机制叫Ahead-Of-Time (AOT）编译。在移除解释代码这一过程后，应用程序执行将更有效率，启动更快。
- ART优点：
  1. 系统性能的显著提升。
  2. 应用启动更快、运行更快、体验更流畅、触感反馈更及时。
  3. 更长的电池续航能力。
  4. 支持更低的硬件。
- ART缺点：
  1. 更大的存储空间占用，可能会增加10%-20%。
  2. 更长的应用安装时间。
- 

### 进程间通信

- 使用Intent
- 使用文件共享以及SharedPreferences 
  - 并发读取存在问题，可能丢失数据
- Content Provider

#### Message

- 一种轻量化的解决方案，适用于数据量不大的情况	
  - Messenger 是以串行的方式处理客户端发来的消息，如果大量消息同时发送到服务端，服务端只能一个一个处理，所以大量并发请求就不适合用 Messenger ，而且 Messenger 只适合传递消息，不能跨进程调用服务端的方法。

- 服务端进程：服务端创建一个 Service 来处理客户端请求，同时通过一个 Handler 对象来实例化一个 Messenger 对象，然后在 Service 的 onBind 中返回这个 Messenger 对象底层的 Binder 即可。
- 客户端进程：首先绑定服务端 Service ，绑定成功之后用服务端的 IBinder 对象创建一个 Messenger ，通过这个 Messenger 就可以向服务端发送消息了，消息类型是 Message 。如果需要服务端响应，则需要创建一个 Handler 并通过它来创建一个 Messenger（和服务端一样），并通过 Message 的 replyTo 参数传递给服务端。服务端通过 Message 的 replyTo 参数就可以回应客户端了。
- 即双向互相广播

#### AIDL

- 服务端：服务端创建一个 Service 用来监听客户端的连接请求，然后创建一个 AIDL 文件，将暴露给客户端的接口在这个 AIDL 文件中声明，最后在 Service 中实现这个 AIDL 接口即可。

- 客户端：绑定服务端的 Service ，绑定成功后，将服务端返回的 Binder 对象转成 AIDL 接口所属的类型，然后就可以调用 AIDL 中的方法了。客户端调用远程服务的方法，被调用的方法运行在服务端的 Binder 线程池中，同时客户端的线程会被挂起，如果服务端方法执行比较耗时，就会导致客户端线程长时间阻塞，导致 ANR 。客户端的 onServiceConnected 和 onServiceDisconnected 方法都在 UI 线程中

### Bitmap压缩

- 很多时候ImageView并没有原始图片的尺寸那么大（即屏幕区域分辨率没那么大），这个时候把整个图片加载进来后再设置给ImageView，显然是没有必要的，因为ImageView根本没办法显示原始图片。这时候就可以按一定的采样率来将图片缩小后再加载进来，这样图片既能在ImageView显示出来，又能降低内存占用
- Bitmap在Android中指的是一张图片。通过BitmapFactory类提供的四类方法：decodeFile,decodeResource, decodeStream和decodeByteArray, 分别从文件系统，资源，输入流和字节数组中加载出一个Bitmap对象。

#### BitmapFactory.Options参数

- 通过对inSampleSize（采样率）的设置，对图片的像素的高和宽进行缩放。

  - 当inSampleSize=1，即采样后的图片大小为图片的原始大小。小于1，也按照1来计算。 当inSampleSize>1，即采样后的图片将会缩小，缩放比例为1/(inSampleSize的**二次方**)。

    *inSampleSize的取值应该总是**2的指数**，如1，2，4，8等。如果外界传入的inSampleSize的值不为2的指数，那么系统会向下取整并选择一个最接近2的指数来代替。

  - 例如：一张1024 ×1024像素的图片，采用ARGB8888格式存储，那么内存大小1024×1024×4=4M。如果inSampleSize=2，那么采样后的图片内存大小：512×512×4=1M。

- inJustDecodeBounds

  - 通过inJustDecodeBounds=true，然后加载图片就可以实现**只解析图片的宽高信息**，并不会真正的加载图片，所以这个操作是轻量级的。
  - 计算出缩放比后，然后在将inJustDecodeBounds=false,再重新加载图片，就可以加载缩放后的图片。

#### 加载流程

- 将BitmapFactory.Options的inJustDecodeBounds参数设为**true并加载图片**。
- 从BitmapFactory.Options中取出图片的**原始宽高信息**，它们对应于outWidth和outHeight参数。
- 根据采样率的规则并结合目标View的所需大小计算出**采样率inSampleSize**。
- 将BitmapFactory.Options的inJustDecodeBounds参数设为**false，然后重新加载图片**。

### 进程优先级

- 当系统内存不足时，Android系统将根据进程的优先级选择杀死一些不太重要的进程，优先级低的先杀死。进程优先级**从高到低**如下。
- 前台进程：
  - 处于**正在与用户交互**的activity
  - 与前台activity**绑定**的service
  - 调用了startForeground（）方法的service（前台服务）
  - 正在执行oncreate（），onstart（），ondestroy（）方法的 service。
  - 进程中包含正在执行onReceive（）方法的BroadcastReceiver。
- 可视进程：
  - 为处于前台，但仍然可见的activity（例如：调用了onpause（）而**还没调用onstop（）**的activity）。典型情况是：运行activity时，弹出对话框（dialog等），此时的activity虽然不是前台activity，但是仍然可见。
  - 可见activity绑定的service。（处于上诉情况下的activity所绑定的service）
- 服务进程：
  - 已经启动的service
- 后台进程：
  - 不可见的activity（调用**onstop（）之后**的activity）
- 空进程：
  - 任何没有活动的进程

### 创建9-Patch图⽚

- 右键png
- 右键png图片生成
- 图⽚的4个边框绘制⼀个个的⼩⿊点，在上边框和左边框绘制的部分表⽰当图⽚需要**拉伸时**就拉伸⿊点标记的区域，在下边框和边框绘制的部分表⽰内容**允许被放置**的区域。按住Shift键拖动可以进⾏擦除
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230717185105977.png" alt="image-20230717185105977" style="zoom:33%;" />

### Jetpack

#### ViewModel

- ⽤于存放与界⾯相关的数据

- 并且ViewModel在⼿机屏幕发⽣旋转的时候不会被重新创建，数据不会丢失

- 引入`implementation "androidx.lifecycle:lifecycle-extensions:2.2.0"`

- ```kotlin
  class MainViewModel : ViewModel() {
      var counter = 0
  }
  
  class MainActivity : AppCompatActivity() {
      lateinit var viewModel: MainViewModel
      override fun onCreate(savedInstanceState: Bundle?) {
          super.onCreate(savedInstanceState)
          setContentView(R.layout.activity_main)
          viewModel = ViewModelProvider(this).get(MainViewModel::class.java)
          plusOneBtn.setOnClickListener {
              viewModel.counter++
              refreshCounter()
          }
          refreshCounter()
      }
      private fun refreshCounter() {
          infoText.text = viewModel.counter.toString()
      }
  }
  ```

  - 通过ViewModelProvider来获取ViewModel的实例`ViewModelProvider(<你的Activity或Fragment实例>).get(<你的ViewModel>::class.java)`

- 带参数初始化 

  - ```kotlin
    class MainViewModelFactory(private val countReserved: Int) :ViewModelProvider.Factory {
        override fun <T : ViewModel> create(modelClass: Class<T>): T {
            return MainViewModel(countReserved) as T
        }
    }
    
    class MainViewModel(countReserved: Int) : ViewModel() {
        var counter = countReserved
    }
    
    viewModel = ViewModelProvider(this, MainViewModelFactory(countReserved))
    .get(MainViewModel::class.java)
    ```

#### Lifecycles

- 让任何⼀个类都能轻松感知到Activity的⽣命周期

- ```kotlin
  class MyObserver : LifecycleObserver {
  @OnLifecycleEvent(Lifecycle.Event.ON_START)
      fun activityStart() {
          Log.d("MyObserver", "activityStart")
      }
      @OnLifecycleEvent(Lifecycle.Event.ON_STOP)
      fun activityStop() {
          Log.d("MyObserver", "activityStop")
      }
  }
  ```

  - ON_CREATE、ON_START、ON_RESUME、ON_PAUSE、ON_STOP和ON_DESTROY分别匹配Activity中相应的⽣命周期回调；另外还有⼀种ON_ANY类型，表⽰可以匹配Activity的任何⽣命周期回调

- 在activity中绑定`lifecycle.addObserver(MyObserver())`

#### LiveData

- `implementation "androidx.lifecycle:lifecycle-livedata-ktx:2.2.0"`

- ⼀种响应式编程组件，在数据发⽣变化的时候通知给观察者

- ```kotlin
  class MainViewModel(countReserved: Int) : ViewModel() {
      val counter = MutableLiveData<Int>()
      //指定它的泛型为Int
      init {
          counter.value = countReserved
      }
      fun plusOne() {
          val count = counter.value ?: 0
          counter.value = count + 1
      }
      fun clear() {
          counter.value = 0
      }
  }
  
  class MainActivity : AppCompatActivity() {
      ...
      override fun onCreate(savedInstanceState: Bundle?) {
          ...
          plusOneBtn.setOnClickListener {
              viewModel.plusOne()
          }
          clearBtn.setOnClickListener {
              viewModel.clear()
          }
          //发生变化时自动进行回调
          viewModel.counter.observe(this) { count ->infoText.text = count.toString()
  }
                                                   })
      }
      override fun onPause() {
          super.onPause()
          sp.edit {
              putInt("count_reserved", viewModel.counter.value ?: 0)
          }
      }
  }
  ```

- 读写数据⽅法

  - `getValue()`⽅法⽤于获取LiveData中包含的数据
  - `setValue()`⽅法⽤于给LiveData设置数据，但是只能在主线程中调⽤
  - `postValue()`⽅法⽤于在⾮主线程中给LiveData设置数据

#### WorkManager

- 在没有被销毁的情况下是⼀直保持在后台运⾏，可以保证即使在应⽤退出甚⾄⼿机重启的情况下，之前注册的任务仍然将会得到执⾏

- 引入`implementation "androidx.work:work-runtime:2.2.0"`

- 定义⼀个后台任务，并实现具体的任务逻辑

  - ```kotlin
    class SimpleWorker(context: Context, params: WorkerParameters) :Worker(context, params) {
        override fun doWork(): Result {
            Log.d("SimpleWorker", "do work in SimpleWorker")
            return Result.success()
        }
    }

  - doWork()⽅法要求返回⼀个Result对象，⽤于表⽰任务的运⾏结果，成功就返回Result.success()，失败就返回Result.failure()

- 配置该后台任务的运⾏条件和约束信息，并构建后台任务请求

  - 单次运行的后台任务

  - ```kotlin
    val request = OneTimeWorkRequest.Builder(SimpleWorker::class.java).build()
    ```

  - 周期运行的后台任务（周期大于等于15分钟）

  - ```kotlin
    val request = PeriodicWorkRequest.Builder(SimpleWorker::class.java,15, TimeUnit.MINUTES).build()
    ```

- 将该后台任务请求传⼊WorkManager的enqueue()⽅法中，系统会在合适的时间运⾏

  - `WorkManager.getInstance(context).enqueue(request)`

  - 链式执行多个后台任务

    - ```kotlin
      WorkManager.getInstance(this)
      .beginWith(sync)
      .then(compress)
      .then(upload)
      .enqueue()
      ```

    - 

- 指定延迟的任务

  - ```kotlin
    val request = OneTimeWorkRequest.Builder(SimpleWorker::class.java)
    .setInitialDelay(5, TimeUnit.MINUTES)
    .addTag("simple")//添加标签方便管理
    .build()
    ```

- 取消任务

  - 通过标签进行`WorkManager.getInstance(this).cancelAllWorkByTag("simple")`
  - 通过id进行`WorkManager.getInstance(this).cancelWorkById(request.id)`
  - 全部取消`WorkManager.getInstance(this).cancelAllWork()`

- 失败重试

  - 返回Result.retry()
  - 指定间隔重试`.setBackoffCriteria(BackoffPolicy.LINEAR, 10, TimeUnit.SECONDS)`

- 结果监听

  - ```kotlin
    WorkManager.getInstance(this)
    .getWorkInfoByIdLiveData(request.id)
    .observe(this) { workInfo ->
                    if (workInfo.state == WorkInfo.State.SUCCEEDED) {
                        Log.d("MainActivity", "do work succeeded")
                    } else if (workInfo.state == WorkInfo.State.FAILED) {
                        Log.d("MainActivity", "do work failed")
                    }
                   }
    ```

### 深色模式

#### 自动化实现

- 使用`android:forceDarkAllowed`，Android 10.0系统开始才有的

- 差异化配置创建⼀个values-v29⽬录，然后右击values-v29⽬录→New→Values resource file，创建⼀个styles.xml⽂件。

  - ```xml
    <resources>
        <style name="AppTheme"
               parent="Theme.AppCompat.Light.NoActionBar">
            <item name="colorPrimary">@color/colorPrimary</item>
            <item
                  name="colorPrimaryDark">@color/colorPrimaryDark</item>
            <item name="colorAccent">@color/colorAccent</item>
            <item name="android:forceDarkAllowed">true</item>
        </style>
    </resources>
    ```

#### 手动配置

- 通过AppCompat库内置的不同主题（系统色）

- 直接在values/styles.xml

  - ```kotlin
    <resources>
    <!-- Base application theme. -->
    <style name="AppTheme" parent="Theme.AppCompat.DayNight.NoActionBar">
    <!-- Customize your theme here. -->
    <item name="colorPrimary">@color/colorPrimary</item>
    <item name="colorPrimaryDark">@color/colorPrimaryDark</item>
    <item name="colorAccent">@color/colorAccent</item>
    </style>
    ...
    </resources>
    ```

- 对于自定义颜色，在`values-night/colors.xml`及`values-light`中分别设置

### 工具

#### 调试

- 重写日志打印，方便 通过全局变量level对日志 是否进行打印进行管理

  - ```kotlin
    object LogUtil {
        private const val VERBOSE = 1
        private const val DEBUG = 2
        private const val INFO = 3
        private const val WARN = 4
        private const val ERROR = 5
        private var level = VERBOSE
        fun v(tag: String, msg: String) {
            if (level <= VERBOSE) {
                Log.v(tag, msg)
            }
        }
        fun d(tag: String, msg: String) {
            if (level <= DEBUG) {
                Log.d(tag, msg)
            }
        }
        fun i(tag: String, msg: String) {
            if (level <= INFO) {
                Log.i(tag, msg)
            }
        }
        fun w(tag: String, msg: String) {
            if (level <= WARN) {
                Log.w(tag, msg)
            }
        }
        fun e(tag: String, msg: String) {
            if (level <= ERROR) {
                Log.e(tag, msg)
            }
        }
    }
    ```

  - 

### 补充
