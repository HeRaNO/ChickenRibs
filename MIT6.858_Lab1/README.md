# MIT 6.858 Lab1: Buffer overflows

同时也是网络与信息安全课程的实验一。用的是 2014 年版的。

`exploit-3.py` 十分坑，首先要绕 `read_line` 里读 `\n` 就退出，网上很多实现都是用 `execve` 的，这里的是用自增绕的。而且字符串要以 `\0` 结尾，需要在 shellcode 里自己造出一个末尾的 `\0`。和我差不多的 [exploit-3.py](https://github.com/lxs137/MIT6.858/blob/master/lab1/zook-server/exploit-3.py) 和 [shellcode.S](https://github.com/lxs137/MIT6.858/blob/master/lab1/zook-server/shellcode.S) 完全不懂是怎么过的，明明两个坑全踩了，真不信能过。

硬生生调了一天，泪目。

HeRaNO @ 2022.11.16
