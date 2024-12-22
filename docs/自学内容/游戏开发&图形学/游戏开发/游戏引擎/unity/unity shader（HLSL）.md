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

### 渲染路径

- 渲染路径决定光照是如何应用到Unity Shader中，通过为pass指定使用的渲染路径，unity才知道如何把光**源和处理后的光照信息**放在数据里以供访问
- 常用的渲染路径：前向渲染路径、延迟渲染路径
  - 一般一个项目只使用一种渲染路径，因此在项目设置中配置
  - 但也可以给每个摄像机设置不同的方式
- 在pass中配置`Tags {"LightMode" = "ForwardBase"}`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221201217671.png" alt="image-20241221201217671" style="zoom:50%;" />

#### 前向渲染路径

- 使用颜色、深度两个缓冲区，根据深度缓冲区深度测试来判断是否更新颜色缓冲区的值
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221201949675.png" alt="image-20241221201949675" style="zoom:50%;" />
- 不同等级的光照处理方式：逐顶点处理、逐像素处理、球谐函数
  - 渲染一个物体时，unity会根据光源距离以及重要程度进行排序，最多4个光源按照逐顶点的方式处理，剩下的可以用SH等
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221202628062.png" alt="image-20241221202628062" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221203528740.png" alt="image-20241221203528740" style="zoom:50%;" />
  - 如果一个场景只有一个光源，只会调用 `ForwardBase`，效率最高。
  - 如果场景中增加了更多光源，Unity可以按需调用 `ForwardAdd`，不需要修改主光源的渲染逻辑。
- 默认情况下forwardadd用于计算附加光源的光照共享而不处理阴影，因此只有主光源（通常平行光）才有阴影
  - 前向渲染光照的开销比较大
- 内置变量
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221205709397.png" alt="image-20241221205709397" style="zoom:50%;" />
- 内置函数
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221205809469.png" alt="image-20241221205809469" style="zoom:50%;" />
- 实例代码（双光源，平行光+点光源）
  - 拆分为两个pass：
    - **ForwardBase**：处理环境光和第一个方向光。
    - **ForwardAdd**：处理其他像素光源。
  - 

```c
Shader "Unity Shaders Book/Chapter 9/Forward Rendering" {
    Properties {
        _Diffuse ("Diffuse", Color) = (1, 1, 1, 1)
        _Specular ("Specular", Color) = (1, 1, 1, 1)
        _Gloss ("Gloss", Range(8.0, 256)) = 20
    }
    SubShader {
        Tags { "RenderType"="Opaque" }

        Pass {
            // Pass for ambient light & first pixel light (directional light)
            Tags { "LightMode"="ForwardBase" }

            CGPROGRAM

            // Apparently need to add this declaration 
            #pragma multi_compile_fwdbase	
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
                float3 worldNormal : TEXCOORD0;
                float3 worldPos : TEXCOORD1;
            };

            v2f vert(a2v v) {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);

                o.worldNormal = UnityObjectToWorldNormal(v.normal);

                o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

                return o;
            }

            fixed4 frag(v2f i) : SV_Target {
                fixed3 worldNormal = normalize(i.worldNormal);
                fixed3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz);

                fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;

                fixed3 diffuse = _LightColor0.rgb * _Diffuse.rgb * max(0, dot(worldNormal, worldLightDir));

                fixed3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldPos.xyz);
                fixed3 halfDir = normalize(worldLightDir + viewDir);
                fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(worldNormal, halfDir)), _Gloss);

                fixed atten = 1.0;

                return fixed4(ambient + (diffuse + specular) * atten, 1.0);
            }

            ENDCG
        }

        Pass {
            // Pass for other pixel lights
            Tags { "LightMode"="ForwardAdd" }

            Blend One One

                CGPROGRAM

                // Apparently need to add this declaration
                #pragma multi_compile_fwdadd

                #pragma vertex vert
                #pragma fragment frag

                #include "Lighting.cginc"
                #include "AutoLight.cginc"

                fixed4 _Diffuse;
            fixed4 _Specular;
            float _Gloss;

            struct a2v {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
            };

            struct v2f {
                float4 pos : SV_POSITION;
                float3 worldNormal : TEXCOORD0;
                float3 worldPos : TEXCOORD1;
            };

            v2f vert(a2v v) {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);

                o.worldNormal = UnityObjectToWorldNormal(v.normal);

                o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

                return o;
            }
			//关键代码，处理非平行光的渲染
            fixed4 frag(v2f i) : SV_Target {
                fixed3 worldNormal = normalize(i.worldNormal);
                #ifdef USING_DIRECTIONAL_LIGHT//平行光
                fixed3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz);
                #else
                fixed3 worldLightDir = normalize(_WorldSpaceLightPos0.xyz - i.worldPos.xyz);
                #endif

                fixed3 diffuse = _LightColor0.rgb * _Diffuse.rgb * max(0, dot(worldNormal, worldLightDir));

                fixed3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldPos.xyz);
                fixed3 halfDir = normalize(worldLightDir + viewDir);
                fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(worldNormal, halfDir)), _Gloss);
				//计算光线衰减
                #ifdef USING_DIRECTIONAL_LIGHT
                fixed atten = 1.0;//平行光没有衰减
                #else
                #if defined (POINT)//点光源
                float3 lightCoord = mul(unity_WorldToLight, float4(i.worldPos, 1)).xyz;
                fixed atten = tex2D(_LightTexture0, dot(lightCoord, lightCoord).rr).UNITY_ATTEN_CHANNEL;
                #elif defined (SPOT)//聚光灯
                float4 lightCoord = mul(unity_WorldToLight, float4(i.worldPos, 1));
                fixed atten = (lightCoord.z > 0) * tex2D(_LightTexture0, lightCoord.xy / lightCoord.w + 0.5).w * tex2D(_LightTextureB0, dot(lightCoord, lightCoord).rr).UNITY_ATTEN_CHANNEL;
                #else
                fixed atten = 1.0;
                #endif
                #endif

                return fixed4((diffuse + specular) * atten, 1.0);
            }

            ENDCG
        }
    }
    FallBack "Specular"
}

```



#### 顶点照明渲染路径（已废弃）

- 性能高效果较差，不支持逐像素才能得到的效果，如阴影，高精度高光反射等，只使用了**逐顶点方式计算光照**
- 通常只需要一个Pass，会在这里完成所有光源对物体照明的计算（一个pass中最多8个逐顶点光源）
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222144043955.png" alt="image-20241222144043955" style="zoom:50%;" />
- ![image-20241222144349596](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222144349596.png)

#### 延迟渲染路径

- 当场景中包含过多实时光源时，前向渲染的性能会大幅下降，延迟渲染就主要用于有大量实时光照的场景
  - 延迟渲染问题：不支持真正的抗锯齿、不能处理半透明物体、对显卡要求
- 延迟渲染使用额外的缓冲区G缓冲，存储更多的表面信息，如法线、位置、材质等
- 延迟渲染包含了两个Pass
  - 第一个Pass仅仅极速那哪些片元可见（深度缓冲），并将可见的片元的相关信息存储到G缓冲区
  - 在第二个Pass中，利用G缓冲区的各个片元信息进行真正的光照计算

```c
// Pass 1: 不进行真正的光照计算
// 仅将光照计算需要的信息存储到 G 缓冲中
for (each primitive in this model) {
    for (each fragment covered by this primitive) {
        if (failed in depth test) {
            // 如果没有通过深度测试，说明该片元是不可见的
            discard;
        } else {
            // 如果该片元可见
            // 就把需要的信息存储到 G 缓冲中
            writeGBuffer(materialInfo, pos, normal, lightDir, viewDir);
        }
    }
}

// Pass 2: 利用 G 缓冲中的信息进行真正的光照计算
for (each pixel in the screen) {
    if (the pixel is valid) {
        // 如果该像素是有效的
        // 读取之前写入的 G 缓冲中的信息
        readGBuffer(pixel, materialInfo, pos, normal, lightDir, viewDir);

        // 根据读取到的信息进行光照计算
        float4 color = Shading(materialInfo, pos, normal, lightDir, viewDir);

        // 更新帧缓冲
        writeFrameBuffer(pixel, color);
    }
}
```

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222150747461.png" alt="image-20241222150747461" style="zoom:50%;" />

### 光源

- 光源的属性：位置、方向、颜色、强度、衰减
- **平行光**：位置属性不影响光照，并且没有衰减
- **点光源**：球形范围照明

#### 光线衰减

- unity使用一张**纹理**来查找光照衰减数值
  - 灵活性受限
  - 性能较好，大部分情况下效果良好
- 将点转换到光源坐标系，然后用其平方来对纹理采样

```c
float3 lightCoord mul(LightMatrix0,float4(i.worldPosition,1)).xyz;
fixed atten tex2D(LightTexture0,dot(1ightCoord,lightCoord).rr).UNITY ATTEN CHANNEL;
```

- 也可以使用数学公式进行计算

### 阴影

- 两个部分：一个物体向其他物体投射阴影，物体还要接受来自其他物体的阴影
- 使用shadowmap来实现，由于只需要深度信息，使用一个额外的pass来更新深度纹理`LightMode = ShadowCaster`
  - 首先将摄影机放置到光源上然后调用该pass，输出深度信息系到阴影映射纹理

#### 不透明物体的阴影

- 开启灯光和物体的阴影
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222165144871.png" alt="image-20241222165144871" style="zoom:50%;" />
- 开启上面两个位置后，即使没有在shader中编写对应的pass，实际上也是有阴影的，这是通过`Fallback "Specular"`逐层回调到了内置的`shadowcaster`的pass
  - 这也是实际上通常使用的方法，并不会自定义
- 为了让使用自定义shader的物体可以接收阴影，还需要使用一些宏定义
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222171323071.png" alt="image-20241222171323071" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222171335666.png" alt="image-20241222171335666" style="zoom:50%;" />
  - 最后将得到的shadow与颜色相乘
  - 这些宏可以在不同平台处理不同光源类型

#### 统一管理光线衰减和阴影

- 光线衰减和阴影对渲染结果的影响本质上是一样的，都是与最终的渲染结果相乘
- **`UNITY_LIGHT_ATTENUATION(atten, i, i.worldPos)`**:
  - 计算光照衰减（Attenuation）值，同时结合了阴影信息。
  - 主要作用：
    1. **光照衰减**：基于光源与片元之间的距离，计算光照强度的衰减值。
    2. **阴影计算**：结合阴影映射，确定片元是否被阴影覆盖。
  - 结果存储在 `atten` 中，用于控制最终光照效果。

```c
fixed4 frag(v2f i) : SV_Target {
    ...
    UNITY_LIGHT_ATTENUATION(atten, i, i.worldPos);
    return fixed4(ambient + (diffuse + specular) * atten, 1.0);
}
```

#### 半透明物体的阴影

- 对于透明物体只用fallback提供的默认shader通常无法得到正确的纹理
- 就直接在半透明渲染代码的基础上添加上阴影宏即可

```c
// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Chapter 9/Alpha Blend With Shadow" {
	Properties {
		_Color ("Color Tint", Color) = (1, 1, 1, 1)
		_MainTex ("Main Tex", 2D) = "white" {}
		_AlphaScale ("Alpha Scale", Range(0, 1)) = 1
	}
	SubShader {
		Tags {"Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent"}
		
		Pass {
			Tags { "LightMode"="ForwardBase" }
			
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha
			
			CGPROGRAM
			
			#pragma multi_compile_fwdbase
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "Lighting.cginc"
			#include "AutoLight.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed _AlphaScale;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;
				SHADOW_COORDS(3)
			};
			
			v2f vert(a2v v) {
			 	v2f o;
			 	o.pos = UnityObjectToClipPos(v.vertex);
			 	
			 	o.worldNormal = UnityObjectToWorldNormal(v.normal);
			 	
			 	o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

			 	o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);
			 	
			 	// Pass shadow coordinates to pixel shader
			 	TRANSFER_SHADOW(o);
			 	
			 	return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));
				
				fixed4 texColor = tex2D(_MainTex, i.uv);
				
				fixed3 albedo = texColor.rgb * _Color.rgb;
				
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;
				
				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

			 	// UNITY_LIGHT_ATTENUATION not only compute attenuation, but also shadow infos
				UNITY_LIGHT_ATTENUATION(atten, i, i.worldPos);
			 	
				return fixed4(ambient + diffuse * atten, texColor.a * _AlphaScale);
			}
			
			ENDCG
		}
	} 
	FallBack "Transparent/VertexLit"
	// Or  force to apply shadow
//	FallBack "VertexLit"
}

```



### 可以实际使用的光照shader

- phong

```c
// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Common/Bumped Diffuse" {
	Properties {
		_Color ("Color Tint", Color) = (1, 1, 1, 1)
		_MainTex ("Main Tex", 2D) = "white" {}
		_BumpMap ("Normal Map", 2D) = "bump" {}
	}
	SubShader {
		Tags { "RenderType"="Opaque" "Queue"="Geometry"}

		Pass { 
			Tags { "LightMode"="ForwardBase" }
		
			CGPROGRAM
			
			#pragma multi_compile_fwdbase
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "Lighting.cginc"
			#include "AutoLight.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			sampler2D _BumpMap;
			float4 _BumpMap_ST;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 tangent : TANGENT;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float4 uv : TEXCOORD0;
				float4 TtoW0 : TEXCOORD1;  
				float4 TtoW1 : TEXCOORD2;  
				float4 TtoW2 : TEXCOORD3;
				SHADOW_COORDS(4)
			};
			
			v2f vert(a2v v) {
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);
				
				o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
				o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;
				
				float3 worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;  
				fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
				fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
				fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 
				
				o.TtoW0 = float4(worldTangent.x, worldBinormal.x, worldNormal.x, worldPos.x);
				o.TtoW1 = float4(worldTangent.y, worldBinormal.y, worldNormal.y, worldPos.y);
				o.TtoW2 = float4(worldTangent.z, worldBinormal.z, worldNormal.z, worldPos.z);  
				
				TRANSFER_SHADOW(o);
				
				return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				float3 worldPos = float3(i.TtoW0.w, i.TtoW1.w, i.TtoW2.w);
				fixed3 lightDir = normalize(UnityWorldSpaceLightDir(worldPos));
				fixed3 viewDir = normalize(UnityWorldSpaceViewDir(worldPos));
				
				fixed3 bump = UnpackNormal(tex2D(_BumpMap, i.uv.zw));
				bump = normalize(half3(dot(i.TtoW0.xyz, bump), dot(i.TtoW1.xyz, bump), dot(i.TtoW2.xyz, bump)));
				
				fixed3 albedo = tex2D(_MainTex, i.uv.xy).rgb * _Color.rgb;
				
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;
			
			 	fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(bump, lightDir));
				
				UNITY_LIGHT_ATTENUATION(atten, i, worldPos);
				
				return fixed4(ambient + diffuse * atten, 1.0);
			}
			
			ENDCG
		}
		
		Pass { 
			Tags { "LightMode"="ForwardAdd" }
			
			Blend One One
		
			CGPROGRAM
			
			#pragma multi_compile_fwdadd
			// Use the line below to add shadows for point and spot lights
//			#pragma multi_compile_fwdadd_fullshadows
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "Lighting.cginc"
			#include "AutoLight.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			sampler2D _BumpMap;
			float4 _BumpMap_ST;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 tangent : TANGENT;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float4 uv : TEXCOORD0;
				float4 TtoW0 : TEXCOORD1;  
				float4 TtoW1 : TEXCOORD2;  
				float4 TtoW2 : TEXCOORD3;
				SHADOW_COORDS(4)
			};
			
			v2f vert(a2v v) {
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);
				
				o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
				o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;
				
				float3 worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;  
				fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
				fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
				fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 
				
				o.TtoW0 = float4(worldTangent.x, worldBinormal.x, worldNormal.x, worldPos.x);
				o.TtoW1 = float4(worldTangent.y, worldBinormal.y, worldNormal.y, worldPos.y);
				o.TtoW2 = float4(worldTangent.z, worldBinormal.z, worldNormal.z, worldPos.z);  
				
				TRANSFER_SHADOW(o);
				
				return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				float3 worldPos = float3(i.TtoW0.w, i.TtoW1.w, i.TtoW2.w);
				fixed3 lightDir = normalize(UnityWorldSpaceLightDir(worldPos));
				fixed3 viewDir = normalize(UnityWorldSpaceViewDir(worldPos));
				
				fixed3 bump = UnpackNormal(tex2D(_BumpMap, i.uv.zw));
				bump = normalize(half3(dot(i.TtoW0.xyz, bump), dot(i.TtoW1.xyz, bump), dot(i.TtoW2.xyz, bump)));
				
				fixed3 albedo = tex2D(_MainTex, i.uv.xy).rgb * _Color.rgb;
				
			 	fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(bump, lightDir));
				
				UNITY_LIGHT_ATTENUATION(atten, i, worldPos);
				
				return fixed4(diffuse * atten, 1.0);
			}
			
			ENDCG
		}
	} 
	FallBack "Diffuse"
}

```

- blinn-phong

```c
// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Common/Bumped Specular" {
	Properties {
		_Color ("Color Tint", Color) = (1, 1, 1, 1)
		_MainTex ("Main Tex", 2D) = "white" {}
		_BumpMap ("Normal Map", 2D) = "bump" {}
		_Specular ("Specular Color", Color) = (1, 1, 1, 1)
		_Gloss ("Gloss", Range(8.0, 256)) = 20
	}
	SubShader {
		Tags { "RenderType"="Opaque" "Queue"="Geometry"}
		
		Pass { 
			Tags { "LightMode"="ForwardBase" }
		
			CGPROGRAM
			
			#pragma multi_compile_fwdbase	
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"
			#include "Lighting.cginc"
			#include "AutoLight.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			sampler2D _BumpMap;
			float4 _BumpMap_ST;
			fixed4 _Specular;
			float _Gloss;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 tangent : TANGENT;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float4 uv : TEXCOORD0;
				float4 TtoW0 : TEXCOORD1;  
                float4 TtoW1 : TEXCOORD2;  
                float4 TtoW2 : TEXCOORD3; 
				SHADOW_COORDS(4)
			};
			
			v2f vert(a2v v) {
			 	v2f o;
			 	o.pos = UnityObjectToClipPos(v.vertex);
			 
			 	o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
			 	o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;

				TANGENT_SPACE_ROTATION;
				
				float3 worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;  
                fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
                fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
                fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 
                
                o.TtoW0 = float4(worldTangent.x, worldBinormal.x, worldNormal.x, worldPos.x);  
                o.TtoW1 = float4(worldTangent.y, worldBinormal.y, worldNormal.y, worldPos.y);  
                o.TtoW2 = float4(worldTangent.z, worldBinormal.z, worldNormal.z, worldPos.z);  
  				
  				TRANSFER_SHADOW(o);
			 	
			 	return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				float3 worldPos = float3(i.TtoW0.w, i.TtoW1.w, i.TtoW2.w);
				fixed3 lightDir = normalize(UnityWorldSpaceLightDir(worldPos));
				fixed3 viewDir = normalize(UnityWorldSpaceViewDir(worldPos));
				
				fixed3 bump = UnpackNormal(tex2D(_BumpMap, i.uv.zw));
				bump = normalize(half3(dot(i.TtoW0.xyz, bump), dot(i.TtoW1.xyz, bump), dot(i.TtoW2.xyz, bump)));

				fixed3 albedo = tex2D(_MainTex, i.uv.xy).rgb * _Color.rgb;
				
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;
				
			 	fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(bump, lightDir));
			 	
			 	fixed3 halfDir = normalize(lightDir + viewDir);
			 	fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(bump, halfDir)), _Gloss);
			
				UNITY_LIGHT_ATTENUATION(atten, i, worldPos);

				return fixed4(ambient + (diffuse + specular) * atten, 1.0);
			}
			
			ENDCG
		}
		
		Pass { 
			Tags { "LightMode"="ForwardAdd" }
			
			Blend One One
		
			CGPROGRAM
			
			#pragma multi_compile_fwdadd
			// Use the line below to add shadows for point and spot lights
//			#pragma multi_compile_fwdadd_fullshadows
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "Lighting.cginc"
			#include "AutoLight.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			sampler2D _BumpMap;
			float4 _BumpMap_ST;
			float _BumpScale;
			fixed4 _Specular;
			float _Gloss;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 tangent : TANGENT;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float4 uv : TEXCOORD0;
				float4 TtoW0 : TEXCOORD1;  
                float4 TtoW1 : TEXCOORD2;  
                float4 TtoW2 : TEXCOORD3;
				SHADOW_COORDS(4)
			};
			
			v2f vert(a2v v) {
			 	v2f o;
			 	o.pos = UnityObjectToClipPos(v.vertex);
			 
			 	o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
			 	o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;

				float3 worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;  
                fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
                fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
                fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 
	
  				o.TtoW0 = float4(worldTangent.x, worldBinormal.x, worldNormal.x, worldPos.x);
			  	o.TtoW1 = float4(worldTangent.y, worldBinormal.y, worldNormal.y, worldPos.y);
			  	o.TtoW2 = float4(worldTangent.z, worldBinormal.z, worldNormal.z, worldPos.z);  
			 	
			 	TRANSFER_SHADOW(o);
			 	
			 	return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				float3 worldPos = float3(i.TtoW0.w, i.TtoW1.w, i.TtoW2.w);
				fixed3 lightDir = normalize(UnityWorldSpaceLightDir(worldPos));
				fixed3 viewDir = normalize(UnityWorldSpaceViewDir(worldPos));
				
				fixed3 bump = UnpackNormal(tex2D(_BumpMap, i.uv.zw));
				bump = normalize(half3(dot(i.TtoW0.xyz, bump), dot(i.TtoW1.xyz, bump), dot(i.TtoW2.xyz, bump)));
				
				fixed3 albedo = tex2D(_MainTex, i.uv.xy).rgb * _Color.rgb;
				
			 	fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(bump, lightDir));
			 	
			 	fixed3 halfDir = normalize(lightDir + viewDir);
			 	fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(bump, halfDir)), _Gloss);
			
				UNITY_LIGHT_ATTENUATION(atten, i, worldPos);

				return fixed4((diffuse + specular) * atten, 1.0);
			}
			
			ENDCG
		}
	} 
	FallBack "Specular"
}

```



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
### 法线纹理
- 法线纹理有两种实现模式：将光照等准换到切线坐标系进行计算；将物体表面信息转换到世界坐标系进行计算
#### 转换到法线坐标系

- 在顶点着色器中构建变换矩阵，将摄像机、灯光等变换到法线坐标系
  - 由于计算过程是在顶点着色器中进行，因此会自动插值到不同片元，需要在片元着色器中再归一化一下

```c
v2f vert(a2v v) {  
    v2f o;  
    o.pos = UnityObjectToClipPos(v.vertex);  
    o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;  
    o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;  
    //得到变换矩阵（世界坐标系->切线坐标系）
    fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);    
    fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);    
    fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w;   

    float3x3 worldToTangent = float3x3(worldTangent, worldBinormal, worldNormal);  
    o.lightDir = mul(worldToTangent, WorldSpaceLightDir(v.vertex));  
    o.viewDir = mul(worldToTangent, WorldSpaceViewDir(v.vertex));  

    return o;  
}          
fixed4 frag(v2f i) : SV_Target {              
    fixed3 tangentLightDir = normalize(i.lightDir);  
    fixed3 tangentViewDir = normalize(i.viewDir);  

    fixed4 packedNormal = tex2D(_BumpMap, i.uv.zw);  //从法线贴图读取法线
    fixed3 tangentNormal;  

    tangentNormal = UnpackNormal(packedNormal);  
    tangentNormal.xy *= _BumpScale;  
    tangentNormal.z = sqrt(1.0 - saturate(dot(tangentNormal.xy, tangentNormal.xy)));  
    fixed3 albedo = tex2D(_MainTex, i.uv).rgb * _Color.rgb;  
    fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;  
    fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(tangentNormal, tangentLightDir));  

    fixed3 halfDir = normalize(tangentLightDir + tangentViewDir);  
    fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(tangentNormal, halfDir)), _Gloss);  
    return fixed4(ambient + diffuse + specular, 1.0);  
}
```

#### 转换到世界坐标系

- 在顶点着色器中计算出转换矩阵,并将矩阵拆分（因为插值参数限制最多只能是float4不能是矩阵）、传递到片元着色器
  - 因为在偏远着色器中还需要用矩阵对发线进行变换

```c
v2f vert(a2v v) {
    v2f o;
    o.pos = UnityObjectToClipPos(v.vertex);

    o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
    o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;

    fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
    fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
    fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 

    float3x3 worldToTangent = float3x3(worldTangent, worldBinormal, worldNormal);

    o.lightDir = mul(worldToTangent, WorldSpaceLightDir(v.vertex));
    o.viewDir = mul(worldToTangent, WorldSpaceViewDir(v.vertex));

    return o;
}

fixed4 frag(v2f i) : SV_Target {				
    fixed3 tangentLightDir = normalize(i.lightDir);
    fixed3 tangentViewDir = normalize(i.viewDir);

    fixed4 packedNormal = tex2D(_BumpMap, i.uv.zw);
    fixed3 tangentNormal;

    tangentNormal = UnpackNormal(packedNormal);
    tangentNormal.xy *= _BumpScale;
    tangentNormal.z = sqrt(1.0 - saturate(dot(tangentNormal.xy, tangentNormal.xy)));

    fixed3 albedo = tex2D(_MainTex, i.uv).rgb * _Color.rgb;

    fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

    fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(tangentNormal, tangentLightDir));

    fixed3 halfDir = normalize(tangentLightDir + tangentViewDir);
    fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(tangentNormal, halfDir)), _Gloss);

    return fixed4(ambient + diffuse + specular, 1.0);
}
```

### 渐变纹理

- 主要用于卡通风格渲染
  - 使用渐变纹理来控制漫反射
- 通过漫反射强度控制uv坐标（从而实现按照渐变纹理来表示漫反射强度）

```c
v2f vert(a2v v) {
    v2f o;
    o.pos = UnityObjectToClipPos(v.vertex);

    o.worldNormal = UnityObjectToWorldNormal(v.normal);

    o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

    o.uv = TRANSFORM_TEX(v.texcoord, _RampTex);

    return o;
}

fixed4 frag(v2f i) : SV_Target {
    fixed3 worldNormal = normalize(i.worldNormal);
    fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

    fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;

    // Use the texture to sample the diffuse color
    fixed halfLambert  = 0.5 * dot(worldNormal, worldLightDir) + 0.5;
    fixed3 diffuseColor = tex2D(_RampTex, fixed2(halfLambert, halfLambert)).rgb * _Color.rgb;

    fixed3 diffuse = _LightColor0.rgb * diffuseColor;

    fixed3 viewDir = normalize(UnityWorldSpaceViewDir(i.worldPos));
    fixed3 halfDir = normalize(worldLightDir + viewDir);
    fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(worldNormal, halfDir)), _Gloss);

    return fixed4(ambient + diffuse + specular, 1.0);
}
```

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221171453320.png" alt="image-20241221171453320" style="zoom: 50%;" />

### 遮罩纹理

- 使用遮罩来具体控制模型不同区域的反射（高光强度等）
  - 比如将一个纹理的红色通道作为镜面反射的系数

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221171522698.png" alt="image-20241221171522698" style="zoom:50%;" />
  - 减少砖缝的反光

### 立方体纹理

- 使用立方体纹理实现环境映射
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222210508738.png" alt="image-20241222210508738" style="zoom:50%;" />
  - 使用六张平面材质创建
  - 或者使用特殊布局的纹理，并将texturetype 设置为cubemap
- 代码动态创建纹理
  - 在renderFromPosition位置动态创建一个摄像机，将**当前位置的图像**渲染到指定纹理对象

```c
void OnwizardCreate (
    //-create temporary camera for rendering
    Gameobject go = new Gameobject "CubemapCamera");
	go.AddComponent<Camera>();
	//place it on the object
	go.transform.position = renderFromPosition.position;
	//render into cubemap
	go.GetComponent<Camera>().RenderToCubemap(cubemap);
	//destroy temporary camera
	DestroyImmediate(go);
}
```



- 设置天空盒材质
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222211129219.png" alt="image-20241222211129219" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241222211141682.png" alt="image-20241222211141682" style="zoom:50%;" />

#### 反射

- 通过入射方向和表面法线来计算反射方向，再利用反射方向对立方体纹理进行采样
- 在vert计算反射方向，frag中获取对应立方体纹理片元

```c
fixed4 _Color;
fixed4 _ReflectColor;
fixed _ReflectAmount;
samplerCUBE _Cubemap;

struct a2v {
    float4 vertex : POSITION;
    float3 normal : NORMAL;
};

struct v2f {
    float4 pos : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    fixed3 worldNormal : TEXCOORD1;
    fixed3 worldViewDir : TEXCOORD2;
    fixed3 worldRefl : TEXCOORD3;
    SHADOW_COORDS(4)
};

v2f vert(a2v v) {
    v2f o;

    o.pos = UnityObjectToClipPos(v.vertex);

    o.worldNormal = UnityObjectToWorldNormal(v.normal);

    o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

    o.worldViewDir = UnityWorldSpaceViewDir(o.worldPos);

    // Compute the reflect dir in world space
    o.worldRefl = reflect(-o.worldViewDir, o.worldNormal);

    TRANSFER_SHADOW(o);

    return o;
}

fixed4 frag(v2f i) : SV_Target {
    fixed3 worldNormal = normalize(i.worldNormal);
    fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));		
    fixed3 worldViewDir = normalize(i.worldViewDir);		

    fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;

    fixed3 diffuse = _LightColor0.rgb * _Color.rgb * max(0, dot(worldNormal, worldLightDir));

    // Use the reflect dir in world space to access the cubemap
    fixed3 reflection = texCUBE(_Cubemap, i.worldRefl).rgb * _ReflectColor.rgb;

    UNITY_LIGHT_ATTENUATION(atten, i, i.worldPos);

    // Mix the diffuse color with the reflected color
    fixed3 color = ambient + lerp(diffuse, reflection, _ReflectAmount) * atten;

    return fixed4(color, 1.0);
}
```



#### 折射

- 简化为一次折射，不考虑进入离开介质两次折射

```c
fixed4 _Color;
fixed4 _RefractColor;
float _RefractAmount;
fixed _RefractRatio;
samplerCUBE _Cubemap;

struct a2v {
    float4 vertex : POSITION;
    float3 normal : NORMAL;
};

struct v2f {
    float4 pos : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    fixed3 worldNormal : TEXCOORD1;
    fixed3 worldViewDir : TEXCOORD2;
    fixed3 worldRefr : TEXCOORD3;
    SHADOW_COORDS(4)
};

v2f vert(a2v v) {
    v2f o;
    o.pos = UnityObjectToClipPos(v.vertex);

    o.worldNormal = UnityObjectToWorldNormal(v.normal);

    o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

    o.worldViewDir = UnityWorldSpaceViewDir(o.worldPos);

    // Compute the refract dir in world space
    o.worldRefr = refract(-normalize(o.worldViewDir), normalize(o.worldNormal), _RefractRatio);

    TRANSFER_SHADOW(o);

    return o;
}

fixed4 frag(v2f i) : SV_Target {
    fixed3 worldNormal = normalize(i.worldNormal);
    fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));
    fixed3 worldViewDir = normalize(i.worldViewDir);

    fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;

    fixed3 diffuse = _LightColor0.rgb * _Color.rgb * max(0, dot(worldNormal, worldLightDir));

    // Use the refract dir in world space to access the cubemap
    fixed3 refraction = texCUBE(_Cubemap, i.worldRefr).rgb * _RefractColor.rgb;

    UNITY_LIGHT_ATTENUATION(atten, i, i.worldPos);

    // Mix the diffuse color with the refract color
    fixed3 color = ambient + lerp(diffuse, refraction, _RefractAmount) * atten;

    return fixed4(color, 1.0);
}
```



#### 菲涅尔反射

- 用于计算被反射的光和入射光之间的比例
- `fixed fresnel = _FresnelScale + (1 - _FresnelScale) * pow(1 - dot(worldViewDir, worldNormal), 5);`

### 渲染纹理

- 将摄像机内容渲染到**渲染纹理**

#### 镜子

- 创建一个摄像机，使得其视野是镜子中希望显示的图像，将创建的渲染纹理MirrorTexture若拽到摄像机的目标纹理

```c
sampler2D _MainTex;

struct a2v {
    float4 vertex : POSITION;
    float3 texcoord : TEXCOORD0;
};

struct v2f {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

v2f vert(a2v v) {
    v2f o;
    o.pos = UnityObjectToClipPos(v.vertex);

    o.uv = v.texcoord;
    // Mirror needs to filp x
    o.uv.x = 1 - o.uv.x;

    return o;
}

fixed4 frag(v2f i) : SV_Target {
    return tex2D(_MainTex, i.uv);
}
```



#### 玻璃

- 除了摄像机，可以使用GrabPass来获取屏幕图像，将当前屏幕的图像绘制在一张纹理中
- 与透明度混合可以实现更多的后处理，可以用于实现模拟折射来实现玻璃等效果
- 使用cubemap来实现玻璃反射，使用grabpass来获取玻璃后的屏幕图像，通过法线贴图便宜来实现折射效果

```c
// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Chapter 10/Glass Refraction" {
    Properties {
        //玻璃纹理
        _MainTex ("Main Tex", 2D) = "white" {}
        //法线贴图
        _BumpMap ("Normal Map", 2D) = "bump" {}
        //环境立方体贴图
        _Cubemap ("Environment Cubemap", Cube) = "_Skybox" {}
        //折射强度
        _Distortion ("Distortion", Range(0, 100)) = 10
        //折射的权重，决定折射和反射的混合比例
        _RefractAmount ("Refract Amount", Range(0.0, 1.0)) = 1.0
    }
    SubShader {
        // We must be transparent, so other objects are drawn before this one.
        Tags { "Queue"="Transparent" "RenderType"="Opaque" }

        // This pass grabs the screen behind the object into a texture.
        // We can access the result in the next pass as _RefractionTex
        GrabPass { "_RefractionTex" }

        Pass {		
            CGPROGRAM

                #pragma vertex vert
                #pragma fragment frag

                #include "UnityCG.cginc"

                sampler2D _MainTex;
            float4 _MainTex_ST;
            sampler2D _BumpMap;
            float4 _BumpMap_ST;
            samplerCUBE _Cubemap;
            float _Distortion;
            fixed _RefractAmount;
            sampler2D _RefractionTex;
            float4 _RefractionTex_TexelSize;

            struct a2v {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
                float4 tangent : TANGENT; 
                float2 texcoord: TEXCOORD0;
            };

            struct v2f {
                float4 pos : SV_POSITION;
                float4 scrPos : TEXCOORD0;
                float4 uv : TEXCOORD1;
                float4 TtoW0 : TEXCOORD2;  
                float4 TtoW1 : TEXCOORD3;  
                float4 TtoW2 : TEXCOORD4; 
            };

            v2f vert (a2v v) {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);
 				// 2. 计算抓取屏幕位置，用于后续的折射采样
                o.scrPos = ComputeGrabScreenPos(o.pos);

                o.uv.xy = TRANSFORM_TEX(v.texcoord, _MainTex);
                o.uv.zw = TRANSFORM_TEX(v.texcoord, _BumpMap);

                float3 worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;  
                fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
                fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
                fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 

                o.TtoW0 = float4(worldTangent.x, worldBinormal.x, worldNormal.x, worldPos.x);  
                o.TtoW1 = float4(worldTangent.y, worldBinormal.y, worldNormal.y, worldPos.y);  
                o.TtoW2 = float4(worldTangent.z, worldBinormal.z, worldNormal.z, worldPos.z);  

                return o;
            }

            fixed4 frag (v2f i) : SV_Target {		
                float3 worldPos = float3(i.TtoW0.w, i.TtoW1.w, i.TtoW2.w);
                fixed3 worldViewDir = normalize(UnityWorldSpaceViewDir(worldPos));

                // Get the normal in tangent space
                fixed3 bump = UnpackNormal(tex2D(_BumpMap, i.uv.zw));	

                // Compute the offset in tangent space
                float2 offset = bump.xy * _Distortion * _RefractionTex_TexelSize.xy;
                i.scrPos.xy = offset * i.scrPos.z + i.scrPos.xy;
                fixed3 refrCol = tex2D(_RefractionTex, i.scrPos.xy/i.scrPos.w).rgb;

                // Convert the normal to world space
                bump = normalize(half3(dot(i.TtoW0.xyz, bump), dot(i.TtoW1.xyz, bump), dot(i.TtoW2.xyz, bump)));
                fixed3 reflDir = reflect(-worldViewDir, bump);
                fixed4 texColor = tex2D(_MainTex, i.uv.xy);
                fixed3 reflCol = texCUBE(_Cubemap, reflDir).rgb * texColor.rgb;

                fixed3 finalColor = reflCol * (1 - _RefractAmount) + refrCol * _RefractAmount;

                return fixed4(finalColor, 1);
            }

            ENDCG
        }
    }

    FallBack "Diffuse"
}

```



### 程序纹理

- 

## 透明效果

- 透明度测试：通过比较片元的透明度值（Alpha 通道）与指定阈值
  - 添加透明度测试：将 Alpha 值与指定的阈值（`Alpha Cutoff`）比较。
    - 如果满足条件（如 Alpha 值 > 阈值），片元通过测试并被渲染。
    - 如果不满足条件，片元被丢弃，不会参与后续的渲染管线。
  - 片元要么完全渲染，要么完全丢弃，不需要进行混合运算
- 透明度混合：通过将片元的颜色与背景颜色按透明度比例混合，计算出最终颜色
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221172837991.png" alt="image-20241221172837991" style="zoom: 50%;" />
  - 通常启用透明度混合时会禁用深度缓冲写入，以避免影响后续透明物体的渲染。（因此可能要手动排序，**调整渲染顺序**）

#### 渲染顺序

- 先渲染所有不透明物体，并开启深度测试和深度写入
- 按照距离摄像机远近对半透明物体排序，按照从后往前的的顺序渲染，开启深度测试，关闭深度写入
  - 透明物体渲染顺序会导致颜色叠加出现问题，（比如先红色 再 蓝色， 和 先蓝色 在红色）两种方式混合出的颜色是不同的
- 通过渲染队列进行控制
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221174726794.png" alt="image-20241221174726794" style="zoom:50%;" />
- `Tags{"Queue"="Transparent"}`就用于透明混合

#### 透明度测试

- 在片元着色器中添加测试

```c
if ((texColor.a - _Cutoff) < 0.0) {
    discard;
}
//等价写法
clip (texColor.a - _Cutoff);
```



#### 透明度混合

- 混合方式
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221184805013.png" alt="image-20241221184805013" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221184953890.png" alt="image-20241221184953890" style="zoom:50%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221185251192.png" alt="image-20241221185251192" style="zoom:50%;" />
- 混合类型模板
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221185342246.png" alt="image-20241221185342246" style="zoom:50%;" />

```c
Shader "Unity Shaders Book/Chapter 8/Alpha Blend" {
    Properties {
        _Color ("Color Tint", Color) = (1, 1, 1, 1)
        _MainTex ("Main Tex", 2D) = "white" {}
        _AlphaScale ("Alpha Scale", Range(0, 1)) = 1//控制整个物体的全局不透明度
    }
    SubShader {
        Tags {"Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent"}

        Pass {
            Tags { "LightMode"="ForwardBase" }

            ZWrite Off//关闭深度写入
                //ZTest 控制透明测试
            Blend SrcAlpha OneMinusSrcAlpha//开启混合

            CGPROGRAM

            #pragma vertex vert
            #pragma fragment frag

            #include "Lighting.cginc"

            fixed4 _Color;
            sampler2D _MainTex;
            float4 _MainTex_ST;
            fixed _AlphaScale;

            struct a2v {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
                float4 texcoord : TEXCOORD0;
            };

            struct v2f {
                float4 pos : SV_POSITION;
                float3 worldNormal : TEXCOORD0;
                float3 worldPos : TEXCOORD1;
                float2 uv : TEXCOORD2;
            };

            v2f vert(a2v v) {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vertex);

                o.worldNormal = UnityObjectToWorldNormal(v.normal);

                o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

                o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);

                return o;
            }

            fixed4 frag(v2f i) : SV_Target {
                fixed3 worldNormal = normalize(i.worldNormal);
                fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

                fixed4 texColor = tex2D(_MainTex, i.uv);

                fixed3 albedo = texColor.rgb * _Color.rgb;

                fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

                fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

                return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
            }

            ENDCG
        }
    } 
    FallBack "Transparent/VertexLit"
}
```

##### 半透明渲染方式

- ZTest On能保证透明物体和不透明物体间的渲染正确
  - ZTest Off后，会导致半透明物体直接将所有的不透明物体覆盖。。本来被不透明物体覆盖的，看不见的半透明物体都错误的显示出来了。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinede47591c0f7446af5acaef135d91548c6.png" alt="在这里插入图片描述" style="zoom: 33%;" />
- ZWrite On 能保证**不同透明物体**间穿插渲染正确
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinede104dc4f5547dbc59f54e679aeb9d1ff.png" alt="在这里插入图片描述" style="zoom:33%;" />
- Cull Back能避免部分背面的渲染异常问题（控制剔除的面Cull Back/Front/Off）
  - 虽然避免了自身出现穿插的问题，但是却没有还原出背面的不透明效果。缺失了真实感。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedbc562e757888f976bec2c7383b38347d.png" alt="在这里插入图片描述" style="zoom:33%;" />
- 

- 由于关闭了深度写入，我们就只能纯粹用Unity提供的渲染队列来解决渲染顺序这个问题。但是当遇到渲染模型本身遮挡效果复杂的情况下，效果往往会出错
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221175932278.png" alt="image-20241221175932278" style="zoom:33%;" />
  - 可以通过开启深度写入来修复显示错误
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedimage-20241221182155654.png" alt="image-20241221182155654" style="zoom:33%;" />

```c
Pass {
    ZWrite On
    ColorMask 0
}

Pass {
    Tags { "LightMode"="ForwardBase" }

    ZWrite Off
    Blend SrcAlpha OneMinusSrcAlpha
}
```

- 使用两阶段pass
  - **第一个 Pass**（“Depth Only” Pass）只负责向深度缓冲写入 (ZWrite On)，并且 `ColorMask 0` 意味着它并不往屏幕上画任何颜色。
  - **第二个 Pass**（“ForwardBase” Pass）才进行真正的渲染，包括光照计算、纹理采样、Alpha Blending 等，但它将 `ZWrite Off`，避免在这个阶段修改深度缓冲。



- 默认情况下渲染是cull back会剔除背面，也就是说物体内部不会被渲染出来

  - 但是对于透明物体，背面可能是可见的，要`Cull Off`

  - 拆分为两个pass，第一个渲染背面，第二个渲染正面

```c
// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Chapter 8/Alpha Blend With Both Side" {
	Properties {
		_Color ("Color Tint", Color) = (1, 1, 1, 1)
		_MainTex ("Main Tex", 2D) = "white" {}
		_AlphaScale ("Alpha Scale", Range(0, 1)) = 1
	}
	SubShader {
		Tags {"Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent"}
		
		Pass {
			Tags { "LightMode"="ForwardBase" }
			
			// First pass renders only back faces 
			Cull Front
			
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha
			
			CGPROGRAM
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "Lighting.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed _AlphaScale;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;
			};
			
			v2f vert(a2v v) {
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);
				
				o.worldNormal = UnityObjectToWorldNormal(v.normal);
				
				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;
				
				o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);
				
				return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));
				
				fixed4 texColor = tex2D(_MainTex, i.uv);
				
				fixed3 albedo = texColor.rgb * _Color.rgb;
				
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;
				
				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));
				
				return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
			}
			
			ENDCG
		}
		
		Pass {
			Tags { "LightMode"="ForwardBase" }
			
			// Second pass renders only front faces 
			Cull Back
			
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha
			
			CGPROGRAM
			
			#pragma vertex vert
			#pragma fragment frag
			
			#include "Lighting.cginc"
			
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed _AlphaScale;
			
			struct a2v {
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD0;
			};
			
			struct v2f {
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;
			};
			
			v2f vert(a2v v) {
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);
				
				o.worldNormal = UnityObjectToWorldNormal(v.normal);
				
				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;
				
				o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);
				
				return o;
			}
			
			fixed4 frag(v2f i) : SV_Target {
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));
				
				fixed4 texColor = tex2D(_MainTex, i.uv);
				
				fixed3 albedo = texColor.rgb * _Color.rgb;
				
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;
				
				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));
				
				return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
			}
			
			ENDCG
		}
	} 
	FallBack "Transparent/VertexLit"
}
```

## 动画

### 纹理动画

### 顶点动画

# shader 蓝图

## 基本
![image.png|650](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212205645.png)
1. blackboard 中用于创建输入变量（再外面 material 处的面板可以直接设置）
2. graph inspector 处面板可以用于设置一个节点的具体参数，比如设置默认颜色

### 子蓝图

- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241212213845.png)
