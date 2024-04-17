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
## 问题及思考