# OJ.Harmonics
## Introduction  介绍

This is a tool for importing or exporting problems on an Online Judge.

这是一个导入导出在线测评系统上题目的工具。

Before using `HUSTOJ2Standard.py` ,you should make sure that you have installed `python` and `pip` .

在使用 `HUSTOJ2Standard.py` 之前，请先确认您已经安装了 `python` 和 `pip`。

Then clone the project.

然后克隆这个项目到本地。

In the root of the repository, input commands as follows:

```shell
python -m pip install -r requirements.txt
```

在项目的根目录下输入以上命令。

Finally, input commands as follows:

```shell
python <name>.py
```

最后，项目的根目录输入以上命令。

Do as the notice.

按提示做。

## How it works  这个程序如何运行

You can put it at `/home/<your_username>/` . Then run the program, input your password to the database and input the start and the end problem. After a while, all will be OK!

您可以将程序放在 `/home/<你的用户名>` 下。然后运行程序，输入数据库密码，然后输入开始和结束的题号。等一会就好了。

The program will create `Standard/` at the place where the program is placed. In this folder, you can find many folders named by number and some text.

程序会在程序放置的目录下建立 `Standard/` 文件夹。在这个文件夹中，会有很多以数字命名的文件夹和一些文本文档。

These folders are 'Standard problem files', the structure is as follows:

这些文件夹就是「标准题目文件夹」 ，它的结构如下：

1. Folder `/data` ,It contains all the test data and the program or the source code of the Special Judge;

`/data` 文件夹，包含所有数据和 Special Judge 程序或源代码；

2. Folder `/pic_and_other` ,It contains pictures and attachment in the problem;

`/pic_and_other` 文件夹，包含题面内的图片，附件等内容；

3. `title.txt` ,contains the title of the problem;

`title.txt`，包含题目标题；

4. `description.txt` ,contains the description of the problem;

`description.txt`，包含题目描述；

5. `input.txt/output.txt` ,contains the format of input and output;

`input.txt/output.txt`，包含题目的输入输出格式；

6. `sample_input.txt/sample_output.txt` ,contains the sample of the problem;

sample_input.txt/sample_output.txt，包含题目的样例输入输出；

7. `spj.txt` ,contains whether the problem have Special Judge, `0` means there's no Special Judge, `1` means there is a Special Judge.

`spj.txt `，包含是否含有 Special Judge，`0` 表示没有，`1` 表示有；

8. `hint_and_source.txt` ,contains the hint to the problem and the source of the problem;

`hint_and_source.txt`，包含对题目的提示和来源；

9. `limitation.txt` ,contains the limitation of time and memory. The first line is the time limitation in second, the second line is the memory limitation in MB.

`limitation.txt`，包含题目的时间和空间限制。第一行为时间限制，以秒为单位，第二行为空间限制，以兆为单位。

In the folder `/Standard` ,there're three extra text, `problemcnt.txt` , `have_spj.txt` and `have_source.txt`.

在 `/Standard` 文件夹下，还有三个文件： `problemcnt.txt` , `have_spj.txt` 和 `have_source.txt`。

`problemcnt.txt`  contains the number of the problems.

`problemcnt.txt` 包含题目数量。

`have_spj.txt` contains the problem id which the problem has Special Judge.

`have_spj.txt` 包含有 Special Judge 的题目编号。

`have_source.txt` contains the problem id which the problem has picture, attachment etc.

`have_source.txt` 包含有图片或附件等的题目编号。

## Blablabla~

This project is my first project(except Yiyuyan and VB). All issue,pr and complaint are welcomed.

这是我的第一个项目（除了易语言和 VB 之外）。欢迎提 issue 和 pr，同时欢迎吐槽。

All the notice message will be written in English and Chinese.

所有提示信息都用汉语与英语书写。

Enjoy using!

用得愉快！

HeRaNO @ 2018.7.18
