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
## opengl 基础
### 工作流程

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



#### 顶点着色器

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

#### 片段着色器

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

#### 链接着色器

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

#### 设置缓冲区

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
#### 链接顶点属性

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

##### 顶点数组对象VAO

- 每次都重新进行绑定设置很麻烦，使用**顶点数组对象VAO**可以像顶点缓冲对象那样被绑定，任何随后的**顶点属性调用**都会储存在这个VAO中。
  - VAO是一个容器，用于保存多个VBO的**状态**以及**如何解释**这些VBO中的数据。它记录了**如何将VBO中的数据绑定到顶点属性上。**
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

##### 元素缓冲对象EBO

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

#### 完整代码
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

### GLSL

- glsl 代码与 c 接近，开始于版本声明，与 opengl 类似，如 3.3 版本对应 330 `#version 330 core`
- 点着色器示例
```glsl
#version 330 core
//定义一个三维向量变量，用来接收输入的坐标，同时绑定在位置0
layout (location = 0) in vec3 aPos;

void main()
{
    //简单的转化为四元坐标
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

- 片段着色器示例

```glsl
#version 330 core
out vec4 FragColor;

void main()
{
    //全部输出为橙色
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
```

