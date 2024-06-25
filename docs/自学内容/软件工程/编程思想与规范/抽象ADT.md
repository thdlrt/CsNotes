### 抽象数据结构

- 抽象数据结构的方法分类
	- Creators 构造器，如构造方法及 asList 静态工厂方法，**参数不能是本身类型**
	- Producers 获取新对象，如 concat，从**同类型对象**中创建
	- Observers 获取信息，如 size  
	- Mutators 对数据类型进行修改
	- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240120104832.png)

- 设计原则：
	- 包含一系列简单的便于组合的操作（而不是复杂的操作）
	- 操作应该具有一致性，而不是针对一系列特殊情况分类 (如 sum 对 List ，如果 List 不是数值数据就是特殊情况)
	- 应该提供足够的操作，便于获取足够的信息进行测试等目的

### 抽象方法

#### 不变性

- 程序实现不变性更好，不应该依赖使用者维护不变性（不进行修改）
- 避免返回成员变量的引用（即使是 final 也不行）避免外部通过这种方法修改成员变量（如 getTime 就不应该直接返回成员变量）
	- 修改为 `return new Date(timestamp.getTime());`
- 除了在 get 方法可能由于引用造成修改，在 set 方法仍然可能出现问题，如使用一个值反复修改对列表每一项赋值，最后会使得列表所有项完全相同
```java
for (int i = 0; i < 24; i++) {
        date.setHours(i);
        list.add(new Tweet("rbmllr", "keep it up! you can do it", date));
    } 
```
- 因此应该考虑也增加复制
```java
public Tweet(String author, String text, Date timestamp) {
    this.author = author;
    this.text = text;
    this.timestamp = new Date(timestamp.getTime());
}
```
- 或者考虑使用完全不可变的数据类型，如 `Collections.unmodifiableList()`

- 不变量的创建与维护
	- 初始成立：确保在对象的**初始状态**下，不变量是成立的。
	- 保持不变
		- Creator+Producer 为实例新对象建立不变量
		- Mutator+Observer 保持不变量的成立 
	- 避免表示暴露

#### 表示值与抽象值

- **表示值空间（Space of Representation Values）**:
    - 这个空间包含了实现抽象数据类型所用的**实际数据值**。
    - 在简单的情况下，一个抽象类型可能会通过一个单一的对象来实现。然而，在更常见的情况下，可能需要一组对象的网络来实现这一类型，因此表示值空间通常相当复杂。
    - 即便如此，我们可以先简单地将其视为一个数学值，以便于理解和操作。
- **抽象值空间（Space of Abstract Values）**:
    - 这个空间包含了抽象数据类型旨在支持的值。
    - 这些值是我们想象中的并不真实存在。但这些值代表了我们希望抽象类型的客户端（使用者）**如何看待抽象类型中的元素**。
    - 例如，一个用于无界整数的抽象类型可能将数学上的整数作为其抽象值空间；即使这个类型在实际中是通过一个有界整数的数组来实现的，这种实现细节对于用户来说是不可见的，也不重要的。
- **使用表示值空间来实现抽象值空间**。这意味着他们需要确保虽然在内部使用了特定的数据结构和算法，但对外提供的抽象类型的行为和性质应当与抽象值空间保持一致，从而对使用者隐藏实现细节。
- 如使用字符串表示 charset
	- ![image.png|375](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240120120705.png)
	- 每一个抽象值会被 map 到一个表示值
	- 一个抽象值可能对应**多个**表示值
	- 不是所有的表示只都会被使用

- **抽象函数** AF
	- 定义了从表示值空间（R）到抽象值空间（A）的映射
	- 可能满射（每个抽象值至少有一个对应表示值），不必是单射
- **表示不变性** RI 
	- **Rep Invariant** 指的是一个对象内部状态的一组属性，**这些属性在对象的整个生命周期中始终为真**。这些属性定义了对象的一个有效状态。当一个对象的表示不变性被维持时，我们可以确信对象不会处于一个破坏其设计和意图的状态。
	- 表示值空间（R）到布尔值的映射
	- 对于表示值 r，当且仅当 r 被 AF 映射时，RI(r) 为 true。换句话说，RI 告诉我们**给定的表示值是否是格式正确的**。
	- 有必要依据 RI 对表示值进行检查
- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240120144940.png)
- 对于 AF 和 RI 的描述同样需要写在注释里
```java
public class CharSet {
    private String s;
    // Rep invariant://对表示值的要求
    //    s contains no repeated characters
    // Abstraction Function://对映射方式（功能）的描述
    //   represents the set of characters found in s
    ...
}
```
- 设计抽象类型**不仅仅是选择表示值空间和抽象值空间，还涉及决定使用哪些表示值以及如何解释它们**。

- 暴露安全性论证 **Rep Exposure**（表示暴露）
	- 除了文档化 AF 和 RI 之外，还建议编写表示暴露安全性论证。这是一种注释，用于检查表示的每个部分，并审视处理表示的代码（特别是与客户端的参数和返回值有关的部分，因为这是表示暴露可能发生的地方），以及提供为什么代码不会暴露表示的理由
	- 检查所有可能与外部代码交互的部分，包括构造函数、方法参数、返回值以及任何公共字段。对于每个这样的部分，写下一个论证，说明为什么它不会导致表示暴露。这可能包括使用不可变对象、返回副本、使用封装好的数据结构等策略。
```java
// Immutable type representing a tweet.
public class Tweet {

    private final String author;
    private final String text;
    private final Date timestamp;

    // Rep invariant:
    //   author is a Twitter username (a nonempty string of letters, digits, underscores)
    //   text.length <= 140
    // Abstraction Function:
    //   represents a tweet posted by author, with content text, at time timestamp 
    // Safety from rep exposure:
    //   All fields are private;
    //   author and text are Strings, so are guaranteed immutable;
    //   timestamp is a mutable Date, so Tweet() constructor and getTimestamp() 
    //        make defensive copies to avoid sharing the rep's Date object with clients.

    // Operations (specs and method bodies omitted to save space)
    public Tweet(String author, String text, Date timestamp) { ... }
    public String getAuthor() { ... }
    public String getText() { ... }
    public Date getTimestamp() { ... }
}
```

- 结构归纳法：如果ADT的一个不变量是**通过创建者和生产者建立的，通过修改者和观察者保持的**，且**没有表示暴露发生**，那么可以断定这个**不变量**对ADT的所有实例**都是真的**。
### 接口

- 在接口中添加静态方法创建具体的实现类可以避免使用者直接调用实现类的构造函数，给更换底层实现类造成麻烦
	- 如果未来需要更改底层实现，只需要修改静态工厂方法内部的逻辑即可，客户端代码无需任何改动。
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240121124526.png)
	- 静态方法不属于类的某个实例，而是属于类本身。因此，它们不能访问类的实例类型参数，因此它需要声明自己的类型参数 `<E>`
### 等价

- 定义数据类型等价性的方法：
	- 根据抽象函数，a 与 b 等价 iff $f(a)=f(b)$
	- 满足等价关系的性质
	- 如果对两个对象应用的**所有操作都能得到相同的结果**，则等价

- equals 的要求
	- 重复调用得到相同的结果
	- 满足等价关系性质
	- 和 null 比较应该返回 false
	- 与 hashcode 的结果一致（因此重写 equals 时总应该重写 hashcode）

- 默认 hashcode 是通过存储地址生成
	- 重写为固定值会导致搜索变为近似 $O(n)$ 
	- 重写为属性是较好的方式

- 观察性**observational**等价：
	- 调用不改变对象状态的方法无法区分两个对象
	- 观察性等价性通常严格限定在**当前程序状态下**，测试两个对象是否“看起来”相同。
	- 观察性等价是较弱的，比如 java 中的集合通常为观察性等价，因此如果把集合放入 set ，如果修改集合会出现位置，因为 hashcode 更新，但是元素的位置仍保持不变
- 行为性**behavioral**等价：
	- 这种等价性允许调用两个对象上的任何方法，包括修改者（mutator）方法。这些方法可能会改变对象的状态。
	- 行为性等价性测试两个对象在**当前和所有未来**的状态下是否会“表现”相同。
- 对于不可变对象这两种等价一致（因为根本不能修改）

- 行为性等价性通常更适合 `equals()` 方法，因为它反映了两个对象是否是同一个对象的别名这一更一般的概念。对于需要比较对象当前状态的场景，应该考虑定义一个单独的方法，如 `similar()`，以避免与 `equals()` 方法的预期行为相冲突。

- 对于不可变对象通常比较抽象值，而对于可变对象通常是比较引用相等来实现行为性等价
	- 可变对象通常不重写`equals()` 和 `hashCode()` 方法

## 使用抽象方法编程

- 基本流程：
	- 攥写 spec、编写 test、实现（选择 rep，设计 repcheck、实现各种操作）

### 递归数据类型

- 递归抽象数据类型的表示方法
	- `ImList<E> = Empty + Cons(first:E, rest:ImList)`
	- `Tree<E> = Empty + Node(e:E, left:Tree<E>, right:Tree<E>)`
- 可以处理递归和无界结构，还提供了描述操作的方式

- 不可变 list 的定义
```java
public class Empty<E> implements ImList<E> {
    public Empty() {
    }
    public ImList<E> cons(E e) {
        return new Cons<>(e, this);
    }
    public E first() {
        throw new UnsupportedOperationException();
    }
    public ImList<E> rest() {
        throw new UnsupportedOperationException();
    }
}

public class Cons<E> implements ImList<E> {
    private final E e;
    private final ImList<E> rest;

    public Cons(E e, ImList<E> rest) {
        this.e = e;
        this.rest = rest;
    }
    public ImList<E> cons(E e) {
        return new Cons<>(e, this);
    }
    public E first() {
        return e;
    }
    public ImList<E> rest() {
        return rest;
    }
}
```

- 递归实现操作
```java
public interface ImList<E> {
    // ...
    public int size();
}

public class Empty<E> implements ImList<E> {
    // ...
    public int size() { return 0; }
}

public class Cons<E> implements ImList<E> {
    // ...
    public int size() { return 1 + rest.size(); }
}
```
