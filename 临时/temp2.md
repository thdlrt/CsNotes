### 系统机构设计

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524151400192.png" alt="image-20240524151400192" style="zoom: 33%;" />

### 消息传递

#### 配置中间件RabbitMQ

`application.yml`文件的配置

```yml
spring:
  rabbitmq:
    host: localhost
    port: 5672
    username: guest
    password: guest
  cloud:
    stream:
      bindings:
        order-out:
          destination: orders
          content-type: application/json
        delivery-in:
          destination: orders
          content-type: application/json
```

### 定义消息通道

创建一个接口定义消息通道，用于发送和接收订单事件。

`OrderProcessor`接口定义了两个通道：一个用于输出（`order-out`），另一个用于输入（`delivery-in`）。通过使用`@Output`和`@Input`注解，Spring Cloud Stream将这些通道与RabbitMQ绑定，以实现消息的发送和接收。

```java
public interface OrderProcessor {
    String OUTPUT = "order-out";
    String INPUT = "delivery-in";

    @Output(OUTPUT)
    MessageChannel output();

    @Input(INPUT)
    SubscribableChannel input();
}
```

### Order Service发送事件

在Order Service中实现订单事件的发送逻辑，当订单生成后，将订单事件发送到RabbitMQ。

`OrderEvent`类定义了订单事件的结构，这里仅包含订单ID。可以根据需要扩展此类以包含更多订单信息。

```java
public class OrderEvent {
    private String orderId;
    public OrderEvent() {}
    public OrderEvent(String orderId) {
        this.orderId = orderId;
    }
}
```

在`OrderService`中，定义了一个`createOrder`方法用于创建订单。创建订单后，生成一个`OrderEvent`对象，并通过`orderProcessor`将该事件发送到RabbitMQ。这里使用了`MessageBuilder`来构建消息并发送。

### Delivery Service接收事件

在Delivery Service中实现接收订单事件的逻辑，当接收到订单事件后，生成相应的配送条目并存储。

`Delivery`类定义了配送条目的结构，包括ID、订单ID和状态。

```java
@Entity
public class Delivery {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String orderId;
    private String status;
}
```

`DeliveryRepository`接口继承自`JpaRepository`，提供了基本的CRUD操作，并定义了一个自定义方法`findByOrderId`用于根据订单ID查询配送条目。

在`DeliveryService`中，定义了一个方法`handleOrderEvent`来处理订单事件。当接收到订单事件时，生成一个新的`Delivery`对象并将其状态设置为"Processing"，然后保存到数据库中。

### 查询配送状态

创建API端点，允许用户查询订单的配送状态。

```java
@RestController
@RequestMapping("/deliveryService")
public class DeliveryController {

    @Autowired
    private DeliveryService deliveryService;

    @GetMapping("/orders/{orderId}")
    public ResponseEntity<List<Delivery>> getDeliveryByOrderId(@PathVariable String orderId) {
        List<Delivery> deliveries = deliveryService.getDeliveryByOrderId(orderId);
        if (deliveries.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(deliveries);
    }
}
```

在`DeliveryController`中，我们定义了一个GET端点，用于根据订单ID查询配送状态。如果找到相应的配送条目，则返回其列表；否则返回404 Not Found。

### 实验总结

通过上述步骤，成功扩展了MicroPOS系统，实现了用户下单后自动生成配送信息，并支持用户查询订单的配送状态。

- 下面是一个输出的测试，不过由于前端没有完全改好，只能实现订单信息的一个示例

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20240524152335200.png" alt="image-20240524152335200" style="zoom: 33%;" />