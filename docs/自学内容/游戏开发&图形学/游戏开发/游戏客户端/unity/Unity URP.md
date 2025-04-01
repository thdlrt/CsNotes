>  Universal Render Pipeline 通用渲染管线

### 基本使用
#### URP 配置
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
- （延迟）渲染流程
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250401174901.png)
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250401174924.png)


##### 创建对象

##### General
##### Quality
##### Lighting
##### Shadows
##### Post-processing
