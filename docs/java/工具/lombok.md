- Lombok 是一种 Java 实用**注解工具**，可用来帮助开发人员消除 Java 的冗长代码，尤其是对于简单的 Java 对象
- maven 添加
```xml
<dependency>     <groupId>org.projectlombok</groupId>     <artifactId>lombok</artifactId>     <version>1.16.8</version></dependency>
```
### 基本用法
- `val`：用在局部变量前面，相当于将变量声明为 final
- `@NonNull`：给方法参数增加这个注解会自动在方法内对该参数进行是否为空的校验，如果为空，则抛出NPE（NullPointerException）
- `@Cleanup`：自动管理资源，用在局部变量之前，在当前变量范围内即将执行完毕退出之前会自动清理资源，自动生成try-finally这样的代码来关闭流
- `@Getter/@Setter`：用在属性上，再也不用自己手写setter和getter方法了，还可以指定访问范围
- `@ToString`：用在类上，可以自动覆写toString方法，当然还可以加其他参数，例如@ToString(exclude=”id”)排除id属性，或者@ToString(callSuper=true, includeFieldNames=true)调用父类的toString方法，包含所有属性
- `@EqualsAndHashCode`：用在类上，自动生成equals方法和hashCode方法
- `@NoArgsConstructor, @RequiredArgsConstructor and @AllArgsConstructor`：用在类上，自动生成无参构造和使用所有参数的构造函数以及把所有@NonNull属性作为参数的构造函数，如果指定staticName = “of”参数，同时还会生成一个返回类对象的静态工厂方法，比使用构造函数方便很多
- `@Data`：注解在类上，相当于同时使用了`@ToString`、`@EqualsAndHashCode`、`@Getter`、`@Setter`和`@RequiredArgsConstrutor`这些注解，对于`POJO类`十分有用
- `@Value`：用在类上，是@Data的不可变形式，相当于为属性添加final声明，只提供getter方法，而不提供setter方法
- `@Builder`：用在类、构造器、方法上，为你提供复杂的builder APIs，让你可以像如下方式一样调用`Person.builder().name("Adam Savage").city("San Francisco").job("Mythbusters").job("Unchained Reaction").build();`更多说明参考[Builder](https://www.google.com/url?q=https%3A%2F%2Flink.juejin.im%2F%3Ftarget%3Dhttps%253A%252F%252Fprojectlombok.org%252Ffeatures%252FBuilder.html&sa=D&sntz=1&usg=AOvVaw1VmNt1ScbfLh1KHyiia09H)
- `@SneakyThrows`：自动抛受检异常，而无需显式在方法上使用throws语句
- `@Synchronized`：用在方法上，将方法声明为同步的，并自动加锁，而锁对象是一个私有的属性`$lock`或`$LOCK`，而java中的synchronized关键字锁对象是this，锁在this或者自己的类对象上存在副作用，就是你不能阻止非受控代码去锁this或者类对象，这可能会导致竞争条件或者其它线程错误
- `@Getter(lazy=true)`：可以替代经典的Double Check Lock样板代码
- `@Log`：根据不同的注解生成不同类型的log对象，但是实例名称都是log，有六种可选实现类
    
    - `@CommonsLog` Creates log = org.apache.commons.logging.LogFactory.getLog(LogExample.class);
    - `@Log` Creates log = java.util.logging.Logger.getLogger(LogExample.class.getName());
    - `@Log4j` Creates log = org.apache.log4j.Logger.getLogger(LogExample.class);
    - `@Log4j2` Creates log = org.apache.logging.log4j.LogManager.getLogger(LogExample.class);
    - `@Slf4j` Creates log = org.slf4j.LoggerFactory.getLogger(LogExample.class);
    - `@XSlf4j` Creates log = org.slf4j.ext.XLoggerFactory.getXLogger(LogExample.class);