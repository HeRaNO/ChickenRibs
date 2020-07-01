# CFAtRating

用于统计 Codeforces 和 AtCoder 的 Rating。

规则是在一定时间之前有至少五场 Rating 记录，并且取第三高 Rating 作为依据。

先安装依赖：

```bash
pip install -r requirements.txt
```

`cfrating.py` 使用前需要修改其中第 10, 11, 12 行的参数。

- `key`：Codeforces 的 API key；
- `secret`：Codeforces 的 API secret，上述两者需要事先在 `https://codeforces.com/settings/api` 申请；
- `stdTime`：统计的截止时间，格式同 UNIX 时间戳（以秒为单位，建议先获取截止场次的 `ratingUpdateTimeSeconds` 后填写）。

`atrating.py` 还没写，因为没 API 写起来挺麻烦的……

HeRaNO @ 2020.7.2