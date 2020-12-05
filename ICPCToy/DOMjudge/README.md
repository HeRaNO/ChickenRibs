# DOMjudge

与 DOMjudge 有关的乱七八糟的东西。

- `getDOMjudgeSubmissions.py`：从 DOMjudge 上获取比赛的所有提交。
- `generatePwd.py`：生成六位随机密码（`0-9a-z`）。

滚榜注意：

- **使用 2.1.2100** 版，在 Bash 下运行 `ICPC_FONT="Microsoft Yahei" ./resolver.bat awards.json`；
- 或者 `Microsoft JhengHei`，是个中文字体就行；

- 不要手贱多次 Finalize！！！
- 要等 TOO-LATE 测评完；
- Observer 隐藏再 Award 之后还要手动删掉这些队，但是可能会导致 Invalid Submissions；
- 114514 个技术细节没确定……

Judgehost 注意：

- 不宜开太多；
- Python 的测评容易导致 Judgehost 崩溃，莫名其妙；
- 如果大面积挂掉的话检查网络；
- 开 11 个左右就能挡住 5k 提交了……

Web Server 注意：

- 千兆网络，36 核 80G 平均 CPU 占用不超过 50%，内存也不超过 3G。

- Docker 是个好东西

