>教程地址：[主页 - LearnOpenGL CN](https://learnopengl-cn.github.io/)
>
>代码：[LearnOpenGL/src at master · JoeyDeVries/LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src)

## 常用库

### GLFW
- 用于**窗口管理、处理输入**、创建 opengl 上下文等
- GLFW 封装了底层窗口系统的实现，提供了跨平台的接口
- GLFW 提供了键盘、鼠标和游戏手柄的输入支持
- GLFW 支持 Windows、macOS 和 Linux，帮助你实现一次编写、跨平台运行的代码
#### 基本使用
- 参数配置：以键值对的形式进行配置
	- 如配置版本号位 `3.3`
```c
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
```

- 创建一个简单的窗口对象并设置为上下文
```c
GLFWwindow* window = glfwCreateWindow(800, 600,"LearnOpenGL", NULL, NULL);
glfwMakeContextCurrent(window);
```


- 注册回调，当窗口大小调整时自动调整视口的大小
```c
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
```

- 最简答的事件循环
```c
while(!glfwWindowShouldClose(window))
{
    glfwSwapBuffers(window);
    glfwPollEvents();    
}
```
- glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW**是否被要求退出**
- glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数。
- glfwSwapBuffers函数会**交换**颜色缓冲，它在这一迭代中被用来**绘制**，并且将会作为输出显示在屏幕上。
	- 双缓冲：下一帧完全渲染完之后再进行交换，避免由于渲染过程造成闪烁
- 在循环中可以进行输入检查控制
 ```c
 void processInput(GLFWwindow* window)
  {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
          glfwSetWindowShouldClose(window, true);
  } 
 ```

- 完整的代码
```c
#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //参数设置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //创建上下文
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //板顶函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清除用的颜色
        glClear(GL_COLOR_BUFFER_BIT);
        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //释放资源
    glfwTerminate();

    return 0;
}
```
- glClear 用于清除缓冲，可选参数如：GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT 用于清除不同的数据
### GLAD
- 是一个 **OpenGL 扩展加载器**，一个基于 OpenGL 函数指针的加载库，用于加载不同 OpenGL 版本的函数
	- OpenGL 本身并不包含所有的函数定义和实现，因此你需要一个加载器来动态加载这些函数地址
- 由于不同操作系统和驱动支持不同版本的 opengl，因此不能直接调用这些函数，而是通过函数加载器来获取这些函数的地址

- 加载函数 
```c
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
}
```
- **函数指针的地址**只有在创建了 OpenGL 上下文后才能正确获取。GLFW 负责初始化和创建这个 OpenGL 上下文，这是 GLAD 开始加载 OpenGL 函数的前提条件。(提供了获取函数地址的方法)
- GLAD 就可以通过 `glfwGetProcAddress` 动态加载所有 OpenGL 函数，而不需要开发者关心平台差异。
- 基本流程就是：**使用 GLFW 创建 OpenGL 上下文->使用 GLAD 加载 OpenGL 函数->程序可以调用 OpenGL 函数**

### stb_image

- 可以使用`stb_image.h`[下载](https://github.com/nothings/stb/blob/master/stb_image.h)来进行文件图像加载，加载为char*字节量

### GLM

- 用于opengl的数学库
- GLM库从0.9.9版本起，默认会将矩阵类型初始化为一个零矩阵（所有元素均为0），而不是单位矩阵
  - 需要初始化为单位矩阵`glm::mat4 mat = glm::mat4(1.0f)`
  - `glm` 是一个头文件库，它不生成动态链接库（.dll）或静态库（.lib）,可以直接在项目中包含 `glm` 的头文件来使用它。
- 常用头文件内容

```c
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

- 可以用glm快速**创建各种变换矩阵**

```c
glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
// 之后将不再进行提示
glm::mat4 trans;
trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
vec = trans * vec;
//glm::radians(90.0f)将角度转化为弧度
//glm::vec3(0.0, 0.0, 1.0)指定旋转方向
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
```

- 用同一个矩阵`trans`可以进行不同的变化，glm会自动将变化乘到`trans`上，最终用`trans`乘以目标矩阵就可以实现所有变化（注意变化**倒序**执行，上面就是先缩放再旋转）



- 将变化矩阵传递给着色器
  - `uniform mat4 transform;`就可以传递一个四维矩阵

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
```

```c
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
```

- 1表示要传递的矩阵数目
- GL_FALSE表示是否需要转置矩阵
- value_ptr将glm矩阵转化为opengl可以接受的

# opengl 基础

## 工作流程

- [环境配置](https://learnopengl-cn.github.io/01 Getting started/02 Creating a window/)

- 几个重要概念
  - 顶点数组对象：Vertex Array Object，**VAO**
  - 顶点缓冲对象：Vertex Buffer Object，**VBO**
  - 元素缓冲对象：Element Buffer Object，**EBO** 或 索引缓冲对象 Index Buffer Object，IBO

- 渲染管线接受一组 3 D 坐标，最终转化为屏幕上的 2 D 画面
- 渲染管线包含一系列**着色器**，流水线处理数据，opengl 中的着色器使用 GLSL 语言
![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241104153939.png)
- **图元**用于指示 opengl 如何处理输入，如把一系列点绘制成三角形？线？等。即传递绘制指令，如 `GL_POINTS、GL_TRIANGLES、GL_LINE_STRIP`

基本流程
- **顶点着色器**接受单独的顶点作为输入，将 3 D 坐标进行转化(比如转换到 opengl 的可视区域)，并对顶点的属性进行一些基本处理
- **几何着色器**接受顶点着色器的输出，通过输入的顶点形成图元
- **图元装配**阶段将预处理的顶点装配成图元的形状
- **片段着色器**就散像素的颜色（结合光照等信息）
- **测试与混合阶段**进行深度测试，以及不透明度的混合

- opengl 中至少要配置顶点着色器和判断着色器
- opengl 只处理-1~1 立方范围内的信息
- 使用 GLSL 编写着色器，编译之后就可以在程序中使用



### 顶点着色器

- 创建并编译着色器

```c
//着色器代码
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
//创建点着色器，同样用id表示
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
//传入并编译着色器（要编译的着色器，字符串树木，字符参数）
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

- 检查编译错误并输出错误信息

```c
int  success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

### 片段着色器

- 创建与编译与点着色器同理

```c
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

### 链接着色器

- 将编译好的着色器对象**链接**到用于渲染的**程序对象**

```c
//创建着色器
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
//附加编译好的着色器
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
//链接
glLinkProgram(shaderProgram);
//同样可以检查是否成功
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    ...
}
```

- 创建好之后激活**程序对象**`glUseProgram(shaderProgram);`
  - 之后每个着色器调用和渲染调用都会使用这个程序对象
  - 创建之后可以释放之前的着色器对象`glDeleteShader(vertexShader); glDeleteShader(fragmentShader);`

### 设置缓冲区

- 通过 **VBO** **顶点缓冲对象**管理存储顶点数据的内存（由 cpu 发送到 gpu 并存储在**显存**中），之后顶点着色器就能迅速访问显存中的顶点数据
```c
//定义顶点坐标
float vertices[] = {
-0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 0.0f,  0.5f, 0.0f
};
//存储缓冲区对象id
unsigned int VBO;
//生成缓冲区对象并获取id
glGenBuffers(1, &VBO);
//将缓冲对象绑定到上下文，作为数组缓冲区
glBindBuffer(GL_ARRAY_BUFFER, VBO);
//复制数据到缓冲区
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

```
- 复制数据的选项：
	- GL_STATIC_DRAW ：数据不会或几乎不会改变。
	- GL_DYNAMIC_DRAW：数据会被改变很多。
	- GL_STREAM_DRAW ：数据每次绘制时都会改变。
### 链接顶点属性

- 上面的三个点以float来存储
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241104202631131.png" alt="image-20241104202631131" style="zoom: 50%;" />
- 指出如何来解析顶点数据`glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);`
  - `0`表示顶点属性所在的位置（对应编译器中的位置`location=0`）
  - `3`表示参数类型的大小（由几个值组成），即Vec3
  - `GL_FLOAT`制定参数的类型
  - `GL_FALSE`表示是否要进行标准化（0~1）映射
  - `3 * sizeof(float)`表示连续的属性之间的存储间隔，为0时由opengl自动决定（连续紧密排列）
  - `(void*)0`表示数据在缓冲中的起始位置的偏移量
- 顶点属性是从之前绑定了`GL_ARRAY_BUFFER`的VBO顶点缓冲对象来获取的

- 基本工作流程如下

```c
// 0. 复制顶点数组到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 1. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// 2. 当我们渲染一个物体时要使用着色器程序
glUseProgram(shaderProgram);
// 3. 绘制物体
someOpenGLFunctionThatDrawsOurTriangle();
```

- 当然也可以使用更多的属性，比如位置+颜色
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105132752122.png" alt="image-20241105132752122" style="zoom: 50%;" />

```glsl
// 位置属性
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// 颜色属性
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);
```



#### 顶点数组对象VAO

- 每次都重新进行绑定设置很麻烦，使用**顶点数组对象VAO**可以像顶点缓冲对象那样被绑定，任何随后的**顶点属性调用**都会储存在这个VAO中。
  - VAO是一个容器，用于保存多个VBO的**状态**以及**如何解释**这些VBO中的数据。它记录了**如何将VBO中的数据绑定到顶点属性上。**
    - VAO 可以看作是一个“顶点属性的配置**快照**”。一旦配置好，VAO 会记录下所有与顶点属性相关的状态（例如顶点数据的格式、位置、是否启用等）。
    - VAO 本身不直接存储顶点数据，而是保存了 VBO 和顶点属性之间的关联。当绑定 VAO 时，OpenGL 会自动按照配置好的顶点属性状态读取数据。
    - VAO 允许我们在绘制不同物体时只需绑定不同的 VAO 就能快速切换顶点属性的配置，方便管理多个物体的不同顶点属性。
    - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241107211438589.png" alt="image-20241107211438589" style="zoom: 50%;" />
  - opengl可以通过VAO获取要使用的数据和读取方式
  - 即**VBO提供实际的顶点数据，而VAO则定义了如何使用这些数据。**
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241104204009412.png" alt="image-20241104204009412" style="zoom:50%;" />
- 只需要使用glBindVertexArray绑定VAO
  - 绑定之后，所有与顶点属性的设置操作（例如，绑定VBO、设置顶点属性指针等）都将与这个VAO关联。
  - 之后通过绑定不同的VAO，快速切换不同的顶点数据和状态，而无需重新配置顶点属性指针。

```c
//创建VAO
unsigned int VAO;
glGenVertexArrays(1, &VAO);
//绑定VAO
glBindVertexArray(VAO);
//解除绑定
glBindVertexArray(0);
```

#### 元素缓冲对象EBO

- EBO是一个缓冲区，就像一个顶点缓冲区对象一样，它存储 OpenGL 用来决定要**绘制哪些顶点的索引**（决定点的绘制顺序避免性能浪费，比如两个三角拼接成一个矩形）



- 使用索引来用更少的点进行绘制

```c
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};
//创建EBO
unsigned int EBO;
glGenBuffers(1, &EBO);
//把索引复制到缓冲里
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//使用索引进行绘制
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

- 当目标是GL_ELEMENT_ARRAY_BUFFER的时候，V**AO会储存glBindBuffer的函数调用**，这样使用时就只需要绑定VAO而不再需要绑定EBO
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241104205920696.png" alt="image-20241104205920696" style="zoom: 50%;" />

```c
// ..:: 初始化代码 :: ..
// 1. 绑定顶点数组对象
glBindVertexArray(VAO);
// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
// 4. 设定顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
```

### 完整代码
```cpp
#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //参数设置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //创建上下文
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //板顶函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //存储缓冲区对象id
    unsigned int VBO;
    //生成缓冲区对象并获取id
    glGenBuffers(1, &VBO);
    //将缓冲对象绑定到上下文，作为数组缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制数据到缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    //创建点着色器，同样用id表示
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //传入并编译着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);
        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //释放资源
    glfwTerminate();

    return 0;
}

```
## 着色器
- 一些**运行在 GPU 上**的小程序，着色器的功能比较简单，只是接受输入并产生输出
### GLSL
- 着色器程序通常的结构
```glsl
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

void main()
{
  // 处理输入并进行一些图形操作
  ...
  // 输出处理过的结果到输出变量
  out_variable_name = weird_stuff_we_processed;
}
```
- 能声明的顶点属性是有上限的，它一般由硬件来决定，OpenGL确保至少有16个包含4分量的顶点属性可用
  - 查询`glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);`

- glsl 代码与 c 接近，开始于版本声明，与 opengl 类似，如 3.3 版本对应 330 `#version 330 core`
#### 数据类

- 除了基本数据类型int、float、double、bool等，有两种容器类型：vector和matrix



- 向量可以包含2~4个分量

| 类型    | 含义                            |
| :------ | :------------------------------ |
| `vecn`  | 包含`n`个float分量的默认向量    |
| `bvecn` | 包含`n`个bool分量的向量         |
| `ivecn` | 包含`n`个int分量的向量          |
| `uvecn` | 包含`n`个unsigned int分量的向量 |
| `dvecn` | 包含`n`个double分量的向量       |

- 大部分时候使用vecn即可
- 通过`.x`、`.y`、`.z`和`.w`来获取分量
  - GLSL也允许对颜色使用`rgba`，或是对纹理坐标使用`stpq`访问相同的分量。

```glsl
//灵活的组合运算
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
//创建变量
vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);

```



#### 输入输出

- 使用`in`和`out`关键字来定义输入输出
- 每个着色器使用这两个关键字设定输入和输出，只要一个输出变量与下一个着色器阶段的输入**匹配**，它就会传递下去。
  - **特殊输入**：其中顶点着色器是从缓冲区获取顶点元数据，通过设置`location`来获取CPU配置的属性，如`layout (location = 0)`
  - **特殊输出**：片段着色器的输出为`vec4`(RGBA)
- 点着色器示例

```glsl
#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0

out vec4 vertexColor; // 为片段着色器指定一个颜色输出

void main()
{
    gl_Position = vec4(aPos, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色
}
```

- 片段着色器示例

```glsl
#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）

void main()
{
    FragColor = vertexColor;
}
```

#### uniform

- 实现从CPU传递数据到GPU上的着色器（如从应用程序直接发送一个颜色给片段着色器）
- uniform是全局作用域的，因此在所有着色器程序中都不能重名
  - `uniform vec4 ourColor;`

- 要注意的是激活**新**的着色器程序后，必须要**重新传递所有**的uniform变量

```glsl
//在片段着色器中使用uniform变量
#version 330 core
out vec4 FragColor;
uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量
void main()
{
    FragColor = ourColor;
}
//在程序循环中设置颜色
float timeValue = glfwGetTime();
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//获取uniform变量的位置值
glUseProgram(shaderProgram);
//参数位置+参数(4个)
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
```

> glsl中通常的表示类型的后缀

| 后缀 | 含义                                 |
| :--- | :----------------------------------- |
| `f`  | 函数需要一个float作为它的值          |
| `i`  | 函数需要一个int作为它的值            |
| `ui` | 函数需要一个unsigned int作为它的值   |
| `3f` | 函数需要3个float作为它的值           |
| `fv` | 函数需要一个float向量/数组作为它的值 |

#### 附：着色器管理类

- 从硬盘读取着色器，编译、链接、检查

```c
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif

//创建对象
Shader myShader("path/to/vertex_shader.glsl", "path/to/fragment_shader.glsl");
//激活程序
myShader.use();
//设置Uniform变量
myShader.setFloat("ourColor", 0.0f, 1.0f, 0.0f, 1.0f);
//渲染循环中使用
while (!glfwWindowShouldClose(window))
{
    // 清除屏幕
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 激活着色器
    myShader.use();
    
    // 动态设置 Uniform 颜色
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    myShader.setFloat("ourColor", 0.0f, greenValue, 0.0f, 1.0f); // 颜色随时间变化
    
    // 绘制操作
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // 交换缓冲
    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

### 纹理

- 为了在图像上显示问题，需要给出图像上坐标和纹理文件的对应关系
  - 对于三角形，每个顶点附带一个纹理坐标，用于表示从纹理图像的哪个部分进行采样，其他部分**插值**处理进行填充
  - 纹理（uv）坐标为二维，范围0~1
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105140259126.png" alt="image-20241105140259126" style="zoom: 50%;" />

#### 重复纹理

- 坐标**超出纹理范围**（0~1）时，有如下处理方式
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105140518522.png" alt="image-20241105140518522" style="zoom:67%;" />
  - 重复、镜像、拉伸、特定颜色
- 可以对每个坐标轴分别进行设置

```c
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
```

#### 纹理过滤

- 决定如何将纹理像素映射到纹理坐标（尤其是纹理分辨率较低的情况）
- `GL_NEAREST`临近过滤（默认），OpenGL会选择中心点**最接**近纹理坐标的那个像素作为样本颜色，效果上更加清晰（颗粒感）
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105141329442.png" alt="image-20241105141329442" style="zoom:33%;" />
- GL_LINEAR线性过滤会：于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。产生更加平滑的图像
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105141340563.png" alt="image-20241105141340563" style="zoom:33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105141425518.png" alt="image-20241105141425518" style="zoom:50%;" />

- 对放大、缩小纹理的情况分别设置

```c
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

#### 多级渐远纹理

- 准备一系列分别率不同（1/2每级）的贴图素材，用于不同显示大小的物体
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedmipmaps.png" alt="img" style="zoom: 67%;" />
- 注意：**只能用于纹理被缩小的情况**
- 通过`glGenerateMipmap`进行创建
- 在不同大小纹理图之间还可以制定不同的过滤方式

| 过滤方式                  | 描述                                                         |
| :------------------------ | :----------------------------------------------------------- |
| GL_NEAREST_MIPMAP_NEAREST | 使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样 |
| GL_LINEAR_MIPMAP_NEAREST  | 使用最邻近的多级渐远纹理级别，并使用线性插值进行采样         |
| GL_NEAREST_MIPMAP_LINEAR  | 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样 |
| GL_LINEAR_MIPMAP_LINEAR   | 在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样 |

#### 加载与使用

- 可以使用`stb_image.h`[下载](https://github.com/nothings/stb/blob/master/stb_image.h)来进行文件图像加载

```c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

- 加载图片为字节码

```c
int width, height, nrChannels;//宽度、高度、颜色通道个数
unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
```

- 生成纹理

```c
//创建纹理对象
unsigned int texture;
glGenTextures(1, &texture);
//绑定为当前使用的纹理
glBindTexture(GL_TEXTURE_2D, texture);
//设置环绕、过滤模式
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//绑定读取的数据
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
//释放内存
stbi_image_free(data);
```

- 第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
- 第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
- 第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有`RGB`值，因此我们也把纹理储存为`RGB`值。
- 第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
- 下个参数应该总是被设为`0`（历史遗留的问题）。
- 第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为`char`(byte)数组，我们将会传入对应值。
- 最后一个参数是真正的图像数据。



- 应用纹理，顶点还要给出纹理坐标
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedvertex_attribute_pointer_interleaved_textures.png" alt="img" style="zoom: 67%;" />

```c
float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
//配置VAO属性
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	//uv属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
```



- 着色器中获取纹理

```c
uniform sampler2D ourTexture;

void main()
{
   FragColor = texture(ourTexture, TexCoord)
}
```

- 这个uniform不需要手动传入
- 通过**纹理单元**还可以实现将**多个纹理用于同一个片段着色器**
  - 首先激活纹理单元，然后为纹理单元绑定数据

```c
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);
```

- opengl至少保证有16个纹理单元可以使用

- 在着色器中使用两个纹理单元

```c
#version 330 core
...

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
```

- 默认情况下uniform会自动绑定纹理单元0,也可以手动指定

```c
    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // 手动设置
    shader.setInt("texture2", 1); // 或者使用着色器类设置
```

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241105154439987.png" alt="image-20241105154439987" style="zoom:33%;" />

#### 完整代码

```c

#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //参数设置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //创建上下文
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //板顶函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //存储缓冲区对象id
    unsigned int VBO;
    //生成缓冲区对象并获取id
    glGenBuffers(1, &VBO);
    //将缓冲对象绑定到上下文，作为数组缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制数据到缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
	Shader shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader.use();

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	//uv属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data1 = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);

    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    unsigned int texture2;
    glGenTextures(2, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);

    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // 手动设置
    shader.setInt("texture2", 1); // 或者使用着色器类设置


    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染
        // 清除颜色缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 记得激活着色器
        shader.use();

        // 更新uniform颜色
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;

		shader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        // 绘制三角形
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //释放资源
    glfwTerminate();

    return 0;
}
//点着色器
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 ourColor;
out vec2 TexCoord;
void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
}
//片段着色器
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
```



## 变换

### 坐标系统

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedcoordinate_systems_right_handed.png" alt="coordinate_systems_right_handed" style="zoom: 80%;" />

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241107145529476.png" alt="image-20241107145529476" style="zoom:67%;" />

- **局部空间**(Local Space)：对象相对于局部原点的坐标
  - 适合对物体自身进行操作(如调整模型)
  - 通过**模型**矩阵转换
- **世界空间**(World Space)：相当于世界的全局原点
  - 物体之间的位置关系，对物体进行移动、缩放、旋转等，场景布置
  - 通过**观察**矩阵转换
- **观察空间**(View Space)：从摄像机/观察者角度观察
  - opengl本身没有摄像机的概念，通过相反移动物体来实现模拟摄像机
  - 通过**投影**矩阵转换

- **裁剪空间**(Clip Space)：裁剪到 -1~1的范围
  - 将大范围坐标转化到小范围，比如在每个维度上的-1000到1000。投影矩阵接着会将在这个指定的范围内的坐标变换为标准化设备坐标的范围(-1.0, 1.0)。所有在范围外的坐标不会被映射到在-1.0到1.0的范围之间，所以**会被裁剪**掉。
  - 裁剪之后进行投影映射到屏幕空间
- **屏幕空间**(Screen Space)：屏幕上的坐标



- **正交投影**
  - 可以使用glm创建投影矩阵`glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);`
  - 参数给出了宽度，长度，远近平面的范围
  - 主要用于二维渲染、建筑工程
- **透视投影**
  - `glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);`
  - 参数给出fov视野角度，宽高比，远近平面
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedperspective_frustum.png" alt=" perspective_frustum" style="zoom: 67%;" />



- 完整的变换$V_{clip}=M_{projection}\cdot M_{view}\cdot M_{model}\cdot V_{local}$
  - 着色器中`gl_Position = projection * view * model * vec4(aPos, 1.0);`




#### 深度缓冲

- 开启深度缓冲`glEnable(GL_DEPTH_TEST);`
- 附加每帧清楚缓冲`glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);`

### 摄像机

- 通过构建摄像机三维坐标系矩阵，来对物体进行变换

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedcamera_axes.png" alt="img" style="zoom: 80%;" />

- 首先摄像机的**坐标**`glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);`
- 结合指向计算得到摄像机**指向**（反方向，图中蓝色）

```c
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
```

- **右轴**：摄像机空间的x轴正方向
  - ​	通过定义上向量，与指向叉乘就可以得到右轴

```c
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
```

- **上轴**：摄像机空间的y轴正方向
  - 可以由另外两个轴计算得到`glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);`



- 用这三个向量，和摄像机坐标就能构建变换矩阵Lookat矩阵
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241107160228888.png" alt="image-20241107160228888" style="zoom:67%;" />
- 只需要提供摄像机**位置、目标位置、上向量**就可以用glm创建出lookat矩阵

```c
glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
           glm::vec3(0.0f, 0.0f, 0.0f), 
           glm::vec3(0.0f, 1.0f, 0.0f));
```

- 实现一个简单的摄像机环绕

```c
float radius = 10.0f;
float camX = sin(glfwGetTime()) * radius;
float camZ = cos(glfwGetTime()) * radius;
glm::mat4 view;
view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
```

#### 平移

- 要想实现平移效果，可以让目标点与摄像机坐标相关，比如始终值指向前面

```c
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//用键盘来控制移动
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
```

- 左右移动方向是根据叉乘再标准化得到的
- 注意这种移动速度和刷新率相关，想要恒定速度要计算时间

#### 旋转

- 三种旋转角：俯仰角、偏航角、滚转角
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedcamera_pitch_yaw_roll.png" alt="img" style="zoom:80%;" />



- 通过鼠标输入实现旋转控制：水平的移动影响偏航角，竖直的移动影响俯仰角
  - 通过比较两帧之间坐标差距，决定角度的偏移



- 捕捉光标，在窗口内不显示（但是记录位置用于操控）`glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);`

- 注册监听`glfwSetCursorPosCallback(window, mouse_callback);`

```c
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

}
```



#### 缩放

- 通过监听滚轮调整fov来实现
- 

#### 示例：摄像机类

```c
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif
1
```

- 程序代码

```c

#include "shader.h"
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad\glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float screenWidth = 800;
float screenHeight = 600;
float lastX = screenWidth/2, lastY = screenHeight/2;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main()
{
    //参数设置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //创建上下文
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //板顶函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //存储缓冲区对象id
    unsigned int VBO;
    //生成缓冲区对象并获取id
    glGenBuffers(1, &VBO);
    //将缓冲对象绑定到上下文，作为数组缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制数据到缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader shader("vertex_shader.glsl", "fragment_shader.glsl");
    shader.use();

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data1 = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data1);

    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    unsigned int texture2;
    glGenTextures(2, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data2);

    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // 手动设置
    shader.setInt("texture2", 1); // 或者使用着色器类设置
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // 输入
        processInput(window);

        // 渲染
        // 清除颜色缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 记得激活着色器
        shader.use();

        // 更新uniform颜色
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;

		shader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        // 绘制三角形
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), screenWidth / screenHeight, 0.1f, 100.0f);
        unsigned transformLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 view;
        view = camera.GetViewMatrix();
        transformLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            transformLoc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //释放资源
    glfwTerminate();

    return 0;
}
```



## 光照

### 颜色

- 将光源的颜色与物体的颜色**相乘**得到物体反射的颜色
  - 物体的颜色就是物体从光源反射的颜色分量的大小，由**物体自身的性质和光源决定**

```c
//白色光源
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);
//绿色光源
glm::vec3 lightColor(0.0f, 1.0f, 0.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (0.0f, 0.5f, 0.0f);
```

- 为了实现灯光和普通物体不同的渲染模式，可以使用两套着色器程序（比如灯光固定为白色）

### 基础光照——phong模型

- 模型中由三个分量组成：环境光、漫反射、镜面反射

#### 环境光

- 简单的将一个**很小的常量颜色**添加到物体片段的最终颜色

```c
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}
```

#### 漫反射

- 光源与平面的夹角决定漫反射的强度

```c
vec3 norm = normalize(Normal);//发现
vec3 lightDir = normalize(lightPos - FragPos);//根据输入的光源位置和着色点计算出入射光线向量
float diff = max(dot(norm, lightDir), 0.0);//计算夹角
vec3 diffuse = diff * lightColor;
```

- `FragPos`通过输入顶点着色器的点经过模型变换得到（世界坐标系，为了方便的与灯光等计算）

##### 法向量与变换

- 由于法向量没有齐次坐标，因此不会进行平移操作，只能缩放和旋转
- 如果模型进行了不等比缩放，法向量可能不再垂直与表面，也就是说通过这样的模型矩阵不能得到正确的法向量
- 因此通过特殊的**法线矩阵**（模型矩阵左上角3x3部分的逆矩阵的转置矩阵）来进行变换更为恰当
  - `Normal = mat3(transpose(inverse(model))) * aNormal;`
  - 矩阵求逆对着色器开销较大，因此在CPU进行计算之后求逆更为恰当

#### 镜面反射

  

#### 代码示例

### 材质



### 光照贴图



### 投光物



### 多光源



## 模型加载

## PBR

## 高级

### 高级opengl

### 高级光照

