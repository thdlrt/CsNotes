生成`javadoc -d doc -sourcepath src -subpackages com.mycompany`
  - 生成源代码路径 `src` 下 `com.mycompany` 包（及其子包）的Javadoc，并将文档输出到 `doc` 目录。

- 只会为public和protected成员处理文档，生成时添加`-private`将private纳入考虑

- 分类
  - 类的注释
  - 字段注释
  - 方法注释

``` java
import java.util.*;

/** The first On Java 8 example program.
 * Displays a String and today's date.
 * @author Bruce Eckel
 * @author www.MindviewInc.com
 * @version 5.0
 */
public class HelloDateDoc {
  /** Entry point to class & application.
   * @param args array of String arguments
   * @throws exceptions No exceptions thrown
   */
  public static void main(String [] args) {
    System.out.println("Hello, it's: ");
    System.out.println(new Date());
  }
}
```

### 基本语法

- 所有Javadoc指令都在`/**  */`格式的注释内

#### 嵌入式HTML

``` java
/** You can <em> even </em> insert a list:
 * <ol>
 * <li> Item one
 * <li> Item two
 * <li> Item three
 * </ol>
 */
public class Documentation3 {}
```

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231121151640157.png" alt="image-20231121151640157" style="zoom:33%;" />
- 行首的星号和空格会抛弃
- 不要使用标题标签

#### 标签

- 独立doc标签以@开头必须在每行注释的开头
- 行内标签同样以@开头但是可以位于注释的任意位置，并且需要用{}包住

| 标签          | 描述                                                   | 示例                                                         |
| ------------- | ------------------------------------------------------ | ------------------------------------------------------------ |
| @author       | 标识一个类的作者，一般用于类注释                       | @author description                                          |
| @deprecated   | 指名一个过期的类或成员，表明该类或方法不建议使用       | @deprecated description                                      |
| {@docRoot}    | 指明当前文档根目录的路径                               | Directory Path                                               |
| @exception    | 可能抛出异常的说明，一般用于方法注释                   | @exception exception-name explanation                        |
| {@inheritDoc} | 从直接父类继承的注释                                   | Inherits a comment from the immediate surperclass.           |
| {@link}       | 插入一个到另一个主题的链接                             | {@link name text}                                            |
| {@linkplain}  | 插入一个到另一个主题的链接，但是该链接显示纯文本字体   | Inserts an in-line link to another topic.                    |
| @param        | 说明一个方法的参数，一般用于方法注释                   | @param parameter-name explanation                            |
| @return       | 说明返回值类型，一般用于方法注释，不能出现再构造方法中 | @return explanation                                          |
| @see          | 指定一个到另一个主题的链接                             | @see anchor <br>@see classname#methodname                    |
| @serial       | 说明一个序列化属性                                     | @serial description                                          |
| @serialData   | 说明通过 writeObject() 和 writeExternal() 方法写的数据 | @serialData description                                      |
| @serialField  | 说明一个 ObjectStreamField 组件                        | @serialField name type description                           |
| @since        | 说明从哪个版本起开始有了这个函数                       | @since release                                               |
| @throws       | 和 @exception 标签一样.                                | The @throws tag has the same meaning as the @exception tag.  |
| {@value}      | 显示常量的值，该常量必须是 static 属性。               | Displays the value of a constant, which must be a static field. |
| @version      | 指定类的版本，一般用于类注释                           | @version info                                                |