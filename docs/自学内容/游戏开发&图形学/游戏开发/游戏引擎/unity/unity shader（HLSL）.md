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
### 变量类型
- 不同精度浮点数
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219215706.png)
	- 通常颜色和单位矢量用 half，更大范围用 float（fixed 通常弃用了，会被视为 half）
### unity 扩展
- unity 简化了 shader 的编写
#### 内置变量
- 变换矩阵
![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219172434.png)
- 摄像机
![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219172843.png)
#### 内置文件
- 在 CG 代买快 `CGPROGRAM` 内，也可以通过 `#include "xx"` 来包含文件
	- 可以从 unity 逛网下载提供的一些文件 `CGIncludes`
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219211932.png)
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219211943.png)
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241220152229.png)
#### CG/HLSL 语义
- 语义让 shader 知道从哪里读取数据并把数据输出到哪里
- 系统数值语义：`SV_` 开头，有特殊含义，如 `SV_POSITION SV_Target` 分别作为顶点着色器和片元着色器的输出
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219214301.png)
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219214325.png)
- ![image.png|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219214337.png)
#### 调试
- 将数据作为假彩色输出到屏幕上，通过屏幕上显示内容来判断值是否正确
```c

Shader "Unity Shaders Book/Chapter 5/Simple Shader" {

    SubShader {
        Pass {
            CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag

                #include "UnityCG.cginc"

                struct v2f {
                    float4 pos : SV_POSITION;
                    fixed4 color : COLOR0;
                };

            v2f vert(appdata_full v) {
                v2f o;
                o.pos = mul(UNITY_MATRIX_MVP, v.vertex);

                // 可视化法线方向
                o.color = fixed4(v.normal * 0.5 + fixed3(0.5, 0.5, 0.5), 1.0);

                // 可视化切线方向
                o.color = fixed4(v.tangent * 0.5 + fixed3(0.5, 0.5, 0.5), 1.0);

                // 可视化副切线方向
                fixed3 binormal = cross(v.normal, v.tangent.xyz) * v.tangent.w;
                o.color = fixed4(binormal * 0.5 + fixed3(0.5, 0.5, 0.5), 1.0);

                // 可视化第一组纹理坐标
                o.color = fixed4(v.texcoord.xy, 0.0, 1.0);

                // 可视化第二组纹理坐标
                o.color = fixed4(v.texcoord1.xy, 0.0, 1.0);

                // 可视化第一组纹理坐标的小数部分
                o.color = frac(v.texcoord);
                if (any(saturate(v.texcoord) - v.texcoord)) {
                    o.color.b = 0.5;
                }
                o.color.a = 1.0;

                // 可视化第二组纹理坐标的小数部分
                o.color = frac(v.texcoord1);
                if (any(saturate(v.texcoord1) - v.texcoord1)) {
                    o.color.b = 0.5;
                }
                o.color.a = 1.0;

                // 可视化顶点颜色
                // o.color = v.color;

                return o;
            }

            fixed4 frag(v2f i) : SV_Target {
                return i.color;
            }
            ENDCG
        }

    }
}

```
##### ide 调试
- ide 如 vs 提供了 Graphics Debugger 调试功能，可以查看每个像素的信息
##### 帧调试
- unity 提供帧调试器 `window/frame debugger` 来检查图像一帧的渲染过程

### unity 着色器
- **表面着色器**：对顶点、片元着色器更高层级的封装，在 subshader 中而不是 pass 中
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219155308.png)
- **顶点、片元着色器**
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219155501.png)
	- 片元着色器中获取屏幕坐标：VPOS 或 WPOS `fixed4 frag(float4 sp:VPOS)`
#### 编写顶点着色器与片元着色器
- 一个最简单的着色器
```c
Shader "Unity Shaders Book/Chapter 5/Simple Shader"  
{  
    SubShader  
    {  
        Pass  
        {  
            CGPROGRAM  
            //指出对应着色器函数
                #pragma vertex vert  
                #pragma fragment frag  

                float4 vert(float4 vertex : POSITION) : SV_POSITION  
                {  
                    return UnityObjectToClipPos(vertex);  
                }  
            	fixed4 frag() : SV_Target  
            	{                
                	return fixed4(1.0, 1.0, 1.0, 1.0);            
            	}                        
            ENDCG  
            }  
    }
}
```
- `POSITION` 和 `SV_POSITION` 等都为**语义**，告诉系统用户需要哪些输入值，以及用户输出的是什么
	- 常见的语义：`POSITION` `TRANGENT` `NORMAL` `TEXCOORD0` `COLOR`
- 创建并使用自定义数据类型
```c
  
Shader "Unity Shaders Book/Chapter 5/Simple Shader" {  
    Properties  
    {  
        _Color ("Color Tint", Color) = (1,1,1,1)  
    }    SubShader {  
        Pass {  
            CGPROGRAM  
            #pragma vertex vert  
            #pragma fragment frag  
  
            fixed4 _Color;  
  
            struct a2v {  
                float4 vertex : POSITION;  
                float3 normal : NORMAL;  
                float4 texcoord : TEXCOORD0;  
            };  
            struct v2f {  
                float4 pos : POSITION;  
                fixed3 color : COLOR0;  
            };  
            v2f vert(a2v v) : POSITION {  
                v2f o;  
                o.pos = UnityObjectToClipPos(v.vertex);  
                o.color = v.normal * 0.5 + fixed3(0.5, 0.5, 0.5);  
                return o;  
            }  
            fixed4 frag(v2f i) : SV_Target {  
                fixed3 color = i.color * _Color.rgb;  
                return fixed4(color, 1.0);  
            }            ENDCG  
        }  
    }}
```
- `Properties` 可以配置输入参数，注意如果有输入，下面着色器代码中要有对应的变量，如这里的 `fixed4 _Color;`
	- 类型对应关系：![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219211426.png)

#### 表面着色器
### 平台兼容性问题
- 坐标系
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219214934.png)
	- 大部分情况 unity 会自动对 dx 进行翻转，但是如果开启了抗锯齿并使用帧缓冲渲染到纹理处理多个图片时要小心，可能不会自动翻转
	- ![image.png|248](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241219215246.png)
### 性能优化
- 慎用分支和循环语句，GPU 开销很大
## 光照
### 简单光照
#### 手动实现
- 顶点光照着色
```c
Shader "Unity Shaders Book/Chapter 5/Simple Shader" {  
    Properties  
    {  
        _Diffuse ("Diffuse", Color) = (1, 1, 1, 1)  
        _Specular ("Specular", Color) = (1, 1, 1, 1)  
        _Gloss ("Gloss", Range(8.0, 256)) = 20  
    }  
    SubShader {  
        Pass {  
            Tags {"LightMode" = "ForwardBase"}  
            CGPROGRAM  
            #pragma vertex vert  
            #pragma fragment frag  
            #include "Lighting.cginc"  
  
            fixed4 _Diffuse;  
            fixed4 _Specular;  
            float _Gloss;  
  
            struct a2v {  
                float4 vertex : POSITION;  
                float3 normal : NORMAL;  
            };  
            struct v2f {  
                float4 pos : SV_POSITION;  
                fixed3 color : COLOR;  
            };  
            v2f vert(a2v v) {  
                v2f o;  
                o.pos = UnityObjectToClipPos(v.vertex);  
                fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;  
                fixed3 wordNormal = normalize(mul(v.normal,(float3x3)unity_WorldToObject));  
                fixed3 lightDir = normalize(_WorldSpaceLightPos0.xyz);  
                fixed3 diffuse = _LightColor0.rgb * _Diffuse.rgb * saturate(dot(wordNormal, lightDir));  
  
                fixed3 reflectDir = normalize(reflect(-lightDir, wordNormal));  
                fixed viewDir = normalize(_WorldSpaceCameraPos - mul(unity_ObjectToWorld, v.vertex).xyz);  
                fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(saturate(dot(reflectDir, viewDir)), _Gloss);  
                                o.color = ambient + diffuse + specular;  
                return o;  
            }  
            fixed4 frag(v2f i) : SV_Target {  
                fixed3 color = i.color;  
                return fixed4(color, 1.0);  
            }            ENDCG  
        }  
    }    Fallback "Diffuse"  
}
```
#### 使用内置函数
- 手动计算光源反射很麻烦，尤其是光源较多时
- ![|550](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20241220152229.png)
## 纹理
```c

Shader "Unity Shaders Book/Chapter 7/Single Texture" {  
    Properties {  
       _Color ("Color Tint", Color) = (1, 1, 1, 1)  
       _MainTex ("Main Tex", 2D) = "white" {}  
       _Specular ("Specular", Color) = (1, 1, 1, 1)  
       _Gloss ("Gloss", Range(8.0, 256)) = 20  
    }  
    SubShader {         
Pass {   
Tags { "LightMode"="ForwardBase" }  
       CGPROGRAM  
          #pragma vertex vert  
          #pragma fragment frag  
  
          #include "Lighting.cginc"  
          fixed4 _Color;  
          sampler2D _MainTex;  
          float4 _MainTex_ST;  
          fixed4 _Specular;  
          float _Gloss;  
          struct a2v {  
             float4 vertex : POSITION;  
             float3 normal : NORMAL;  
             float4 texcoord : TEXCOORD0;  
          };          struct v2f {  
             float4 pos : SV_POSITION;  
             float3 worldNormal : TEXCOORD0;  
             float3 worldPos : TEXCOORD1;  
             float2 uv : TEXCOORD2;  
          };          v2f vert(a2v v) {  
             v2f o;  
             o.pos = UnityObjectToClipPos(v.vertex);  
                          o.worldNormal = UnityObjectToWorldNormal(v.normal);  
                          o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;  
                          o.uv = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;  
             // Or just call the built-in function  
//           o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);  
             return o;  
          }          fixed4 frag(v2f i) : SV_Target {  
             fixed3 worldNormal = normalize(i.worldNormal);  
             fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));  
             // Use the texture to sample the diffuse color  
             fixed3 albedo = tex2D(_MainTex, i.uv).rgb * _Color.rgb;  
             fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;  
             fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));  
             fixed3 viewDir = normalize(UnityWorldSpaceViewDir(i.worldPos));  
             fixed3 halfDir = normalize(worldLightDir + viewDir);  
             fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(worldNormal, halfDir)), _Gloss);  
             return fixed4(ambient + diffuse + specular, 1.0);  
          }          ENDCG  
       }  
    }FallBack "Specular"  
}
```
- 添加了贴图参数（默认为纯白）
- `纹理名_ST` 表示某个纹理的属性，ST 即缩放和平移属性
	- `.xy` 获取缩放
	- `.zw` 获取偏移
	- 对纹理坐标进行修正 `o.uv = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;`或者使用内置 `TRANSFORM_TEX(v.texcoord, _MainTex)` 如果要使用平铺等纹理效果必须要加上这个设置
### 纹理的属性

# shader 蓝图
## 基本
![image.png|650](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212205645.png)
1. blackboard 中用于创建输入变量（再外面 material 处的面板可以直接设置）
2. graph inspector 处面板可以用于设置一个节点的具体参数，比如设置默认颜色

### 子蓝图

- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212213845.png)
