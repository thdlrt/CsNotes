## Package Manager
- 用于管理Unity项目中所需的各种库、插件和工具包
## 资源加载
![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241103171530.png)
### 文件结构
#### 资源存储
**Resource**
- Resources文件夹是一个**只读**的文件夹，通过Resources.Load()来读取对象。
- 这里的文件会被**全部**打到发布包中
	- 打包时会进行压缩和加密
- 适合存放 prefab 等对象

**streamingAssets**
- **只读**，资源不会被加密，是原封不动进行打包
- 适合存储一些二进制文件

**Application**.dataPath
- 只读，防止资源数据

**Application**.persistentDataPath
- 可读可写，存储配置文件等
- 在PC上的地址是：C:\Users\用户名 \AppData\LocalLow\DefaultCompany\test
#### Editor
- 存储的资源和脚本不会被打包进发布包，脚本也只在编辑时使用，用于存放工具类的脚本以及一些编辑时使用的 DLL
#### Scripts
- 存储游戏脚本
#### Scenes
- 存储场景数据，以及灯光烘培、导航数据等
#### plugins
- 存储第三方 SDK 以及库
#### Shaders
- 存储 shader
### AssetBundle
- AssetBundle可以将多个资源**打包**为单个文件，通过StreamingAssets分发，且可以从该目录直接加载AssetBundle资源。这种方式避免了资源的解压和重组，加载速度更**快**。
- 先手动或通过编辑器脚本进行打包，得到 AssetBundle，用于游戏中加载以及获取数据

- 手动设置 assetbundle
	- ![image.png|300](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241103172649.png)
- 
### ASS 系统
- 优势
	- **解耦资源路径与加载逻辑**：资源的路径变动不会影响到代码加载逻辑。
	- **灵活的更新机制**：支持差异化更新，提升用户体验，尤其适合在线游戏。
	- **提升资源管理效率**：跨平台和多环境配置简化了资源管理过程，适合大规模游戏开发项目。
- 提供了一种按“地址”加载资产的方法

- 也是通过AssetBundle 进行打包存储，是支持热更新的（Resource 下就是只读）

- 以 group 为单位进行分组
## Assembly Definition files
- 将项目中的脚本划分为多个独立的程序集，每个程序集通过一个**asmdef文件**来定义。这样可以将代码按模块组织，不同模块之间可以**独立编译和引用**，可以起到加速编译的作用，并确保模块代码的安全性和独立性，减少耦合
- 主要用于大型项目的优化以及依赖管理等
- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241103151043.png)

- 通过Assets > Create > Assembly Definition菜单创建. asmdef 文件
- asmdef 文件的 name 属性就是程序集的名称
- 只需要在脚本文件中创建 asmdef 文件，就可以自动实现模块的划分，此外可能还需要生动设置包之间的依赖关系
- 嵌套文件夹中不同层级都可以有 asmdef，每个脚本被添加到离这个脚本最短路径的ADF中去