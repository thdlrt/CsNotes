### 基本概念
- Spring 是一个容器，通过**反转控制**（IoC）和**依赖注入**（DI）来实现高内聚、低耦合的应用。除此之外它可以整合很多第三方框架，它还提供**面向切面编程**（AOP）的能力，对数据库事务的管理尤其方便。
- 功能
	- 帮助**通过配置方式**来创建对象，管理对象之间**依赖关系**
	- Spring 面向切面编程能帮助我们无耦合的实现**日志记录、性能统计、安全控制**。这些日志记录、权限控制、性能统计从**业务逻辑中分离出来**，通过 Spring 支持的面向切面编程，动态添加这些功能，无需渗透到各个需要的方法或对象中。
	- Spring 能非常简单的帮我们管理数据库事务

- 一些概念：
	- 非侵入式设计：没有继承框架的类
	- 轻量级与重量级：轻量级一般是非入侵的，所依赖的东西很少，部署简单
	- 容器：装对象的对象
	- 控制反转：由容器控制程序之间的关系
	- bean：容器管理对象
	- POJO：简单的 JAVA 对象，不继承不实现其他框架类或接口

- spring 的优点
	- 非常轻量的容器：spring 容器是非侵入的，以集中的、自动化的方式进行应用程序对象创建和装配，除此之外还会负责管理对象生命周期，能组合成复杂的应用程序。
	- AOP：面相切面编程，可以通过在编译期间、装载期间或运行期间实现在**不修改源代码**的情况下给程序**动态添加功能**的一种技术。如安全、日志记录等
	- 简单的数据库事务管理
	- 灵活的 web 层支持
	- 简化各种技术集成
### 反转控制&依赖注入 IOC
#### 什么是组件
- ccm 抽象构建
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307144504.png)
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307144529.png)
- spring：支持构建现代化的构件软件系统
	- spring 负责对构件管理和组装，即由 spring 框架来控制程序中各个类之间的关系
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307151410.png)
#### 控制反转 IOC

- 控制反转就是指模块将内部的控制权交给了外部

- 软件设计中的**依赖注入**模式。在 IoC 模式中，控制权从程序代码转移**给了外部系统或框架**
- 比如有一个程序 MovieLister 有一个功能是使用实现了 MovieFinder 接口的类从列表中寻找符合条件的项
	- 依赖注入是 IoC 的一种形式，它涉及到在运行时动态地将具体的 `MovieFinder`**实现注入**到 `MovieLister` 中，而不是由 `MovieLister` 自己构造或查找 `MovieFinder` 的实现。这样，我们就可以在不改变 `MovieLister` 代码的情况下，改变它所依赖的电影查找方式，增加了代码的模块化和**灵活性**。
	- 在 Lister 内自己创建就**不是一个好设计**，写死了算法 ![image.png|425](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307152005.png)
	- 也就是说应该由第三方来组装 MovieLister 和 MovieFinderImpI（**依赖注入**）
		- ![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307152252.png)
```java
public class MovieLister{
  MovieFinder finder;

  public void setFinder(MovieFinder finder){
    this.finder = finder;
  }
  ...
}
```

- 依赖注入方法分类：
	- 构造器注入：`MovieLister` 的依赖会在 `MovieLister` 实例化的时候通过构造器传递进来。
	- 设置值注入：这允许在对象创建后的任何时刻注入依赖，提供了更大的灵活性。
	- 接口注入：任何需要使用 `MovieFinder` 的类（如 `MovieLister`）都需要实现这个接口，并通过实现的 `injectFinder` 方法接收依赖注入。

- 在 spring 中配置（bean 就表示构件）早起方式，现在可以使用注解等方式实现
```xml
<beans>
    <bean id="MovieLister" class="spring.MovieLister">                   
        <property name="finder">
            <ref local="MovieFinder" />
        </property>
    </bean>
    <bean id="MovieFinder" class="spring.ColonMovieFinder">
        <property name="filename">
            <value>movies1.txt</value>
        </property>
    </bean>
</beans>
```
- 对于属性 finder 会自动去找对应的 setFinder 来对属性值进行修改
- spring 通过 xml 配置文件对构件进行组装
	- ![image.png|376](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307153409.png)
```java
public void testWithSpring() throws Exception{

  ApplicationContext ctx = new FileSystemXmlApplicationContext("spring.xml");

  MovieLister lister = (MovieLister) ctx.getBean("MovieLister");
  Movie[] movies = lister.moviesDirectedBy("Sergio Leone");

  assertEquals("Once Upon a Time in the West", movies[0].getTitle());
}
```
### AOP 面相切面编程