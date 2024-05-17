---
url: https://blog.csdn.net/liu17234050/article/details/103471658?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522171592594716800222833307%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=171592594716800222833307&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-103471658-null-null.142^v100^control&utm_term=%E6%95%B0%E6%8D%AE%E5%BA%93%E9%80%89%E6%8B%A9%E9%A2%98&spm=1018.2226.3001.4187
title: 数据库理论习题四（58 道题 - 含答案）选择题_以下对存储过程的叙述中 - CSDN 博客
date: 2024-05-17 14:06:22
tag: 
summary: 
---
1、下列关于 SQL 的叙述中，正确的是

A)  SQL 是专供 MySQL 使用的结构化查询语言

B)  SQL 是一种过程化的语言

C)  SQL 是[关系数据库](https://so.csdn.net/so/search?q=%E5%85%B3%E7%B3%BB%E6%95%B0%E6%8D%AE%E5%BA%93&spm=1001.2101.3001.7020)的通用查询语言

D)  SQL 只能以交互方式对数据库进行操作

【解析】SQL 是一个通用的、功能极强的关系数据库语言；SQL 是一个非过程化的语言，因为它一次处理一个记录，对数据提供自动导航；作为独立的语言，SQL 可以独立用于联机交互的使用方式，作为嵌入式语言，SQL 语句能够嵌入到高级语言（C，Java）程序中。

答案 C。

2、在 CREATE TABLE 语句中，用来指定外键的关键字是

A)  CONSTRAINT

B)  PRIMARY KEY

C)  FOREIGN KEY

D)  CHECK

【解析】constraint : 用于各种约束的定义说明；PRIMARY KEY: 主键约束; FOREIGN KEY: 外键约束; CHECK: 条件约束（mysql 中不支持该约束）。

答案 C。

3、如果 DELETE 语句中没有使用 WHERE 子句，则下列叙述中正确的是

A)  删除指定数据表中的最后一条记录

B)  删除指定数据表中的全部记录

C)  不删除任何记录

D)  删除指定数据表中的第一条记录

解析】WHERE 子句说明只删除表中满足 WHERE 子名条件的记录。如果省略，则表示要删除表中全部记录。

答案 B。

4、指定一个数据库为当前数据库的 SQL 语句语法格式是

A)  CREATE DATABASE db_name;

B)  USE db_name;

C)  SHOW DATABASES;

D)  DROP DATABASE db_name;

答案: B

5、查询一个表中总记录数的 SQL 语句语法格式是

A)  SELECT COUNT(*) FROM tbl_name;

B)  SELECT COUNT FROM tbl_name;

C)  SELECT FROM COUNT tbl_name;

D)  SELECT * FROM tbl_name;

解析】在查询数据库中记录总数，应该使用关键的聚合函 COUNT，并且指定要统计的属性，或者用 "*" 号来表示，因此 B,C,D 语法错误，答案 A。

6、给定如下 SQL 语句

CREATE  VIEW   test.V_test

AS

SELECT * FROM   test.students

WHERE age<19;

该语句的功能是

A)  在 test 表上建立一个名为 V_test 的视图

B)  在 students 表上建立一个查询，存储在名为 test 的表中

C)  在 test 数据库的 students 表上建立一个名为 V_test 的视图

D)  在 test 表上建立一个名为 students 的视图

【解析】test.V_test，即为数据库 test 建立视图 V_test，视图内容是选取数据库 test 中表 students 中年龄小于 19 的所有信息。

答案 C。

7、MySQL 中用来创建数据库对象的命令是

A)  CREATE

B)  ALTER

C)  DROP

D)  GRANT

【解析】CREATE 用于创建数据库对象，ALTER 用于对数据库或数据库对象的结构进行修改；DROP 用于删除数据库或数据库对象；grant 用于给用户授予权限。答案 A。

8、下列关于 DROP、TRUNCATE 和 DELETE 命令的描述中，正确的是

A)  三者都能删除数据表的结构

B)  三者都只删除数据表中的数据

C)  三者都只删除数据表的结构

D)  三者都能删除数据表中的数据

【解析】delete 可以删除表中数据，DROP 语句可删除整个表对象，truncate 删除表比较快，只能删除表中的所有数据。答案 D。

9、下列关于空值的描述中，正确的是

A)  空值等同于数值

B)  空值等同于空字符串

C)  空值表示无值

D)  任意两个空值均相同

【解析】空值表示值未知。空值不同于空白或零值。没有两个相等的空值。答案 C。

10、在 MySQL 中，关键字 AUTO_INCREMENT 用于为列设置自增属性，能够设置该属性的数据类型是

A)  字符串类型

B)  日期类型

C)  整型

D)  枚举类型

【解析】Auto-increment 会在新记录插入表中时生成一个唯一的数字，一个表只能有一个 AUTO_INCREMENT 属性，且该属性必须为主键的一部分。AUTO_INCREMENT 属性可以是任何整数类型（tinyint，smallint，int，bigint 等）。答案 C。

11、下列关于 MySQL 基本表和视图的描述中，正确的是

A)  对基本表和视图的操作完全相同

B)  只能对基本表进行查询操作，不能对视图进行查询操作

C)  只能对基本表进行更新操作，不能对视图进行更新操作

D)  能对基本表和视图进行更新操作，但对视图的更新操作是受限制的

解析】表可以建立各种触发器，可以建立索引，可以建立主健、约束等。但是视图不能建立这些对象 (视图可以建立替代触发器）。表和视图可以更新，但是视图的更新受到约束。答案 D。

12、下列关于 PRIMARY KEY 和 UNIQUE 的描述中，错误的是

A)  两者都要求属性值唯一，故两者的作用完全一样

B)  每个表上只能定义一个 PRIMARY KEY 约束

C)  每个表上可以定义多个 UNIQUE 约束

D)  建立 UNIQUE 约束的属性列上，允许属性值为空

解析】PRIMARY KEY 是主键约束，UNIQUE 是唯一性约束，一张表只能设置一个主键，但可以设置多个唯一键，主键值不能重复也不能为 null，唯一键的值不能重复但可以为 null，答案 A。

13、SQL 中，激活触发器的命令包括

A)  CREATE、DROP、INSERT

B)  SELECT、CREATE、UPDATE

C)  INSERT、DELETE、UPDATE

D)  CREATE、DELETE、UPDATE

【解析】对一个表进行操作（ insert，delete， update）时才会激活触发器执行，即对表进行基本数据的操作时会激活触发器。答案 C。

14、下列关于 MySQL 触发器的描述中，错误的是

A)  触发器的执行是自动的

B)  触发器多用来保证数据的完整性

C)  触发器可以创建在表或视图上

D)  一个触发器只能定义在一个基本表上

【解析】触发器（trigger）的执行不是由程序调用，也不是手工启动，而是由事件来触发自动执行。触发器仅能在表上创建, 而不能在视图上定义。答案 C。

15、使用关键字 CALL 可以调用的数据库对象是

A)  触发器

B)  事件

C)  存储过程    

D)  存储函数

【解析】mysql 中 call 调用存储过程。C 对。触发器是由 select、updae、delete 语句激活，A 错。事件是系统调用，B 错。存储函数用 select 调用。答案 C。

16、

![](https://img-blog.csdnimg.cn/20191210105402153.png)

17、下列不能使用 ALTER 命令进行修改的数据库对象是

A)  触发器

B)  事件

C)  存储过程

D)  存储函数

【解析】若要修改触发器，将其重新创建并重新部署，将原始版本替换为修改后的版本。事件、存储过程、存储函数都能通过 alter 修改。答案 A。

18、函数 NOW() 返回的结果是

A)  系统的当前日期

B)  系统的当前时间

C)  系统的当前日期和时间

D)  系统的当前用户

【解析】NOW() 函数返回当前的日期和时间。答案 C。

19、撤销用户的权限应使用的语句是

A)  DROP

B)  ALTER

C)  REVOKE

D)  GRANT

解析】drop 是删除表、数据库对象时使用，A 错。Alter 是变更表的结构等时会用，B 错，grant 是给数据库用户授权时使用，D 错。要取消一个用户的权限，使用 REVOKE 语句。答案 C。

20、MySQL 中，下列关于授权的描述中，正确的是

A)  只能对数据表和存储过程授权

B)  只能对数据表和视图授权

C)  可以对数据项、数据表、存储过程和存储函数授权

D)  可以对属性列、数据表、视图、存储过程和存储函数授权

解析】授权包括：创建表、索引、列、视图、存储过程、函数等权限。答案 D。

21、MySQL 成功安装后，在系统中默认建立的用户个数是

A)  0

B)  1

C)  2

D)  3

解析】安装后，建立的用户是默认 root。答案 B。

22、用户 LISA 在 MySQL 中建立了一个读者借阅图书数据库，在该数据库中创建了读者表、图书表和借阅表，并为该数据库添加了两个用户 U1 和 U2，给 U1 授予对所有数据表的查询权限，给 U2 授予对所有数据表的插入权限，下列用户中不能使用 CREATE USER 创建用户的是

A)  root

B)  LISA

C)  U1

D)  U2

【解析】。Root 是超级管理员用记，拥有所有的权限，包括建用户的权限，A 对。lisa 在本题中已建用户 U1、U2，显然有建新用户的权限，B 对。U1 只有查询权限，不具有创建用户的权限, C 错，U2 拥有插入权限，使用 create user 命令创建用户等同于向 mysql.user 表插入数据，可建新用户，D 对。答案 C。

23、备份整个数据库的命令是

A)  mysqldump

B)  mysql

C)  mysqlimport

D)  backup

【解析】mysqldump 可以备份数据库、备份数据表的结构、备份整个数据库系统，A 对。mysql 是恢复数据库使用的命令，B 错。mysqlimport 用于恢复数据表中的数据, C 错。无 backup 命令，D 错。答案 A。

24、下列关于 MySQL 数据库的叙述中，错误的是

A)  执行 ATLER DATABASE 语句更改参数时，不影响数据库中现有对象

B)  执行 CREATE DATABASE 语句后，创建了一个数据库对象的容器

C)  执行 DROP DATABASE 语句后，数据库中的对象同时被删除

D)  CREATE DATABASE 与 CREATE SCHEMA 作用相同

【解析】执行 ATLER DATABASE 语句更改参数时，更改数据库属性，会影响数据库现有对象。A 错。Create database.. 是创建数据库的语句，B 对。Drop database.. 是删除数据库，C 对。CREATE SCHEMA 从 MySQL5.0.2 起，可作为 CREATE DATABASE 的一个代名词，D 对。答案 A 。

25、在 MySQL 中，NULL 的含义是

A)  无值

B)  数值 0

C)  空串

D)  FALSE

【解析】无值。B、C、D 皆不对。答案 A。

26、在使用 MySQL 进行数据库程序设计时，若需要支持事务处理应用，其存储引擎应该是

A) InnoDB

B) MyISAM

C) MEMORY

D)  CSV

【解析】InnoDB 存储引擎支持事务处理，其他几个都不支持事务处理，答案 A。

27、使用 SQL 语句查询学生信息表 tbl_student 中的所有数据，并按学生学号 stu_id 升序排列，正确的语句是

A)  SELECT * FROM tbl_student ORDER BY stu_id ASC;

B)  SELECT * FROM tbl_student ORDER BY stu_id DESC;

C)  SELECT * FROM tbl_student stu_id ORDER BY ASC;

D)  SELECT * FROM tbl_student stu_id ORDER BY DESC;

解析】基本语法，ASC 为升序，DESC 为降序，ORDER BY 后面必须跟上要排序的属性名，B 为降序排列，C、D 语法错误。答案 A。

28、统计表中所有记录个数的聚集函数是

A)  COUNT

B)  SUM

C)  MAX

D)  AVG

【解析】COUNT：统计，SUM: 求和，MAX: 求最大值，AVG：求均值。答案 A。

29、下列关于索引的叙述中，错误的是

A)  索引能够提高数据表读写速度

B)  索引能够提高查询效率

C)  UNIQUE 索引是唯一性索引

D)  索引可以建立在单列上，也可以建立多列上

【解析】索引能够提高查询速度，但会降低数据表的读写速度。A 错，B 对。Unique 是唯一性关键词，该索引是唯一性索引，C 对。索引可以建立在单列或多列上，D 对。答案 A。

30、下列关于视图的叙述中，正确的是

A)  使用视图，能够屏蔽数据库的复杂性

B) 更新视图数据的方式与更新表中数据的方式相同

C)  视图上可以建立索引

D)  使用视图，能够提高数据更新的速度

【解析】视图向用户隐藏了表与表之间的复杂的连接操作; 对视图的更新操作有一定限制；视图不可建索引；数据更新速度与视图无关。答案 A。

31、修改表中数据的命令是

A)  UPDATE

B)  ALTER TABLE

C)  REPAIR TABLE

D)  CHECK TABLE

解析】ALTER TABLE 语句用于修改表的结构; 无 C、D 这种语法。答案 A。

32、下列关于表的叙述中，错误的是

A)  所有合法用户都能执行创建表的命令

B)  MySQL 中建立的表一定属于某个数据库

C)  建表的同时能够通过 Primary Key 指定表的主键

D)  MySQL 中允许建立临时表

【解析】不同的用户享有的权限不一，可以只有查询权限，可以只有创建表权限，A 错。Mysql 中，表是属于数据库的一部分，不可独立存在，B 对。建表时可通过关键字 primary key 指定主键，C 对。可通过 CREATE TEMPORARY TABLE 建立临时表。D 对。答案 A。

33、下列关于存储过程的叙述中，正确的是

A)  存储过程可以带有参数

B)  存储过程能够自动触发并执行

C)  存储过程中只能包含数据更新语句

D)  存储过程可以有返回值

【解析】存储过程存储在数据库内，可由应用程序通过一个调用执行，而且允许用户声明变量、触发器才能由增、删、改事件触发执行，存储函数才能有返回值。答案 A。

34、下列关于用户及权限的叙述中，错误的是

A)  删除用户时，系统同时删除该用户创建的表

B)  root 用户拥有操作和管理 MySQL 的所有权限

C)  系统允许给用户授予与 root 相同的权限

D)  新建用户必须经授权才能访问数据库

【解析】删除用户时，系统不会删除该用户创建的表。root 是系统中的超级管理员用户帐户，拥有所有的权限，B 对。新建用户时，并不任何权限，只有授权后才能访问操作数据库，D 对。系统允许授予用户和 root 权限，C 对。答案 A。

35、MySQL 数据库中最小授权对象是

A)  列 B)  表 C)  数据库 D)  用户

【解析】答案 A。

36、执行 REVOKE 语句的结果是

A)  用户的权限被撤销，但用户仍保留在系统中

B)  用户的权限被撤销，并且从系统中删除该用户

C)  将某个用户的权限转移给其他用户

D)  保留用户权限

【解析】revoke 用于撤销权限，drop 可删除用户。用户的权限被撤销，系统中仍保留用户，只是暂时不能用该用户的身份登录系统。答案 A。

37、下列关于 MySQL 数据库备份与恢复的叙述中，错误的是

A)  mysqldump 命令的作用是备份数据库中的数据

B)  数据库恢复是使数据库从错误状态恢复到最近一次备份时的正确状态

C)  数据库恢复的基础是数据库副本和日志文件

D)  数据库恢复措施与数据库备份的类型有关

【解析】mysqldump 可以备份表、备份数据库、备份整个数据库系统的命令，A 错。数据库的恢复是需要最近一次的备份文件、日志文件，且状态正常，B、C 对。根据数据库备份的类型要采用不同的措施来恢复，D 对。答案 A。

38、恢复 MySQL 数据库可使用的命令是

A)  mysqldump

B)  mysqladmin

C)  mysql

D)  mysqld

解析】答案 C。

39、MySQL 服务器使用 TCP/IP 网络的默认端口号是

A)  3306

B)  8088

C)  8080

D)  3124

解析】TCP/IP 连接的默认端口号是 3306。答案 A。

40、在 SQL 语言按功能的分类中，不包括

A)  DDL

B)  DML

C)  DCL

D)  DLL

解析】sql 按语言分类为：数据操纵语言（DML）；数据定义语言（DDL）；数据控制语言（DCL）。答案 D。

41、在 MySQL 中，可用于创建一个新数据库的 SQL 语句为

A)  CREATE DATABASE

B  CREATE TABLE

C)  CREATE DATABASES

D)  CREATE DB

【解析】建库语句为：CREATE DATABASE db_name，A 对。B 是建表，C、D 语法错。答案 A。

42、在使用 INSERT INTO 插入记录时，对于 AUTO_INCREMENT 列，若需要使其值自动增长，下面填充方式中错误的是

A)  填充 NULL 值

B)  不显式地填充值

C)  填充数字 0

D)  填充数字 1

【解析】AUTO_INCREMENT 所在列在插入数据时自动加 1，且起始值是 1，填充数字不可为 1，可为 null、0 或不写。答案 D。

43、SQL 语句中，判断字段 sno 是否为空值时，应该使用的表达式是

A)  sno IS NULL

B)  sno =NULL

C)  sno NULL OR NOT

D)  以上方式皆可

【解析】NULL 是空值，判断是否为空用 IS NULL。答案 A。

44、要消除查询结果集中的重复值，可在 SELECT 语句中使用关键字

A)  UNION

B)  DISTINCT

C)  LIMIT

D)  REMOVE

解析】union 用于合并两个查询语句的结果集, A 错。关键词 DISTINCT 用于返回唯一不同的值，B 对。Limit 用于限定 select 查询结果最大返回行数，C 错。答案 B。

45、设 WHERE 子句中的条件表达式是：num  20  between 30, 其含义是：num 的值是 20 到 30 范围内的所有整数，且（）

A) 包含 20 和 30

B) 不包含 20 和 30

C) 包含 20，不包含 30

D) 不包含 20，包含 30

答案 C

46、在使用 ALTER TABLE 修改表结构时，关于 CHANGE 和 MODIFY 两子句的描述中，不正确的是

A)  CHANGE 后面需要写两次列名，而 MODIFY 后面只写一次

B)  两种方式都可用于修改某个列的数据类型

C)  都可以使用 FIRST 或 AFTER 来修改列的排列顺序

D)  MODIFY 可用于修改某个列的名称  

【解析】change 可以修改列的名称和数据类型，MODIFY 只能修改列的数据类型。答案 D。

47、在下列有关 GROUP BY 语句的描述中，不正确的是

A)  分组条件可以有多个，并且每一个可以分别指定排序方式

B)  可以使用 WHERE 子句对所得的分组进行筛选

C)  GROUP BY 可配合聚合函数一起使用，但 GROUP BY 子句中不能直接使用聚合函数

D)  除了聚合函数，SELECT 语句中的每个列都必须在 GROUP BY 子句中给出

解析：GROUP BY 对查询结果按字段列表进行分组，字段值相等的记录分为一组，指定用于分组的字段列表可以是一列，也可以是多个列，彼此间用逗号分隔，HAVING 短语对分组的结果进行过滤，仅输出满足条件的组。

答案 B。

48、对于索引，正确的描述是

A)  索引的数据无需存储，仅保存在内存中

B)  一个表上可以有多个聚集索引

C)  索引通常可减少表扫描，从而提高检索的效率

D)  所有索引都是唯一性的索引  

解析】索引需要占物理空间，不存储在内存；一个表可以有多个索引；索引可以提高检索效率。答案 C。

49、在 MySQL 数据库中，可以在服务器、数据库、表等级别上指定缺省字符集，而这些字符集的设定将作用于

A)  所有字段

B)  CHAR、VARCHAR、TEXT 等字符类型的字段

C)  所有数据库连接

D)  数值型字段

解析】服务器、数据库、表等级别上指定缺省字符集作用于 CHAR、VARCHAR、TEXT 等字符类型的字段。答案 B。

50、对于 SQL 查询：

SELECT * FROM tbl_name WHERE id=(SELECT id FROM tbl_name)，假设该表中包含 id 字段，那么该语句正确执行的条件是

A)  该表中必须有多条记录

B)  该表中必须只有一条记录

C)  该表中记录数必须小于等于一条

D)  此 [SQL 语句](https://so.csdn.net/so/search?q=SQL%E8%AF%AD%E5%8F%A5&spm=1001.2101.3001.7020)错误

【解析】当表中记录多于 1 条记录时，(SELECT id FROM tbl_name) 返回的是一个结果集，把结果集赋给 id，显然执行语句失败，当记录小于等于 1 时，返回的是空或者是 id 值，可以作为条件查询。答案 C。

51、下列操作中，不可能触发对应关系表上触发器的操作是

A)  SELECT

B)  INSERT

C)  UPDATE

D)  DELETE

【解析】对一个表进行操作（ insert，delete， update）时就会激活触发器执行。答案 A。

52、在存储过程的定义中，其参数的输入输出类型包括

A)  IN、OUT

B)  IN、OUT、INOUT

C)  IN

D)  OUT

【解析】在存储过程的定义中，其参数的输入输出类型包括 IN、OUT、INOUT 答案 B。

53、在存储过程中，使用游标的一般流程是

A)  打开 --> 读取 --> 关闭

B)  声明 --> 读取 --> 关闭

C)  声明 --> 打开 --> 读取 --> 关闭

D)  声明 --> 填充内容 --> 打开 --> 读取 --> 关闭  

【解析】使用游标的一般流程是 声明、打开、读取、关闭。C 对，其它选项流程错误。答案 C。

54、关于 MySQL 中存储函数和存储过程的区别，不正确的是

A)  存储过程可以有输出参数，而存储函数则没有

B)  存储函数必须使用 RETURN 语句返回结果

C)  调用存储函数无需使用 CALL 语句

D)   存储函数中不能像存储过程那样定义局部变量

解析】存储函数中可以定义局部变量，D 错。存储过程有输出参数 out，存储函数可通过且必须通过 return 返回结果值，无输出参数，A、B 对。调用存储过程用 call, 调整存储函数用 select。C 对。答案 D。

55、修改用户登录口令的命令是

A)  SET PASSWORD

B)  UPDATE PASSWORD

C)  CHANGE PASSWORD

D)   MODIFY PASSWORD

【解析】修改用户登录口令用 SET PASSWORD。无 B、C、D 相当语句。答案 A。

56、用户刚创建后，只能登录服务器，而无法执行任何数据库操作的原因是

A)  用户还需要修改密码

B)  用户尚未激活

C)  用户还没有任何数据库对象的操作权限

D)  以上皆有可能

【解析】用户创建时，是不具有访问数据库权限的，只有在给用户授予操作数据库的权限，才可以操作数据库。答案 C。

57、在 GRANT 授权语句中，WITH GRANT OPTION 的含义是

A)  用户权限在服务器重启之后，将自动撤销

B)  该用户权限仅限于所指定的用户

C)  用户将获得指定数据库对象上的所有权限

D)  允许该用户将此权限转移授予其他用户

 解析】允许将权限传递给第三方。答案 D。

58、在 GRANT ALL ON *.* TO… 授权语句中，ALL 和 *.* 的含义分别是

A)  所有权限、所有数据库表

B)  所有数据库表、所有权限

C)  所有用户、所有权限

D)  所有权限、所有用户

析】*.* 意为所有权限、所有数据库中的所有表。答案 A