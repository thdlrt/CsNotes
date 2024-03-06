## MySQL卸载文档-Windows版

### 1. 停止MySQL服务

win+R 打开运行，输入 services.msc 点击 "确定" 调出系统服务。

![image-20220209203115052](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20220209203115052.png) 

![image-20220209203253220](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20220209203253220.png) 





### 2. 卸载MySQL相关组件

打开控制面板 ---> 卸载程序 ---> 卸载MySQL相关所有组件

![image-20220209203345746](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20220209203345746.png) 

![image-20220209203431405](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20220209203431405.png) 



### 3. 删除MySQL安装目录

![image-20220209205157019](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20220209205157019.png) 





### 4. 删除MySQL数据目录

数据存放目录是在 C:\ProgramData\MySQL，直接将该文件夹删除。

![image-20220209205401563](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20220209205401563.png) 





### 5. 再次打开服务，查看是否有MySQL卸载残留

如果已将MySQL卸载，但是通过任务管理器--->服务，查看到MySQL服务仍然残留在系统服务里。

解决办法：

​	以管理员方式运行cmd命令行，输入以下命令：

​	sc delete 服务名称（如MySQL80）

这样可以实现删除服务。





