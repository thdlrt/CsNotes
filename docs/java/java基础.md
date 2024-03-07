## java基础

### 主类&程序入口

- 文件中必须存在与文件名相同的类
- 入口函数`public static void main(String[] args){}`
  - 多个类都可以有main，但是只有主类的会被自动调用

- 每个java文件中只能有一个public类，也只有这一个类可以在包外访问
  - 即其他的类适用于支撑唯一的public类的

### [[基本数据类型与包装类]]

### [[数组类型]]

### [[枚举类型]]

### [[字符串]]

### [[拷贝与引用]]

### 补充

- 自动类型推断（JDK11）
  - 使用`var`关键字
  - 必须为变量提供初始值才能进行推断
  - 不允许作为返回值

- Java不允许重复定义变量（即使是在内层作用域），也就是不能在内层重新定义并隐藏外层

- 比较：
  - 对于基本类型直接使用`= !=`
  - 对于非基本类型使用`=`会直接比较**引用**是否相同
  - 内置类型可以直接使用`equals()`进行比较
  - 自定义类型`equals()`也是比较引用，需要重写方法

- 位移
  - 数学位移`>>`
  - 逻辑位移`>>>`

 - 向上转型会丢失特定**类型的信息**，通过向下转型可以重新获取类型信息
- java中所有的转型都会被检查，运行时会检查强制转型是否正确（会抛出异常），这也是Java反射的一部分

### 流程控制

- for-in
``` java
for(type element: array)
{
    System.out.println(element);
}
```

- break标签
  - 标签应该放置在迭代语句之前
``` java
label:
xxx{
    {
        break label;
    }
}
```
- 控制break、continue控制**特定的迭代**（比如直接从内层break到最外层）
- 应用于嵌套循环

### [[switch]]

### 方法

- `public static void(){}`静态方法是类方法，可以通过**类名**直接调用(如main方法)，不能被子类重写，但可以被同名函数覆盖

- 静态代码块，内部全部为静态
``` java
static{

}
```
- 静态方法不能访问实例变量或实例方法，只能**访问静态变量和其他静态方法**。

- 方法与方法之间是平级关系，不能嵌套定义

- 可变参数
  - 必须是最后一个参数` public static void printMax( double... numbers)`使用数组类型也可以
  - 可以将传入的多个参数自动**转化为一个数组**
  - 允许传入0个元素

## 面向对象

### 思想

- 数据操作分离：实体类只负**责数据存取**（get/set），而对数据的处理交给其他类来完成，以实现**数据和数据业务**处理相分离

### 访问权限控制

- 成员的访问权限
	- public
	- private：仅类内访问
	- default：包内可见（即不添加任何修饰符）
	- protected：子类可访问，即使不在一个包，同时也提供了包访问权限
- 类的访问权限
  - 类中可以不存在public类，此时文件可以随意命名
  - 只有默认（包），和public两种作用域

### [[构造方法]]

### 继承

- `public class Zi extends Fu{} `
- 多态
  - 对象多态 : 将方法的形参定义为父类类型, 这个方法可以接收该父类的任意子类对象 
  - 行为多态 : 同一个行为, 具有多个不同表现形式或形态的能力
  - 多态的好处：提高了程序的扩展性
  - 多态的弊端：不能使用子类的特有成员、

-  **不应该在构造函数中使用动态绑定**：构造函数被调用时子类还没有完全初始化，此时通过动态绑定去调用子类的方法可能存在问题（甚至成员变量都还没有赋初值进行初始化！
- 子类中重写方法的返回值可以是基类方法返回值的子类型

### 抽象类与抽象方法

- 抽象方法：`public abstract void`

- 抽象类：存在抽象方法的类必须**声明为抽象类**
``` java
public abstract class Fu {
    public abstract void 行善();
}
```
- 抽象类不能实例化，抽象类的子类要么重写抽象类中所有抽象方法，要么也是抽象类
### ![[docs/java/java基础/杂项/final]]

### 组合与聚合

- **组合**强合成：“部分”的生命期不能比“整体”还要长
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230921115727663.png" alt="image-20230921115727663" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230921115826475.png" alt="image-20230921115826475" style="zoom: 50%;" />
- **聚合**、关联弱合成：部分可以独立存在
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230921115848748.png" alt="image-20230921115848748" style="zoom:50%;" />


### 委托

- java没有直接提供，需要手动实现
- 将成员对象放在新类中，并在新类中公开
- 如飞船继承发动机并不合理，因此使用组合并公开方法（通过组合的方式间接实现委托）
``` java
public class SpaceShipControls {
  void up(int velocity) {}
  void down(int velocity) {}
  void left(int velocity) {}
  void right(int velocity) {}
  void forward(int velocity) {}
  void back(int velocity) {}
  void turboBoost() {}
}
public class SpaceShipDelegation {
  private String name;
  private SpaceShipControls controls =
    new SpaceShipControls();
  public SpaceShipDelegation(String name) {
    this.name = name;
  }
  // Delegated methods:
  public void back(int velocity) {
    controls.back(velocity);
  }
  public void down(int velocity) {
    controls.down(velocity);
  }
  public void forward(int velocity) {
    controls.forward(velocity);
  }
  public void left(int velocity) {
    controls.left(velocity);
  }
  public void right(int velocity) {
    controls.right(velocity);
  }
  public void turboBoost() {
    controls.turboBoost();
  }
  public void up(int velocity) {
    controls.up(velocity);
  }
  public static void main(String [] args) {
    SpaceShipDelegation protector =
      new SpaceShipDelegation("NSEA Protector");
    protector.forward(100);
  }
}
```

### [[接口]]

### [[内部类]]

## [[泛型]]

## [[反射]]

## [[异常]]

## [[docs/java/java基础/杂项/测试|测试]]

## 并发编程

### [[基本概念]]

### [[线程与线程池]]

### [[线程安全的数据类型]]

### [[高级#任务调度|任务调度]]

## I/O

### [[控制台IO]]

### [[旧IO]]

### [[NIO]]

### [[文件]]

### [[序列化与反序列化]]

### [[网络编程]]

## java.util

### 集合

- 长度可变，更多功能，不能使用基本数据类型

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231112215809676.png" alt="image-20231112215809676" style="zoom:33%;" />

- `Collection`是**一个接口**，是Java集合框架的一部分。它提供了用于操作一组对象的基本方法，如添加、删除、遍历等。`Collection`接口是多个集合类的超接口，包括`List`、`Set`、`Queue`等。
  - 是所有序列集合共同的**根接口**，存在一个默认实现AbstractCollection，可以通过继承来实现接口

- [[Collections工具类|Collections]] 是一个包含**静态方法的工具类**，这些方法用于操作或返回集合。它为整个集合框架提供了一系列的静态方法，如排序、搜索、线程安全转换等。

#### 基本方法

- 集合都需要引入，如`import java.util.ArrayList;`
  - `import java.util.*
- 创建，如`ArrayList<String> sites = new ArrayList<String>();`
- 添加元素`add([index],item)`
- （按照下标）访问`get(下标)`
- 修改元素`set(下标,item)`
- 删除元素`remove(下标/引用)`
- 大小`size()`
- 清空`clear()`
- 复制`clone()`
- 查找`indexOf() lastIndexOf()`
- 删除位于指定集合内的元素`removeAll()`
- 添加一组元素
  - `list2.addAll([Index, ]list1);`
  - 所有Collection都具有的方法,只接受另一个Collection作为参数
- 打印集合
  - 可以直接`println`
  - 默认的打印是通过集合的`toString`方法提供的

- 创建**不可修改**的Collection或map
  - Collrctions接受一个原始集合返回一个只读版本
``` java
Collections.unmodifiableCollection(
       new ArrayList <>(data));
List <String> a = Collections.unmodifiableList(
        new ArrayList <>(data));
 Set <String> s = Collections.unmodifiableSet(
      new HashSet <>(data));
 Set <String> ss = Collections.unmodifiableSortedSet(
        new TreeSet <>(data));
Map <String,String> m = Collections.unmodifiableMap(
        new HashMap <>(Countries.capitals(6)));
Map <String,String> sm = Collections.unmodifiableSortedMap(
        new TreeMap <>(Countries.capitals(6)));
```
- 调用修改集合内容的方法会触发 UnsupportedOperationException

#### [[Iterator]]

#### [[Collections工具类]]

#### List

- List承诺以特定的顺序维护元素，支持在List中间插入和删除元素
- 使用`contains()`确认对象是否在列表中
- 切片`subList(int fromIndex, int toIndex);`，不包含`toIndex`
- `containsAll(Collection<?> c);`是否包含全部元素
- 求交`list.retainAll(retainElements);`,会对list进行原地修改

##### ArrayList

- 默认情况下存入的时Object对象`xx = new ArrayList();	
  - 明确类型`ArrayList<xx> xx = new ArrayList<>();`
  - 更简洁的写法`var apples = new ArrayList<xx>();`

- 可以向上转型为接口使用`List<Apple>apples = new ArrayList/LinkedList<>();`
- 添加一组元素
  - `new ArrayList<>(Arrays.asList(1,2,3...))`
    - 也可以直接传入一个数组                                            
    - 这种方法的底层是数组，后续不能添加/删除元素

- 转化为数组`.toArray()`
  - 默认会返回一个Object数组
  - 如果传递一个目标类那个的数组。就会根据这个类型生成
    - `pets.toArray(new Pet[0]);`


##### LinkedList

- 实现了 queue deque 等接口，可以作为队列使用
- 使用`add`默认在末尾加，也可以指定`addFirst()/addLast()`
  - remove、get同理
  - 也可以随机访问，不过如果访问元素不在收尾，效率很低

###### Stack

- 使用ArrayDeque实现栈的方法，但必须声明为Deque类型
  - `Deque<String> stack = new ArrayDeque<>();`
- `.push(T item)`
- `.peek()`返回栈顶元素
- `.pop()`移除并返回栈顶元素

###### Queue

- `element()`返回队首元素，null时会报错
  - `peek()`可以返回null
- `offer()`在队尾插入元素
- `remove()` 出队并返回队首元素，null 时会报错
  - `poll()`可以返回null
- 虽然来源于LinkedList，但不能直接使用其方法

###### Deque

- Deque<\T>是一个接口
  - `Deque<String> deque = new linkedList<>();`
- `addFirst(E e)` / `offerFirst(E e)`: 在队列的头部插入元素。`addFirst`在空间不足时抛出异常，而`offerFirst`则返回`false`。
- `addLast(E e)` / `offerLast(E e)`: 在队列的尾部插入元素。`addLast`在空间不足时抛出异常，而`offerLast`则返回`false`。
- `removeFirst()` / `pollFirst()`: 移除并返回队列头部的元素。`removeFirst`在队列为空时抛出异常，而`pollFirst`则返回`null`。
- `removeLast()` / `pollLast()`: 移除并返回队列尾部的元素。`removeLast`在队列为空时抛出异常，而`pollLast`则返回`null`。
- `getFirst()` / `peekFirst()`: 返回队列头部的元素但不移除。`getFirst`在队列为空时抛出异常，而`peekFirst`则返回`null`。
- `getLast()` / `peekLast()`: 返回队列尾部的元素但不移除。`getLast`在队列为空时抛出异常，而`peekLast`则返回`null`。

#### PriorityQueue

- 基本操作与Queue一致，但是是优先队列
- 默认是小根堆
- 可以传入比较器，或者类型实现 Comporable<>接口

#### Set

##### HashSet

- 不允许有重复元素，HashSet **是无序的**，即不会记录插入的顺序
- 使用`contains()`判断元素是否存在
- 允许存储null
- 自定义数据类型要实现equals、hashCode

##### TreeSet

- 实现 SortedSet 接口
- 允许存储null
- 使用红黑树实现元素排序存储
- 创建时可以传入一个比较器，如`String.CASE_INSENSITIVE_ORDER`
- 自定义数据类型要实现equals、Comparable<>接口
- `last() first()` 生成最大/小元素
- `floor(E e)`：返回在 `TreeSet` 中小于等于给定元素的最大元素，如果不存在这样的元素，则返回 `null`。
- `ceiling(E e)`：返回在`TreeSet`中大于等于给定元素的最小元素，如果不存在这样的元素，则返回`null`。
- `higher(E e)`：返回在`TreeSet`中严格大于给定元素的最小元素，如果不存在这样的元素，则返回`null`。
- `lower(E e)`：返回在`TreeSet`中严格小于给定元素的最大元素，如果不存在这样的元素，则返回`null`。
- 范围搜索
  - `subSet(E fromElement, E toElement)`：获取 `TreeSet` 的一个子集，该子集包含从 `fromElement`（包含）到 `toElement`（不包含）的所有元素。（Element 不一定要在集合中，只是表示一个范围）
  - `headSet(E toElement)` 方法返回一个视图，包含小于（不包含）`toElement` 的所有元素。
  - `tailSet(E fromElement)` 方法返回一个视图，包含大于或等于 `fromElement` 的所有元素。
  - 注意对视图的修改是对原集合的修改


##### LinkedHashSet

- 允许存储null
- 保持元素的**插入顺序**，迭代时将按照元素的添加顺序返回。
- 性能略低于`HashSet`，但在迭代访问整个集合时有更好的性能。

#### Map

- java 中如何进行 `map[x]++`

##### HashMap

- 添加`put(,)`
- 对键、值分别查找`containsKey() containsValue()`
- 创建`Map<Integer, Integer>m = new HasMap<>();`
``` java
Integer freq = m.get(r);
m.put(r, freq==null?1: freq+1);
```

- 允许`null`键和`null`值。
- 不保证映射的顺序，顺序可能随时间发生变化。
- `entrySet()`生成Map.Entry（Map中的键值对）组成的Set，这个Set可以转化为流对象进行操作

##### TreeMap

- 不允许`null`键（如果使用自然顺序），但允许`null`值。
- 提供了一个有序的映射。
- 基于红黑树实现

- 常用方法
``` java
//小于等于 n 的最大键值（向前）
floorEntry(n);
//小于
lowerEntry(n);
//大于等于的（向后）
ceilingEntry();
//大于
higherEntry(K key);
//首尾元素
firstEntry();
lastEntry();
pollFirstEntry();
pollLastEntry();
//逆序排序
map = map.descendingMap();
```


- 范围操作
  - `subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive)`:
    - 返回一个视图，包含从`fromKey`到`toKey`范围内的所有键值对，根据`fromInclusive`和`toInclusive`标志确定是否包含边界键。
  - `headMap(K toKey, boolean inclusive)`:
    - 返回一个视图，包含小于（或等于，如果`inclusive`为`true`）`toKey`的所有键值对。
  - `tailMap(K fromKey, boolean inclusive)`:
    - 返回一个视图，包含大于（或等于，如果`inclusive`为`true`）`fromKey`的所有键值对。

##### LinkedHashMap

- 基于哈希表和链表实现。
- 按插入顺序或访问顺序（构造时指定）**保持映射的顺序**。
- 允许`null`键和`null`值。

##### WeakHashMap

- 使用弱引用，可以减少存储空间占用
- 当一个键不再被使用时就会被垃圾清理自动处理

#### [[equals()与hashCode()]]

#### [[record记录]]

#### [[使用享元自定义Collecction和Map]]
### [[时间类]]
### [[Math类]]

### [[日志]]
## 杂项

### [[jvm]]

### [[注解]]

### [[函数式编程]]

### [[流|流Stream]]

### [[包]]

### [[Java编码规范]]

### 环境配置

- `java-version`正常但是找不到`javac`：
  - 新建->变量名“CLASSPATH”,变量值`“.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar”`

### [[Javadoc]]