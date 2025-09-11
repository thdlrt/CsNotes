### 环境配置
#### 调试（rider）
- 编辑运行配置
	- ![image.png|600](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240927174015.png)
	- 将代码 2 拷贝，在游戏初始化时运行
```Csharp
private void InitializeLuaDebugger()  
{  
    Debug.Log("<color=yellow>Initializing Lua Debugger...</color>");  
    luaEnv.DoString(@"  
        package.cpath = package.cpath .. ';C:/Users/MSI/AppData/Roaming/JetBrains/Rider2024.1/plugins/EmmyLua/debugger/emmy/windows/x64/?.dll'        local dbg = require('emmy_core')        dbg.tcpListen('localhost', 9966)        dbg.waitIDE()    ");  
    Debug.Log("<color=green>Lua Debugger Initialized</color>");  
}
```
- 注意这个总模式下 unity 会卡住等待 ide 连接
### 与 C# 交互
#### C# 调用 lua
- 直接执行语句 `luaEnv.DoString("")`
#### lua 调用 C\#

### 热更
- 简单的热更实现思路，维护每个文件的更新时间，如果发现有新的更改，就卸载模块重新加载