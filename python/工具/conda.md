[ Anaconda conda常用命令](https://blog.csdn.net/chenxy_bwave/article/details/119996001)

## 管理conda

- 查看版本`conda --version`
- 提示`conda -h`

## 管理环境

- 创建虚拟环境`conda create -n env_name python=3.8`

  -  这表示创建python版本为3.8、名字为env_name的虚拟环境

- 查看虚拟环境`conda env list`

- 激活虚拟环境`conda activate env_name`

- 退出虚拟环境`conda activate`

- 删除虚拟环境`conda env remove -n env_name`

  - 删除包`conda remove --name env_name package_name`

- 导出环境

  - ```
    #获得环境中的所有配置
    conda env export --name myenv > myenv.yml
    #重新还原环境
    conda env create -f  myenv.yml
    ```

### 管理包

- 查询当前环境中已经安装的包`conda list`
- 安装包`conda install package_name`
- 更新包`conda update package_name`
- 卸载包`conda uninstall package_name`

### 补充

- 更新python版本：`conda update python`
