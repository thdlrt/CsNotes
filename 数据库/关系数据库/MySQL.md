### 配置与安装

- [[MySQL卸载文档-Windows版]]
- [[MySQL安装]]

### 基本操作

- 启动停止

  ```shell
    net start mysql80
    net stop mysql80
#linux
sudo service mysql start
```

- 连接到数据库

```shell
    mysql [-h 127.0.0.1] [-P 3306] -u root -p
    参数：
    -h : MySQL服务所在的主机IP(省略默认为本地)
    -P : MySQL服务端口号， 默认3306
    -u : MySQL数据库用户名
    -p ： MySQL数据库用户名对应的密码
```

- 查看已经创建的数据库 `show databases;`
	- 连接到数据库 `use name`
- 查看数据库中的表 `show tables;`

#### 导入和导出

- 数据文件导入方式只包含数据，导入规则由数据库系统完成；SQL 文件导入相当于执行该文件中包含的 SQL 语句，可以实现多种操作，包括删除，更新，新增，甚至对数据库的重建。
- 导入数据文件：`LOAD DATA INFILE '文件路径和文件名' INTO TABLE 表名字;`
	- `LOAD DATA INFILE '/var/lib/mysql-files/in.txt' INTO TABLE employee;`
	- 导入导出大量数据都属于敏感操作，根据 mysql 的安全策略，导入导出的文件都**必须在指定的路径**下进行
	- 查看指定的路径 ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240214154101.png)
	- 注意到 secure_file_priv 变量指定安全路径为 `/var/lib/mysql-files/` ，要导入数据文件，需要将该文件**移动到安全路径下**。

- 导入 sql 文件：
	- `source /home/shiyanlou/Desktop/MySQL-04-01.sql`

- 导出数据  `SELECT 列1，列2 INTO OUTFILE '文件路径和文件名' FROM 表名字;`
	- `SELECT * INTO OUTFILE '/var/lib/mysql-files/out.txt' FROM employee;`

#### 备份和恢复

- 备份
	- **导出**的文件只是保存数据库中的**数据**；而备份，则是把**数据库的结构**，包括数据、约束、索引、视图等全部另存为一个文件。
	- 备份整个数据库 `mysqldump -u root 数据库名>备份文件名;`
	- 备份数据库中的某一个表 `mysqldump -u root 数据库名 表名字>备份文件名;`
	- 不需要进入 mysql 命令行就执行命令
	- 生成脚本文件（.sql）

- 恢复
	- 在 mysql 状态下执行 `source /home/shiyanlou/Desktop/MySQL-06.sql`
	- 或者先创建数据库 `CREATE DATABASE test;`，退出 mysql 后执行 `mysql -u root test < bak.sql`
	- 

