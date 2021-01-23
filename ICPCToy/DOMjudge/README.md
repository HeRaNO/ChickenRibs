# DOMjudge

与 DOMjudge 有关的乱七八糟的东西。

- `getDOMjudgeSubmissions.py`：从 DOMjudge 上获取比赛的所有提交。
- `generatePwd.py`：生成六位随机密码（`0-9a-z`）。

滚榜注意：

- **使用 2.2.415** 版，在 Bash 下运行 `ICPC_FONT="Microsoft Yahei" ./resolver.bat awards.json`；
- ~~或者 `Microsoft JhengHei`，是个中文字体就行~~ 貌似新版对中文字体的支持变好了，不用加环境变量了；
- 为啥我在 2.1.2100 测的时候也不用加环境变量（系统 `ICPC_FONT` 的环境变量已经删了）……
- 结束之后把打星队设置为隐藏就行了，不用去删什么；
- 要把下载下来的 `event-feed` 加上 `.json` 后缀名（加上之后感觉怎么都能跑）！！！
- 下榜地址 `http://domjudge/api/contests/{id}/event-feed?stream=false`；
- 要等 TOO-LATE 测评完（感觉其实不太重要）；
- 总感觉滚榜的时候统计过题数是挂了的（旧版没有显示过题数的功能）……

Judgehost 注意：

- 不宜开太多；
- Python 的测评容易导致 Judgehost 崩溃，莫名其妙；
- 如果大面积挂掉的话检查网络；
- 开 11 个左右就能挡住 5k 提交了（虽然是在手动管理测评机池的情况下）……

Web Server 注意：

- 千兆网络，36 核 80G 平均 CPU 占用不超过 50%，内存也不超过 3G。
- Docker 是个好东西；
- 设置 MariaDB 密码不能有特殊字符（最好是大小写字母加数字，否则会搭建失败）。

