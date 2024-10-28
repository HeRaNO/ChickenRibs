# ICPC Chengdu

The 2024 ICPC Asia Chengdu Regional Contest 运维脚本。

- `gen_banner.py`：做直播用的 [`achivement.svg`](https://github.com/icpc/live-v3/blob/main/config/_media/easy-achivements-icpc.svg)，注意队伍名超长的时候手动调整字号
- `make_json.py`：做队伍和账号导入的 json，密码用的是拼音密码，`seats.json` 是 xcpc-tools 导出的队伍编号到 IP 的 map
- `domjudge-chroot-build/`：[@cubercsl](https://github.com/cubercsl) 提供的做 domjudge chroot 的脚本，可以和 ICPC WF 环境对齐，注意要梯子，或者直接开香港的云服务器做也行。相对于原本脚本做的修改：
  - 没有 Kotlin
  - 删了 `--reflink` 因为不是 btrfs

HeRaNO @ 2024.10.28