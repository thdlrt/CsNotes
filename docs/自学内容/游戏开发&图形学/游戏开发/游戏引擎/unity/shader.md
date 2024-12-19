> [GameDev.tv - The World's Most Loved Game Development Courses](https://www.gamedev.tv/dashboard/courses/6/4418) gamedev unity shader 蓝图课程
# 编写 shader
## unity shader 基础
- unityshader 使用 shaderlab 进行编写，这是专用的说明性语言，可以更加简单的进行开发
	- 分别在不同的语义块中定义配置
```c
Shader "Custom/SimpleShader"//定义shader目录及名称
{
    Properties
    {//Name ("display name", PropertyType) = DefaultValue
        _MainTex ("Base (RGB)", 2D) = "white" { }
        _Color ("Main Color", Color) = (.5,.5,.5,1)
    }
    
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        
        Pass
        {
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
                o.pos = UnityObjectToClipPos(v.vertex);
                o.color = v.color;
                return o;
            }

            half4 frag(v2f i) : SV_Target
            {
                return i.color;
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
	- 至少有一个，unityshader 加载时，unity 会扫描所有的 subshader 语义块并选择第一个能够在目标平台上运行的 subshader，如果均不支持就会使用 fallback 指定的 unityshader
# shader 蓝图
## 基本
![image.png|650](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212205645.png)
1. blackboard 中用于创建输入变量（再外面 material 处的面板可以直接设置）
2. graph inspector 处面板可以用于设置一个节点的具体参数，比如设置默认颜色

### 子蓝图

- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212213845.png)
