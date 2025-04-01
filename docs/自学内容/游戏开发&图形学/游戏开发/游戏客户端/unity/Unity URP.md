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
- 

## 后处理
## 着色器与材质