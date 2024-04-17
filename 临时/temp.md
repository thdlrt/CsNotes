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
## 问题及思考