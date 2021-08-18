# Lutece Judge Core Prototype

给 Lutece-next 的容器环境，基于 [libcontainer](https://github.com/opencontainers/runc/tree/master/libcontainer) 开发。runc 是基于 libcontainer 的，docker 是基于 runc 的，所以它是 docker（错乱）。

首先你需要：
- 一个 rootfs，比如
  - [Alpine Linux](https://www.alpinelinux.org/downloads/)
  - [Ubuntu Base](https://cdimage.ubuntu.com/ubuntu-base/releases/)
  - [Arch Linux](https://mirror.rackspace.com/archlinux/iso/latest/)
- 在 rootfs 里建立一个普通用户，比如 test
- 在 rootfs 里建立一个文件夹作为测试用文件夹，比如 `/judge-test`

改一下代码里的 rootfs 路径，然后差不多就可以用了。

需要注意的是，Alpine Linux 用的是 musl libc 而一般大家都用 glibc，注意两个库的差别可能导致程序无法运行。

rootfs 里一般没有网络，是因为 DNS 解析错误。把主机的一份 `/etc/resolv.conf` 复制进来就行了。

推荐用 Ubuntu Base，比 Arch 小。不过测试的时候用的是 Alpine Linux。 

打算支持的题型：
- 传统题（Batch）：传统题就是传统题，给一个输入，拿到一个输出的那种。
- 交互题（Interaction）：测量程序调用函数的效率。强制建议所有在线问题都采用交互题测评方式。
- 通信题（Communication）：从实现上就是跑两遍交互题，主要测量双端通信中的「通信通量」和编解码效率，「通信通量」这个词是我自己造的，表达意思的类似信息熵，但是不好定义成信息熵那个样子，说实话我也不知道应该怎么说。
- 提交答案（Answer-submitting）：提交答案即可。

打算支持的 feature：
- 多线程
- 多平台支持（基于 rootfs）

在探索的：
- GPU 题：估计挂一个 devices 就行了，再看看

不打算支持的：
- libcontainer 不支持的各种系统

TODO List：
- 时间稳定性测试
- 安全测试

欢迎来 Hack。

HeRaNO @ 2021.8.18
