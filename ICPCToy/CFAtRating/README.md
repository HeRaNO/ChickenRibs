# CFAtRating

用于统计 Codeforces 和 AtCoder 的 Rating。规则是在一定时间之前有至少五场 Rating 记录，并且取第三高 Rating 作为依据。

先安装依赖：

```bash
pip install -r requirements.txt
```

输入如下命令使用：

```bash
python cfrating.py <userFile>
python atrating.py <userFile>
```

其中，`userFile` 中包含所有需要统计 Rating 的用户名，一行一个。

程序会输出运行时访问网页为止所有 Rating 中第三高 Rating 或输出用户不存在等其他信息。

请注意截止时间不要与 Rating 结算时间重合，以免造成统计上的不准确。这一点与规划截止日期也有关。

HeRaNO @ 2020.7.2