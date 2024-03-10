## 基本概念
- 一个 key-value 存储系统。
- Redis 常被称作是一款**数据结构服务器**。Redis 的**键值**可以包括字符串类型，同时它还包括哈希、列表、集合和有序集合等**数据类型**。并且可以执行对这些数据结构的操作
- 优点：
	- 性能极高
	- 原子操作
	- 丰富数据类型
- Redis 是一个**服务端和客户端**配合的程序
### Redis 的安装与配置

### 基本操作
```shell
# 开启 redis-server(服务端)
sudo service redis-server start
# 进入 redis-cli(客户端)
redis-cli
```
## 用法
### Redis 中的数据结构
#### Redis strings
- Redis 字符串是二进制安全的，可以存储 base 64 编码的图片以及序列化对象等
- **过大文件**不适合存入 Redis，符串类型的值最多能存储 512M 字节的内容。
- 设置和获取 set、get 命令
	- ![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240310225534.png)
```shell
set mykey newval nx
set mykey newval xx
```
- set 参数：nx 表示只有 key **不存在才设置**新值；xx 表示当 key 已经**存在了才设置**新值
- 一次获取多个键值
```shell
mset a 10 b 20 c 30 
mget a b c
```

#### Redis Lists
- 支持从头尾插入元素
	- `rpush mylist A` 向末尾添加元素 A
	- 一次添加多个元素 `rpush mylist 1 2 3 4 5 "foo bar"`
	- `lpush mylist B` 向头部添加元素 B
- 弹出元素
```shell
rpop mylist
lpop mylist
```
- 范围获取元素 `lrange mylist 0 -1`

- 阻塞操作：数据不存在时阻塞请求队列，超时还没有数据则返回 nil
```shell
brpop list 10
brpop mylist 10
```
#### Redis Hashes
- 字符串字段和字符串值之间的映射
- 定义哈希表
```shell
hmset user:1000 username antirez birthyear 1977 verified 1
```
- 建立一个名称为 `user:1000` 的哈希表，建立的键值映射关系为 `username:antirez`、`birthyear:1977` 、`verified:1`
- 获取值
```shell
hget user:1000 username 
hget user:1000 birthyear
# 获取全部键和值
hgetall user:1000
```
- 修改值
```shell
hincrby user:1000 birthyear 10
hincrby user:1000 birthyear 10
```
#### Redis 无序集合
- （哈希表 unordered_set）
- 支持进行集合运算
- 创建集合 `sadd myset 1 2 3`
- 查看集合元素 `smembers myset` 
- 查看集合元素是否存在（返回 01）`sismember myset 3`
#### Redis 有序集合
- 支持获取范围元素