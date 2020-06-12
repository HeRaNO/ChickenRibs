# Database Principle And Its Application

软件学院数据库原理及应用课程第六次作业。用 Mybatis+Servlet+JSP 写一个数据库查询页面。

已知问题：PostgreSQL 中文操作反人类，可以存中文但是返回中文~~大概~~是 GBK 编码，转换也不对，不知道为啥……

UPD：[@QWsin](https://github.com/QWsin) 帮改了一下不支持中文的 Bug 但是好像还需要改别的地方。

`src/main/java` 下的 `GradeQueryServlet.java` 第 30 行添加以下语句：

```java
	response.setContentType("text/html;charset=UTF-8");
```

`src/main/webapp` 下的 `index.html` 文件头部添加：

```html
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
        "http://www.w3.org/TR/html4/loose.dtd">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
```

但是未经过测试，如有测好的修改方案欢迎 PR。

HeRaNO @ 2020.6.2

