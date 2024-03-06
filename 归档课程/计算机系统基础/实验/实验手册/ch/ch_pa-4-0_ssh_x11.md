# PA 4-0 SSH和X11转发配置说明

**进入PA 4阶段后，由于需要转发图形界面，必须使用本节所述方法连接教学服务器。若使用网页终端，会导致程序执行时出现段错误。**

目前我们只能通过Windows客户端的测试，如果是Linux客户端，还需要摸索一下。Windows客户端连接实验服务器的具体步骤如下：

使用`MobaXterm`登录服务器，需有线连接校园网接口或无线连接`NJU_WLAN`，建议使用`NJU_WLAN`，并拨号`p.nju.edu.cn`登录，接入学校局域网。**注意，客户端机器必须直连校园网，如果通过自己搭建的路由器局域网连接服务器无法进行X11转发。连接校园网后需要重启`MobaXterm`!**

## 下载安装MobaXterm

官方网址：https://https://mobaxterm.mobatek.net/download.html
![download](http://114.212.10.201/images/MobaXterm/download.png)
下载完成后解压缩并打开界面。

## 通过MobaXterm登录教学平台

进入MobaXterm点击左上角的Session按钮创建新的session；
![create_session](http://114.212.10.201/images/MobaXterm/create_session.png)

选择ssh
![choose_ssh](http://114.212.10.201/images/MobaXterm/choose_ssh.png)

根据各自学号和分配得到的IP地址和端口进行登录,并确保X11转发打开：
例如学生：pa031221097；IP地址：114.212.10.201；端口号：5200；
![sign_in](http://114.212.10.201/images/MobaXterm/sign_in.png)
设置完成后，点击` OK `进入；

输入各自仓库密码。
![passwd](http://114.212.10.201/images/MobaXterm/passwd.png)

## X11转发配置

1. 确保` Xserver`处于开启状态（彩色）
2. 在命令行输入：
> export DISPLAY=xxx.xxx.xxx.xxx:x.x

![export_DISPLAY](http://114.212.10.201/images/MobaXterm/export_DISPLAY.png)

## 测试X11转发是否成功

在命令行输入：
> xclock

![xclock](http://114.212.10.201/images/MobaXterm/xclock.png)

如果出现小时钟，则X11转发成功，该时钟为服务器时间；

如果没有出现小时钟，可能是被windows防火墙拦截，请关闭防火墙再尝试.若还是无法转发成功，请联系[助教](../blame.md)协助解决。
