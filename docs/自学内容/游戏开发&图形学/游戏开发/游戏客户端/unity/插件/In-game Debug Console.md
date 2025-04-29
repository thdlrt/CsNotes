这个终端命令控制台（Command Console）是一个用于在游戏或应用程序运行时快速执行特定功能或调试任务的工具。它允许你通过简单的文本输入来调用预先定义好的函数或方法。下面我会用中文详细讲解如何使用它。

---

## 一、基础使用方式：

控制台一般由以下部分组成：

- **输入区域**：位于终端底部，你可以在这里输入命令。
- **输出区域**：显示执行的结果或反馈信息。

你首先可以输入以下命令查看所有可用的命令：

```
help
```

---

## 二、命令的基本格式：

命令的基本格式为：

```
命令 参数1 参数2 参数3 ...
```

每一个命令背后对应一个函数。比如文档中的示例：

```
cube [0 2.5 0]
```

- 这里的`cube`即为命令名。
- `[0 2.5 0]`是一个`Vector3`类型的参数，表示创建方块的位置坐标。

---

## 三、参数输入规范：

控制台有以下输入规则：

|数据类型|输入示例|说明|
|---|---|---|
|字符串|`"hello world"` 或 `'hello world'`|必须用引号包裹|
|向量（Vector2, Vector3, Vector4）|`[1 2 3]` 或 `(1 2 3)`|必须用方括号或圆括号包裹|
|空向量（Vector.zero）|`[]`|表示全零向量|
|布尔类型（true / false）|`1`（代表true）或`0`（代表false）|可用数字简化表示|
|空对象|`null`|用于表示空的 GameObject 或 Component|

例如：

- 创建方块在原点：`cube []` 或者 `cube [0 0 0]`
- 创建方块在坐标(1, 2, 3)：`cube [1 2 3]`

---

## 四、自定义命令的注册方式：

你可以用以下四种方式将自己的函数注册为命令：

### 方法1：使用 `[ConsoleMethod]` 属性标记（最简单，推荐）

```csharp
[ConsoleMethod("cube", "在指定位置创建立方体")]
public static void CreateCubeAt(Vector3 position)
{
    GameObject.CreatePrimitive(PrimitiveType.Cube).transform.position = position;
}
```

### 方法2：用强类型函数注册（推荐）

```csharp
DebugLogConsole.AddCommand<Vector3>("cube", "在指定位置创建立方体", CreateCubeAt);
```

### 方法3：用静态弱类型函数注册（不直接推荐）

```csharp
DebugLogConsole.AddCommandStatic("cube", "在指定位置创建立方体", "CreateCubeAt", typeof(TestScript));
```

### 方法4：用实例弱类型函数注册（不直接推荐）

```csharp
DebugLogConsole.AddCommandInstance("cube", "在指定位置创建立方体", "CreateCubeAt", this);
```

> 注意：方法3、方法4需要输入方法名的字符串，容易出错，一般只在特殊情况下使用。

---

## 五、移除已经注册的命令：

```csharp
DebugLogConsole.RemoveCommand("cube");
```

或者

```csharp
DebugLogConsole.RemoveCommand(CreateCubeAt);
```

---

## 六、自定义参数类型（进阶使用）：

如果你想让控制台支持更多种类的自定义参数类型（例如你自定义的类），可以用以下方式：

### 方法1：强类型方式定义（推荐）

```csharp
public class Person
{
    public string Name;
    public int Age;
}

// 注册自定义类型的解析函数
DebugLogConsole.AddCustomParameterType(typeof(Person), ParsePerson);

// 解析函数的定义
private static bool ParsePerson(string input, out object output)
{
    List<string> inputSplit = new List<string>(2);
    DebugLogConsole.FetchArgumentsFromCommand(input, inputSplit);

    if(inputSplit.Count != 2)
    {
        output = null;
        return false;
    }

    object age;
    if(!DebugLogConsole.ParseInt(inputSplit[1], out age))
    {
        output = null;
        return false;
    }

    output = new Person()
    {
        Name = inputSplit[0],
        Age = (int)age
    };

    return true;
}
```

### 方法2：使用 `[ConsoleCustomTypeParser]` 属性标记（更简单）

```csharp
[ConsoleCustomTypeParser(typeof(Person))]
public static bool ParsePerson(string input, out object output)
{
    // 与上面代码相同...
}
```

---

## 七、移除已添加的自定义参数类型：

```csharp
DebugLogConsole.RemoveCustomParameterType(typeof(Person));
```

---

## 八、实操步骤举例（入门实践）：

假设你已经写好了一个创建立方体的函数：

```csharp
[ConsoleMethod("cube", "在指定位置创建立方体")]
public static void CreateCubeAt(Vector3 position)
{
    GameObject.CreatePrimitive(PrimitiveType.Cube).transform.position = position;
}
```

实际操作步骤：

1. 在游戏运行时打开命令终端。
2. 在终端输入区域输入命令，例如：
    
    ```
    cube [1 2 3]
    ```
    
3. 回车执行，观察场景中就会在坐标(1, 2, 3)位置创建一个立方体。

---

## 九、常见问题与注意事项：

- 命令名、函数名、参数类型一定要对应。
- 字符串参数记得用引号包裹。
- 向量参数记得用括号括住。
- 如果命令执行失败，可以输入`help`查看命令的语法是否正确。
