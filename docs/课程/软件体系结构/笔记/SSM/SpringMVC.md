## 软件体系结构
### 分层系统
- 软件层级的发展历程
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240316133914.png)
	- 提取不同软件的公共部分，简化软件的开发流程

- 应用程序的三层结构：
	- **展示层**：展示数据、与用户交互
	- **业务逻辑层**：处理业务逻辑和决策
	- **数据访问层**：负责与数据库或其他持久化存储机制进行通讯
### CS 模式
- 客户机-服务器模式：客户机和服务器都具有一定的计算能力
- 对三层的划分
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401140641.png)
- Fat Clients
	- 应用系统是在 Client 端运行的
	- Client 知道 Sever 上的数据组织方式，调用 API 从服务器获取部分信息
	- 用户端程序设计有较大灵活性
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401141022.png)
	- 相对**较难管理**，因为业务逻辑在终端运行，所以如果需要修改业务逻辑就需要**修改每一个客户端的程序**
- Fat Severs（现在使用更为广泛）
	- Sever **通过一组确定的过程**提供资源访问，而**不**是提供对资源的**直接访问和操作**
	- Client 提供 GUI 供用户操作，并通过远程方法调用与 Sever 通信，获得服务
	- 应用系统集中于 Sever ，**便于部署和管理**
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401141625.png)
- 
### BS 模式
