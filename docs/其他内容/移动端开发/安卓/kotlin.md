## 语法基础

- 注释
  - `//`
  - `/**/`
  
- 类型别名

  - ```kotlin
    typealias NodeSet = Set<Network.Node>
    
    typealias FileTable<K> = MutableMap<K, MutableList<File>>
    ```

### 包与导入

- 包声明`package org.example`（用于制作可以被引入的包）
- 导入包的具体内容（函数）`import org.example.Message`
  - 别名设置`import org.test.Message as TestMessage`
- 导入全部内容`import org.example.*`

### 变量

- 定量`val`只赋值一次，变量`val`
- `:Int`显示声明类型
- 在类型后面添加`?`表示可以为空(null)
  - `: Int?`

#### 数据类型

- 非空断言`!!`类型后面添加，表示告诉编译器保证这个变量不会为空（如果为空则会抛出异常）

- Kotlin 中的数字没有隐式拓宽转换（即如果参数类型指定为double则不会接受float）

  - 显示类型转化

    - ```kotlin
      toByte(): Byte
      toShort(): Short
      toInt(): Int
      toLong(): Long
      toFloat(): Float
      toDouble(): Double
      ```

- 整数
  - 当初始化一个没有显式指定类型的变量时，编译器会自动推断为足以表示该值的最小类型。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230715103619088.png" alt="image-20230715103619088" style="zoom:33%;" />
    - 末尾标记L表示Long

- 浮点数

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230715103832255.png" alt="image-20230715103832255" style="zoom:33%;" />
    - 末尾标记f表示float

- Boolean

- Char

  - 字符转数字`digitToInt()`
  - `''`

- String

  - `""`

  - 字符串是**不可变**的。 一旦初始化了一个字符串，就不能改变它的值或者给它赋新值。 所有转换字符串的操作都以一个新的 `String` 对象来返回结果，而保持原始字符串不变

  - 原始字符串：内部没有转义并且可以包含换行以及任何其他字符

    - ```kotlin
      val text = """
          for (c in "foo")
              print(c)
      """
      ```

    - 去掉原始字符串中的前导空格(每行以`|`开始)

    - ```kotlin
      val text = """
      |Tell me and I forget.
      |Teach me and I remember.
      |Involve me and I learn.
      |(Benjamin Franklin)
          """.trimMargin()
      ```

- list

  - 只读list`val list = listOf("a", "b", "c")`
  - 初始化
    -  `arrayOf(1, 2, 3)` 
    -  `arrayOfNulls()` 可以用于创建一个指定大小的、所有元素都为空的数组。
    - `val asc = Array(5) { i -> (i * i).toString() }`

- map

  - 遍历

    - ```kotlin
      for ((k, v) in map) {
          println("$k -> $v")
      }
      ```

  - 只读map`val map = mapOf("a" to 1, "b" to 2, "c" to 3)`

#### 类型检测

- is

  - `is` 操作符检测一个表达式是否某类型的一个实例。 如果一个不可变的局部变量或属性已经判断出为某类型，那么检测后的分支中可以直接当作该类型使用，无需显式转换：

    - ```kotlin
      fun getStringLength(obj: Any): Int? {
          if (obj is String) {
              // `obj` 在该条件分支内自动转换成 `String`
              return obj.length
          }
      
          // 在离开类型检测分支后，`obj` 仍然是 `Any` 类型
          return null
      }
      ```

- 通常，如果转换是不可能的，转换操作符会抛出一个异常。因此，称为*不安全的*。 Kotlin 中的不安全转换使用中缀操作符 `as`。

  ```kotlin
  val x: String = y as String
  ```

- 为了避免异常，可以使用*安全*转换操作符 `as?`，它可以在失败时返回 `null`：

  ```kotlin
  val x: String? = y as? String
  ```

#### 运算

- `shl(bits)` – 有符号左移
- `shr(bits)` – 有符号右移
- `ushr(bits)` – 无符号右移
- `and(bits)` – 位**与**
- `or(bits)` – 位**或**
- `xor(bits)` – 位**异或**
- `inv()` – 位非
- Kotlin 中没有基础数据类型，只有封装的数字类型，你每定义的一个变量，其实 Kotlin 帮你封装了一个对象，这样可以保证不会出现空指针。数字类型也一样，所以在比较两个数字的时候，就有比较数据大小和比较两个对象是否相同的区别了。在 Kotlin 中，三个等号 === 表示比较**对象地址**，两个 == 表示比较两个**值大小**。

### 输入输出 

- 输出

  - `print()`

  - `println()`输出并自动换行

  - 字符串内插，使用 `$`加变量名`println("Name $name")`


- 输入
  - 


### 流程控制

- 条件

  - 如果不为空就获取属性继续执行语句`println(files?.size) `

  - if-not-null-else 缩写`println(files?.size ?: "empty") // 如果 files 为 null，那么输出“empty”`

  - if-null`xx ?: xx`

  - if语句具有返回值功能

    - ```kotlin
      return if(x>y){
          x
      } else {
          y
      }
      
      ans  = if(x>y){
          x
      } else {
          y
      }
      ```

- when

  - 分支，与switch类似

  - ```kotlin
    when (x) {
        1 -> print("x == 1")
        2 -> print("x == 2")
        else -> {
            print("x is neither 1 nor 2")
        }
    }
    ```

  - 可以用任意表达式（而不只是常量）作为分支条件

    - ```kotlin
      when (x) {
          in 1..10 -> print("x is in the range")
          in validNumbers -> print("x is valid")
          !in 10..20 -> print("x is outside the range")
          else -> print("none of the above")
      }
      ```

- for

  - 范围for循环使用in（默认只遍历值）‘

  - 以下标遍历

    - ```kotlin
      for (i in array.indices) {
              println(array[i])
          }
      ```

  - ```kotlin
    for ((index, value) in array.withIndex()) {
            println("the element at $index is $value")
        }
    ```

- range

  - 判断是否在区间内`if(x in 1..y+1)`
  - 也可以用于for区间迭代
    - `for (x in 1..10 step 2)`
    - `x in 9 downTo 0 step 3`
  - 区间类型
    - 闭区间`1..100`
    - 半开区间（不含 右边界）`1 until 100`
    - 倒序`downTo`
    - 另一种写法`(1..10).forEach{}`

- repeat
  - `repeat(n){}`将函数体重复执行n次

#### 返回与跳转

- 使用标签对指定的流程进行控制

  - ```kotlin
    loop@ for (i in 1..100) {
        for (j in 1..100) {
            if (……) break@loop
        }
    }
    ```

  - ```kotlin
    fun foo() {
        listOf(1, 2, 3, 4, 5).forEach {
            if (it == 3) return@forEach // 局部返回到该 lambda 表达式的调用者——forEach 循环（而不是foo函数）
            print(it)
        }
        print(" done with implicit label")
    }
    ```

### 函数

- 无返回值的返回类型为`Unit`

- `fun`声明函数

- 函数参数与返回值的类型声明

  - ```kotlin
    fun sum(a: Int, b: Int): Int {
        return a + b
    }
    ```

- 单表达式函数`fun double(x: Int): Int = x * 2`

- 可变数目传参`varargs`，以list接受

  - ```kotlin
    fun greet(vararg names: String) {
        for (name in names) {
            println("Hello, $name!")
        }
    }
    
    fun main() {
        greet("Alice", "Bob", "Charlie")
        greet("John")
        greet() // 也可以传递零个参数
    }
    ```

- 中缀表示法

  - ```kotlin
    infix fun Int.shl(x: Int): Int { …… }
    
    // 用中缀表示法调用该函数
    1 shl 2
    
    // 等同于这样
    1.shl(2)
    ```

#### 高阶函数

- 高阶函数是将函数用作参数或返回值的函数或将函数作为参数。

  - ```kotlin
    fun calculate(x: Int, y: Int, operation: (Int, Int) -> Int): Int {
        return operation(x, y)
    }
    ```

  - ```kotlin
    fun operation(): (Int) -> Int {
        return { x -> x * x }
    }
    ```

- 将函数作为参数传入要使用引用的形式`::函数名`

- 如果函数的最后一个参数是函数，那么可以将该函数提出来写在函数括号外面，这就是所谓的"尾随闭包"语法

  - ```kotlin
    val result1 = num1AndNum2(num1, num2) { n1, n2 ->
        n1 + n2
    }
    
    val result1 = num1AndNum2(num1, num2, { n1, n2 ->
        n1 + n2
    })
    ```

- 函数类型`func: (String, Int) -> Unit`

  - 完整格式还需要指出函数的所属的类`(block: StringBuilder.() -> Unit`

  - 这样在函数内会自动拥有指定类的上下文(apply的实现原理)

  - ```kotlin
    fun StringBuilder.build(block: StringBuilder.() -> Unit): StringBuilder
    {
        block()
        return this
    }
    
    fun main() {
        val list = listOf("Apple", "Banana", "Orange", "Pear", "Grape")
        val result = StringBuilder().build {
            append("Start eating fruits.\n")
            for (fruit in list) {
                append(fruit).append("\n")
            }
            append("Ate all fruits.")
        }
        println(result.toString())
    }
    ```

#### 内联函数

- 提高高阶函数的运行效率，在fun前面加上inline

- 使用noinline声明部分函数不内联`inline fun inlineTest(block1: () -> Unit, noinline block2: () -> Unit)`

- 因为内联的函数类型参数在编译的时候会被进⾏代码替换，因此它没有真正的参数属性。**⾮内联的函数**类型参数可以⾃由地传递给**其他任何函数**，因为它就是⼀个真实的参数，⽽**内联的函数类型参数**只允许传递给**另外⼀个内联函数**

  - ```kotlin
    inline fun foo(bar: () -> Unit, noinline baz: () -> Unit) {
        bar()
        someOtherFunction(baz)
    }
    
    fun someOtherFunction(baz: () -> Unit) {
        baz()
    
    ```

- `crossinline` 关键字用于防止在内联函数中直接使用 `return` 语句来返回

  - ```kotlin
    inline fun runOnNewThread(crossinline block: () -> Unit) {
        Thread { block() }.start()
    }
    
    fun main() {
        runOnNewThread {
            println("I am in a new thread")
            // Error: 'return' is not allowed here
            // return
        }
        println("I am in the main thread")
    }
    ```

#### 匿名函数

- 省略了函数名称

  - ```kotlin
    fun(x: Int, y: Int): Int {
        return x + y
    }
    ```

#### 顶层函数

- 在任意包名路径下创建文件
- 直接在文件中写函数
- 在Kotlin代码中调⽤，所有的顶层⽅法都可以在任何位置被直接调⽤，不⽤管包名路径，也不⽤创建实例 

#### lambda表达式

- lambda 表达式与匿名函数是*函数字面值*，函数字面值即没有声明而是立即做为表达式传递的函数。

- `val sum: (Int, Int) -> Int = { x: Int, y: Int -> x + y }`

  - `{参数名1: 参数类型, 参数名2: 参数类型 -> 函数体}`
  - 完整语法形式的参数声明放在花括号内，并有可选的类型标注。
  - 函数体跟在一个 `->` 之后。
  - 如果推断出的该 lambda 的返回类型不是 `Unit`，那么该 lambda 主体中的最后一个（或可能是单个）表达式会视为返回值。
  - `val sum = { x: Int, y: Int -> x + y }`lambda相当于一种”代码“类型的变量

- 可以使用限定的返回语法从 lambda 显式返回一个值。 否则，将隐式返回最后一个表达式的值。

  因此，以下两个片段是等价的：

  ```kotlin
  ints.filter {
      val shouldFilter = it > 0
      shouldFilter
  }
  
  ints.filter {
      val shouldFilter = it > 0
      return@filter shouldFilter
  }
  ```

  - 当Lambda表达式的参数列表中**只有⼀个参数**时，也不必声明参数名，⽽是可以使⽤it关键字来代替
  
- 引用普通函数作为lambda表达式`::函数名`

- lambda中不允许直接使用return函数

  - ```
    list.forEach { 
        if (it == 0) return@forEach 
        //... 
    }
    ```

  - 要使用带标签的版本，避免非局部返回


### 类与对象

#### this

- 在[类](https://book.kotlincn.net/text/classes.html#继承)的成员中，`this` 指的是该类的当前对象。
- 在扩展函数或者带有接收者的函数字面值中， `this` 表示在点左侧传递的 *接收者* 参数
- 要访问来自外部作用域的 `this`，用`this@label`

#### 成员可见性

- `private` 意味着只该成员在这个**类内部**（包含其所有成员）可见；
- `protected` 意味着该成员具有与 `private` 一样的可见性，但也在子类中可见。
- `internal` 意味着能见到类声明的*本**模块**内*的任何客户端都可见其 `internal` 成员。
- `public` 意味着能见到类声明的任何客户端都可见其 `public` 成员。

#### 构造函数

- 默认构造函数(主构造函数)会对类参数自动构造

  - 主构造函数用于初始化类，它在**类标题**中声明。

  - ```kotlin
    class Rectangle(var height: Double, var length: Double) {
        var perimeter = (height + length) * 2 
    }
    ```

  - 如果要私有化构造函数，则constructor不可以省略

    - ```kotlin
      class Person private constructor(name:String,age:Int){
           val name:String
           val age:Int
          init {
              this.name = name
              this.age = age
          }
      }
      
      class Person private constructor(name:String,age:Int){
           val name:String = name
           val age:Int = age
      }
      
      class Person private constructor(val name:String,val age:Int){
          
      }
      ```

  - 主构造函数不能包含任何的代码。初始化的代码可以放到以 `init` 关键字作为前缀的初始化块中，初始化块按照它们出现在类体中的顺序执行。

    - ```kotlin
      class InitOrderDemo(name: String) {
          val firstProperty = "First property: $name".also(::println)
      
          init {
              println("First initializer block that prints $name")
          }
      
          val secondProperty = "Second property: ${name.length}".also(::println)
      
          init {
              println("Second initializer block that prints ${name.length}")
          }
      }
      ```
  
- 次级构造函数（可以有多个）

  - 如果类有一个主构造函数，每个次构造函数需要**委托给主构造函数**， 可以直接委托或者通过别的次构造函数间接委托。委托到同一个类的另一个构造函数用 `this` 关键字即可：

  - ```kotlin
    class Person (name:String){
    
        constructor(name:String,age:Int):this(name){
            
        }
        constructor(name: String,age: Int,sex:String):this(name,age){
            
        }
    }
    ```
  
  - 用于提供多种不同的类初始化方法
  
- 如果一个类没有主构造函数，那么在继承时不需要添加括号，次构造函数通过super间接调用父类的构造函数

- 自定义get&set方法

  - ```kotlin
    class Person {
    
        var lastName: String = "zhang"
            get() = field.toUpperCase()   // 将变量赋值后转换为大写
            set
    
        var no: Int = 100
            get() = field                // 后端变量
            set(value) {
                if (value < 10) {       // 如果传入的值小于 10 返回该值
                    field = value
                } else {
                    field = -1         // 如果传入的值大于等于 10 返回 -1
                }
            }
    
        var heiht: Float = 145.4f
            private set
    }
    ```

  - 在 Kotlin 中，属性默认情况下有一个自动生成的 backing field。当你声明一个属性时，Kotlin 会在幕后自动为该属性创建一个字段，用于存储属性的实际值。可以通过 `field` 关键字在自定义的 getter 和 setter 方法中访问这个 backing field。



#### 静态方法

- 不需要创建实例就能调⽤的⽅法

- 更推荐使用单例类来实现

  - ```kotlin
    object Util {
        fun doAction() {
            println("do action")
        }
    }
    ```

- 只希望将部分方法定义为静态

  - ```kotlin
    class Util {
        fun doAction1() {
            println("do action1")
        }
        companion object {
            fun doAction2() {
                println("do action2")
            }
        }
    }
    ```

  - 在类中定义一个伴生对象，然后在该对象中定义函数。

#### 接口

- 设定接口，规定使用接口的类应该完成的功能

  - ```kotlin
    interface MyInterface {
        fun bar()
        fun foo() {
          // 可选的方法体
        }
    }
    ```

- 一个类只能继承一个父类，但是可以实现多个接口

- 继承接口不需要添加括号（不调用父类的构造函数）

- 子类中使用override来重写接口中的函数

- 在接口中可以为函数提供默认实现

- 接口中的属性只能是抽象的，不允许初始化值，接口不会保存属性值，实现接口时，必须重写属性：

#### 继承

- 继承

  - `open`表示类可以被继承

  - ```kotlin
    open class Shape
    
    class Rectangle(var height: Double, var length: Double): Shape() {
        var perimeter = (height + length) * 2 
    }
    ```

  - ` Shape()`表示调用shape的无参构造函数

    - 如果要调用有参构造函数则要传入参数，注意一定要与父类的主构造函数一致
    
  - 如果子类有主构造函数， 则基类必须在主构造函数中立即初始化。

    - ```kotlin
      open class Person(var name : String, var age : Int){// 基类
      
      }
      
      class Student(name : String, age : Int, var no : String, var score : Int) : Person(name, age) {
      
      }
      
      ```

  - 如果子类没有主构造函数，则必须在**每一个**二级构造函数中用 super 关键字初始化基类，或者在代理另一个构造函数。初始化基类时，可以调用基类的不同构造方法。（如果父类有一个带参数的主构造函数，那么子类必须明确传递参数到它，子类都必须确保父类的构造函数被调用）

    - ```kotlin
      class Student : Person {
      
          constructor(ctx: Context) : super(ctx) {
          } 
      
          constructor(ctx: Context, attrs: AttributeSet) : super(ctx,attrs) {
          }
      }
      ```

- 使用super访问基类

  - 多继承时要指出具体使用的是哪一个

  - ```kotlin
    class C() : A() , B{
        override fun f() {
            super<A>.f()//调用 A.f()
            super<B>.f()//调用 B.f()
        }
    }
    ```

- 只有声明为open的属性和方法才可以被重写

- 抽象类与实例化

  - override本身也是开放的，如果不想被再次覆盖则需要使用final进行覆盖

  - ```kotlin
    abstract class MyAbstractClass {
        abstract fun doSomething()
        abstract fun sleep()
    }
    
    fun main() {
        val myObject = object : MyAbstractClass() {
            override fun doSomething() {
                // ……
            }
    
            override fun sleep() { // ……
            }
        }
        myObject.doSomething()
    }
    ```

- 如果派生类有一个主构造函数，其基类可以（并且必须）根据其参数在该主构造函数中初始化。如果派生类没有主构造函数，那么每个次构造函数必须使用`super` 关键字初始化其基类型，或委托给另一个做到这点的构造函数。 请注意，在这种情况下，不同的次构造函数可以调用基类型的不同的构造函数：

  ```kotlin
  class MyView : View {
      constructor(ctx: Context) : super(ctx)
  
      constructor(ctx: Context, attrs: AttributeSet) : super(ctx, attrs)
  }
  ```

#### 实例化

- 直接调用构造函数`val customer = Customer("Joe Smith")`

#### 扩展

- 类或接口扩展新功能而无需继承该类（为类新增加成员）

	- ```kotlin
  fun MutableList<Int>.swap(index1: Int, index2: Int) {
      val tmp = this[index1] // “this”对应该列表
      this[index1] = this[index2]
      this[index2] = tmp
  }
  
- 给String类添加新功能

  - ```kotlin
    fun String.lettersCount(): Int {
        var count = 0
        for (char in this) {
            if (char.isLetter()) {
                count++
            }
        }
        return count
    }
    ```

- 扩展**不能真正的修改**他们所扩展的类。通过定义一个扩展，并没有在一个类中插入新成员， 只不过是可以通过该类型的变量用点表达式去调用这个新函数。

- 也可以针对对象使用（可空接收者）

  - ```kotlin
    fun Any?.toString(): String {
        if (this == null) return "null"
        // 空检测之后，“this”会自动转换为非空类型，所以下面的 toString()
        // 解析为 Any 类的成员函数
        return toString()
    }
    ```

- 扩展属性 

  - ```
    val <T> List<T>.lastIndex: Int
        get() = size - 1
       
    var StringBuilder.lastChar: Char
        get() = get(length - 1)
        set(value) = setCharAt(length - 1, value)
    ```
    
  - 扩展属性只能被声明为 val。
  - 初始化属性因为属性没有后端字段（backing field），所以不允许被初始化，只能由**显式提供的 getter/setter 定义**。

- 要使用所定义包之外的一个扩展, 通过import导入扩展的函数名进行使用:

#### 密封类

- ```kotlin
  sealed class Result
  class Success(val msg: String) : Result()
  class Failure(val error: Exception) : Result()
  
  fun getResultMsg(result: Result) = when (result) {
      is Success -> result.msg
      is Failure -> "Error is ${result.error.message}"
  }
  ```

- 不再需要else处理而外的情况（即使根本不可能存在），Kotlin编译器会⾃动检查该密封类有哪些⼦类，并强制要求你将每⼀个⼦类所对应的条件全部处理。

#### 单例类

- 只能创建单个对象，保证全局只会存在⼀个实例。
- 只需要将class关键字改成object关键字即可

#### 数据类

- 仅用于存储数据的类（结构体）
  - `data class User(val name: String, val age: Int)`
- 编译器自动从主构造函数中声明的所有属性导出以下成员：
  - `equals()`/`hashCode()` 对
  - `toString()` 格式是 `"User(name=John, age=42)"`
  - `componentN()` 函数按声明顺序对应于所有属性。
  - `copy()` 函数

#### 枚举类

- 枚举类可以定义属性和方法。每个枚举常量都可以访问这些属性和方法

  - ```kotlin
    enum class Direction(val degrees: Int) {
        NORTH(0),
        EAST(90),
        SOUTH(180),
        WEST(270);
    
        fun getDescription(): String {
            return when (this) {
                NORTH -> "North"
                EAST -> "East"
                SOUTH -> "South"
                WEST -> "West"
            }
        }
    }
    
    val direction: Direction = Direction.NORTH
    println(direction.degrees) // 输出: 0
    println(direction.getDescription()) // 输出: North
    ```

- Kotlin 中的枚举类具有合成方法，允许遍历定义的枚举常量，并通过其名称获取枚举常数。

  ```
  EnumClass.valueOf(value: String): EnumClass  // 转换指定 name 为枚举值，若未匹配成功，会抛出IllegalArgumentException
  EnumClass.values(): Array<EnumClass>        // 以数组的形式，返回枚举值
  ```

#### 内部类

- 使用inner标识
- 可以通过this@name访问外部类

#### 对象表达式（匿名对象）

- 允许在不创建命名类的情况下定义一个类的实例并执行其成员函数。对象表达式通常用于创建临时的、只在特定作用域内有效的对象。

- ```kotlin
  fun main() {
      val person = object {
          val name = "John"
          val age = 30
  
          fun sayHello() {
              println("Hello, my name is $name and I'm $age years old.")
          }
      }
  
      person.sayHello()
  }
  ```

- 对象可以继承于某个基类，或者实现其他接口

- 匿名对象可以用作只在本地和私有作用域中声明的类型。如果你使用匿名对象作为公有函数的 返回类型或者用作公有属性的类型，那么该函数或属性的实际类型 会是匿名对象声明的超类型，如果你没有声明任何超类型，就会是 Any。在匿名对象 中添加的成员将无法访问。

#### 伴生对象

- 类内部的对象声明可以用 companion 关键字标记，这样它就与外部类关联在一起，我们就可以直接通过外部类访问到对象的内部元素。

  - ```kotlin
    class MyClass {
        companion object Factory {
            fun create(): MyClass = MyClass()
        }
    }
    
    val instance = MyClass.create()   // 访问到对象的内部元素
    ```

- 通常来说伴生对象不需要命名，用于实现静态方法/属性

#### 委托

- `by`关键字

- 将其成员委托给指定对象来实现一个接口 `Base`：

  - 通过类委托，类可以将接口的实现责任交给委托对象，从而避免了多重继承的复杂性

  - ```kotlin
    interface Base {
        fun printMessage()
        fun printMessageLine()
    }
    
    class BaseImpl(val x: Int) : Base {
        override fun printMessage() { print(x) }
        override fun printMessageLine() { println(x) }
    }
    
    class Derived(b: Base) : Base by b {
        override fun printMessage() { print("abc") }
    }
    
    fun main() {
        val b = BaseImpl(10)
        Derived(b).printMessage()
        Derived(b).printMessageLine()
    }
    ```
  
- 属性委托：属性委托允许将属性的访问和修改委托给另一个对象。通过属性委托，可以自定义属性的读取和写入逻辑，以及实现属性的惰性初始化、属性值的缓存等。

  - ```kotlin
    class Example {
        var p: String by Delegate()
    }
    ```

  - 当调⽤p属性的时候会⾃动调⽤Delegate类的getValue()⽅法，当给p属性赋值的时候会⾃动调⽤Delegate类的setValue()⽅法。

  - ```kotlin
    class Delegate {
        var propValue: Any? = null
        operator fun getValue(myClass: MyClass, prop: KProperty<*>):Any? {
            return propValue
        }
        operator fun setValue(myClass: MyClass, prop: KProperty<*>, value: Any?) {
            propValue = value
        }
    }
    ```

  - 第⼀个参数⽤于声明该Delegate类的委托功能可以在什么类中使⽤，这⾥写成MyClass表⽰仅可在MyClass类中使⽤；第⼆个参数KProperty<*>是Kotlin中的⼀个属性操作类，可⽤于获取各种属性相关的值，在当前场景下⽤不着，但是必须在⽅法参数上进⾏声明。

- 标准委托对象

  - `lazy { }`：实现惰性初始化，只有在**首次访问属性时才进行初始化**（执行指定的函数）。

    - ```kotlin
      class Example {
          val lazyProperty: String by lazy {
              println("Initializing lazy property.")//这行只会执行一次
              "Hello, World!"
          }
      }
      ```

  - `observable { }`：监听属性的变化，并在属性值改变时执行特定的操作。

    - 每当我们给属性赋值时会调用该处理程序（在赋值*后*执行）。它有三个参数：被赋值的属性、旧值与新值：

    - ```kotlin
      import kotlin.properties.Delegates
      
      class User {
          var name: String by Delegates.observable("<no name>") {
              prop, old, new ->
              println("$old -> $new")
          }
      }
      ```

  - `vetoable { }`：允许拦截属性的修改，决定是否接受新的属性值。
  
  - `Not Null`适用于那些无法在初始化阶段就确定属性值的场合。
  
    ```
    class Foo {
        var notNullBar: String by Delegates.notNull<String>()
    }
    
    foo.notNullBar = "bar"
    println(foo.notNullBar)
    ```
  
    需要注意，如果属性在赋值前就被访问的话则会抛出异常。
  

#### 操作符重载

- 在指定函数的前⾯加上operator关键字，实现运算符重载的功能

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230717205251654.png" alt="image-20230717205251654" style="zoom:33%;" />

- 结合扩展函数

  - ```kotlin
    operator fun String.times(n: Int): String {
        val builder = StringBuilder()
        repeat(n) {
            builder.append(this)
        }
        return builder.toString()
    }                                    
    ```

- 

### 异常处理

- 抛出异常

  - `  throw Exception("Hi There!")`

- 捕获异常

  - ```kotlin
    try {
        // 一些代码
    } catch (e: SomeException(异常类型)) {
        // 处理程序
    } finally {
        // 可选的 finally 块
    }
    ```

## 进阶语法

- 过滤器
  - `val positives = list.filter { it > 0 }`
  
- `set变量名`与`get变量名`

  - ```kotlin
    public class Book {
    	private int pages;
    		public int getPages() {
    			return pages;
    			}
    		public void setPages(int pages) {
    		this.pages = pages;
    	}
    }
    ```

  - 快捷使用

    - ```kotlin
      val book = Book()
      book.pages = 500
      val bookPages = book.pages
      ```

- 

### 作用域函数

- Kotlin 标准库包含几个函数，它们的唯一目的是在对象的上下文中执行代码块。 当对一个对象调用这样的函数并提供一个 [lambda 表达式](https://book.kotlincn.net/text/lambdas.html)时，它会形成一个临时作用域。在此作用域中，可以访问该对象而无需其名称。这些函数称为*作用域函数*。 共有以下五种：[`let`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/let.html)、 [`run`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/run.html)、 [`with`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/with.html)、 [`apply`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/apply.html)、 以及 [`also`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/also.html)。

- | 函数                                                         | 对象引用 | 返回值            | 是否是扩展函数             |
  | ------------------------------------------------------------ | -------- | ----------------- | -------------------------- |
  | [`let`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/let.html) | `it`     | Lambda 表达式结果 | 是                         |
  | [`run`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/run.html) | `this`   | Lambda 表达式结果 | 是                         |
  | [`run`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/run.html) | -        | Lambda 表达式结果 | 不是：调用无需上下文对象   |
  | [`with`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/with.html) | `this`   | Lambda 表达式结果 | 不是：把上下文对象当做参数 |
  | [`apply`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/apply.html) | `this`   | 上下文对象        | 是                         |
  | [`also`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/also.html) | `it`     | 上下文对象        | 是                         |

- 以下是根据预期目的选择作用域函数的简短指南：

  - 对一个非空（non-null）对象执行 lambda 表达式：`let`
  - 将表达式作为变量引入为局部作用域中：`let`
  - 对象配置：`apply`
  - 对象配置并且计算结果：`run`
  - 在需要表达式的地方运行语句：非扩展的 `run`
  - 附加效果：`also`
  - 一个对象的一组函数调用：`with`

- let一次判断非空执行多个函数

  - ```kotlin
    fun doStudy(study: Study?) {
    	study?.let {
    		it.readBooks()
    		it.doHomework()
    	}
    }
    ```

  - 使用let即使study是全局变量，也能保证正确运行（这种情况下使用if判断 是否为空是无效的）
  
- with

  - with函数接收两个参数：第⼀个参数可以是⼀个任意类型的对象，第⼆个参数是⼀个Lambda表达式。with函数会在Lambda表达式中提供第⼀个参数对象的**上下⽂**，并使⽤Lambda表达式中的最后⼀⾏代码作为返回值返回

  - 例子

    - ```kotlin
      val list = listOf("Apple", "Banana", "Orange", "Pear", "Grape")
      val builder = StringBuilder()
      builder.append("Start eating fruits.\n")
      for (fruit in list) {
          builder.append(fruit).append("\n")
      }
      builder.append("Ate all fruits.")
      val result = builder.toString()
      println(result)
      ```

    - ```kotlin
      val list = listOf("Apple", "Banana", "Orange", "Pear", "Grape")
      val result = with(StringBuilder()) {
          append("Start eating fruits.\n")
          for (fruit in list) {
              append(fruit).append("\n")
          }
          append("Ate all fruits.")
          toString()
      }
      println(result)
      ```

  - 

- run

  - run函数只接收⼀个Lambda参数，并且会在Lambda表达式中提供调⽤对象的上下⽂
  - 只是将with传入对象的方式变成了使用对象调用

- apply

  - apply函数和run函数也是极其类似的，都要在某个对象上调⽤，并且只接收⼀个Lambda参数，也会在Lambda表达式中提供调⽤对象的上下⽂，但是apply函数⽆法指定返回值，⽽是会⾃动返回调⽤对象本⾝。
  
  - ```kotlin
    data class Person(var name: String, var age: Int)
    
    val person = Person("", 0).apply {
        name = "John"
        age = 30
    }
    
    ```

### 延迟初始化

- 由于全局变量的存在，有时即使保证在初始化之前不会被使用，应然需要进行判空处理，从而避免编译器报错
- 延迟初始化使⽤的是lateinit关键字，它可以告诉Kotlin编译器，我会在晚些时候对这个变量进⾏初始化，这样就不⽤在⼀开始的时候将它赋值为null了
  - `private lateinit var x: MsgAdapter`
- 可以使用`::x.isInitialized`来判断变量是否已经初始化

### 泛型

- 泛型类

  - ```kotlin
    class MyClass<T> {
        fun method(param: T): T {
            return param
        }
    }
    
    val myClass = MyClass<Int>()
    val result = myClass.method(123)
    ```

- 泛型方法

  - ```kotlin
    class MyClass {
        fun <T> method(param: T): T {
            return param
        }
    }
    
    val myClass = MyClass()
    val result = myClass.method<Int>(123)
    ```

  - 实际上我们传⼊了⼀个Int类型的参数，它能够⾃动推导出泛型的类型就是Int型，因此这⾥也可以直接省略泛型的指定（`<Int>`）

- 对泛型类型进行限制

  - ```kotlin
    fun <T : Number> method(param: T): T {
        return param
    }
    ```

  - Number:Int、Float、Double

- 作用于函数原理

  - ```kotlin
    fun <T> T.build(block: T.() -> Unit): T {
        block()
        return this
    }
    ```
  
  - `block: T.() -> Unit`: 这是函数的参数，它是一个带有接收者的 lambda，其接收者是 `T` 类型。这意味着，在这个 lambda 中，你可以像操作 `T` 对象那样调用它的方法和属性，而**不需要任何额外的修饰符或引用**。

### infix函数

- A to B这样的写法，实际上等价于A.to(B)的写法
- `infix fun String.beginsWith(prefix: String) = startsWith(prefix)`
  - infix函数可以用特殊的格式进行调用`"Hello Kotlin" beginsWith "Hello"`，省略小数点以及括号
- infix函数是不能定义成顶层函数的，它必须是某个类的成员函数；infix函数必须接收且只能接收⼀个参数

### 协程

- 线程与进程：
  - **独立性**: 进程是完全独立的，而线程共享其所属进程的资源。
  - **通信**: 线程间通信比进程间通信更简单和快速。
  - **开销**: 线程通常比进程轻量，尤其在创建和终止时。
  - **影响范围**: 一个线程的崩溃可能会导致其所在进程的所有线程都崩溃，而一个进程的崩溃通常不会影响其他进程。
  - **使用场景**: 对于需要频繁通信或共享大量数据的任务，线程可能更合适；而对于需要隔离和独立执行的任务，进程可能更合适。

- 编程语⾔的层⾯，轻量级的线程，在单线程模式下模拟多线程编程的效果（挂起与恢复）

- 引入

  - ```kotlin
    implementation "org.jetbrains.kotlinx:kotlinx-coroutines-
    core:1.1.1"
    implementation "org.jetbrains.kotlinx:kotlinx-coroutines-
    android:1.1.1"
    ```

- 开启协程`GlobalScope.launch{...}`

  - Global.launch函数每次创建的都是⼀个顶层协程，这种协程当应⽤程序运⾏结束时也会跟着⼀起结束，可以阻塞主程序，防止过快关闭`Thread.sleep(1000)`

  - 改用`runBlocking{}`保证协程作用域内代码执行完毕之前不会关闭

    - 内部嵌套多个`launch {}`创建多个协程

    - 声明为挂起函数从而实现调用delay等函数

    - ```kotlin
      suspend fun printDot() {
          println(".")
          delay(1000)
      }
      ```

    - 获取协程作用域，继续嵌套

    - ```kotlin
      suspend fun printDot() = coroutineScope {
          launch {
              println(".")
              delay(1000)
          }
      }
      ```

- 取消协程

  - ```kotlin
    val job = GlobalScope.launch {
    // 处理具体的逻辑
    }
    job.cancel()
    ```

  - 手动传入便于分类管理

    - ```kotlin
      val job = Job()
      val scope = CoroutineScope(job)
      scope.launch {
      // 处理具体的逻辑
      }
      job.cancel()
      ```

- 数据返回

  - 使用async

    - ```kotlin
      fun main() {
          runBlocking {
              val result = async {
                  5 + 5
              }.await()
              println(result)
          }
      }
      ```

    - 当调⽤await()⽅法时，如果代码块中的代码还没执⾏完，那么await()⽅法会将当前协程阻塞住，直到可以获得async函数的执⾏结果(即如果有多个async则是串行关系)

  - 在获取结果时再调用await实现并行

    - ```kotlin
      fun main() {
          runBlocking {
              val start = System.currentTimeMillis()
              val deferred1 = async {
                  delay(1000)
                  5 + 5
              }
              val deferred2 = async {
                  delay(1000)
                  4 + 6
              }
              println("result is ${deferred1.await() + deferred2.await()}.")
              val end = System.currentTimeMillis()
              println("cost ${end - start} milliseconds.")
          }
      }
      ```

- 

## 标准库

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230716110602161.png" alt="image-20230716110602161" style="zoom:33%;" />

### 通用操作

#### 构造集合

- 创建集合的最常用方法是使用标准库函数 [`listOf()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/list-of.html)、 [`setOf()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/set-of.html)、 [`mutableListOf()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/mutable-list-of.html)、 [`mutableSetOf()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/mutable-set-of.html)。 

  - `val numbersMap = mapOf("key1" to 1, "key2" to 2, "key3" to 3, "key4" to 1)`

- 还有用于创建没有任何元素的集合的函数：[`emptyList()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/empty-list.html)、 [`emptySet()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/empty-set.html) 与 [`emptyMap()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/empty-map.html)。 创建空集合时，应指定集合将包含的元素类型。

  - `val empty = emptyList<String>()`

- 深拷贝

  - [`toList()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/to-list.html)、 [`toMutableList()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/to-mutable-list.html)、 [`toSet()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/to-set.html)

  - ```kotlin
        val sourceList = mutableListOf(alice, Person("Bob"))
        val copyList = sourceList.toList()
    ```

  - 直接使用`=`的拷贝为浅拷贝

#### 迭代器

- [`Iterable`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-iterable/index.html) 接口的继承者 （包括 `Set` 与 `List`）可以通过调用 [`iterator()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-iterable/iterator.html) 函数获得迭代器。

  - 一旦获得迭代器它就指向集合的第一个元素；调用 [`next()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-iterator/next.html) 函数将返回此元素，并将迭代器指向下一个元素

  - ```kotlin
    fun main() {
    //sampleStart
        val numbers = listOf("one", "two", "three", "four")
        val numbersIterator = numbers.iterator()
        while (numbersIterator.hasNext()) {
            println(numbersIterator.next())
        }
    //sampleEnd
    }
    ```

  - 也可以使用for/forEach循环进行遍历

  - 对于列表，有一个特殊的迭代器实现： [`ListIterator`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-list-iterator/index.html)。 它支持列表双向迭代：正向与反向。

    反向迭代由 [`hasPrevious()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-list-iterator/has-previous.html) 与 [`previous()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-list-iterator/previous.html) 函数实现。 此外， `ListIterator` 通过 [`nextIndex()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-list-iterator/next-index.html) 与 [`previousIndex()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-list-iterator/previous-index.html) 函数提供有关元素索引的信息。

- 为了迭代可变集合，于是有了 [`MutableIterator`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-mutable-iterator/index.html) 来扩展 `Iterator` 使其具有元素删除函数 [`remove()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-mutable-iterator/remove.html) 。 因此，可以在迭代时从集合中删除插入、修改元素。

  - remove、add、set

  - ```kotlin
    fun main() {
    //sampleStart
        val numbers = mutableListOf("one", "four", "four")
        val mutableListIterator = numbers.listIterator()
    
        mutableListIterator.next()
        mutableListIterator.add("two")
        mutableListIterator.next()
        mutableListIterator.set("three")
        println(numbers)
    //sampleEnd
    }
    ```

#### 公共操作

> 的操作将返回其结果，而不会影响原始集合，只读集合与可变集合通用

- 集合转换

  - 从集合映射到新集合当Lambda表达式的参数列表中只有⼀个参数时，也不必声明参数名，⽽是可以使⽤it关键字来代替
    
  - 
  
    - ```kotlin
      fun main() {
      //sampleStart
          val numbers = setOf(1, 2, 3)
          println(numbers.map { it * 3 })
          println(numbers.mapIndexed { idx, value -> value * idx })
      //sampleEnd
      }
      ```
  
  - *合拢* 转换是根据两个集合中具有相同位置的元素构建配对。 在 Kotlin 标准库中，这是通过 [`zip()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/zip.html) 扩展函数完成的。
  
    - ```kotlin
      val list1 = listOf("A", "B", "C")
      val list2 = listOf(1, 2, 3)
      val result = list1.zip(list2)
      
      // 输出结果：[(A, 1), (B, 2), (C, 3)]
      println(result)
      ```
  
  - 展平
  
    -  [`flatten()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/flatten.html)。 可以在一个集合的集合（例如，一个 `Set` 组成的 `List`）上调用它。 该函数返回嵌套集合中的所有元素的一个 `List`。
  
  - 转化为字符串
  
    - `joinToString()` 根据提供的参数从集合元素构建单个 `String`。 
      - 自定义间隔符、前后缀`println(numbers.joinToString(separator = " | ", prefix = "start: ", postfix = ": end"))`
    - `joinTo()` 执行相同的操作，但将结果附加到给定的 [`Appendable`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.text/-appendable/index.html) 对象。
  
- 集合过滤

  - 对于普通集合，使用it对元素操作` val numbers = listOf("one", "two", "three", "four")  `
    - 同时检查元素的下标` val filteredIdx = numbers.filterIndexed { index, s -> (index != 0) && (s.length < 5)  }`
  - 对于map，`val filteredMap = numbersMap.filter { (key, value) -> key.endsWith("1") && value > 10}`
  - 内置过滤器
    - `filterIsInstance<T>()`筛选特定类型的字符串
    - [`filterNotNull()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/filter-not-null.html) 返回所有的非空元素

- 集合检查

  - 如果至少有一个元素匹配给定谓词，那么 [`any()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/any.html) 返回 `true`。

  - 如果没有元素与给定谓词匹配，那么 [`none()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/none.html) 返回 `true`。

    - `any()` 和 `none()` 也可以不带谓词使用：在这种情况下它们只是用来检查集合是否为空。 如果集合中有元素，`any()` 返回 `true`，否则返回 `false`；`none()` 则相反。

  - 如果所有元素都匹配给定谓词，那么 [`all()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/all.html) 返回 `true`。 

  - ```kotlin
     println(numbers.any { it.endsWith("e") })
        println(numbers.none { it.endsWith("a") })
        println(numbers.all { it.endsWith("e") })
    ```

- `plus` 与 `minus` 操作符

  - `plus` 的结果包含原始集合 *和* 第二个操作数中的元素。
  - `minus` 的结果包含原始集合中的元素，但第二个操作数中的元素 *除外*。 如果第二个操作数是一个元素，那么 `minus` 移除其在原始集合中的 *第一次* 出现；如果是一个集合，那么移除其元素在原始集合中的 *所有* 出现。

- 分组

  - 集合划分（划分为2部分）` val (match, rest) = numbers.partition { it.length > 3 }`
  - 使用一个 lambda 函数并返回一个 `Map`此 Map 中，每个键都是 lambda 结果，而对应的值是返回此结果的元素 `List`
    - 如根据首字母进行分类` println(numbers.groupBy { it.first().uppercase() })`

- 取集合的一部分

  - [`slice()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/slice.html) 返回具有给定索引的集合元素列表。

    - ````kotlin
      fun main() {
      //sampleStart    
          val numbers = listOf("one", "two", "three", "four", "five", "six")    
          println(numbers.slice(1..3))
          println(numbers.slice(0..4 step 2))
          println(numbers.slice(setOf(3, 5, 0)))    
      //sampleEnd
      }
      ```
      ````

  - 要从头开始获取指定数量的元素，请使用 [`take()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/take.html) 函数。 要从尾开始获取指定数量的元素，请使用 [`takeLast()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/take-last.html)。 当调用的数字大于集合的大小时，两个函数都将返回整个集合。

    要从头或从尾去除给定数量的元素，请调用 [`drop()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/drop.html) 或 [`dropLast()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/drop-last.html) 函数。

    ```kotlin
    fun main() {
    //sampleStart
        val numbers = listOf("one", "two", "three", "four", "five", "six")
        println(numbers.take(3))
        println(numbers.takeLast(3))
        println(numbers.drop(1))
        println(numbers.dropLast(5))
    //sampleEnd
    }
    ```

    - [`takeWhile()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/take-while.html) 是带有谓词的 `take()`：它将不停获取元素直到排除与谓词匹配的首个元素。如果首个集合元素与谓词匹配，则结果为空。

    - [`takeLastWhile()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/take-last-while.html) 与 `takeLast()` 类似：它从集合末尾获取与谓词匹配的元素区间。区间的首个元素是与谓词不匹配的最后一个元素右边的元素。如果最后一个集合元素与谓词匹配，则结果为空。
    - [`dropWhile()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/drop-while.html) 与具有相同谓词的 `takeWhile()` 相反：它将首个与谓词不匹配的元素返回到末尾。
    - [`dropLastWhile()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/drop-last-while.html) 与具有相同谓词的 `takeLastWhile()` 相反：它返回从开头到最后一个与谓词不匹配的元素。


- 取单个元素

  - 检索集合的第一个与最后一个元素：[`first()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/first.html) 与 [`last()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/last.html)。
    - 附带条件`numbers.first { it.length > 3 }`

  - 为了避免在检索位置不存在的元素时出现异常，请使用 `elementAt()` 的安全变体：
    - 当指定位置超出集合范围时，[`elementAtOrNull()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/element-at-or-null.html) 返回 null。

    - [`elementAtOrElse()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/element-at-or-else.html) 还接受一个 lambda 表达式，该表达式能将一个 `Int` 参数映射为一个集合元素类型的实例。 当使用一个越界位置来调用时，`elementAtOrElse()` 返回对给定值调用该 lambda 表达式的结果。

  - 随机获取 [`random()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/random.html) 

  - 判断多个元素是否存在`numbers.containsAll(listOf("one", "zero"))`

  - 调用 [`isEmpty()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/is-empty.html) 和 [`isNotEmpty()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/is-not-empty.html) 来检查集合中是否包含任何元素。

- 集合排序

  - 基本的函数 [`sorted()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/sorted.html) 和 [`sortedDescending()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/sorted-descending.html) **返回**集合的元素，这些元素按照其自然顺序升序和降序排序。

  - 为了按照自定义顺序排序或者对不可比较对象排序，可以使用函数 [`sortedBy()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/sorted-by.html) 和 [`sortedByDescending()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/sorted-by-descending.html)。 它们接受一个将集合元素映射为 `Comparable` 值的选择器函数，并以该值的自然顺序对集合排序。
    - `val sortedNumbers = numbers.sortedBy { it.length }`

  -  [`reversed()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/reversed.html) 函数以相反的顺序检索集合

  - [`shuffled()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/shuffled.html) 对函数进行随机排列

- 集合聚合操作

  - [`minOrNull()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/min-or-null.html) 与 [`maxOrNull()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/max-or-null.html) 分别返回最小和最大的元素。 On empty collections, they return `null`.
  - [`average()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/average.html) 返回数字集合中元素的平均值。
  - [`sum()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/sum.html) 返回数字集合中元素的总和。
  - [`count()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/count.html) 返回集合中元素的数量。
  - 有函数 [`reduce()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/reduce.html) 和 [`fold()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/fold.html)，它们依次将所提供的操作应用于集合元素并返回**累积**的结果（对集合中每个元素进行操作）。 操作有两个参数：先前的累积值和集合元素。这两个函数的区别在于：`fold()` 接受一个初始值并将其用作第一步的累积值，而 `reduce()` 的第一步则将第一个和第二个元素作为第一步的操作参数。
    - `val sumDoubled = numbers.fold(0) { sum, element -> sum + element * 2 }`

- 写操作

  - 添加元素`numbers.add(5)`
    - 添加多个元素` numbers.addAll(arrayOf(7, 8))`

  - 

  - 若要从可变集合中移除元素，请使用 [`remove()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/remove.html) 函数。 `remove()` 接受元素值，并删除该值的一个匹配项。
    - [`removeAll()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/remove-all.html) 移除参数集合中存在的所有元素。 或者，你可以用谓词作为参数来调用它；在这种情况下，函数移除谓词产生 `true` 的所有元素。

    - [`retainAll()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/retain-all.html) 与 `removeAll()` 相反：它移除除参数集合中的元素之外的所有元素。 当与谓词一起使用时，它只留下与之匹配的元素。
    - [`clear()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-mutable-list/clear.html) 从列表中移除所有元素并将其置空。

  ### Collection


- 表示一个只读集合的共同行为：检索大小、 检测是否为成员等等。

#### MutableCollection

- 是一个具有写操作的 `Collection` 接口，例如 `add` 以及 `remove`。

### *Sequence

- 序列（Sequence）是一系列元素的**延迟计算**的对象。它们提供了一种惰性计算的方式，只有在需要时才会进行计算。序列可以看作是一种管道，当你需要一个元素时，它才会计算下一个元素并返回给你。这种延迟计算的特性使得序列非常适用于处理大量的数据或者需要进行复杂的计算的场景。使用序列可以避免在处理大数据集时产生不必要的中间结果。

### List

- 以指定的顺序存储元素，并提供使用索引访问元素的方法。
- 截取`println(numbers.subList(3, 6))`
- 在任何列表中，都可以使用 [`indexOf()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/index-of.html) 或 [`lastIndexOf()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/last-index-of.html) 函数找到元素的位置。 它们返回与列表中给定参数相等的元素的第一个或最后一个位置。 如果没有这样的元素，则两个函数均返回 `-1`。
- 二分搜索，如果存在这样的元素，则函数返回其索引；否则，将返回 `(-insertionPoint - 1)`，其中 `insertionPoint` 为应插入此元素的索引，以便列表保持排序。
  - 自定义比较`println(productList.binarySearch(Product("AppCode", 99.0), compareBy<Product> { it.price }.thenBy { it.name }))`


#### MutableList

- 是可以进行写操作的 `List`，例如用于在特定位置添加或删除元素

### Set

-  存储唯一的元素
-  要将两个集合合并为一个（并集），可使用 [`union()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/union.html) 函数。也能以中缀形式使用 `a union b`。 注意，对于有序集合，操作数的顺序很重要：在结果集合中， 左侧操作数在前。
-  要查找两个集合中都存在的元素（交集），请使用 [`intersect()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/intersect.html) 。 要查找另一个集合中不存在的集合元素（差集），请使用 [`subtract()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/subtract.html) 。 这两个函数也能以中缀形式调用，例如， `a intersect b` 。

#### MutableSet

- 带有来自 `MutableCollection` 的写操作接口的 `Set`。

### Map

- `Map` 存储 *键-值* 对（或 *条目*）；键是唯一的，但是不同的键可以与相同的值配对。 `Map` 接口提供特定的函数进行通过键访问值、搜索键和值等操作。
- 过滤` val filteredMap = numbersMap.filter { (key, value) -> key.endsWith("1") && value > 10}`
- 要将新的键值对添加到可变 Map ，请使用 [`put()`](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-mutable-map/put.html) 。
  - `numbersMap.put("three", 3)`


### MutableMap

- 是一个具有写操作的 `Map` 接口，可以使用该接口添加一个新的键值对或更新给定键的值。