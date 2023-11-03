# Send Email

发邮件的东西，首先把 `const.go` 里的配置改成生产环境的配置。实际上只需要改：

- `example.com` 替换成发信域名
- `smtp.example.com` 替换成发信服务器
- `password` 替换成发信密码

然后发信注册一个 `noreply` 的邮箱就行了。

邮件内容改 `email-account.tmpl`，`tag` 是设置好的，不需要动。所有人的信息放在 `data.csv` 里，一共四列，每列分别是学号，姓名，用户名和密码。

改一次 `const.go` 里的配置需要重新 build 一下。

HeRaNO @ 2023.11.3