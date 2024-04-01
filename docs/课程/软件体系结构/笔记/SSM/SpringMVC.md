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
### BS 模式
- 三层模式
	- 用户 PC：展示层，用户界面**不再需要专门的客户端**，使用浏览器来对 html 进行渲染显示
	- 应用服务器：应用服务层
	- 资源管理系统：数据层
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401142509.png)
#### 具体实现：JAVA EE
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401142829.png)
- CGI：用于生成动态内容
	- 每当 Web 服务器收到一个请求，它就会启动一个新的 CGI 程序（或脚本）实例来处理请求（即**一个新进程**）。这种处理方式相对效率较低，因为每次请求都需要创建一个新的进程，增加了 CPU 和内存的负担。
	- 无状态
	- HTML内容通常是由脚本语言（如Perl、Python等）**动态生成并打印出来的**。脚本会执行必要的逻辑处理，并将处理结果以字符串的形式嵌入到HTML标记中，最后将整个HTML内容作为响应输出。
- Active Page（如 JSP）
	- 支持使用线程池、缓存登记书，并且支持应用状态管理（不同请求之间可以共享信息，如用户会话），效率更高
	- Java代码**嵌入**到特定的JSP标签中。当页面被请求时，服务器上的JSP引擎会**处理这些标签**，执行其中的Java代码，生成动态内容，并**插入到HTML页面中。**
	- CGI 脚本通常是**完全独立**于 HTML 的，而 JSP 将 Java 代码**嵌入**HTML 中。

- Java Servlet 是作为控制器，接受并读取 http 请求，访问数据并生成相应，之后将响应发送给服务器
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401143909.png)
	- 使用的是 CGI 分离模式，在 JAVA 点钟编写相应逻辑而不是在 HTML 中嵌入代码
	- 可维护性较差，混杂了逻辑处理及页面生成等不同功能，不能使用变化

- Thyme leaf 
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401151011.png)
	- 添加 UI 模块负责将生成的结果填入到页面，即 Active Page
	- 即将内容动态填入到 HTML 模板
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401151143.png)

- 对结构进一步细分，提取业务处理代码
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401151346.png)
### MVC
- ![image.png|425](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401151625.png)
	- View：模版引擎->HTML，决定用户界面
	- Controller：处理请求操作了，决定**输入**的处理方式
	- Model：核心数据功能（实际进行请求的数据计算），进行**业务逻辑的处理**
- 多视图：结合设备信息发送不同的视图
	- ![image.png|400](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401163935.png)

## SpringMVC
### 例子
- [spring-petclinic](https://github.com/spring-petclinic/spring-framework-petclinic?tab=readme-ov-file)
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401155056.png)
	- ![image.png|275](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240401164136.png)
- 在控制器和仓库接口之间添加了服务层
	- 让多个控制器可以重用相同代码，实现代码复用，并且简化了控制器的实现
	- 服务层可以进行验证和授权，提高系统的安全性
```java
//controller与服务层交互
    @PostMapping(value = "/owners/{ownerId}/edit")
    public String processUpdateOwnerForm(@Valid Owner owner, BindingResult result, @PathVariable("ownerId") int ownerId) {
        if (result.hasErrors()) {
            return VIEWS_OWNER_CREATE_OR_UPDATE_FORM;
        }

        owner.setId(ownerId);
        this.clinicService.saveOwner(owner);
        return "redirect:/owners/{ownerId}";
    }
    //server与仓库交互
    @Override  
@Transactional  
public void saveOwner(Owner owner) {  
    ownerRepository.save(owner);  
}
```
- 