## 基本概念
- 一个内存 key-value 存储系统。 Redis 可用作数据库、缓存、消息代理和队列等。
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
- 添加元素\<排序用的键 元素>
```shell
zadd hackers 1940 "Alan Kay"
zadd hackers 1957 "Sophie Wilson"
add hackers 1953 "Richard Stallman"
```
- 范围查看集合
```shell
zrange hackers 0 -1
zrevrange hackers 0 -1
```
### 常用命令
#### key 操作
- Redis 命令**大小不敏感**
- 判断 key 是否存在 `exits keyname`
- 删除 key `del keyname`
- 获取 key 元素的数据类型 `type keyname`
- 返回匹配的 key 列表 `keys keypattern` 如 `keys my*`
- 随机获取已经存在的 key，数据库为空则返回空字符串 `randomkey`
- 重命名 key `rename oldname newname` (存在则覆盖新键) `renamenx` 存在则更新失败
- 获取数据库中 key 的总数目 `dbsize`
- `flushdb`：清空当前数据库中的所有键。
-  `flushall`：清空所有数据库中的所有键。
#### 时间
- 设置 key 的生存周期（多长时间之后自动删除）`expire key 10` 表示 10 s 之后自动删除 key
	- 在添加 key 时设置时间 `set key 100 ex 30`
- 查询 key 的剩余时间 `ttl key`
#### 设置&配置信息
- `config get`：用来读取运行 Redis 服务器的配置参数。 
- `config set`：用于更改运行 Redis 服务器的配置参数。
- `auth`：认证密码。
```shell
> config get requirepass  # 查看密码
> config set requirepass test123  # 设置密码为 test123
> config get requirepass  # 报错，没有认证
> auth test123  # 认证密码
> config get requirepass
```
-  `info [section]`：查询 Redis 相关信息。
	- server: Redis server 的常规信息
	- clients: Client 的连接选项
	- memory: 存储占用相关信息
	- persistence: RDB and AOF 相关信息
	- stats: 常规统计
	- replication: Master/Slave 请求信息
	- cpu: CPU 占用信息统计
	- cluster: Redis 集群信息
	- keyspace: 数据库信息统计
	- all: 返回所有信息
	- default: 返回常规设置信息
### 高级应用
#### 安全性
- 为客户端连接制定密码
- 使用 `config set` 命令的 requirepass 参数，具体格式为 `config set requirepass [password]"`
	- 登录时可以使用 `redis-cli -a password`。
	- 登录后可以使用 `auth password`。
#### 主从复制
- 为了分担服务器压力，会在特定情况下部署多台服务器分别用于缓存的读和写操作，用于**写操作的服务器称为主服务器**，用于**读操作的服务器称为从服务器。**
- 主从复制过程
	- Slave 与 Master 建立连接，发送 psync 同步命令。
	- Master 会启动一个后台进程，将数据库快照保存到文件中，同时 Master 主进程会开始收集新的写命令并缓存。
	- 后台完成保存后，就将此文件发送给 Slave。
	- Slave 将此文件保存到磁盘上。
- 主从复制特点
	- 可以拥有多个 Slave。
	- 多个 Slave 可以连接同一个 Master 外，还可以连接到其它的 Slave。（当 Master 宕机后，相连的 Slave 转变为 Master）。
	- 主从复制不会阻塞 Master，在同步数据时， Master 可以继续处理 Client 请求。
	- 提高了系统的可伸缩性。
- 如果在同步过程中，主服务器修改了一篇博客，而同步到从服务器上的博客是**修改前的**。这时候就会出现时间差，即修改了博客过后，在访问网站的时候还是原来的数据，这是因为从服务器还未同步最新的更改，这也就意味着**非阻塞式的同步只能应用于对读数据延迟接受度较高的场景。**
#### 事务处理
- 只能保证 client 发起的事务中的**命令可以连续的执行**，而且不会插入其它的 client 命令
	- 它**不会**在事务过程中出错时**恢复**到之前的状态，这在实际应用中导致我们不能依赖 redis 的事务来保证数据一致性。
- 使用 multi 和 exec 保住事务代码
```shell
> multi
> set name a
> set name b
> exec
> get name
```
#### 虚拟化机制
- Redis 是一个支**持持久化**的内存数据库，Redis 需要经常将内存中的数据**同步到磁盘**来保证持久化。
- 快照：将内存中的数据以快照的方式写入到二进制文件（可以配置快照频率，如时间间隔、操作数目等）使用快照仍然会丢失最后一次**快照之后的所有修改**
- AOF：将收到的每一个写命令都通过 write 存储到文件，redis 启动时通过保存的写命令来**重建数据库**
	- 由于 os 会在内核中缓存 write 做的修改，所以可能不是立即写到磁盘上，这样 aof 方式的持久化也还是有可能会丢失一部分数据。
#### 虚拟内存
- 把**不经常访问**的数据**从内存交换到磁盘**，节约内存空间（对于 redis 这样的内存数据库，内存总是不够用的）
## 八股
### 基础功能及原理
- Redis 的使用场景
	- **缓存**：Redis 最常用的场景是作为缓存，Redis 通过支持多种高级数据结构，例如哈希表、有序集合和位图等，可以提供高效的缓存功能。
	- **实时数据处理**：Redis 可以用于实时数据处理，例如在大型游戏或社交网络中跟踪用户活动或统计实时事件。由于 Redis 的高性能和低延迟，它可以快速处理大量的实时数据，并提供高效的查询和分析功能。
	- **分布式锁**：Redis 还可以用于实现分布式锁。分布式锁用于协调分布式系统中的并发访问，确保**每个操作都具有唯一的锁**。Redis 可以提供原子操作，使其成为一种可靠的分布式锁解决方案。
	- **消息队列**：Redis 还可以用作消息队列。消息队列用于异步处理任务，例如将电子邮件或推送通知发送到目标用户或将任务传递给后台处理程序。Redis 可以通过支持多种数据结构（例如队列、堆栈和发布/订阅）来简化消息队列的实现。
	- **地理位置服务**：Redis 还可以用于实现地理位置服务，例如在地图应用程序中查找附近的商店或定位服务。Redis 可以利用其支持的**地理位置索引和排序功能**来实现这种应用程序需求。

- 
### 事件分析