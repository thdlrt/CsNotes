## Package Manager
- 用于管理Unity项目中所需的各种库、插件和工具包
### 包管理
- Packages 文件夹下主要存储了工程所需包的配置文件
	- `manifest.json`：存储项目中所需的所有 Unity Package（包）的依赖信息（包含包的名称及对应的版本号）![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250404003231.png)
	- `packages-lock.json`：记录项目中包的确切版本和依赖关系树![image.png|400](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20250404003247.png)
- Unity 的 Package Manager 管理的包都是自动维护的，实际代码通常存放在 Library/PackageCache 中，这里的文件是**只读**且由 Unity 自动生成的映射。
	- 修改缓存中的文件不会被持久保存
- 如果项目中需要对这些代码进行修改，一般的做法是将包嵌入到工程中，这样对应文件就会从 Library/PackageCache 移动到工程的 Packages 文件夹中，就可以自由修改而不会被覆盖。
	- 可以把文件从 Library/PackageCache 中复制出来，放到 Packages 文件夹下，自行管理和修改。

- package 的加载过程
	- 解析 manifest.json：
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
- AssetBundle 可以更好的进行平台优化和按需加载

- 手动设置 assetbundle
	- ![image.png|300](https://thdlrt.oss-cn-beijing.aliyuncs.com/undefined20241103172649.png)
- 一个简易的打包工具代码
	- 加载 `AssetBundle` 的时候，如果 `AssetBundle` 依赖了另一个 `AssetBundle`，则**需要加载依赖的**这个 `AssetBundle`（不加载会造成连接缺失等）
	- 如果依赖文件不打包进其他 assetbundle，则会被打包进该 assetbundle，也就不存在依赖问题
	- 打包时可以自动生成这种依赖关系
```c
using UnityEngine;
using UnityEditor;

public class BuildAB
{
    [MenuItem("Tools/BuildAB")]
    public static void StartBuild()
    {
    //打包AssetBundle，输出目录Application.streamingAssetsPath
        BuildPipeline.BuildAssetBundles(Application.streamingAssetsPath, 
        BuildAssetBundleOptions.ChunkBasedCompression, 
        BuildTarget.StandaloneWindows);
    }
}
```
- 一个简单的管理系统
```csharp
using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;

public class AssetBundleLoaderMgr
{
    /// <summary>
    /// 初始化，加载AssetBundleManifest，方便后面查找依赖
    /// </summary>
    public void Init()
    {
        string streamingAssetsAbPath = Path.Combine(Application.streamingAssetsPath, "StreamingAssets");
        AssetBundle streamingAssetsAb = AssetBundle.LoadFromFile(streamingAssetsAbPath);
        m_manifest = streamingAssetsAb.LoadAsset<AssetBundleManifest>("AssetBundleManifest");
    }

    /// <summary>
    /// 加载AssetBundle
    /// </summary>
    /// <param name="abName">AssetBundle名称</param>
    /// <returns></returns>
    public AssetBundle LoadAssetBundle(string abName)
    {
        AssetBundle ab = null;
        if (!m_abDic.ContainsKey(abName))
        {
            string abResPath = Path.Combine(Application.streamingAssetsPath, abName);
            ab = AssetBundle.LoadFromFile(abResPath);
            m_abDic[abName] = ab;
        }
        else
        {
            ab = m_abDic[abName];
        }

        //加载依赖
        string[] dependences = m_manifest.GetAllDependencies(abName);
        int dependenceLen = dependences.Length;
        if (dependenceLen > 0)
        {
            for (int i = 0; i < dependenceLen; i++)
            {
                string dependenceAbName = dependences[i];
                if (!m_abDic.ContainsKey(dependenceAbName))
                {
                    AssetBundle dependenceAb = LoadAssetBundle(dependenceAbName);
                    m_abDic[dependenceAbName] = dependenceAb;
                }
            }
        }

        return ab;
    }

    /// <summary>
    /// 从AssetBundle中加载Asset
    /// </summary>
    /// <typeparam name="T">类型</typeparam>
    /// <param name="abName">AssetBundle名</param>
    /// <param name="assetName">Asset名</param>
    /// <returns></returns>
    public T LoadAsset<T>(string abName, string assetName) where T : Object
    {
        AssetBundle ab = LoadAssetBundle(abName);
        T t = ab.LoadAsset<T>(assetName);
        return t;
    }

    /// <summary>
    /// 缓存加载的AssetBundle，防止多次加载
    /// </summary>
    private Dictionary<string, AssetBundle> m_abDic = new Dictionary<string, AssetBundle>();

    /// <summary>
    /// 它保存了各个AssetBundle的依赖信息
    /// </summary>
    private AssetBundleManifest m_manifest;

    /// <summary>
    /// 单例
    /// </summary>
    private static AssetBundleLoaderMgr s_instance;
    public static AssetBundleLoaderMgr instance
    {
        get
        {
            if (null == s_instance)
                s_instance = new AssetBundleLoaderMgr();
            return s_instance;
        }
    }
}

```
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