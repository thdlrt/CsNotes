> 作业代码（即 Sever）位于 sever 分支
## 实验过程
### 对控制器进行修改
- 原先的控制器使用 SpringMVC 以及模版引擎，因此主要需要对 controller 进行修改，使得可以相应客户端的 REST API
- 依据“在 REST 风格的控制器中，方法应直接返回**对象或数据集合**，而不是视图名称“编写新的 API：`\product` 和 `\product\{id}`
	- 至于原先对购物车从操作的 API 可以删除，因为现在 REST 模式使用无状态链接，购物车中商品的信息属于应用信息，由客户端而不是服务端进行维护
```java
@GetMapping("/product")  
public ResponseEntity<List<Product>> products() {  
    return ResponseEntity.ok(posService.products());  
}  
  
@GetMapping("/product/{productId}")  
public ResponseEntity<Product> product(@PathVariable Long productId) {  
    Product product = posService.getProduct(productId);  
    if (product == null) {  
        return ResponseEntity.notFound().build();  
    }  
    return ResponseEntity.ok(product);  
}
```
- 除此之外只需要简单修改 Product 类以适应新的客户端需求
### 解决跨域请求问题
- 由于前端页面的分发的端口与 spring 服务端响应端口不同，因此默认下会被浏览器拒绝
- 添加一个配置类
```java
@Configuration  
public class WebConfig implements WebMvcConfigurer {  
  
    @Override  
    public void addCorsMappings(CorsRegistry registry) {  
        registry.addMapping("/**")  // 为所有路径启用CORS  
                .allowedOrigins("http://localhost:63342")  // 允许来自指定源的访问  
                .allowedMethods("GET", "POST", "PUT", "DELETE")  // 允许的HTTP方法  
                .allowCredentials(true)  // 允许凭证  
                .maxAge(3600);  // 预检请求的缓存持续时间  
    }  
}
```
- 对于另外两个配置项支架返回数据对象
```java
@GetMapping("/categories")  
public ResponseEntity<List<Categories>>catefories(){  
    List<Categories>res = List.of(new Categories(1711853606L,"drink","1711853606"));  
    return ResponseEntity.ok(res);  
}  
  
@GetMapping("/settings")  
public ResponseEntity<List<Setting>>settings(){  
    List<Setting>res = List.of(new Setting(1711853606L,1711853606L));  
    return ResponseEntity.ok(res);  
}
```
### 运行效果
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240418003757.png)
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240418003820.png)
- 与使用虚拟 json-server 效果一直，spring 后端正常工作
## 问题及思考
- 应用状态就是由客户端所维护的状态
	- 应用状态是客户端需要了解以正确展示用户界面或执行用户请求的所有信息。
	- 在这个任务里，购物车就是一个重要的应用状态
	- 在上一次作业中，购物车是由服务器维护的，服务器负责维护增加删除
	- 而本次作业中，购物车由本地应用维护，给服务器不关心也不再持有用户购物车的信息。

- 资源状态是指服务器上的信息
	- 资源状态是指服务器上的资源（如数据库中的数据或服务器上的文件）的当前状态。
	- 服务器上的资源，如本次的 products 信息，系统信息，都具有唯一的 URI，客户端通过使用 HTTP 方法进行请求，再通过 JSON 等数据格式由服务器发送到客户端
	- 不过本次客户端是由 idea 作为服务器模拟的，并没有真正向后端请求图片等数据

- 通过将购物车从资源状态转化为应用状态，实现了无状态访问
	- 用户发起请求时，服务器可以统一的返回资源，而不需要用户的信息（进而进行购物车的操作）
	- 当用户需要获取更多信息，或者进行结账时，也只需要发送指定商品 id，而这个操作是**与用户的信息本身不相关**的，服务器可以独立的处理操作
	- 由此实现了无状态的 HTTP 通信