### 依赖自动管理
- 当使用 `spring-boot-starter-parent` 作为项目的父 POM 时，不需要在大多数情况下**指定依赖的版本**。
```xml
<parent>  
<groupId>org.springframework.boot</groupId>  
    <artifactId>spring-boot-starter-parent</artifactId>  
    <version>3.2.4</version>  
    <relativePath/>
</parent>

<dependencies>  
    <dependency>  
<groupId>org.springframework.boot</groupId>  
        <artifactId>spring-boot-starter-thymeleaf</artifactId>  
    </dependency>
</dependencies>
```
- 但是如果想使用一个新版本的库或者一个父 POM 中没有的第三方库，你需要在 `pom.xml` 中指定版本号。
### 程序入口
```java
@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```