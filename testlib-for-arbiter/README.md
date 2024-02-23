# Testlib for Arbiter

修改自 [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib)，可适配 Arbiter 2.0。

- 修改 `registerTestlibCmd`，直接对 `resultName` 赋值；
- `quit` 调用时将信息写入 `/tmp/_eval.score` 文件。

HeRaNO @ 2024.2.23

