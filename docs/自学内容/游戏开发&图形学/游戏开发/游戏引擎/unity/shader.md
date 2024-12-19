> [GameDev.tv - The World's Most Loved Game Development Courses](https://www.gamedev.tv/dashboard/courses/6/4418) gamedev unity shader 蓝图课程
# 编写 shader
## unity shader 基础
- unityshader 使用 shaderlab 进行编写，这是专用的说明性语言，可以更加简单的进行开发
	- 分别在不同的语义块中定义配置
```c
Shader "Custom/BasicShader"
{
    Properties
    {
        _MainTex ("Base (RGB)", 2D) = "white" { }
        _Color ("Main Color", Color) = (.5, .5, .5, 1)
    }

    SubShader
    {
        Tags { "RenderType"="Opaque" }

        Pass
        {
            Name "BasePass"
            Tags { "LightMode"="ForwardBase" }

            // 渲染状态设置
            ZWrite On
            ZTest LEqual
            Blend SrcAlpha OneMinusSrcAlpha

            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            struct appdata
            {
                float4 vertex : POSITION;
                float4 color : COLOR;
            };

            struct v2f
            {
                float4 pos : POSITION;
                float4 color : COLOR;
            };

            v2f vert(appdata v)
            {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);  // 顶点变换
                o.color = v.color;  // 顶点颜色
                return o;
            }

            half4 frag(v2f i) : SV_Target
            {
                return i.color;  // 返回颜色
            }
            ENDCG
        }
    }

    Fallback "Diffuse"
}

```
- 属性语义块
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219143105.png)

- SubShader
	- 至少有一个，unityshader 加载时，unity 会扫描所有的 subshader 语义块并选择第一个能够在目标平台上运行的 subshader，如果均不支持就会**使用 fallback 指定的 unityshader**
	- 分为三个部分：Pass 定义完整的渲染流程；渲染状态（应用到 pass）；以及标签
- 状态设置：如是否开启混合、深度测试等
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219145515.png)
- 标签
	- 以键值对进行存储（字符串）
	- 用于 subshader 和渲染引擎之间进行沟通
	- 如果想分别设置，可以在 pass 语义块中单独进行设置
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219152010.png)
- pass
	- 可以对 pass 进行命名 `Name "MyPassName"` (名称大小写不区分，会被替换为纯大写名称)
	- 这样就可以在其他位置来使用 `Useapsss "MyShader/MYPASSNAMME"`
	- 一个 subshader 可以包含多个 pass，多个 pass 在同一个 subshader 中完成不同的渲染任务
- 可以使用 CG、HLSL，嵌套在 `CGPROGRAM` 和 `ENDCG`
	- GLSL 嵌套在 `GLSLPROGRAM` 和 `GLSL`
	- 用于嵌套在 subshader 中编写着色器
### 内置变量
- 变换矩阵
![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219172434.png)
- 摄像机
![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219172843.png)

### unity 着色器
- **表面着色器**：对顶点、片元着色器更高层级的封装，在 subshader 中而不是 pass 中
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219155308.png)
- **顶点、片元着色器**
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219155501.png)
#### 表面着色器
# shader 蓝图
## 基本
![image.png|650](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212205645.png)
1. blackboard 中用于创建输入变量（再外面 material 处的面板可以直接设置）
2. graph inspector 处面板可以用于设置一个节点的具体参数，比如设置默认颜色

### 子蓝图

- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212213845.png)
