# 运维手册

> [!IMPORTANT]
> 大部分抄的是蔡队和 panda 老师的作业，很多命令可以在 [unicup/unicup-finals-2025](https://github.com/unicup/unicup-finals-2025) 找到。
> 
> 强烈建议学习使用 ansible。

## Web 服务器

### 删 DOMjudge 的访问前缀

参考 [87ouo/cn-xcpc-docs](https://github.com/87ouo/cn-xcpc-docs/blob/master/DOMjudge_8.3.1%2BDebian_12.8%2BNGINX_1.22.1%2BPHP_8.2.24%2BPHP8.2-FPM.md#62-%E4%BF%AE%E6%94%B9%E9%85%8D%E7%BD%AE%E6%96%87%E4%BB%B6) 中说明。

### 配置 chrony

安装之后修改 `/etc/chrony/chrony.conf`

```text
server ntp.tencent.com iburst
server ntp.aliyun.com iburst
server 127.0.0.1 iburst

driftfile /var/lib/chrony/drift

makestep 1.0 3

rtcsync

allow all

local stratum 10

logdir /var/log/chrony
```

然后 `systemctl restart chronyd`

## 测评机

如果使用了 `isolate-environment-checker`，脚本会在操作系统层面 ban 超线程，所以核心的 CPU ID 并不连续，需要 `lscpu` 看目前在线的 CPU ID。如果绑到了离线的 CPU，测评时 `create_cgroup` 会报错。

如果是在 BIOS 里 ban 的应该是可以忽略的。

## 选手机

### 配 hosts

运行的时候改一下 `[dj_ip]` 变成真实的 IP。

```bash
echo "[dj_ip]    domjudge" >> /etc/hosts
```

### 时间和 server 同步

运行的时候改一下 `[dj_ip]` 变成真实的 IP。

```bash
timedatectl set-timezone Asia/Shanghai
systemctl stop systemd-timesyncd
# 如果有就删，没有不需要删
# rm -f /etc/systemd/timesyncd.d/local.conf
cat > /etc/systemd/timesyncd.conf <<EOF
[Time]
NTP=[dj_ip]
EOF
timedatectl set-ntp true
systemctl daemon-reload
systemctl restart systemd-timesyncd
systemctl enable systemd-timesyncd
```

### 配 submit

```bash
cat > /etc/profile.d/contest.sh <<EOF
#!/bin/bash
export SUBMITBASEURL="http://domjudge/"
EOF
```

### 建用户

建到 `teams` 组里就不需要禁 U 盘了。

```bash
useradd --create-home --comment $(hostname) --shell /bin/bash --groups teams --password "$(openssl passwd -6 some_strong_password)" team

# 可以一起把正式赛账户建了
# useradd --create-home --comment $(hostname) --shell /bin/bash --groups teams --password "$(openssl passwd -6 another_strong_password)" team2

# 锁定原有账户
passwd -l icpc
# 或者说改强密码
# echo "icpc:really_strong_password" | chpasswd
```

### 屏幕解锁和锁定

#### 单个选手

```bash
bash -c 'echo -e "[daemon]\nAutomaticLoginEnable = true\nAutomaticLogin = team\n[security]\n\n[xdmcp]\n\n[chooser]\n\n[debug]" > /etc/gdm3/custom.conf && sleep 1 && systemctl restart gdm3'
```

`AutomaticLogin` 后面填用户名，根据前面建用户的情况对应。

`AutomaticLoginEnable` 设成 `false` 就是锁定，`AutomaticLogin` 后面可以什么都不填。

#### 所有选手

无线网发命令很慢，所以需要配置屏幕定时解锁。

```bash
cat > /etc/systemd/system/enable_team_autologin.timer <<EOF
[Unit]
Description=Enable team autologin
[Timer]
OnCalendar=*-*-* 8:58:00
Persistent=true
AccuracySec=1us
[Install]
WantedBy=timers.target
EOF

cat > /etc/systemd/system/enable_team_autologin.service <<EOF
[Unit]
Description=Enable team autologin
[Service]
Type=oneshot
ExecStart=bash -c 'echo -e "[daemon]\nAutomaticLoginEnable = true\nAutomaticLogin = team\n[security]\n\n[xdmcp]\n\n[chooser]\n\n[debug]" > /etc/gdm3/custom.conf && sleep 1 && systemctl restart gdm3'
EOF

systemctl daemon-reload
systemctl enable --now enable_team_autologin.timer
```

`OnCalendar` 后面时间换成开赛前几分钟，和内场负责人商定。

### 配屏幕监控重启

可能是蔡队镜像里没 enable，需要手动 enable，后续版本可能无需手动操作

```bash
systemctl enable vlc-restart-screen.path
```

如果不配的话，需要在选手机解锁之后统一 restart 一下 `vlc-screen` 服务

```bash
systemctl restart vlc-screen
```

### 网络隔离

运行的时候改一下 `[dj_ip]` 变成真实的 IP。如果已经在网络侧配了就不用配了。

```bash
ufw default allow incoming
ufw default deny outgoing
ufw allow out to [dj_ip]
ufw enable
```

### 选手机弹窗

```bash
export DISPLAY=:1
zenity --info --text "<span font='256'>done1</span>"
```

### 删历史命令

```bash
history -c && history -w
```

## XCPC Tools

client 接 server 打印的路径是 `/print/[secretRoute]`，把 `[secretRoute]` 换成 config 里的那个。

live-v3 里访问选手机推流的 URL 后面带的 token 是 config 里 `viewPass` 那项，也就是 XCPC Tools 的 admin 密码。

访问 `http://localhost:5283/monitor` 可以下载选手机监控的 json 数据。
