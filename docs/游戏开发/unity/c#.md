### 与c++不同的一些基础语法

- `foreach`循环

  - ```
    foreach(string item in strings)
    {
        print (item);
    }
    ```

- 值类型与引用类型

  - 常见值类型
    - **基本数据类型**：`int`, `float`, `double`, `char`, `bool`, `byte`, `short`, `long`, `sbyte`, `ushort`, `uint`, `ulong`, `decimal`.
    - **结构体 (Structs)**：例如 Unity 中的 `Vector3`, `Vector2`, `Quaternion`, `Color`, `Rect`, 等。
    - **枚举 (Enums)**
  - 引用数据类型
    - **类 (Classes)**：例如 Unity 中的 `GameObject`, `Transform`, `Rigidbody`, 以及你自己定义的任何类。
    - **字符串 (Strings)**：尽管 `string` 看起来像是一个基本数据类型，但它实际上是一个类，因此它是一个引用类型。
    - **数组 (Arrays)**：无论数组的元素是值类型还是引用类型，数组本身总是引用类型。
    - **委托 (Delegates)**
    - **接口 (Interfaces)**

- 类型转化`as`

- 命名空间

  - 同一命名空间不能使用相同的名称，通过使用命名空间限定，可以使用不同的具有相同名称的属性/方法

  - 使用命名空间的方式

    - ```c#
      namespace MyNamespace
      {
          class MyClass
          {
              // 类的实现
          }
      }
      ```

      - 如果不同位置使用相同名称，表示两个块使用**相同的命名空间**

    - 直接限定`MyNamespace.MyClass myObject = new MyNamespace.MyClass();`

    - 对整个文件使用`using MyNamespace;`

  - 嵌套命名空间

    - ```c#
      namespace MyNamespace
      {
          namespace MySubNamespace
          {
              class MyClass
              {
                  // 类的实现
              }
          }
      }
      ```

    - `MyNamespace.MySubNamespace.MyClass myObject = new MyNamespace.MySubNamespace.MyClass();`

    - `using MyNamespace.MySubNamespace;`

- **协程（重要）**

  - 在需要延迟、重复或异步执行代码时非常有用。比如实现点击移动（这是一个有时长的过程），以及某种动作等等

  - unity中允许你在多帧上执行长时间的任务，而不是在单个帧中执行，从而防止游戏**因复杂的计算而“冻结”**。

  - 时间延迟

    - ```c#
      IEnumerator WaitAndPrint()
      {
          yield return new WaitForSeconds(5);
          Debug.Log("Printed after 5 seconds");
      }
      ```

  - 帧延迟

    - ```c#
      IEnumerator WaitForFrames()
      {
          for (int i = 0; i < 5; i++)
          {
              yield return null;
              Debug.Log("New frame");
          }
      }
      ```

  - 也可以将另一个协程作为返回条件

    - ```c#
      IEnumerator MainRoutine()
      {
          yield return StartCoroutine(SubRoutine());
          Debug.Log("Subroutine finished!");
      }
      
      IEnumerator SubRoutine()
      {
          yield return new WaitForSeconds(3);
      }
      
      ```

  - 启动协程

    - ```c#
      StartCoroutine(MyCoroutine());
      Coroutine myCoroutine = StartCoroutine(MyCoroutine());
      ```

  - 停止协程

    - ````c#
      StopCoroutine(myCoroutine);
      StopCoroutine("MyCoroutine");
      //全部停止
      StopAllCoroutines();
      ````

  - 应用：

    - ```c#
      //缓释复杂计算
      IEnumerator LoadData()
      {
          for (int i = 0; i < 10000; i++)
          {
              // Simulating data load with a simple operation
              float data = i * 0.5f;
              
              if (i % 100 == 0)  // Every 100 iterations, wait for the next frame
                  yield return null;
          }
          Debug.Log("Data loaded!");
      }
      ```

    - ```c#
      //两点之间移动
      public Transform pointA;
      public Transform pointB;
      public float speed = 1.0f;
      
      IEnumerator MoveObjectBackAndForth()
      {
          Vector3 startPos = pointA.position;
          Vector3 endPos = pointB.position;
          float journeyLength = Vector3.Distance(startPos, endPos);
          while (true)
          {
              float startTime = Time.time;
              float journeyCovered = 0;
              while (journeyCovered < journeyLength)
              {
                  journeyCovered = (Time.time - startTime) * speed;
                  float fracJourney = journeyCovered / journeyLength;
                  transform.position = Vector3.Lerp(startPos, endPos, fracJourney);
                  yield return null;
              }
      
              // Swap points for the next journey
              Vector3 temp = startPos;
              startPos = endPos;
              endPos = temp;
          }
      }
      ```

    - ```c#
      //延迟启动
      IEnumerator Start()
      {
          yield return new WaitForSeconds(5);
          ShowWelcomeMessage();
      }
      
      void ShowWelcomeMessage()
      {
          Debug.Log("Welcome to the game!");
      }
      
      ```


- 委托

  - 功能上类似函数指针

  - 使用`delegate`定义`public delegate void SimpleDelegate();`

  - ```c#
    public class DelegateExample
    {
        public delegate void ShowMessage(string message);
    
        public void DisplayMessage(string text)
        {
            Console.WriteLine(text);
        }
    
        public void Execute()
        {
            ShowMessage showMessage = DisplayMessage; // 创建委托实例并关联方法
            showMessage("Hello, World!"); // 调用委托
        }
    }
    ```

  - 多播委托

    - ```c#
      public delegate void MathOperation(int number);
      
      public void MultiplyByTwo(int num)
      {
          Console.WriteLine(num * 2);
      }
      
      public void Square(int num)
      {
          Console.WriteLine(num * num);
      }
      
      MathOperation operation = MultiplyByTwo;
      operation += Square; // 将 Square 方法添加到委托链
      
      operation(5); // 输出: 10 (5的两倍) 和 25 (5的平方)
      ```

  - `Func` 和 `Action` 是两种**预定义的委托类型**，提供了更简便的方式来表示具有特定参数和返回类型的方法，从而避免了为每个方法声明新的委托类型。
  - func委托
    - `Func<int>`: 一个没有参数、返回 `int` 类型值的方法。
    - `Func<int, int>`: 一个接受一个 `int` 参数、返回 `int` 类型值的方法。
    - `Func<string, int>`: 一个接受一个 `string` 参数、返回 `int` 类型值的方法。
    - `Func<T1, T2, TResult>`: 一个接受两个参数的方法，第一个参数是 `T1` 类型，
  - action委托
    - `Action`: 一个没有参数的方法。
    - `Action<int>`: 一个接受一个 `int` 参数的方法。
    - `Action<string, int>`: 一个接受 `string` 和 `int` 两个参数的方法。
    - `Action<T1, T2>`: 一个接受两个参数的方法，第一个参数是 `T1` 类型，第二个参数是 `T2` 类型。

- lambda表达式

  - ```c#
    x => x * x
        
    (x, y) => 
    {
        int result = x + y;
        Console.WriteLine(result);
        return result;
    }
    
    (int x, int y) => x + y 
    ```

  

### 数据结构（标准库）

- 名空间`using System.Collections.Generic`

#### 常用模板

- 初始化`List<int>arr=new list<int>();`

#####  List\<T\>

- `Add(T item)`: 添加元素到列表的末尾。
- `Remove(T item)`: 从列表中移除特定对象的第一个匹配项。
- `Clear()`: 移除所有元素。
- `Contains(T item)`: 确定某元素是否在列表中。
- `Sort()`: 对整个列表进行排序。

##### Dictionary<TKey, TValue>

- `Add(TKey key, TValue value)`: 将指定的键和值添加到字典中。
- `Remove(TKey key)`: 从字典中移除所指定的键的值。
- `TryGetValue(TKey key, out TValue value)`: 获取与指定的键相关联的值。
- `ContainsKey(TKey key)`: 确定字典是否包含指定的键。

##### Queue\<T>

- `Enqueue(T item)`: 将元素添加到队尾。
- `Dequeue()`: 移除并返回队首对象。
- `Peek()`: 返回位于队列开始处的对象但不将其移除。

##### Stack\<T>

- `Push(T item)`: 在 `Stack<T>` 的顶部插入对象。
- `Pop()`: 移除并返回在 `Stack<T>` 顶部的对象。
- `Peek()`: 返回在 `Stack<T>` 顶部的对象但不移除它。

##### HashSet\<T>

- `Add(T item)`: 将元素添加到集合中。
- `Remove(T item)`: 移除集合中的某个元素。
- `Contains(T item)`: 判断集合中是否包含某个元素。
- `UnionWith(IEnumerable<T> other)`: 修改当前 `HashSet<T>` 对象，以包含它自己和指定集合的并集。

##### LinkedList\<T> 

- `AddLast(T value)`: 将新节点添加到链表的末尾。
- `AddFirst(T value)`: 将新节点添加到链表的开始处。
- `RemoveLast()`: 移除链表的最后一个节点。
- `RemoveFirst()`: 移除链表的第一个节点。

##### SortedSet\<T>

- `Add(T item)`: 添加元素。
- `Remove(T item)`: 移除元素。
- `Contains(T item)`: 判断集合中是否包含某个元素。

##### SortedDictionary<TKey, TValue>

- `Add(TKey key, TValue value)`: 添加键/值对。
- `Remove(TKey key)`: 根据键移除键/值对。
- `ContainsKey(TKey key)`: 判断是否包含特定的键。

#### 自定义

- 自定义比较IComparer\<T>

  - ```c#
    public class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }
    }
    //外部比较器，方便一个类有多种不同比较方式
    public class AgeComparer : IComparer<Person>
    {
        public int Compare(Person x, Person y)
        {
            return x.Age.CompareTo(y.Age);  // 正常顺序
            // 或者
            // return y.Age.CompareTo(x.Age);  // 反向顺序
        }
    }
    
    List<Person> people = new List<Person> { /* ... */ };
    people.Sort(new AgeComparer());
    //或者直接写在类里（内部比较器）为一个类定义默认比较方式
    public class BadGuy : IComparable<BadGuy>
    {
        public string name;
        public int power;
    
        public BadGuy(string newName, int newPower)
        {
            name = newName;
            power = newPower;
        }
    
        //IComparable 接口需要
        //此方法。
        public int CompareTo(BadGuy other)
        {
            if(other == null)
            {
                return 1;
            }
    
            //返回力量差异。（正负表示大小关系）
            return power - other.power;
        }
    }
    ```

- 自定义判断相等/计算哈希(使用哈希表/字典时)IEqualityComparer\<T>

  - ```c#
    public class NameEqualityComparer : IEqualityComparer<Person>
    {
        public bool Equals(Person x, Person y)
        {
            return x.Name == y.Name;
        }
    
        public int GetHashCode(Person obj)
        {
            return obj.Name.GetHashCode();
        }
    }
    
    HashSet<Person> uniquePeople = new HashSet<Person>(new NameEqualityComparer());
    ```

### 面向对象

- 一个文件可以有多个类
  - **组织结构**：与其他编程语言不同，C#不要求文件名和公共类名相同。但按照这一约定组织代码可以使源代码更加有组织、清晰。
  - **可见性**：文件中的非公共类（如 `internal`, `protected`, `private` 或没有任何访问修饰符的类）只能在其所属的程序集中访问。这有时被用作一个文件中与主类紧密相关的辅助类。
  - **编译**：多个类的存在不会影响文件的编译。但要注意，如果你**有多个**`public`类并且你试图在命令行上使用`csc`编译器进行单文件编译，那么**编译器将要求主类（其名字与文件名相同）存在**。

- 配置属性的get、set方法

  - ```c#
    public int Level
    {
        get
        {
            return experience / 1000;
        }
        set//value表示输入的值
        {
            experience = value * 1000;
        }
    }
    ```

  - 更为灵活的控制访问，不写get/set表示只写/读

- 操作符重载函数必须是static的

- 泛型

  - ```c#
    public class GenericClass <T>
    {
        T item;
        public void UpdateItem(T newItem)
        {
            item = newItem;
        }
    }
    
    public class SomeClass 
    {
        //这是一个通用方法。注意通用
        //类型“T”。该“T”将在运行时替换为
        //实际类型。
        public T GenericMethod<T>(T param)
        {
            return param;
        }
    }
    ```

- 继承和多态

  - sealed阻止重写（override）

  - 使用`virtual`关键字来标记**可以被重写**的方法，然后在子类中使用`override`关键字来实际重写。

  - `abstract`表示抽象方法（类似virtual=0）

  - c#不支持多继承，但是可以实现多个接口

- 接口

  - ```c#
    public interface IFlyable
    {
        void Fly();
    }
    ```

  - 向继承那样表示实现接口

- 成员隐藏

  - 当派生类声明了一个与基类中具有相同名称的成员时，基类的成员会被派生类的成员**隐藏**。

  - 为了避免产生警告，显式地指定你想要隐藏基类的成员，可以使用`new`关键字

    - ```c#
      public class BaseClass
      {
          public void MyMethod()
          {
              Console.WriteLine("BaseClass MyMethod");
          }
      }
      
      public class DerivedClass : BaseClass
      {
          // 使用new关键字明确隐藏基类的MyMethod
          public new void MyMethod()
          {
              Console.WriteLine("DerivedClass MyMethod");
          }
      }
      ```

- 静态类

  - **不能被实例化**：因为静态类不能被实例化，所以它也不包含任何构造函数（除了静态构造函数）。
  - **只包含静态成员**：静态类可以包含静态方法、静态属性、静态字段和静态事件。它不能包含实例方法、实例属性、实例字段、实例构造函数或实例事件。
  - **不能被继承**：静态类是隐式地密封的，所以不能作为其他类的基类。
  - **静态构造函数**：静态类可以有一个静态构造函数，它会在第一次访问类的任何静态成员之前自动执行。静态构造函数不接受参数，并且在整个应用程序生命周期内只执行一次。
  - **线程安全**：静态构造函数是线程安全的，并且由.NET Framework确保在多线程环境中只初始化一次。
  - 静态类在设计**实用程序和工具函数**时特别有用。静态类的生命周期与应用程序的生命周期一致。

- 扩展

  - 扩展方法必须定义在**非泛型、非嵌套的静态类中**。（但这不是目标即被扩展类的条件）

  - 定义一个静态方法，将你想要扩展的类型作为它的第一个参数。这个参数必须前面有`this`修饰符。

    - ```c#
      public static class StringExtensions
      {
          public static bool IsNumeric(this string str)
          {
              return str.All(char.IsDigit);
          }
      }
      
      string value = "12345";
      bool result = value.IsNumeric();
      Console.WriteLine(result);  // 输出: True
      ```

  - 尽管扩展方法允许为类型添加新方法，但它们不能访问类型的私有字段或方法。

  - 如果类型已经有了与扩展方法同名的方法，原始的方法会优先被调用。