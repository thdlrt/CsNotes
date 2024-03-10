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
- 