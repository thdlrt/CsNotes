## 基本

### 概念

- 场景由许多游戏对象GameObject（如摄像机、球体）构成；一个游戏对象由许多组件构成（如transform移动组件、mesh renderer渲染组件）。
- 可以直接在左侧菜单拖拽一个节点到另一个作为联动子节点

### 场景

### UGUI

- 基本组成
  - **Canvas**：所有的 UI 元素都需要放在 Canvas 下。Canvas 可以是屏幕空间、世界空间或摄像机空间。
  - **Rect Transform**：替代了传统的 Transform，用于 2D 界面定位。
  - **UI 组件**：例如 Button、Text、Image、Slider 等。
  - **事件系统**：UGUI 有自己的事件系统，用于处理如点击、拖放、滚动等交互。
  - **Raycasting**：用于确定用户点击了哪个 UI 元素。
  - **布局组件**：如 Grid Layout Group 和 Vertical Layout Group，它们可以自动安排其子对象。

#### 布局

1. **Vertical Layout Group** 和 **Horizontal Layout Group**: 这两个组件会自动将其子元素排列成垂直或水平的线性序列。
2. **Grid Layout Group**: 将其子元素组织成一个网格。你可以定义格子的大小、间距等。
3. **Layout Element**: 允许你为单个元素指定布局属性，例如最小、最大和首选尺寸。
4. **Content Size Fitter**: 调整其矩形大小以适应其内容。
5. **Aspect Ratio Fitter**: 使 GameObject 保持特定的宽高比。

#### 事件系统

- 事件绑定，如按钮
```c#
public Button myButton;

void Start()
{
    myButton.onClick.AddListener(OnClick);
}

void OnClick()
{
    Debug.Log("Button was clicked!");
}

```

- 通过广播进行函数调用
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241125234739477.png" alt="image-20241125234739477" style="zoom:67%;" />

```c#
//gameObject.SendMessage("MethodName", optionalParameter, SendMessageOptions.RequireReceiver);

void Update()
{
    if (Input.GetKeyDown(KeyCode.Space))
    {
        SendMessage("Jump", SendMessageOptions.RequireReceiver);
    }
}

void Jump()
{
    Debug.Log("Jump called on " + gameObject.name);
}
```

- 最多只能传递一个可选参数

#### UI组件


## 脚本c#

### 对象

- 获取对象
  - 通过组件获取`组件.gameObject`
  - 获取被绑定的对象`this.gameObject`
  - 通过名称获取：`GameObject myObject = GameObject.Find("ObjectName");`
  - 通过标签获取：`GameObject myObject = GameObject.Find("ObjectName");`
    - 也可以获取全部：`GameObject[] objectsWithTags = GameObject.FindGameObjectsWithTag("TagName");`
  - 图形界面拖拽：
    - 在你的脚本中定义一个公共（`public`）变量，这样它就会在图形面板中出现。如`public GameObject targetObject;`
    - 将这个脚本拖拽到一个GameObject上，或者直接在GameObject上添加这个脚本作为组件。
    - 直接从窗口中直接拖拽一个GameObject到相应属性上，即可完成绑定。
  
- 通过对象可以直接获得属性`Transform objTransform = myObject.transform;`
- 激活对象
  - `gameObject.SetActive(false);`
  - 获取状态
    - `activeSelf`直接返回对象的激活状态
    - `activelnHierarchy`检查是否是真的活跃（如果任何父对象被停用，则在场景中实际上是不活跃的）
- 删除对象`Destroy(gameObject);`
  - 同样也可以放入组件，删除组件

### 组件

- 获取组件
  - 获取对象上的组件`MyComponent component = myObject.GetComponent<MyComponent>();`
    - 如果一个脚本挂载到了对象上，可以更简便的获取改对象的组件`GetComponent<Renderer>()`，也可以使用`this`获取自身的属性（这里的this就是指向被绑定的对象）
  - 获取子对象上的组件`MyComponent childComponent = myObject.GetComponentInChildren<MyComponent>();`
    - 全部子对象：`MyComponent[] allChildComponents = myObject.GetComponentsInChildren<MyComponent>();`
  - 父对象：`MyComponent parentComponent = myObject.GetComponentInParent<MyComponent>();`
- 动态添加组件`MyComponent newComponent = myObject.AddComponent<MyComponent>();`
- 启用和禁用组件：设置`enabled`属性
- 可以直接使用`.`来访问脚本的属性（包含脚本组件）

#### 碰撞器

- 设置为触发器：不会产生物理碰撞
  - `OnTriggerEnter`、`OnTriggerStay`和`OnTriggerExit`等事件就会被触发。
```c#
using UnityEngine;

public class Cannon : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Enemy"))
        {
            // 敌人进入了攻击范围
            Debug.Log("Enemy in range!");
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Enemy"))
        {
            // 敌人离开了攻击范围
            Debug.Log("Enemy out of range!");
        }
    }
}

```

- 使用标签标识
  - 在Unity的主界面的顶部，点击`Edit`。
  - 从下拉菜单中选择`Project Settings`。
  - 在打开的窗口中选择`Tags and Layers`。
  - 在Tags部分，点击`+`按钮添加一个新的tag，例如"Enemy"。
  - 设定<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231009001609387.png" alt="image-20231009001609387" style="zoom:33%;" />

- 是否发生碰撞的设定
  - 在项目设置中可以全局设定可以放生碰撞的层
  - 在碰撞器组件中可以进行单独自定义设置
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231014161001824.png" alt="image-20231014161001824" style="zoom:33%;" />

- Mesh Colider：
  - 默认条件下会对模型所有的面添加碰撞
  - 开启凸包选项之后则只有模型的凸包（最外层）具有碰撞

- 层级通常用于：摄像机渲染控制、光照控制、物理交互（如是否碰撞）
- 标签通常用于：快速访问对象（筛选），逻辑分组（如敌我识别）

#### Rigidbody

- 

### 脚本文件间交互

- 访问其他类的成员变量
  - 对于public属性，可以直接获取对象再获取脚本组件，使用属性的形式获取

### 预制件prefab

- 创建预制件的克隆体`Instantiate`
  - 要创建一个 Prefab，只需将场景中的游戏物体**拖拽**到 Project 视图中即可。这会创建一个 Prefab 资产，并且场景中的游戏物体现在是该 Prefab 的一个实例。

- 实例化
  - 可以指定位置、角度（省略时在默认位置生成）
```c#
Vector3 position = new Vector3(0, 0, 0);
Quaternion rotation = Quaternion.identity;
GameObject instance = Instantiate(myPrefab, position, rotation);
```
- `Instantiate` 方法的返回值是一个 `Object` 类型。

### 生命周期函数

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231025094712073.png" alt="image-20231025094712073" style="zoom:50%;" />

#### 初始化阶段
- **Awake**
  - 在**加载**包含脚本的游戏对象时调用，无论该对象是否启用。
  - 总是在任何`Start`方法之前被调用。
  - 即使脚本是禁用的，这个方法也会被调用。
  - 初始化变量或状态。配置**不依赖于其他游戏对象**的设置。

- **OnEnable**
  - 当脚本被初始化或者当所在的GameObject被设置为active时调用。在脚本对象被**激活**时调用
  - 这发生在所有对象的 `Awake` 之后、任何对象的 `Start` 之前。
  - 注册事件监听器或**广播消息。开始协程。对外部资源进行订阅或更新状态。**

- **Start**
  - 在**Update之前**的第一个帧中被调用。
  - **仅被调用一次**。
  - 如果 MonoBehaviour 被禁用，则不会被调用。
  - 初始化**依赖于其他对象**的变量或状态。在场景中查找其他游戏对象。设置依赖于场景中其他对象或组件的初始化代码。
#### 更新阶段
- **FixedUpdate**
  - 用于(时间)**固定**的帧率**的更新，与**物理**相关的代码应该放在这里。** 可以保证物理模拟的稳定性
    - 由于物理模拟需要在各种硬件和帧率下保持一致性，使用固定时间间隔可以确保物理模拟的行为是可预测的，不受帧率波动的影响。

- **Update**
  - 每**帧**都被调用。
  - 主要用于普通的游戏逻辑。
  - 获取帧时间 `Time.deltaTime` 

- **LateUpdate**
  - 在每帧在所有 Update 方法**调用后被调用**。
  - 主要用于跟随摄像机的移动、后处理、修正、反馈等操作。
  - 如果你有一个摄像机跟随一个角色，你可能想要确保角色在 `Update()` 中首先移动，然后摄像机在 `LateUpdate()` 中进行更新以**跟随角色**。这确保了无论角色如何移动或如何被其他系统影响，摄像机都能够在该帧结束时准确地跟随它。

#### 渲染阶段
- **`OnPreRender`**：在摄像机开始渲染之前调用
- **`OnRenderObject`**：在所有常规渲染完成后，用于自定义渲染操作。
- **`OnPostRender`**：在摄像机完成渲染后调用。
- **`OnGUI`**：用于渲染和处理GUI事件。每帧可能被调用多次。

#### 禁用或销毁
- **OnDisable**
  - 当脚本被禁用或 GameObject 变为非 active 时调用。

- **OnDestroy**
  - 当 MonoBehaviour 将被销毁、或者关联的 GameObject 被销毁时调用。
#### 补充
- 子类的会覆盖掉父类，也就是说只会执行子类的`Update`等函数
  - 可以使用`base.Update()`手动调用
### 物理系统

- 物理材质
  - 物理材质定义了物体表面的摩擦和反弹特性。
- 重力及空气阻力
  - **gravity**：定义在 `Physics` 菜单中，全局影响所有 Rigidbody 的重力方向和大小。
  - **drag** 和 **angularDrag**：定义 Rigidbody 的空气阻力和角阻力。
- 关节
  - unity 提供了一系列的关节组件（如 Hinge Joint, Spring Joint 等）允许物体之间有约束关系。

#### 基本组件

- 物理组件：`Rigidbody`使游戏物体受物理引擎控制
  - 要使一个对象受物理系统影响需要添加该组件
- 碰撞：`Colider`，有多种碰撞器（形状）
  - 碰撞检测
    - **OnCollisionEnter**, **OnCollisionStay**, **OnCollisionExit**：当 Rigidbody 与其他物体发生碰撞时触发的事件。
    - **OnTriggerEnter**, **OnTriggerStay**, **OnTriggerExit**：当 Collider 设置为 "Trigger" 并与其他 Collider 重叠时触发的事件。
![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20250101215255.png)

#### 常用方法

- **AddForce(Vector3 force)**：向 Rigidbody 添加力。例如，向前添加力：`rb.AddForce(transform.forward * forceAmount);`
- **AddTorque(Vector3 torque)**：向 Rigidbody 添加扭矩，使其旋转。
- **velocity**：直接设置或获取 Rigidbody 的速度。
- **angularVelocity**：直接设置或获取 Rigidbody 的角速度。
- **isKinematic**：如果设置为 `true`，Rigidbody 将不受物理引擎控制，但仍可以与其他非 Kinematic Rigidbody 交互。
- **useGravity**：决定物体是否受重力影响。

### 矢量数学

#### 基本

- 左手坐标系
  - ![image-20231008121916368](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231008121916368.png)

- 向量表示
  - `Vector3 vec = new Vector3(x, y, z);`

  - 常量
```c#
       Vector3 right = Vector3.right;    // (1, 0, 0)
       Vector3 up = Vector3.up;          // (0, 1, 0)
       Vector3 forward = Vector3.forward; // (0, 0, 1)
       Vector3 zero = Vector3.zero;      // (0, 0, 0)
       Vector3 one = Vector3.one;        // (1, 1, 1)
       
```
  - 此外还有 `Vector2`

- 方法
  - 获取模`Vector3.normalized`
  - 计算`Vector3.Dot(a, b)`, `Vector3.Cross(a, b)`
  - 距离`Vector3.Distance(a, b)`
- 获取坐标`transform.position`

#### 坐标变换

- 平移
  - 直接加上一个向量`transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);`

- 旋转
  - 指定向量作为方向，以及旋转的角度`transform.Rotate(Vector3.up, turnSpeed * Time.deltaTime);`

- LookAt
  - 使一个游戏对象的**变换组件**面向另一个游戏对象的**变换组件**
  - 让摄像机指向一个对象
```c#
using UnityEngine;
using System.Collections;

public class CameraLookAt : MonoBehaviour
{
    public Transform target;

    void Update ()
    {
        transform.LookAt(target);
    }
}
```
- 可以在图形界面拖拽绑定对象组件

- 使用四元数管理旋转
  - 允许连续的旋转运算而不失稳定性。使用欧拉角旋转物体时，可能会遇到一个称为“万向锁”的问题，其中某个旋转轴“消失”了。通过使用四元数，可以避免这种情况。
  - 万向节锁：先围绕 Z 轴旋转90度，然后尝试围绕 Y 轴旋转，这种情况下 X 轴会和 Z 轴对齐，导致原本独立的旋转轴合并（此时 Z 轴与 X 轴重合，旋转剩下的 X 与之前的 Z 等价）即损失了一个自由度
- 操作
  - **单位四元数**：表示没有旋转或旋转360°的四元数。
  - **四元数乘法**：你可以通过乘法组合两个四元数，从而组合两个旋转。
  - **四元数的逆**：逆旋转。
  - **四元数的插值**：例如，`Quaternion.Lerp`和`Quaternion.Slerp`可以用于在两个旋转之间平滑过渡。

- 创建
	- `Quaternion.Euler(x, y, z)`：从欧拉角创建四元数。
	- `Quaternion.AngleAxis(angle, axis)`：在给定的轴上创建一个角度的旋转。
	- `Quaternion.LookRotation(forward, up)`：查看一个方向并指定向上的方向。
	- `Quaternion.identity`：这是一个单位四元数，表示无旋转。

- 应用
	- 物体旋转：`transform.rotation = Quaternion.Euler(45, 0, 0);`
```c#
      //面向物体
      Vector3 directionToTarget = target.position - transform.position;
      transform.rotation = Quaternion.LookRotation(directionToTarget);
```

### 线性插值

- `float result = Mathf.Lerp (3f, 5f, 0.5f);`会得到4，参数为：起点终点百分比
- 此外也有`Color.Lerp 和 Vector3.Lerp`等不同的插值函数

- 实现灯光的渐变插值
```c#
void Update ()
{
    light.intensity = Mathf.Lerp(light.intensity, 8f, 0.5f * Time.deltaTime);
}
```

#### Slerp四元数插值

- lerp 会考虑四元数的球形几何特性，从而提供更自然和正确的旋转插值。Slerp 的速度在开始和结束时会减慢，这使得旋转看起来更自然。
```c#
Quaternion startRotation = Quaternion.Euler(0, 0, 0);
Quaternion endRotation = Quaternion.Euler(0, 90, 0);
float t = 0.5f; // t 可以是时间或其他变量，它决定了插值的位置：0 是开始旋转，1 是结束旋转。

transform.rotation = Quaternion.Slerp(startRotation, endRotation, t*Time.deltaTime);
```

### 操作输入

#### 键盘

- `Input.GetKey(KeyCode)`: 在键被按下的每一帧中返回`true`。
- `Input.GetKeyDown(KeyCode)`: 在键第一次被按下的那一帧返回`true`。
- `Input.GetKeyUp(KeyCode)`: 在键释放的那一帧返回`true`。
- `KeyCode`
  - 对于字母：`KeyCode.W`

- 传统方式就是在 Update 中进行轮询
```c#
void Update() {
    if (Input.GetKeyDown(KeyCode.Space)) {
        Debug.Log("Space key was pressed.");
    }

    float horizontal = Input.GetAxis("Horizontal");
    float vertical = Input.GetAxis("Vertical");
}
```

#### 鼠标

- `Input.GetMouseButton(int)`: 在按钮被按下的每一帧中返回`true`。
- `Input.GetMouseButtonDown(int)`: 在按钮第一次被按下的那一帧返回`true`。
- `Input.GetMouseButtonUp(int)`: 在按钮释放的那一帧返回`true`。
- 获取鼠标的位置`Input.mousePosition`: 返回一个屏幕上的鼠标位置的`Vector3`。
- 获取滚轮状态``Input.mouseScrollDelta`: 返回一个表示鼠标滚轮滚动的`Vector2`。`

#### 按钮

- 通过抽象的“虚拟”按钮进行输入，允许代码与实际的物理输入设备抽象出来，从而更容易地支持多种控制方案和设备。
- 按钮的设置
  - 打开Unity编辑器。
  - 选择Edit > Project Settings > Input。
  - 在“Input Manager”窗口中，你会看到一个名为“Axes”的列表。每个轴实际上可以作为一个按钮使用。例如，默认的设置中已经有一个名为“Jump”的按钮，它映射到了键盘的空格键。
- 输入检测：使用`Input.GetButton()`, `Input.GetButtonDown()`, 和 `Input.GetButtonUp()`。

#### GetAxis

- 线性输入（如摇杆、线性扳机），一个-1~1范围的值，可以实现更加平滑的移动
- 返回平滑值（浮点数）`Input.GetAxis()`
- 返回-1、0、1：`Input.GetAxisRaw()`
- 常用名称
  - "Horizontal": 通常映射到左右移动。
  - "Vertical": 通常映射到上下移动。
  - "Mouse X": 鼠标在X轴上的移动。
  - "Mouse Y": 鼠标在Y轴上的移动。
  - 在Unity的Input Manager中，可以自定义轴或修改现有轴的配置。（Edit > Project Settings > Input。）
- **敏感度和死区**: 在 Input Manager 中，还可以为每个轴设置敏感度和死区，这在处理游戏手柄摇杆输入时特别有用，可以帮助消除不希望的微小移动
#### input system 新输入系统
- **多设备支持**：新输入系统支持从多种输入设备接收输入，如键盘、鼠标、游戏手柄、触摸屏等，甚至可以处理更复杂的设备如 VR 控制器。
- **输入动作**：用户可以定义输入动作（Input Actions），这些动作抽象了具体的键位或控制器按钮，允许开发者基于动作而不是具体的按键或按钮编程，这有助于提高代码的可移植性和易用性。
- **事件驱动**：新系统采用事件驱动模型，允许开发者订阅并响应特定的输入事件，而不是在每个更新周期中检查输入状态。
```csharp
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerController : MonoBehaviour
{
    public InputActionAsset inputActions; // 在Inspector中分配

    private InputAction moveAction;

    private void Awake()
    {
        // 获取动作
        var gameplayActionMap = inputActions.FindActionMap("Gameplay");
        moveAction = gameplayActionMap.FindAction("Move");

        // 启用动作
        moveAction.Enable();

        // 订阅事件
        moveAction.performed += OnMovePerformed;
    }

    private void OnMovePerformed(InputAction.CallbackContext context)
    {
        Vector2 moveInput = context.ReadValue<Vector2>();
        // 处理移动逻辑
    }

    private void OnDestroy()
    {
        // 清理
        moveAction.Disable();
    }
}

```
### 事件&广播

- 事件本身是一种特殊的委托（多播）
```c#
//通过委托定义事件格式
public delegate void MyEventHandler(string message);
//声明事件
public event MyEventHandler MyEvent;

```
- 可以讲一个参数匹配的方法赋值给委托，即相当于用这个方法实现了这个委托

- 触发事件`MyEvent()`
- 订阅事件`someInstance.MyEvent += MyHandlerMethod;`
  - 注意一定还得取消注册事件`someInstance.MyEvent -= MyHandlerMethod;`
  - 通常写在生命周期函数中
```c#
      private void OnEnable()
      {
          someEvent += MyEventHandler;
      }
      
      private void OnDisable()
      {
          someEvent -= MyEventHandler;
      }
  //广播
  someEvent?.Invoke();
```

### 补充

- 延时执行函数`invoke`
  - 只能调用不需要参数并且无返回值的函数
  - `Invoke ("函数名", time);`
  - 周期调用`InvokeRepeating(函数名", 初次延时, 周期调用间隔);`

- 属性标志
  - Range限制`Inspector`窗口中变量的取值范围。
```c#
[Range(0, 10)]
public int myNumber;
```

- ExecuteInEditMode将此特性放在MonoBehaviour派生的类之前时，该类中的代码**将在编辑模式下运行**，而不是仅在播放模式下。
```c#
[ExecuteInEditMode]
public class MyScript : MonoBehaviour
{
    void Update()
    {
        // 这个代码将在编辑器模式下每帧执行
    }
}
```
- 存在副作用：使用 `ExecuteInEditMode` 可能会导致场景数据在编辑模式下被更改，如果您没有注意到这些更改并保存了场景，这可能会导致您丢失某些所需的配置或数据。（永久改变）

## 高级
### 文件系统
#### 持久化存储
- playerprefs：存储简单的少量数据，不适用于大量数据或复杂数据结构（类似简答键值对）
```c#
// 保存数据
PlayerPrefs.SetInt("Level", 10);
PlayerPrefs.SetFloat("Health", 75.0f);
PlayerPrefs.SetString("PlayerName", "Alice");
PlayerPrefs.Save(); // 确保数据写入

// 加载数据
int level = PlayerPrefs.GetInt("Level", 1); // 默认值为1
float health = PlayerPrefs.GetFloat("Health", 100.0f); // 默认值为100.0f
string playerName = PlayerPrefs.GetString("PlayerName", "DefaultName"); // 默认值为DefaultName

```

- 文件存储（JSON，XML，Binary）
	- Unity 支持 JSON 和 XML 的**序列化和反序列化**，也可以使用二进制格式存储数据以提高效率和安全性。
```c#
[System.Serializable]
public class GameData
{
    public int level;
    public float health;
    public string playerName;
}

// 保存数据
GameData data = new GameData { level = 10, health = 75.0f, playerName = "Alice" };
string json = JsonUtility.ToJson(data);
System.IO.File.WriteAllText(Application.persistentDataPath + "/savefile.json", json);

// 加载数据
string loadedJson = System.IO.File.ReadAllText(Application.persistentDataPath + "/savefile.json");
GameData loadedData = JsonUtility.FromJson<GameData>(loadedJson);

```

- SQLite 数据库
	- 对于需要管理大量数据或复杂查询的游戏，使用 SQLite 数据库是一个好选择。Unity 可以通过第三方库（如 SQLite4Unity3d）来集成 SQLite 数据库。
#### 序列化与反序列化
- 对象序列化是指将对象的状态信息转换成**可存储或可传输的形式**（如二进制流、XML、JSON 等格式），以便在需要时（如存储到文件、发送到另一台机器等）能够重建对象。
	- 持久化存储
	- 网络通信
	- 深拷贝
- 可以序列化的对象
```c#
[Serializable]
public class Player {
    public string Name;
    public int Score;
    [NonSerialized]
    private int secretValue; // 这个字段不会被序列化
}
```
- 使用 JSON 实现（兼容性好，适用于网络传输）
```c#
using System.Text.Json; // .NET Core 3.0 以上版本引入的命名空间

public class Player
{
    public string Name { get; set; }
    public int Score { get; set; }
}

// 序列化
Player player = new Player { Name = "Alice", Score = 100 };
string jsonString = JsonSerializer.Serialize(player);

// 反序列化
Player deserializedPlayer = JsonSerializer.Deserialize<Player>(jsonString);

```
- 使用二进制实现（效率更高，适合用于本地存储）
```c#
// 序列化
Player player = new Player { Name = "Alice", Score = 100 };
BinaryFormatter formatter = new BinaryFormatter();
using (Stream stream = new FileStream("player.dat", FileMode.Create, FileAccess.Write, FileShare.None))
{
    formatter.Serialize(stream, player);
}

// 反序列化
using (Stream stream = new FileStream("player.dat", FileMode.Open, FileAccess.Read, FileShare.Read))
{
    Player deserializedPlayer = (Player)formatter.Deserialize(stream);
}
```
### 物理系统

#### 射线

- 用于检测是否有遮挡、从摄像机发射射线到平面获取点击位置
- 可以设置屏蔽吗，屏蔽&指定图层
```c#
public static bool RayTrigger(Vector3 from, GameObject to , string tag)
    {
        Vector3 rayOrigin = from;
        Vector3 rayDirection = to.transform.position - from;
        float rayDistance = rayDirection.magnitude;
        RaycastHit hit;
        int layerMask = ~(1 << LayerMask.NameToLayer(tag));//屏蔽码
        // 发送射线
        if (Physics.Raycast(rayOrigin, rayDirection.normalized, out hit, rayDistance, layerMask))
        {
            // 如果射线只碰撞到敌方或没有碰撞到其他物体
            if (hit.collider.gameObject == to)
            {
                return true;
            }
        }
        return false;
    }
```

- 获得点击点的坐标`hit.point`

### 摄像机

#### 多摄像机渲染

- 可以用于调整图层的渲染顺序，通过设置摄像机的深度，可以设置摄像机的渲染顺序，此外再指定摄像机渲染的图层就可以实现分层渲染
- 混合模式
  - **Skybox**：摄像机会先渲染天空盒，然后在其上渲染其他物体。
  - **Solid Color**：摄像机会用一个固定颜色（可以在"Background"属性中设置）清除渲染目标，然后在这个背景上渲染物体。
  - **Depth Only**：摄像机不会清除之前的任何内容，而只会渲染新的内容。这意味着摄像机只更新深度缓冲区，所以渲染的物体会根据深度信息覆盖之前的内容。
  - **Don't Clear**：摄像机不会清除之前的内容，也不更新深度缓冲区，新的渲染内容将直接绘制在之前的内容上。

### 粒子系统

- 
### 灯光
- unity 中的灯光种类
	- 方向光：从犯远方发出的平行光，如太阳光，没有位置只有方向
	- 点光源：从一个点向所有方向均匀发光，随着距离减弱，模拟灯泡火把等局部光源
	- 聚光灯：从一个点放出光纤，在特定角度内形成锥形照明区域，随距离减弱，如手电筒、舞台聚光灯
	- 面光源：从矩形、圆形区域发出光纤，柔和且均匀，模拟窗户光线等大面积光源，常用于室内
	- 环境光：影响整个场景的光照，提供基础光照
### 对象池
- 对象池通过预先创建和维护一定数量的对象实例来工作。这些对象在需要时被激活，不需要时被禁用，而不是被销毁。这样，当游戏需要新对象时，可以**直接从池中获取一个已经存在的禁用对象**，激活并使用它，而不是每次需要时都创建新的对象。
- 基本过程
	- 创建池管理器：创建一个管理对象池的类，用于处理对象的请求和回收。
	- 预先实例化对象：在游戏开始或对象池初始化时，根据需要预先创建足够数量的对象实例。
	- 管理对象的获取与返回：提供方法来让其他游戏组件请求对象和返回对象。获取对象时，检查池中是否有可用的禁用对象；返回对象时，禁用该对象并将其放回池中。（注意在回收时或启用时进行初始化，因为会带有原先的属性数据）
- 优点
	- **性能提升**：减少运行时的实例化和销毁操作，降低**内存分配和回收的压力**，从而提高性能。
	- **内存使用优化**：通过重复使用对象减少内存消耗，避免频繁的内存分配和**碎片化**。
```csharp
using System.Collections.Generic;
using UnityEngine;

public class ObjectPool : MonoBehaviour
{
    public GameObject prefab; // 预设对象
    public int poolSize = 10; // 池的初始大小
    private Queue<GameObject> objectPool = new Queue<GameObject>(); // 使用队列存储池中的对象

    void Start()
    {
        // 初始化池
        for (int i = 0; i < poolSize; i++)
        {
            GameObject obj = Instantiate(prefab); // 创建对象
            obj.SetActive(false); // 禁用对象
            objectPool.Enqueue(obj); // 将对象添加到池中
        }
    }

    // 从池中获取对象
    public GameObject GetObject()
    {
        if (objectPool.Count > 0)
        {
            GameObject obj = objectPool.Dequeue(); // 获取对象
            obj.SetActive(true); // 激活对象
            return obj;
        }
        else
        {
            // 池为空，根据需要可以扩展池
            GameObject obj = Instantiate(prefab);
            obj.SetActive(true);
            return obj;
        }
    }

    // 将对象返回池中
    public void ReturnObject(GameObject obj)
    {
        obj.SetActive(false); // 禁用对象
        objectPool.Enqueue(obj); // 将对象放回池中
    }
}

```
## 杂项

- 打印调试`Debug.Log()`

### 摄像机动画

- [[Unity Cinemachine & Timeline 制作镜头动画](https://zhuanlan.zhihu.com/p/104728350)
- brain组件放置到主摄像机上，创建虚拟摄像机（虚拟摄像机本质上是作为主摄像机上进行移动，即可以被附身）
- 使用<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231027173210290.png" alt="image-20231027173210290" style="zoom:33%;" />
  - 在脚本中进行播放
  - 可以使用timeline文件存储动画，左侧拖入主摄像机，右侧剪辑虚拟摄像机，即不同时间使用不同的虚拟摄像机作为显示

### MonoBehaviour

- `MonoBehaviour` 是Unity提供的一个基类，它允许为游戏对象创建行为脚本。
  - **作为组件附加到游戏对象上**：只有继承自`MonoBehaviour`的脚本才可以直接附加到游戏对象。
  - **利用Unity生命周期方法**：例如`Start()`, `Update()`, `Awake()`, `FixedUpdate()`, `OnCollisionEnter()`, 等等。这些方法在特定的时刻由Unity自动调用，允许开发者编写游戏逻辑。
  - **访问其他游戏对象和组件**：`MonoBehaviour`提供了方法如`GetComponent<T>()`，允许脚本与其所在的或其他游戏对象的组件交互。
  - **与Unity编辑器集成**：通过`MonoBehaviour`，你可以使用诸如`[SerializeField]`、`[HideInInspector]`这样的属性标签，来定制组件在Inspector视图中的显示。
  - **使用协程 (Coroutines)**：`MonoBehaviour`允许使用`StartCoroutine`方法，这使得你可以编写协程来执行延迟、重复或基于时间的任务，而不必完全依赖`Update`方法。
### 调试
- `OnDrawGizmos` 绘制只在编辑器中可见的内容，用于表示范围等可视化
### 版本控制PlasticSCM

#### 分支与合并

- 从主线创建新分支
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231008195802790.png" alt="image-20231008195802790" style="zoom:33%;" />
- 分支切换
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231008200041156.png" alt="image-20231008200041156" style="zoom:33%;" />
- 合并分支
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231008200524733.png" alt="image-20231008200524733" style="zoom:33%;" />
- 冲突处理
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231008201857186.png" alt="image-20231008201857186" style="zoom:33%;" />
  - 对于二进制文件冲突：Unity 提供了一个叫做 Smart Merge（也称为 UnityYAMLMerge）的工具，专门用来解决像 Prefabs 和 Scenes 这样的 YAML 文件冲突。

### 游戏构建

- 

### 教程

- 快速上手：[Unity 10分钟快速入门 #U3D #Unity3D](https://www.bilibili.com/video/BV1PL4y1e7hy?vd_source=acab52c21ffa9e9c57428e615e773279)
- 基本界面&功能&系统讲解：https://b23.tv/VUwhIj5
- unity脚本编程：
  - [C#初级编程 | Unity 中文课堂 (u3d.cn)](https://learn.u3d.cn/tutorial/beginner-gameplay-scripting)
  - [C# 中级编程 | Unity 中文课堂 (u3d.cn)](https://learn.u3d.cn/tutorial/intermediate-gameplay-scripting)
- 综合项目：[3D RPG Course | Core 核心功能 | Unity 中文课堂 (u3d.cn)](https://learn.u3d.cn/tutorial/3drpg-core?chapterId=63562b29edca72001f21d19d#)
- [文档版本 - Unity 手册](https://docs.unity.cn/cn/2022.3/Manual/ManualVersions.html)

### 配置

- 统一unity editor版本：**2022.3.8f1c1**
- editor更换中文(hub更换中文直接设置里改)
  - [https://new-translate.unity3d.jp/v1/live/54/](http://jump.bdimg.com/safecheck/index?url=rN3wPs8te/rPoP5v45JBTu4czwulJGOOaj5g08pyEDegSqfiflO2vx91sG5rwyFyv/fBB5q9WQqltJi6QngliCrc+wPGJ+uFg6bTGKqiExMgZ1h2ZCQ4UKn2oQ7N0q40l40itacg0FRU8hR5zalJyfYTmn8eAnOoVfdkwJqFldMwPGbuJnYGNA==){version}/zh-hans 把{version}换成你的版本，比如说如果你的是2022.3.8f1c1那就填**2022.3.** 其他同理。下完之后放到 Unity 安装目录下 Data 里的 Localization 文件夹里，如果没有就新建一个。放完之后在界面左上角找到 Edit，然后在下面找到 preferences 选项，找到 language，在 editor language 那一栏选简体中文。

### 文件结构

1. **Assets**：所有的游戏资源都放在这里。
   - **Scenes**：存放所有场景文件。
   - **Scripts**：存放所有C#脚本。
   - **Prefabs**：预制体文件，如常用的游戏对象或UI元素。
   - **Materials**：存放材质和材质球。
   - **Textures**：存放所有的纹理和图片资源。
   - **Models**：存放3D模型，如.obj或.fbx文件。
   - **Animations**：存放动画及相关的资源。
   - **Audio**：音效和音乐文件。
     - **Music**：背景音乐文件。
     - **SFX**：音效文件。
   - **Shaders**：自定义的shader文件。
   - **Fonts**：字体文件。
   - **Plugins**：外部插件和库。
   - **Resources**：需要动态加载的资源。
   - **Editor**：与Unity编辑器相关的脚本和工具。
   - **Gizmos**：自定义的编辑器图标。
2. **Packages**：存放Unity Package Manager使用的包。
3. **ProjectSettings**：存放Unity项目的设置文件。这些设置包括输入、标签、图层、物理、渲染和其他全局设置。
4. **UserSettings**：存放某些用户特定的设置。

### 问题及解决

- 移动碰撞后不正常
  - 使用物理刚体线性速度代替直接设置transform

```c#
public class InputMove : MonoBehaviour
{
    private float _speed;
    private Rigidbody rb;

    void Start()
    {
        _speed = GetComponent<Hero>().moveSpeed;
        rb = GetComponent<Rigidbody>();
    }

    void FixedUpdate() // 使用FixedUpdate而不是Update处理物理相关操作
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        Vector3 movement = new Vector3(moveHorizontal, 0.0f, moveVertical);
        rb.velocity = movement * _speed;
    }
}
```

### 静态脚本

- 用于进行一些批量化处理及操作
- 将路径下所有网格设置为可以读取
```c#
using UnityEngine;
using UnityEditor;
using System.Collections.Generic;

public class MeshReadWriteSetter
{
    [MenuItem("Tools/Set Meshes to Read/Write Enabled")]
    public static void SetMeshesToReadWriteEnabled()
    {
        string folder = "Assets/GameMain/Packages"; // 替换 "YourFolderPath" 为你的文件夹路径

        // 获取文件夹中的所有模型
        string[] guids = AssetDatabase.FindAssets("t:Model", new[] { folder });
        List<ModelImporter> importersToModify = new List<ModelImporter>();

        foreach (string guid in guids)
        {
            string assetPath = AssetDatabase.GUIDToAssetPath(guid);
            ModelImporter importer = AssetImporter.GetAtPath(assetPath) as ModelImporter;

            if (importer && !importer.isReadable)
            {
                importersToModify.Add(importer);
            }
        }

        // 设置每个模型为可读/写
        foreach (var importer in importersToModify)
        {
            importer.isReadable = true;
            importer.SaveAndReimport();
        }

        Debug.Log($"Set {importersToModify.Count} meshes to Read/Write Enabled.");
    }
}
```

- 为所有子对象添加mesh碰撞器

```c#
using UnityEngine;
using UnityEditor;

public static class MeshColliderEditorUtility
{
    [MenuItem("GameObject/Add MeshCollider to Children", false, 30)]
    public static void AddMeshColliders()
    {
        GameObject selectedObj = Selection.activeGameObject;

        if (selectedObj == null)
        {
            Debug.LogWarning("No object selected. Please select an object first.");
            return;
        }

        RecursiveAddMeshCollider(selectedObj);
        Debug.Log("MeshColliders added to " + selectedObj.name + " and its children.");
    }

    private static void RecursiveAddMeshCollider(GameObject obj)
    {
        if (obj.GetComponent<MeshFilter>() && !obj.GetComponent<MeshCollider>())
        {
            obj.AddComponent<MeshCollider>();
        }

        foreach (Transform child in obj.transform)
        {
            RecursiveAddMeshCollider(child.gameObject);
        }
    }
}
```

## 常用插件
### inputsystem
- 新输入系统
### probuilder
- 创建、编辑几何体
- 可以用于快速创建关卡白盒