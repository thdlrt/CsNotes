## JVM

### 类的加载

#### Class

- 每一个类都持有其对应的`Class`类的对象的引用，其中包含着与类相关的信息

  - `Object`类中的`getClass()`能让我们获取到这个对象
  - 即对象使用`getClass()`获取；类使用`.class`获取类型的Class对象的引用；或者使用`Class.forName("Circle");`

- 从class对象创建对象

```java
    try {
        Class<?>  circleClass = Class.forName("Circle"); 
        Object obj = circleClass.newInstance();
    } catch (ClassNotFoundException e) {
    
    }
    //or 
    Class<?> circleClass = Circle.class;
    Object obj = circleClass.newInstance()
    ```

- 针对每一个类，编译Java文件会生成一个二进制.class文件，这其中就保存着该类对应的Class对象的信息。

- 类型检查

  - `public boolean isInstance(Object obj)` 是 Class 类的一个方法，它用于确定指定的对象 `obj` 是否是与调用该方法的 Class 对象所表示的类或其子类的实例兼容(是否是子类)。如果兼容，返回 `true`；否则返回 `false`。（动态检查）

```java
      if ( Shape.class.isInstance(x) ) {
           Shape s = (Shape)x;
      }
      ```


  - `x instanceof Shape`静态检查
  - 如果你在编译时已经知道了类型，建议使用 `instanceof` 进行类型检查，因为它更简单、更常见，而且能够在编译时捕获类型不匹配的错误。如果你需要在运行时动态检查类型，可以使用 `isInstance` 方法。

#### 类加载系统

- 触发类加载的条件：	
  - 遇到new,getstatic,putstatic或invokestatic这4条字节码指令时，如果类没有进行过初始化，则需要先触发初始化。
    - 实例化对象、读取设置静态字段、调用类的静态方法。
  - 使用java.lang.reflect包的方法对类进行反射调用的时候。
  - 当初始化一个类的时候，发现其**父类**还没有进行过初始化，则需要先出发父类的初始化。
  - 当虚拟机启动时，虚拟机会先初始化主类。

- **加载**(Loading)。由**类加载器(Class Loaders)** 执行，查找字节码，创建一个`Class`对象。

  - 通过一个类的全限定名来获取定义此类的二进制字节流；将这个字节流所代表的静态存储结构转换为方法区内的运行时数据结构；在内存中生成一个代表这个类的java.lang.Class对象，作为方法区这个类的各种数据的访问入口。
  - Java类由[`java.lang.ClassLoader`](https://docs.oracle.com/javase/8/docs/api/java/lang/ClassLoader.html)加载。
    - 这本身也是一个类，"Bootstrap Class Loader" 是 Java 虚拟机（JVM）中的一种特殊类加载器，它是负责加载 Java 核心类库和其他 JDK 内部类的加载器。这个类加载器是 JVM 的一部分，通常由本地代码实现。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231002201139513.png" alt="image-20231002201139513" style="zoom:33%;" />
  - 获取加载器`Array.class.getClassLoader()`
  - 双亲委派模型
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231002202213181.png" alt="image-20231002202213181" style="zoom:33%;" />
    - 双亲委派模型的工作流程是：如果一个类加载器收到了类加载的请求，它**首先不会自己去尝试加载**这个类，而是把**请求委托给父加载器**去完成，依次向上，因此，所有的类加载请求最终都应该被传递到顶层的启动类加载器中，只有当父加载器在它的搜索范围中**没有找到**所需的类时，即无法完成该加载，**子加载器才会尝试自己去加载该类**。
    - 这样的好处是不同层次的类加载器具有不同优先级，防止用户自定义加载器破坏内置类，比如不能改用一个假的String类

- **链接**(Linking)。**验证字节码**，为静态域分配存储空间，如果必需的话，会解析这个类创建的对其他类的所有引用（比如说该类持有`static`域）。

  - 验证：是连接阶段的第一步，目的是为了确保Class文件的字节流中包含的信息符合当前虚拟机的要求，并且不会危害虚拟机自身的安全。
    - 文件格式验证；元数据验证；字节码验证；符号引用验证

  - 准备：准备阶段是正式为类变量分配内存并设置类变量初始值的阶段。

  - 解析：虚拟机将常量池内的符号引用替换为直接引用的过程。

- **初始化**(Initializing)。如果该类有超类，则对其初始化，执行静态初始化器和静态初始化块。

- 类的热加载&自定义加载策略

```java
    import java.io.ByteArrayOutputStream;
    import java.io.File;
    import java.io.IOException;
    import java.io.InputStream;
    
    public class CustomClassLoader extends ClassLoader {
        // 重写ClassLoader的findClass方法
        @Override
        public Class findClass(String name) throws ClassNotFoundException {
            // 调用loadClassFromFile加载类字节码
            byte[] b = loadClassFromFile(name);
            // 调用ClassLoader的defineClass方法定义类
            return defineClass(name, b, 0, b.length);
        }
    
        // 加载类字节码的方法
        private byte[] loadClassFromFile(String fileName) {
            // 根据类名构造类文件路径，并替换包名中的点号为文件分隔符
            String classFilePath = fileName.replace('.', File.separatorChar) + ".class";
            
            // 使用类加载器的getResourceAsStream方法获取类文件的输入流
            InputStream inputStream = getClass().getClassLoader().getResourceAsStream(classFilePath);
            
            byte[] buffer;
            ByteArrayOutputStream byteStream = new ByteArrayOutputStream();
            int nextValue = 0;
            try {
                // 从输入流中读取类字节码并写入到字节数组中
                while ((nextValue = inputStream.read()) != -1) {
                    byteStream.write(nextValue);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            buffer = byteStream.toByteArray();
            return buffer;
        }
    }
    
    ```

  - 用途

    - **浏览器加载可执行内容：** 浏览器使用自定义类加载器来从网站加载可执行内容，如Applets。浏览器可以使用不同的类加载器从不同的网页加载Applets，这些Applets通过HTTP访问网站上的原始字节码文件，并在JVM内部将它们转换成类。
    - **修改现有字节码：** 自定义类加载器可以用于修改现有的字节码，例如编织代理（weaving agents），这可以用于实现一些高级功能。
    - **动态创建适用于用户需求的类：** 自定义类加载器可以用于动态创建满足用户需求的类。
    - **实现类版本控制机制：** 自定义类加载器可以用于在加载具有相同名称和包的类的不同字节码时实现类版本控制机制。

- 类加载器：

  - **启动类加载器（Bootstrap ClassLoader）：** 由C++语言实现（针对HotSpot）,负责将存放在\lib目录或-Xbootclasspath参数指定的路径中的类库加载到内存中，即负责加载Java的核心类。

  - **其他类加载器：** 由Java语言实现，继承自抽象类ClassLoader。如：
    - **扩展类加载器（Extension（Platform） ClassLoader）：** 负责加载\lib\ext目录或java.ext.dirs系统变量指定的路径中的所有类库，即负责加载Java扩展的核心类之外的类。
  
    - **应用程序类加载器（Application ClassLoader）：** 负责加载用户类路径（classpath）上的指定类库，我们可以直接使用这个类加载器，通过ClassLoader.getSystemClassLoader()方法直接获取。一般情况，如果我们没有自定义类加载器默认就是用这个加载器
  
- 总结：

  - 当程序**创建第一个**对类的**静态成员**的引用时，JVM会使用类加载器来根据类名查找.class文件
  - 一旦某个类的`Class`对象被载入内存，它就被**用来创建**这个类的所有对象
  - 构造器也是类的**静态方法**，使用`new`操作符创建新对象会被当作对类的静态成员的引用

### 类的自射

- Java Reflection 是一种强大的机制，它允许你在运行时检查、分析和操作类、方法、字段和其他类成员的信息，而无需提前知道这些信息。通过 Java Reflection，你可以动态地获取、创建、操作和使用类的对象，以及调用其方法，甚至是私有方法。

  - 反射的核心是 JVM 在运行时才动态加载类或调用方法/访问属性，它不需要事先（写代码的时候或编译期）知道运行对象是谁。
  - 在运行时判断任意一个对象所属的类；
  - 在运行时构造任意一个类的对象；
  - 在运行时判断任意一个类所具有的成员变量和方法
  - 在运行时调用任意一个对象的方法

```java
  import java.lang.reflect.*;
  public class DumpMethods {
      public static void main(String args[]) {
          try {
              Class c = Class.forName(args[0]);
              Method m[] = c.getDeclaredMethods();
              for (int i = 0; i < m.length; i++)
              System.out.println(m[i].toString());
          }
          catch (Throwable e) {
              System.err.println(e);
          }
      }
  }
  ```

  - 使用 Java Reflection 动态获取类的方法信息，以便在运行时检查和操作类的成员。通过运行这个程序并传递一个类的名称作为参数，可以查看该类中声明的所有方法，包括它们的名称、返回类型、参数等信息。这对于编写通用工具、调试和动态加载类非常有用。

### 对象

- 虚拟机遇到一个new指令时，首先将去检查这个指令的参数是否能在常量池中定位到一个类的符号引用；检查这个符号引用代表的类**是否已经被加载**，解析和初始化过。如果没有，那必须先执行响应的**类加载过程**；在类加载检查功通过后，为新生对象分配内存。对象所需的内存大小在类加载完成后便可完全确定。
- 对象的内存布局：
  - 对象头：对象自身的运行时数据，如哈希码，GC分代年龄，锁状态标志，线程持有的锁，偏向线程ID，偏向时间戳等；类型指针，即对象指向它的类元数据的指针，虚拟机通过这个指针来确定这个对象是哪个类的实例。
  - 实例数据：是对象真正存储的有效信息
  - 对齐填充
- 对象访问：Java程序需要通过**栈上了reference数据**来操作**堆上的具体对象**。
  - 句柄访问：Java堆中会划分出一块内存来作为句柄池，reference中存储的就是对象的句柄地址，而句柄中包含了对实例数据与类型数据的各自具体的地址信息。
  - 直接指针访问：reference中存储的直接就是对象地址

### 内存模型

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231002194747154.png" alt="image-20231002194747154" style="zoom:33%;" />

  - 堆内存（Heap）（公有）：堆内存是Java程序运行时动态分配内存的主要区域，它用于存储**对象实例和数组**，所有通过 `new` 关键字创建的对象都会在堆上分配内存。

  - 方法区（Method Area）（公有）：方法区是用于存储类（已被加载的）的元信息、静态变量、常量和方法字节码等信息的地方。

  - 虚拟机栈（VM Stack）：虚拟机栈是用于**存储方法调用和局部变量**的内存区域。每一个java方法从调用直至完成的过程，就对应着一个栈帧在虚拟机栈中入栈到出栈的过程。

  - 本地方法栈（Native Method Stack）：本地方法栈类似于虚拟机栈，但是用于执行**本地**（Native）方法，这些方法通常是由本地库实现的。

  - 程序计数器（Program Counter Register）：程序计数器是当前线程执行的字节码指令的地址指示器。

- **Java内存模型的目的：** 屏蔽掉各种硬件和操作系统的内存访问差异，以实现让java程序在各种平台下都能达到一致的内存访问效果。

- Java内存模型规定了所有的变量都存储在**主内存中**。每条线程中还**有自己的工作内存**，线程的工作内存中保存了被**该线程**所使用到的变量（这些变量是从主内存中拷贝而来）。线程对变量的所有操作（读取，赋值）都必须在工作内存中进行。不同线程之间也**无法直接访问**对方工作内存中的变量，线程间变量值的传递均需要通过主内存来完成。

### 垃圾回收

- 堆是垃圾收集器管理的主要区域

#### 垃圾收集算法

- 标记-清除算法：
  - 首先标记出所有需要回收的对象；在标记完成后统一回收所有被标记的对象。
  - 问题：标记和清除两个过程的效率都不高；标记清除之后产生大量不连续的内存碎片。
- 复制算法：
  - 将可用内存按容量大小划分为大小相等的两块，每次只使用其中的一块。当一块内存使用完了，就将还存活着的对象复制到另一块上面，然后再把已使用过的内存空间一次清理掉。
  - 问题：将内存缩小为了原来的一半
- 标记-整理算法：
  - 标记过程仍然与”标记-清除“算法一样，但后续步骤不是直接对可回收对象进行清理，而是让所有存活的对象都向一端移动，然后直接清理掉边界以外的内存。
- 分代收集算法：
  - 把Java堆分为新生代和老年代，这样就可以根据各个年代的特点采用最适当的收集算法。
  - 在新生代中，每次垃圾收集时都发现有大批对象死去，只有少量存活，那就选用复制算法。（不均匀划分，如8:1）
  - 在老年代中，因为对象存活率高、没有额外空间对它进行分配担保，就必须采用“标记-清除”或“标记-整理”算法来进行回收。

#### 垃圾回收机制

- Minor GC:指发生在新生代的垃圾收集动作，该动作非常频繁。
- Full GC/Major GC:指发生在老年代的垃圾收集动作，出现了Major GC，经常会伴随至少一次的Minor GC。Major GC的速度一般会比Minor GC慢10倍以上。

- JVM中分为年轻代和老年代。
  - HotSpot JVM把年轻代分为了三部分：1个Eden区和2个Survivor区（分别叫from和to）。默认比例为8：1
    - 一般新创建的对象会被分配到**Eden区**，在GC开始的时候，对象只会存在于Eden区和名为“From”的Survivor区，紧接着进行GC，Eden区中所有存活的对象都会被复制到“To”，而在“From”区中，仍存活的对象会根据他们的年龄值来决定去向。年龄达到一定值(年龄阈值，可以通过-XX:MaxTenuringThreshold来设置)的对象会被移动到**年老代**中，没有达到阈值的对象会被复制到**“To”区域**。经过这次GC后，Eden区和From区已经被清空。这个时候，“From”和“To”会交换他们的角色，保证名为To的Survivor区域是空的。
- 空间分配担保
  - 在发生Minor GC之前，虚拟机会**先检查老年代最大可用的连续空间是否大于新生代所有对象的总空间**，如果这个条件成立，那么Minor GC可以 确保是安全的。如果不成立，则虚拟机**会查看HandlePromotionFailure设置值是否允许担保失败**。如果允许，那会继续检查老年代最大可用的连续空间**是否大于历次晋升到老年代对象的平均大小，如果大于，则将尝试进行一次Minor GC**，尽管这个Minor GC是有风险的。如果小于，或者HandlePromotionFailure设置不允许冒险，那这时也要改为进行一次Full GC。

#### 垃圾收集器

- 

#### 判断对象是否可以回收

- 可达性分析算法
  - 通过一些列的称为“GC Roots”的对象作为起始点，从这些节点开始向下搜索，搜索所走过的路径称为引用链，当一个对象到GC Roots没有任何引用链相连时（就是从GC Roots 到这个对象是不可达），则证明此对象是不可用的。所以它们会被判定为可回收对象。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231004203224187.png" alt="image-20231004203224187" style="zoom:33%;" />
  - 可以作为GC Roots的对象
    - 虚拟机栈（栈帧中的本地变量表）中引用的对象；
    - 方法区中类静态属性引用的对象；
    - 方法区中常量引用的对象；
    - 本地方法栈中JNI（即一般说的Native方法）引用的对象；
  - 如果对象在进行可达性分析后发现没有与GC Roots相连接的引用链，那它将会被第一次标记并且进行一次筛选，筛选的条件是此对象是否有必要执行finalize()方法。当对象没有 覆盖finalize()方法，或者finalize()方法已经被虚拟机调用过，虚拟机将这两种情况都视为“没有必要执行”。
  - 如果这个对象被判定为有必要执行finalize()方法，那么这个对象将会放置在一个叫做F-Queue队列之中，并在稍后由一个由虚拟机自动建立的、低优先级的Finalizer线程去执行它。finalize()方法是对象逃脱死亡命运的最后一次机会，稍候GC将对F-Queue中的对象进行第二次小规模的标记，如果对象要在finalie()中成功拯救自己——只要重新与引用链上的任何一个对象建立关联即可，譬如把自己（this关键字）赋值给某个类变量或者对象的成员变量，那在第二次标记时它将会被移除出“即将回收”的集合；如果对象这时候还没有逃脱，那基本上它就真的被回收了。