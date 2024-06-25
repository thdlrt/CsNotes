- docker 使用容器技术，与虚拟机技术相比更加轻量级，对资源的消耗更少
- 通过镜像来创建容器，镜像可以通过 DockerFile 创建
- 容器是镜像创建的**运行实例**，也可以使用云端仓库存储的镜像

### 基本操作

- docker安装`curl https://get.docker.com/ | bash -s docker --mirror Aliyun`
- 检查运行状态`sudo systemctl status docker`
  - 启动`sudo systemctl start docker`
- 将用户添加到docker可执行组`sudo usermod -aG docker username
- 拉取docker镜像：`docker pull name`
- 查看已经安装的镜像：`docker images`
- 删除镜像：`docker rmi name`
  - 强制删除：`docker rmi --force name`
- 查看系统运行状态：`docker info`
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221113905.png)

- 删除所有容器
```shell
# 暂停所有运行中的容器
docker container ls -q | xargs docker container stop

# 删除所有的容器
docker container ls -aq | xargs docker container rm
```

### 容器
 - 查看 (运行中的)容器 `docker container ls`
	 - ![|227](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221121526.png)
- 容器的运行状态
	- Created：容器已经被创建但是还没有启动
	- Running：start 之后容器处在运行状态
	- Paused
	- Restarting：正在重新启动
	- Exited：已经停止运行
	- Dead：无法被停止或删除，异常状态
- 可以使用容器名称或 id（前缀）表示容器

- 运行容器（在新容器中运行命令）：`docker container run [OPTIONS] IMAGE [COMMAND[ARGS]]` 会在指定的镜像上创建容器 
	- 相当于一次进行了 create 和 start 操作
- ![image.png|425](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221114854.png)
	- 如果本地没有镜像则会从仓库自动下载，启动镜像运行 COMMAND，输出结果之后退出程序
	- 获取持续运行的容器（分配一个伪终端）
```shell
docker container run \
    -i -t \
    ubuntu /bin/bash
```
- 退出容器：exit 推出并停止；ctrl+p 再 ctrl+q 后台运行

- 创建容器：`docker container create [OPTIONS] IMAGE [COMMAND] [ARG]`
	- 该命令会在指定的镜像 IMAGE 上创建一个可写容器层，并准备运行指定的命令。(只是创建不会立即运行)
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221120406.png)
- 运行容器 `docker container start [OPTIONS] CONTAINER [CONTAINER...]`
- 停止容器 `docker container stop CONTAINER [CONTAINER...] 
- 重启容器 `docker container restart CONTAINER [CONTAINER...]`
- 连接到（在后台）的容器 `docker container attach [OPTIONS] CONTAINER`
- 容器中执行命令 `docker container exec [OPTIONS] CONTAINER COMMAND [ARG...]`

- 暂停（容器）进程 `docker container pause CONTAINER [CONTAINER...]`
- 恢复进程 `docker container unpause CONTAINER [CONTAINER...]`

- 查看容器的元数据 `docker container inspect [OPTIONS] CONTAINER [CONTAINER...]`
- 容器日志管理 `docker container logs [OPTIONS] CONTAINER `
	- ![image.png|350](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221122348.png)
- 查看容器中的进程信息 `docker container top CONTAINER`
- 查看（容器相对于镜像）文件修改：`docker container diff CONTAINER`

- 删除容器 `docker container rm [OPTIONS] CONTAINER [CONTAINER...]
	- 删除所有停止的容器 `docker container prune -f` 
### 镜像
- 镜像名称 `ubuntu:14:04` 前面啊前面为仓库名后面为镜像的版本号，默认为 `latest`

- 查看镜像列表 `docker image ls`
	- 查看特定镜像 `docker image ls name
	- 查看镜像的详细信息 `docker image inspect name`
- 拉取镜像 `docker image pull [OPTIONS] NAME[:TAG|@DIGEST]`
- 删除镜像 `docker image rm name`
- 搜索镜像 `docker search ubuntu`
- 构建镜像：对镜像进行修改可以先创建容器，在容器中进行修改，然后提交到新的镜像
	- `docker container commit [OPTIONS] CONTAINER [REPOSITORY[:TAG]]`
	- 将容器保存为了镜像
```shell
# 使用 run 创建运行一个新命令
docker container run \
    --name shiyanlou001 \
    -it busybox /bin/sh
# 在运行的容器中创建两个文件，test1 和 test2
touch test1 test2
# 使用 ctrl + p  及  ctrl + q 键退出
# 使用提交命令，提交容器 shiyanlou001 的修改到镜像 busybox:test 中
docker container commit shiyanlou001 busybox:test
# 查看通过提交创建的镜像
docker image ls busybox
```
- build 镜像：从 Dockerfile 构建镜像 `docker image build [OPTIONS] PATH | URL`
	- `docker image build -t shiyanlou:1.0 .`（基于当前目录下的 Dockerfile 进行创建）
### 存储管理
- 数据不都适合存储在容器中，当容器不再运行时，我们无法使用数据，并且容器被删除时，数据并不会被保存。
- 将数据从 Docker 主机挂载到容器中有三种方式：卷、挂载、临时文件系统
	- volumes 卷存储在 Docker 管理的主机文件系统的一部分中（/var/lib/docker/volumes/）中，完全由 Docker 管理。
	- bind mounts 绑定挂载，可以将主机上的文件或目录挂载到容器中。
	- tmpfs 仅存储在主机系统的内存中，而不会写入主机的文件系统

- 卷列表：卷是完全由 Docker 管理的
	- 显示本地可用的卷列表 `docker volume ls`
	- 创建卷 `docker volume create name`
	- 挂载卷：
		- 可以用卷来启动容器
		- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221133528.png)
		- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221133541.png)
```shell
docker container run \
    -it \
    --name shiyanlou001 \
    -v volume1:/volume1 \
    --rm ubuntu /bin/bash
# 另一种表示方式
docker container run \
    -it --name shiyanlou002 \
    --mount type=volume,src=volume1,target=/volume1 \
    --rm ubuntu /bin/bash
```

- 绑定挂载
	- 将主机上的目录绑定到容器中
```shell
docker container run \
    -it \
    -v /home/shiyanlou:/home/shiyanlou \
    --name shiyanlou003 \
    --rm ubuntu /bin/bash

docker container run \
    -it \
    --mount type=bind,src=/home/shiyanlou,target=/home/shiyanlou \
    --name shiyanlou004 \
    --rm ubuntu /bin/bash
```
- 问题：由于 vim 修改文件后是创建新文件而不是在原先绑定的文件上直接修改，因此会出现问题

- tmpfs 只存储在主机的内存中，容器停止时数据会被删除
```shell
docker run \
    -it \
    --mount type=tmpfs,target=/test \
    --name shiyanlou008 \
    --rm ubuntu bash
```

- 数据卷容器
	- 用于容器之间共享一些需要持续更新的数据，其它同期通过挂载这个容器实现数据共享，这个挂载数据卷的容器就叫做数据卷容器
```shell
# 创建一个名为 vdata 的数据卷
docker volume create vdata
# 创建一个挂载了 vdata 的容器，这个容器就是数据卷容器
docker container run \
    -it \
    -v vdata:/vdata \
    --name ShiyanlouVolume ubuntu /bin/bash

# 在 /vdata 目录下创建一个文本文件
echo "I am ShiyanlouVolume" > /vdata/f.txt
# 创建容器 test1
docker container run \
    -it \
    # 继承数据卷容器 ShiyanlouVolume 挂载的数据卷。
    --volumes-from ShiyanlouVolume \
    --name test1 ubuntu /bin/bash

# 查看 vdata 目录是否存在
ls -dl /vdata/

# 创建一个文件，并写入内容
echo "I am test1" > /vdata/test1.txt
```

- 数据备份
	- 通过创建容器备份数据卷
	- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221141051.png)

- 数据恢复
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221141124.png)

### 网络管理
- 查看网络状态 `docker network ls`
	- 三种默认网络为 bridge，host，none
	- 默认情况下使用 bridge ，创建的每一个新容器都会自动连接到 bridge 网络，即默认参数为 `--network bridge`，连接到默认的 bridge 之间的容器可以通过 IP 直接通讯
	- 查看网络详细信息 `docker network inspect bridge`

- 容器端口映射
	- 在容器外对内部进行访问就涉及到了端口的使用
	- 通过 `iptables` 实现端口映射（nat 表和 filter 表）
	- 查看 nat 表的转发规则 `sudo iptables -t nat -nvL`
	- `run` 容器时添加参数 `-p 10001:80` 表示将本机的 10001 端口映射到容器的 80 端口
		- ![image.png|450](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240221142906.png)
	- 范围映射 `-p 10001-10100:1-100`

- 自定义网络与容器互联
	- 对于默认的 bridge 网络来说，每次重启容器，容器的 **IP 地址都是会发生变化的**，因为对于默认的 bridge 网络来说，并不能在启动容器的时候指定 ip 地址
	- 创建桥接网络 `docker network create network1`
		- 指定详细参数 `docker network create -d bridge --subnet=192.168.16.0/24 --gateway=192.168.16.1 network1`
	- 删除网络 `docker network rm network1`
	- 将容器连接到特定网络 `docker network connect network1 shiyanlou001`
		- 连接到自定义网络时还可以手动指定固定 ip `docker run -it --network network1 --ip 192.168.16.100 --rm busybox /bin/sh`
	- 容器之间可以使用容器名来 ping （已经自动映射到dns）

- host 
	- 此时容器可以直接访问主机上的网络
	- `docker run -it --network host --rm busybox /bin/sh`

- none
	- 容器中不提供其它网络接口。none 网络的容器创建之后还可以自己 connect 一个网络，比如使用 docker network connect bridge 容器名可以将这个容器添加到 bridge 网络中。
	- `docker run -it --network none --rm busybox /bin/sh`
### DockerFile 编写
#### DockerFile 的语法结构
- Dockerfile 是一个文本文件，其中包含我们为了构建 Docker 镜像而手动执行的所有命令。Docker 可以从 Dockerfile 中读取指令来自动构建镜像。
- 通常创建一个新目录添加构建 Dockerfile 以及构建需要的文件
- 指定基础镜像 `FROM ubuntu:14.04`
- 指定执行指令的用户 `USER shiyanlou`
- 指定执行指令的工作目录 `WORKDIR /`
- 执行命令 `RUN <command>`，另一种格式 `RUN ["executable", "param1", "param2", ...]`
	- CMD 与 RUN 类似，但是只能有一个，会作为运行容器时提供默认的命令（但是可以被 run 中的具体指令覆盖）
	- ENTRYPOINT 是不能被覆盖的，此时 CMD 会作为 ENTRYPOINT 的参数
```shell
RUN apt-get update

CMD ["param1", "param2"]

FROM ubuntu:latest
ENTRYPOINT ["ls", "-a"]
CMD ["-l"]
```

- 文件操作
	- COPY 和 ADD 都用于将文件，目录等复制到镜像中。
	- \<src> 可以指定多个，但是其路径不能超出**上下文的路径**，即必须在跟 Dockerfile 同级或子目录中。
	- \<dest> 不需要预先存在，不存在路径时会自动创建，如果没有使用绝对路径，则 \<dest> 为相对于工作目录的相对路径。
	- COPY 和 ADD 的不同之处在于，ADD 可以添加**远程路径**的文件，并且 \<src> 为可识别的压缩格式，如 gzip 或 tar 归档文件等，ADD 会自动将其**解压缩**为目录。
```shell
ADD <src>... <dest>
ADD ["<SRC>",... "<dest>"]

COPY <src>... <dest>
COPY ["<src>",... "<dest>"]
```
- 指定挂载目录
```shell
VOLUME /data1 /data2
```
- 创建两个匿名卷，并挂载到容器中的 /data 1 和 /data 2 目录上。

- 设置环境变量
```shell
ENV <key> <value>
ENV <key>=<value> <key>=<value>...
```

- 对外暴露容器端口 `EXPOSE port`
	- EXPOSE 更像是一种约定或声明，真正使端口可访问的是 docker run 命令中的-p 或-P 参数。

- 示例
```shell
# 使用官方Python镜像作为基础镜像
FROM python:3.8-slim

# 设置工作目录为/app
WORKDIR /app

# 使用COPY命令复制当前目录下的requirements.txt文件到容器中的/app目录下
COPY requirements.txt /app/

# 安装requirements.txt中指定的所有依赖
RUN pip install --no-cache-dir -r requirements.txt

# 使用COPY命令复制当前目录下的所有文件到容器中的/app目录下
COPY . /app

# 使用ADD命令复制本地的example.tar.gz文件到容器中的/app目录下，并自动解压
ADD example.tar.gz /app/

# 使用ADD命令从远程URL复制文件到容器中的/app目录下
# 注意：这只是一个示例URL，实际使用时需要替换为有效的URL
ADD https://example.com/examplefile.txt /app/

# 指定容器启动时执行的命令
CMD ["python", "./your-script.py"]

```
#### 通过 DockerFile 创建镜像
- `docker build` 命令会自动在当前目录送偶所名为 Dockerfile 的文件（也可以手动-f name 指出文件名称）
- `docker build -t sshd:test` 构建镜像，镜像名为 `sshd`，标签为 `test`