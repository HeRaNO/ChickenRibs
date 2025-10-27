# Judger

用来做测评机的系统镜像。

## 自动安装配置

可以写 `autoinstall.yaml` 来进行系统自动化安装，参考 [Manual](https://canonical-subiquity.readthedocs-hosted.com/en/latest/reference/autoinstall-reference.html)。用的时候把 `passwd` 和公钥换成自己的。

文件夹中的 `autoinstall` 做的修改：

- 切腾讯云的镜像源
- CGroup 切到 v1
- 安装 docker 并导入自己做的 judgehost 镜像
- 用 [`isolate-check-environment`](https://github.com/ioi/isolate/blob/master/isolate-check-environment) 检查并修改环境，添加开机启动
  - 文件夹中的脚本删除了对 CGroup 和 Swap 的检查

如果不需要对镜像添加大文件（加脚本可以用 `write_files` 进行），并且可以接受安装时输入 `yes`，则可以跳过修改镜像部分（或者使用 [这个回答](https://serverfault.com/a/1157287) 的方法避免），直接用配置加下载的 Server 镜像安装，具体可以看 [文档](https://canonical-subiquity.readthedocs-hosted.com/en/latest/howto/autoinstall-quickstart.html)。

## 修改镜像

### 准备工作

首先安装必要的包。

```bash
sudo apt update
sudo apt install genisoimage squashfs-tools cd-boot-images-amd64
```

建一个工作文件夹，下载 Ubuntu 24.04 Server 的镜像，然后挂载一下。

```bash
mkdir ~/custom_live_cd
mv ubuntu-24.04.3-live-server-amd64.iso ~/custom_live_cd
cd ~/custom_live_cd

sudo mkdir isomount
sudo mount -o loop ubuntu-24.04.3-live-server-amd64.iso isomount
```

挂载之后把镜像里的内容备份挪动。

```bash
sudo mkdir extracted
sudo rsync -a isomount/ extracted
```

### 自定义 SquashFS

如果不需要自定义 SquashFS 请忽略这步。

首先解包 SquashFS。

```bash
sudo unsquashfs isomount/casper/ubuntu-server-minimal.squashfs
sudo mv squashfs-root edit
```

然后 `edit` 文件夹里就是 SquashFS 的内容了。可以往里放一些文件，这样安装好之后测评机就自带了这些文件了。例如将测评机镜像和环境检查脚本放进去。

```bash
sudo cp ~/jh.tar.gz edit/opt
sudo cp ~/isolate-check-environment edit/opt
sudo cp ~/env-checker.service edit/etc/systemd/system
```

不推荐在 SquashFS 直接安装 package，可以利用 cloud-init 在首次启动后安装。

然后打包 SquashFS。

```bash
sudo rm extracted/casper/ubuntu-server-minimal.squashfs
sudo mksquashfs edit extracted/casper/ubuntu-server-minimal.squashfs -comp xz
```

### 打包 ISO

首先把 `autoinstall.yaml` 加进去。

```bash
sudo install -Dm644 ~/autoinstall.yaml extracted
```

然后给 grub 的命令行加上 `autoinstall` 参数，这样就不用安装的时候输入了。

首先加一个写权限。

```bash
sudo chmod +w extracted/boot/grub/grub.cfg
sudo chmod +w extracted/boot/grub/loopback.cfg
```

然后修改各自文件 `Try or Install Ubuntu Server` 这个 `menuentry`，给 `/casper/vmlinuz` 后面加一个 `autoinstall`。修改后 `grub.cfg` 的这个 entry 变成

```text
menuentry "Try or Install Ubuntu Server" {
        set gfxpayload=keep
        linux   /casper/vmlinuz autoinstall  ---
        initrd  /casper/initrd
}
```

`lookback.cfg` 的这个 entry 变成

```text
menuentry "Try or Install Ubuntu Server" {
        set gfxpayload=keep
        linux   /casper/vmlinuz autoinstall  iso-scan/filename=${iso_path} ---
        initrd  /casper/initrd
}
```

最后把写权限取消。

```bash
sudo chmod -w extracted/boot/grub/grub.cfg
sudo chmod -w extracted/boot/grub/loopback.cfg
```

接下来的操作均需要 root 权限。直接进 root 里。

```bash
sudo su
```

在 `custom_live_cd` 下执行，重新生成 MD5

```bash
cd extracted && find . -type f -not -path './boot/grub/fonts/*' -not -path './EFI/*' -not -path './boot/grub/i386-pc/*' -not -path './boot/grub/x86_64-efi/*' -not -name 'md5sum.txt' -not -name 'autoinstall.yaml' -print0 | \
sort -z | xargs -0 -- md5sum | \
tee md5sum.txt
```

这时候会切到 `extracted` 下面，在这里打包 ISO

```bash
xorriso -as mkisofs \
    -V "ICPC Judgehost Image" \
    -iso-level 3 \
    -o "../judge.iso" \
    -J -joliet-long \
    -l -b boot/grub/i386-pc/eltorito.img \
    -no-emul-boot -boot-load-size 4 \
    -boot-info-table \
    --grub2-boot-info \
    --grub2-mbr /usr/share/cd-boot-images-amd64/images/boot/grub/i386-pc/boot_hybrid.img \
    -append_partition 2 0xef /usr/share/cd-boot-images-amd64/images/boot/grub/efi.img \
    -appended_part_as_gpt \
    --mbr-force-bootable \
    -eltorito-alt-boot \
    -e --interval:appended_partition_2:all:: \
    -no-emul-boot \
    -partition_offset 16 -r .
```

打包的 ISO 位于 `custom_live_cd` 下。