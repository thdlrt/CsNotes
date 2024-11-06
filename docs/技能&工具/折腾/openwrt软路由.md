### transmission
#### 如何多次盘下载
- 可能出现无法访问磁盘、虚假的空间不足
- 这是由于 openwrt 沙盒机制造成无法访问磁盘

1.在istore中安装transmission，挂载磁盘啥的就不多说了
2.先去transmission配置页面配置好启用和下载路径。不想麻烦折腾挂载就把用户和组改成root。然后保存并应用
![read-normal-img](https://i0.hdslb.com/bfs/new_dyn/015d3113931a64cb50bde4e9f20c23e93630385.png@.webp)

3.ssh连上openWRT，然后
`vi /etc/init.d/transmission`
4.找到`procd_add_jail_mount_rw "$download_dir"`配置，
5.按`o`在下一行插入（搞乱了的话，`ESC`键，然后输入`:q!`不保存退出重新弄）
按需求添加挂载路径
`procd_add_jail_mount_rw "/mnt/xxx/b/*"`
`6.ESC`键，然后输入`:wq`保存退出
7.重启服务
`/etc/init.d/transmission restart`