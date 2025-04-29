>  Universal Render Pipeline 通用渲染管线
## 渲染管线
### 基本概念
- URP 资源可以控制通用渲染管线的图形功能及质量设置等，继承自RenderPipelineAsset，可以创建多个 URP 资源并进行切换
- 两个类：
	- **Universal Render Pipeline Asset**：定义整个渲染管线的全局设置，包括质量、阴影、光照、后处理和性能优化等。
		- 可以为不同的平台（如 PC、移动设备）创建不同的 Render Pipeline Asset 配置文件，以便优化性能。
		- 包含一个默认的 **Volume Profile** 文件，用于定义全局后处理效果。
		- 包含对 **Universal Renderer Data** 的引用，指定当前渲染器的具体设置。
	- **Universal Renderer Data**：URP 的渲染器配置文件，专注于定义渲染器的具体行为和功能。
		- 支持添加自定义的渲染特性（Renderer Features），例如额外的后处理效果、轮廓描边、屏幕空间效果等。
		- 定义渲染器的行为，例如是否启用深度纹理、法线纹理，或是否启用透明对象的排序。
- 在 Project Settings 窗口的 Graphics 选项卡中设定使用的Universal Render Pipeline Asset
### 编辑渲染管线
#### 自定义渲染阶段
- 可供选择的阶段
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250401174901.png)
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefinedundefined20250401174924.png)

- **ScriptableRendererFeature**：定义自定义渲染功能。
	- 这是一个配置层，用来**注册和管理你的自定义渲染逻辑**。
	- 它会初始化并将自定义的渲染逻辑（**ScriptableRenderPass**）插入到渲染管线中。
- **ScriptableRenderPass**：定义在渲染管线中执行的具体渲染逻辑。
	- 这是实际执行渲染逻辑的地方。
	- 可以在这里指定插入的渲染阶段（通过 `RenderPassEvent`），并实现具体的渲染任务
- 基本步骤
	- 创建一个继承 **ScriptableRendererFeature** 类。
	- 重写一系列方法，其中在 `Create()` 方法中初始化自定义的渲染 Pass。
	- 打开 **Universal Renderer Data** 文件，在 **Renderer Features** 部分，点击 **Add Renderer Feature**，选择刚刚创建的 `CustomRenderFeature`。从而使用![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250401205554.png)

```csharp
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;

public class CustomRenderFeature : ScriptableRendererFeature
{
    private CustomRenderPass renderPass;

    public override void Create()
    {
        // 初始化渲染 Pass，绑定
        renderPass = new CustomRenderPass(RenderPassEvent.AfterRenderingSkybox);
    }

    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        // 将渲染 Pass 添加到渲染管线
        renderer.EnqueuePass(renderPass);
    }

    class CustomRenderPass : ScriptableRenderPass
    {
        public CustomRenderPass(RenderPassEvent passEvent)
        {
            // 设置渲染事件（插入点）
            renderPassEvent = passEvent;
        }

        public override void Execute(ScriptableRenderContext context, ref RenderingData renderingData)
        {
            // 自定义渲染逻辑
            CommandBuffer cmd = CommandBufferPool.Get("Custom Render Pass");

            // 示例：清屏为红色
            cmd.ClearRenderTarget(true, true, Color.red);

            // 执行命令缓冲区
            context.ExecuteCommandBuffer(cmd);
            CommandBufferPool.Release(cmd);
        }
    }
}
```
## 灯光
## 摄像机
- 基础摄像机：渲染到渲染目标的通用摄像机
	- 至少要有一个基础摄像机
- 叠加摄像机：渲染到**另一个摄像机的输出之上**
	- 基础摄像机啊的输出可以和一个或多个叠加摄像机的输出结合起来，即**摄像机堆叠**
- 通过修改属性 `RenderType` 来设置摄像机的类型
### 多摄像机渲染
#### 摄像机堆叠
- 向基础摄像机添加堆叠摄像机
	- ![image.png|364](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250401222927.png)
#### 多个摄像机渲染到同一个渲染目标
- 可以实现将多个摄像机的内容分别渲染到屏幕上的不同区域
	- 通过设置视口坐标 `viewport rect` 来控制
	- xy 参数定义视口的起始位置（左下角）范围\[0- 1\]
	- wh 定义视口的宽度和高度（在总体的比例）范围\[0- 1\]
### 渲染到渲染纹理
- 只需要将摄像机的 output target 设置为 texture，并拖入目标渲染纹理即可
### 清除、渲染顺序和过度绘制
- 基础摄像机：
	- 通过 **Background Type**可以设置在循环开始时对颜色缓冲区的操作，如将其清除初始化为纯色
	- 在每个渲染循环开始时会清除其深度缓冲区
- 叠加摄像机
	- 在渲染循环开始时，叠加摄像机接收一个颜色缓冲区，该缓冲区包含来自摄像机堆叠中先前摄像机的颜色数据。颜色缓冲区的内容不会清除。
	- 通过**Clear Depth**设置是否清空深度缓冲区，当 **Clear Depth** 设置为 false 时，叠加摄像机会在将其视图绘制到颜色缓冲区之前针对深度缓冲区进行测试。
#### 摄像机剔除和渲染顺序
1. Unity 获取场景中所有激活的[基础摄像机](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/camera-types-and-render-type.html#base-camera)的列表。
2. Unity 将激活的基础摄像机组织成 2 组：一组摄像机将其视图渲染到渲染纹理，另一组摄像机将其视图渲染到屏幕。
3. Unity 按照 **Priority** 顺序对渲染到渲染纹理的基础摄像机进行排序，因此具有更高 **Priority** 值的摄像机将最后绘制。
4. 对于渲染到渲染纹理的每个基础摄像机，Unity 执行以下步骤：
    1. 剔除基础摄像机
    2. 将基础摄像机渲染到渲染纹理
    3. 对于基础摄像机的[摄像机堆叠](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/camera-stacking.html)中的每个[叠加摄像机](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/camera-types-and-render-type.html#overlay-camera)，按照在摄像机堆叠中定义的顺序：
        1. 剔除叠加摄像机
        2. 将叠加摄像机渲染到渲染纹理
5. Unity 按照 **Priority** 顺序对渲染到屏幕的基础摄像机进行排序，因此具有更高 **Priority** 值的摄像机将最后绘制。
6. 对于渲染到屏幕的每个基础摄像机，Unity 执行以下步骤：
    1. 剔除基础摄像机
    2. 将基础摄像机渲染到屏幕
    3. 对于基础摄像机的摄像机堆叠中的每个叠加摄像机，按照在摄像机堆叠中定义的顺序：
        1. 剔除叠加摄像机
        2. 将叠加摄像机渲染到屏幕
### 渲染前的额外处理
- Unity 在每一帧中渲染每个活动摄像机之前会引发一个 `beginCameraRendering` 事件。
	- 如果摄像机处于非活动状态（例如，如果摄像机游戏对象上的 **Camera** 组件复选框被清除），Unity 不会引发此摄像机的 `beginCameraRendering` 事件。
- 通过订阅此事件的方法时，可以在 Unity 渲染摄像机之前执行自定义逻辑。
```csharp
private void OnEnable()
   {
       // 添加 WriteLogMessage 作为 RenderPipelineManager.beginCameraRendering 事件的委托
       RenderPipelineManager.beginCameraRendering += WriteLogMessage;
   }

   // Unity 在禁用该组件时会自动调用这一方法
   private void OnDisable()
   {
       // 移除作为 RenderPipelineManager.beginCameraRendering 事件的委托的 WriteLogMessage
       RenderPipelineManager.beginCameraRendering -= WriteLogMessage;
   }
```
## 后处理
- 条件：
	- 摄像机勾选 **Post Processing** 复选框
	- 场景中创建有 Volume 组件的对象，并拖入配置文件
### 范围控制
- 创建不同类型（范围）的 volume：
	- ![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250401232700.png)
- 将 Mode 设置为 **Global** 时，体积会影响场景中各处的摄像机。将 Mode 设置为 **Local** 时，如果**摄像机在碰撞体的边界以内**，则体积会影响摄像机。

### 效果列表
[效果列表 \| Universal RP \| 12.1.1](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/EffectList.html)
## 着色器与材质
### 着色模型
- 基于物理着色：基于物理着色 (PBS) 根据**物理原理**计算从表面反射的光量，从而模拟对象在现实生活中的外观。
	- 遵循能量守恒和物理定律
	- 用于：光照 Lit ；粒子光照 Particles Lit
	- 性能要求较高，不适合低端移动平台硬件

- 简单着色：适用于风格化的视觉效果或适用于性能较弱的平台上的游戏，不会呈现真实的逼真感
	- 不遵守能量守恒
	- 基于Blinn-Phong 模型
	- 用于：简单光照 Simple Lit；粒子简单光照 Particles Simple Lit

- 烘焙光照着色：没有实时光照，材质从光照贴图/探针中接收红配光照，以较低的性能成本为场景增加一些深度，采用此着色模型的游戏可以在性能较弱的平台上运行。
	- URP 烘焙光照着色器是唯一使用烘焙光照着色模型的着色器。

- 无光照：没有方向光，也没有烘焙光照，由于无需进行光照计算，这些着色器的编译速度比具有光照的着色器更快。
	- 用于：无光照 Unlit；粒子无光照 Particles Unlit
### 内置着色器
[着色器和材质 \| Universal RP \| 12.1.1](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/shaders-in-universalrp.html)
### 编写着色器
[[unity shader（HLSL）]]
#### ShaderLab着色器的基本结构
- `Shader "Example/URPUnlitShaderBasic"`：此声明中的路径决定了 Unity 着色器在材质 Shader 菜单中的显示名称和位置。
- Properties 代码块：包含用户**可在材质 Inspector 窗口中**设置的属性的声明。
- SubShader 代码块
	- 一个 Unity 着色器源文件包含一个或多个 SubShader 代码块。渲染网格时，Unity 会选择与目标设备上的 GPU 兼容的第一个 SubShader。
	- `Tags { "RenderType" = "Opaque" "RenderPipeline" = "UniversalPipeline" }` 表示适用范围：如RenderPipeline 的 SubShader 标签告诉 Unity 将此 SubShader 用于哪些渲染管线，而 UniversalPipeline 的值指示 Unity 应将此 SubShader 用于 URP。
- Pass 代码块
	- 包含 HLSL 程序代码
```c
// 此着色器使用可由用户通过材质 Inspector 窗口更改的颜色来
//填充网格形状。
Shader "Example/URPUnlitShaderColor"
{
    // _BaseColor 变量在材质的 Inspector 中显示为一个名为
    // Base Color 的字段。您可以使用它来选择自定义颜色。此变量的
    // 默认值为 (1, 1, 1, 1)。
    Properties
    {
        [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
    }

    SubShader
    {
        Tags { "RenderType" = "Opaque" "RenderPipeline" = "UniversalPipeline" }

        Pass
        {
            HLSLPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"

            struct Attributes
            {
                float4 positionOS   : POSITION;
            };

            struct Varyings
            {
                float4 positionHCS  : SV_POSITION;
            };

            // 要使 Unity 着色器 SRP Batcher 兼容，请在
            // 名为 UnityPerMaterial 的单个 CBUFFER 代码块中声明与材质
            // 相关的所有属性。
            CBUFFER_START(UnityPerMaterial)
                // 以下行声明了 _BaseColor 变量，以便
                // 可以在片元着色器中使用它。
                half4 _BaseColor;
            CBUFFER_END

            Varyings vert(Attributes IN)
            {
                Varyings OUT;
                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);
                return OUT;
            }

            half4 frag() : SV_Target
            {
                // 返回 _BaseColor 值。
                return _BaseColor;
            }
            ENDHLSL
        }
    }
}
```

## 2D URP