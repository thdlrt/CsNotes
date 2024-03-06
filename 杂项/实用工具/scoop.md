- windows包管理器

- 安装

```shell
    # 设置 PowerShell 执行策略
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
    # 下载安装脚本
    irm get.scoop.sh -outfile 'install.ps1'
    # 执行安装, --ScoopDir 参数指定 Scoop 安装路径
    .\install.ps1 -ScoopDir 'C:\Scoop'
```

^255b06

- 更新`scoop update`

- 安装软件包

  - `scoop install curl`

- 卸载

  - `scoop uninstall curl`

- 查看配置信息

  - `scoop info 7zip`

- 查看官网

  - `scoop home 7zip`

- 更新软件包

  - `scoop update curl`
  - `scoop update *`

- 搜索软件包

  - `scoop search ssh`

- scoop bucket软件仓库

  - 添加第三方软件仓库`scoop bucket add xx`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231223143807459.png" alt="image-20231223143807459" style="zoom:33%;" />
    - 搜索时的source就表示来自哪一个bucket，可以针对进行安装 ^2009e9

