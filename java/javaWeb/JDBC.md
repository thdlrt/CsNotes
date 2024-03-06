- 包括了一组**与数据库交互**的 api，还有与数据库进行通信的驱动程序。
- 通过 JDBC 与下层具体数据库交互实现了数据库接口的统一（由中间层进行不同的处理）
	- ![image.png|425](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220142023.png)

- 组成：
	- JDBC 驱动程序管理器
	- JDBC 驱动程序测试工具包
	- JDBC-ODBC 桥
	- ![image.png|425](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220144647.png)

- JDBC 驱动程序可以打开数据库连接，发送 SQL 及数据库命令，收到结果并与 Java 进行交互

- 程序示例
```java
import java.sql.*;

public class JdbcTest {
   // JDBC 驱动器名称 和数据库地址
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
   //数据库的名称为 EXAMPLE
   static final String DB_URL = "jdbc:mysql://localhost/EXAMPLE";

   //  数据库用户和密码
   static final String USER = "root";

   static final String PASS = "";

   public static void main(String[] args) {
       Connection conn = null;
       Statement stmt = null;
       try{
           //注册 JDBC 驱动程序
           Class.forName("com.mysql.jdbc.Driver");

           //打开连接
           System.out.println("Connecting to database...");
           conn = DriverManager.getConnection(DB_URL,USER,PASS);

           //执行查询
           System.out.println("Creating statement...");
           stmt = conn.createStatement();
           String sql;
           sql = "SELECT id, name, age FROM Students";
           ResultSet rs = stmt.executeQuery(sql);

           //得到和处理结果集
           while(rs.next()){
               //检索
               int id  = rs.getInt("id");
               int age = rs.getInt("age");
               String name = rs.getString("name");

               //显示
               System.out.print("ID: " + id);
               System.out.print(", Age: " + age);
               System.out.print(", Name: " + name);
               System.out.println();
           }
           //清理环境
           rs.close();
           stmt.close();
           conn.close();
       }catch(SQLException se){
           // JDBC 操作错误
           se.printStackTrace();
       }catch(Exception e){
           // Class.forName 错误
           e.printStackTrace();
       }finally{
           //这里一般用来关闭资源的
           try{
               if(stmt!=null)
                   stmt.close();
           }catch(SQLException se2){
           }
           try{
               if(conn!=null)
                   conn.close();
           }catch(SQLException se){
               se.printStackTrace();
           }
       }
       System.out.println("Goodbye!");
   }
}
```

### 基本操作

#### 导入 JDBC 驱动

- maven
```xml
<dependency>
	<groupId>mysql</groupId>
	<artifactId>mysql-connector-java</artifactId>
	<version>版本号</version>
</dependency>
```
- gradle
```json
dependencies {
    implementation 'mysql:mysql-connector-java:版本号'
}
```
- 或者直接下载并导入 mysql-connector-java 的 jar 包
#### 连接到数据库

- 注册驱动程序
	- 对于 JDBC 4.0 以上的版本已经不需要手动注册
```java
try { Class.forName("com.mysql.jdbc.Driver"); } catch(ClassNotFoundException ex) { System.out.println("Error: unable to load driver class!"); System.exit(1); }
```
- 指定数据库连接 URL
	- `DriverManager.getConnection(String url[, String user, String password])`
	- 不同数据库的连接格式
		- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220152957.png)
- 创建连接对象
	- `Connection conn = DriverManager.getConnection(URL, USER, PASS);`
	- 通过 Properties (键值对) 对象创建
```java
String URL = "jdbc:mysql://localhost/EXAMPLE";
Properties pro = new Properties( );

//Properties 对象，保存一组关键字-值对
pro.put( "user", "root" );
pro.put( "password", "" );

Connection conn = DriverManager.getConnection(URL, pro);
```
- 关闭连接 `conn.close();`
### 常用接口
![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220154905.png)

#### Statement
- 使用 Connection 对象的 createStatement() 方法进行创建
```java
Statement stmt = null;
try {
   stmt = conn.createStatement( );
   . . .
}
catch (SQLException e) {
   . . .
}
finally {
   stmt.close();
}
```
- 执行 SQL 语句
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220155347.png)
#### PreparedStatement
- PreparedStatement 接口扩展了 Statement 接口，有利于**高效地执行多次使用的** SQL 语句。
	- Statement 为一条 SQL 语句生成执行计划。如果要执行两条 SQL 语句，会生成两个执行计划。一万个查询就生成一万个执行计划！
	- PreparedStatement 用于使用绑定变量**重用**执行计划。通过 set 不同数据，只需要生成一次执行计划，并且可以重用。

- 在 JDBC 中所有的**参数**都被代表**？** 符号，这是已知的参数标记。在执行 SQL 语句之前，必须**提供值的每一个参数**
```java

String sql = "UPDATE Students set age=? WHERE id=?";
stmt = conn.prepareStatement(sql);

//将值绑定到参数，参数从左至右序号为 1，2...
stmt.setInt(1, 22);  // 绑定 age 的值（序号为 1)
stmt.setInt(2, 1); // 绑定 ID 的值

// 更新 ID 为 1 的同学的年龄
int rows = stmt.executeUpdate();
System.out.println("被影响的行数 : " + rows );

// 查询所有记录，并显示。
sql = "SELECT id, name, age FROM Students";
ResultSet rs = stmt.executeQuery(sql);

```
#### CallableStatement
-  提供了一种以标准形式调用**存储过程**的方法，用于执行一系列较为复杂的操作

#### ResultSet
- 获取数据库操作的结果
	- 通过迭代器访问结果

- 创建方法
```java
createStatement(int RSType, int RSConcurrency);
prepareStatement(String SQL, int RSType, int RSConcurrency);
prepareCall(String sql, int RSType, int RSConcurrency);
```
- RSType 表示 ResultSet 对象的类型，RSConcurrency 是 ResultSet 常量，用于指定一个结果集是否为只读或可更新。
	- ResultSet 的类型，如果不指定 ResultSet 类型，将自动获得一个是 TYPE_FORWARD_ONLY：![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220165848.png)
	- 并发性的 ResultSet (RSConcurrency)，如果不指定任何并发类型，将自动获得一个为 CONCUR_READ_ONLY
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220170033.png)
```java
try {
   Statement stmt = conn.createStatement(
                           ResultSet.TYPE_SCROLL_INSENSITIVE,
                           ResultSet.CONCUR_UPDATABLE);
}
catch(Exception ex) {
   ....
}
finally {
   ....
}
```

- 控制迭代器的移动
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220170127.png)
- 结果的获取
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220170444.png)
	- 对于其它数据类型也有相应的获取方式
- 修改（结果集）数据
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220170544.png)
- 将结果集的修改同步到数据库
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220170838.png)

- 向数据库插入数据
```java
ResultSet rs = stmt.executeQuery(sql);

//结果集中插入新行
rs.moveToInsertRow();
rs.updateInt("id",5);
rs.updateString("name","John");
rs.updateInt("age",21);
//更新数据库
rs.insertRow();
```

- java 与 sql 数据类型的准换
	- 通过 JDBC 进行数据类型的转换
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220172858.png)
### 事务

- 默认情况下每个 SQL 语句都是在其完成时提交到数据库（自动提交模式），也可以手动控制让多条 SQL 在同一个事务中进行
	- 关闭自动提交模式 `conn.setAutoCommit(false);`

- 提交事务 `conn.commit();`
```java
//执行查询
           System.out.println("Creating statement...");
           stmt = conn.createStatement();
           //插入
           String sql = "INSERT INTO Students  " +
                    "VALUES (5, 20, 'Rose')";
           stmt.executeUpdate(sql);
           //查找
           sql = "SELECT id, name, age FROM Students";
           ResultSet rs = stmt.executeQuery(sql);

           //提交事务
           conn.commit()
```
- 回滚事务（如在 catch 即发生异常时进行）`conn.rollback();`

### 补充
#### 异常处理
- `java.sql.SQLException` 的方法
- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240220173914.png)

#### 批量处理 
- 将相关的 SQL 语句组合成一个批处理和一个调用数据库提交（一次发送多个 SQL 语句到数据库）、
- 通过 `DatabaseMetaData.supportsBatchUpdates()` 的 bool 返回值检查是否支持批量更新功能
- 本质上与事务是一致的，但是目的是为了减少网络带宽，并且提升性能

```java
// 创建 statement 对象
Statement stmt = conn.createStatement();

// 关闭自动提交
conn.setAutoCommit(false);

// 创建 SQL 语句
String SQL = "INSERT INTO Students (id, name, age) VALUES(6,'Mike', 21)";
// 将 SQL 语句添加到批处理中
stmt.addBatch(SQL);

// 创建更多的 SQL 语句
String SQL = "INSERT INTO Students (id, name, age) VALUES(7, 'Angle', 23)";
// 将 SQL 语句添加到 批处理中
stmt.addBatch(SQL);

// 创建整数数组记录更新情况
int[] count = stmt.executeBatch();

//提交更改
conn.commit();
```