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
#### 补充：渲染模式
##### 服务端渲染 SSR
- 在服务端渲染中，**HTML 页面是在服务器上生成的**。当用户请求一个页面时，服务器将所有必要的数据集成到 HTML 中，并且完成页面的渲染，然后将完整的页面发送给客户端。客户端（浏览器）接收到完整的 HTML 页面后，**直接渲染显示给用户**。（上面提到的吗模板引擎就属于这一种）
- **SEO 友好**：由于页面是预先渲染的，搜索引擎更容易抓取和索引内容，这对 SEO 非常有利。
- **首屏加载快**：用户能更快地看到完整渲染的页面，因为浏览器不需要等待所有JavaScript下载并执行完成才能显示内容。
- **兼容性好**：SSR生成的页面不依赖于客户端JavaScript，因此即使在禁用JavaScript的环境下也能正常显示。
##### 客户端渲染 CSR
- 在客户端渲染中，服务器发送的 HTML 页面最初**几乎是空的**，所有的内容生成和渲染都在浏览器中**通过 JavaScript 完成**。当页面加载到浏览器后，JavaScript 代码会运行，从服务器获取数据，然后在客户端动态生成页面内容。（vue、react 都是这种）
- **富交互性**：CSR 非常适合构建交互性强的单页应用（SPA）。JavaScript 框架（如 React、Vue.js）可以提供流畅的用户体验和高效的页面更新。
- **前后端分离**：客户端渲染支持前后端分离的开发模式，前端负责UI和用户交互，后端通过API提供数据服务，这种模式增强了应用的可维护性和扩展性。
- **减轻服务器负担**：由于页面渲染工作转移到了客户端，服务器的负担减轻了，尤其是在高流量的情况下。
##### 静态站点
- 适用于内容驱动的网站，如博客、文档站点、营销网站。
- 极快的加载速度，优秀的SEO表现，安全性高。
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
### 控制器层
- 处理指定路径的 GET/POST
```java
@GetMapping("/signup")//处理的路径
public String showSignUpForm(User user) {
    return "add-user";
}

@PostMapping("/adduser")
public String addUser(@Valid User user, BindingResult result, Model model) {
    if (result.hasErrors()) {
        return "add-user";
    }
    userRepository.save(user);
    return "redirect:/index";
}
//添加依赖项，用于模板引擎进行渲染
GetMapping("/")
    public String pos(Model model) {
        posService.add("PD1", 2);
        //添加依赖
        model.addAttribute("products", posService.products());
        model.addAttribute("cart", posService.getCart());
        return "index";
    }
```
#### 模板引擎
- 上面 return 的就是一个模板引擎，比如 `"add-user"` 就对应一个 HTML 模板文件的名字。该文件应该位于 `src/main/resources/templates` 目录下，并且文件名应该是 `add-user.html`。
	- Spring Boot 配置了**Thymeleaf**模板引擎作为其默认的模板引擎，所以当返回 `"add-user"` 时，Spring MVC 会寻找名为 `add-user.html` 的模板文件，然后渲染这个模板作为 HTTP 响应。
- 重定义路径：当执行完一个操作后，比如添加或更新数据，将用户重定向到另一个路径，告诉浏览器去请求一个新的 URL。
	- `"redirect:/index"` 就表示重定位到 `/index`

- 模版引擎的内容填充发生在服务器端
	- **解析模板**：模板引擎读取模板文件（例如，`add-user.html`），并解析文件中的 Thymeleaf 语法。
	- **数据绑定**：模板中的动态部分（比如，表达式、选择变量）会与控制器传递给视图的模型数据（Model）进行绑定。模型数据通常是在控制器方法中构造的，可以包含各种形式的数据，如实体对象、列表或任何需要在页面上展示的数据。
	- **生成 HTML**：模板引擎将填充后的模板渲染为最终的 HTML 页面。这个过程包括替换动态表达式为实际的值，执行循环、条件判断等操作。
	- **发送响应**：渲染后的HTML页面作为HTTP响应的一部分发送给客户端（浏览器）。
### 视图层
#### 数据绑定
- 用户表单注册
```html
<form action="#" th:action="@{/adduser}" th:object="${user}" method="post">
    <label for="name">Name</label>
    <input type="text" th:field="*{name}" id="name" placeholder="Name">
    <span th:if="${#fields.hasErrors('name')}" th:errors="*{name}"></span>

    <label for="email">Email</label>
    <input type="text" th:field="*{email}" id="email" placeholder="Email">
    <span th:if="${#fields.hasErrors('email')}" th:errors="*{email}"></span>
    
    <input type="submit" value="Add User">   
</form>
```
- `th:action="@{/adduser}"` 指定表单提交的 URL，Thymeleaf 会解析 `@{/adduser}` 为应用的相对路径。
- `th:object="${user}"` 将表单与后端的`User`对象绑定。
- `th:field="*{name}"` 将输入框绑定到`User`对象的`name`属性，实现数据的双向绑定。
- `th:if="${#fields.hasErrors('name')}" th:errors="*{name}"` 如果 `name` 字段有验证错误，这些错误会被显示出来。
- 设置动态路径 `@{/update/{id}(id=${user.id})}`

- 用户列表展示
```html
<div th:switch="${users}">
    <h2 th:case="null">No users yet!</h2>
    <div th:case="*">
        <h2>Users</h2>
        <table>
            <thead>
                <tr>
                    <th>Name</th>
                    <th>Email</th>
                    <th>Edit</th>
                    <th>Delete</th>
                </tr>
            </thead>
            <tbody>
                <tr th:each="user : ${users}">
                    <td th:text="${user.name}">Name</td>
                    <td th:text="${user.email}">Email</td>
                    <td><a th:href="@{/edit/{id}(id=${user.id})}">Edit</a></td>
                    <td><a th:href="@{/delete/{id}(id=${user.id})}">Delete</a></td>
                </tr>
            </tbody>
        </table>
    </div>      
    <p><a href="/signup">Add a new user</a></p>
</div>
```
- `th:each="user : ${users}"` 遍历所有用户，并为每个用户创建一个表格行。
- `th:text="${user.name}"` 和 `th:text="${user.email}"` 分别显示用户的姓名和电子邮箱。
- `th:href="@{/edit/{id}(id=${user.id})}"` 和 `th:href="@{/delete/{id}(id=${user.id})}"` 分别为编辑和删除操作提供动态链接，链接中包含用户的ID。
### 仓库层（存储）
- 