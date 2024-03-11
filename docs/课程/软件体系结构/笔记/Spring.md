## 基本概念
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
### 使用 Spring
- maven 中引入依赖
```xml
<?xml version = "1.0" encoding = "UTF-8"?>
<project xmlns = "http://maven.apache.org/POM/4.0.0" xmlns:xsi = "http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation = "http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.shiyanlou.spring</groupId>
    <artifactId>bean</artifactId>
    <version>1.0-SNAPSHOT</version>

    <name>bean</name>

    <properties>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
        <maven.compiler.source>1.8</maven.compiler.source>
        <maven.compiler.target>1.8</maven.compiler.target>
        <spring.version>5.1.1.RELEASE</spring.version>

    </properties>

    <dependencies>
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-core</artifactId>
            <version>${spring.version}</version>
        </dependency>
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-context</artifactId>
            <version>${spring.version}</version>
        </dependency>
    </dependencies>
</project>

```
## 反转控制&依赖注入 IOC
### 什么是组件
- ccm 抽象构建
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307144504.png)
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307144529.png)
- spring：支持构建现代化的构件软件系统
	- spring 负责对构件管理和组装，即由 spring 框架来控制程序中各个类之间的关系
	- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307151410.png)
### 控制反转 IOC

- 控制反转就是指模块将内部的控制权交给了外部

- 软件设计中的**依赖注入**模式。在 IoC 模式中，控制权从程序代码转移**给了外部系统或框架**
	- 传统程序设计是在对象内部直接 new 创建对象，而 IoC 是通过专门的容器（context）创建对象，由 IoC 控制对象
	- ![image.png|325](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240311222719.png)

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
	- **构造器注入**：`MovieLister` 的依赖会在 `MovieLister` 实例化的时候通过构造器传递进来。
	- **设置值注入**：这允许在对象创建后的任何时刻注入依赖，提供了更大的灵活性。
	- **接口注入**：任何需要使用 `MovieFinder` 的类（如 `MovieLister`）都需要实现这个接口，并通过实现的 `injectFinder` 方法接收依赖注入。
### 实现控制反转
- bean 的三种定义方式：基于 XML、基于注解、基于 JAVA 类
#### bean 的作用域
- singleton — **单例模式**，由 IOC 容器返回一个唯一的 bean 实例。
- prototype — **原型模式**，被请求时，每次返回一个新的 bean 实例。
- request — 每个 HTTP Request 请求返回一个唯一的 Bean 实例。
- session — 每个 HTTP Session 返回一个唯一的 Bean 实例。
- globalSession — Http Session 全局 Bean 实例。
#### bean 的生命周期
- 一般担当管理角色的是 BeanFactory 或者 ApplicationContext
- Bean 的建立，由 BeanFactory 读取 Bean 定义文件，并生成各个实例。
- Setter 注入，执行 Bean 的属性依赖注入。
- BeanNameAware 的 `setBeanName()`，如果实现该接口，则执行其 setBeanName 方法
- BeanFactoryAware 的 `setBeanFactory()`，如果实现该接口，则执行其 setBeanFactory 方法。
- BeanPostProcessor 的 `processBeforeInitialization()`，如果有关联的 processor，则在 Bean 初始化之前都会执行这个实例的 `processBeforeInitialization()` 方法。
- InitializingBean 的 `afterPropertiesSet()`，如果实现了该接口，则执行其 `afterPropertiesSet()` 方法。
- Bean 定义文件中定义 init-method。
- BeanPostProcessors 的 `processAfterInitialization()`，如果有关联的 processor，则在 Bean 初始化之前都会执行这个实例的 `processAfterInitialization()` 方法。
- DisposableBean 的 `destroy()`，在容器关闭时，如果 Bean 类实现了该接口，则执行它的 `destroy()` 方法。
- Bean 定义文件中定义 destroy-method，在容器关闭时，可以在 Bean 定义文件中使用“destory-method”定义的方法。
- ![image.png|378](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240311231122.png)

#### 使用 XML 配置文件实现
- 在 **xml** 中配置（bean 就表示构件, 通常在 src/main/resources 下）
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
        <!-- 另一种配置方法 缩写方法-->
    <!--
        <bean id = "FileNameGenerator" class = "com.shiyanlou.spring.bean.FileNameGenerator">
               <property name = "name" value = "shiyanlou" />
               <property name = "type" value = "txt" />
           </bean>
     -->
     <!--pschema方法-->
     <!--
     <bean id = "FileNameGenerator" class = "com.shiyanlou.spring.bean.FileNameGenerator" p:name = "shiyanlou" p:type = "txt" />
     -->
</beans>
```
- 通过 property 标签为 name 属性设置默认值，在创建实例时会自动先进性赋值
	- 对于属性 finder 会自动去找对应的 setFinder 来对属性值进行修改
- 有三种配置方式：完整、缩写、pschema
```xml
使用pschma要在beans配置加上
xmlns:p = "http://www.springframework.org/schema/p"
```

- spring 通过 xml 配置文件对构件进行组装
	- ![image.png|376](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240307153409.png)
```java
public void testWithSpring() throws Exception{
//加载spring配置文件
  ApplicationContext ctx = new FileSystemXmlApplicationContext("spring.xml");
//使用配置文件创建对象并还原类型
  MovieLister lister = (MovieLister) ctx.getBean("MovieLister");
  
  Movie[] movies = lister.moviesDirectedBy("Sergio Leone");

  assertEquals("Once Upon a Time in the West", movies[0].getTitle());
}
```
#### 使用注解方式
- 通过使用注释 @Configuration 告诉 Spring，这个 Class 是 Spring 的核心配置文件，并且通过使用注解 @Bean 定义 bean

- 定义 bean
```java
package com.shiyanlou.spring.java_config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class AppConfig {

    @Bean(name = "animal")
    public IAnimal getAnimal(){
        return new Dog();
    }
}
```
- @Configuration 标记类，@Bean 在内部标记需要由同期托管的**方法**
- 三个等效名称（功能无区别）
	- @Controller：对应表现层的 Bean，也就是 Action
	- @Service：对应的是业务层 Bean
	- @Repository：对应数据访问层 Bean

- 将类声明为 Bean 使用 `@Component`表示这个 Class 是一个**自动扫描组件**
```java
@Component
public class MyComponent {
    // Spring将自动将此类的实例注册为bean
}
```
- 默认情况下，Spring 将把组件 Class 的**第一个字母变成小写**，来作为自动扫描组件的名称
	- 即 `context.getBean("myComponent");`
	- 该类会被自动注册为 bean

- 属性注入 `Autowired`
	- 
#### 嵌套 Bean
- 使用 xml
```xml
 <bean id = "CustomerBean" class = "com.shiyanlou.spring.innerbean.Customer">
        <property name = "person">
            <bean class = "com.shiyanlou.spring.innerbean.Person">
                <property name = "name" value = "shiyanlou" />
                <property name = "address" value = "chengdu" />
                <property name = "age" value = "25" />
            </bean>
        </property>
  </bean>
```

#### 集合类型的 Bean
- 使用 xml 注入到不同类型的集合
```java
<?xml version = "1.0" encoding = "UTF-8"?>
<beans xmlns = "http://www.springframework.org/schema/beans"
    xmlns:xsi = "http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation = "http://www.springframework.org/schema/beans
    http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!--bean的 id 最好首字母小写 -->
    <bean id = "customerBean" class = "com.shiyanlou.spring.collections.Customer">

        <!-- java.util.List -->
        <property name = "lists">
            <list>
                <value>1</value>
                <!-- List 属性既可以通过 <value> 注入字符串，也可以通过 <ref> 注入容器中其他的 Bean-->
                 <ref bean = "personBean" />
                 <value>2</value>
                <bean class = "com.shiyanlou.spring.collections.Person">
                    <property name = "name" value = "shiyanlouList" />
                    <property name = "address" value = "chengdu" />
                    <property name = "age" value="25" />
                </bean>
            </list>
        </property>

        <!-- java.util.Set -->
        <property name = "sets">
            <set>
                <value>1</value><!--Set 与 List 类似-->
                <ref bean = "personBean" />
                <bean class = "com.shiyanlou.spring.collections.Person">
                    <property name = "name" value = "shiyanlouSet" />
                    <property name = "address" value = "chengdu" />
                    <property name = "age" value = "25" />
                </bean>
            </set>
        </property>

        <!-- java.util.Map -->
        <property name = "maps">
            <map>
                <entry key = "Key 1" value = "1" />
                <!--一个 entry 就是一个 Map 元素-->
                <entry key = "Key 2" value-ref = "personBean" />
                <entry key = "Key 3">
                    <bean class = "com.shiyanlou.spring.collections.Person">
                        <property name = "name" value = "shiyanlouMap" />
                           <property name = "address" value = "chengdu" />
                        <property name = "age" value = "25" />
                    </bean>
                </entry>
            </map>
        </property>

        <!-- java.util.Properties -->
        <property name = "pros">
        <!-- Properties 类型类似于Map 类型的特例，Map 元素的键值可以对应任何类型的对象，但是Properties只能是字符串-->
            <props>
                <prop key = "admin">admin@nospam.com</prop>
                <prop key = "support">support@nospam.com</prop>
            </props>
        </property>
    </bean>

    <bean id = "personBean" class = "com.shiyanlou.spring.collections.Person">
        <property name = "name" value = "shiyanlouPersonBean" />
        <property name = "address" value = "chengdu" />
        <property name = "age" value = "25" />
    </bean>
</beans>
```

### AOP 面相切面编程