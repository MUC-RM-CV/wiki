# RM-CV Wiki

欢迎来到 RM-CV Wiki。

该仓库计划存放和 Robomaster 机甲大师对抗赛视觉/算法部分有关的内容。

## 使用说明

该内容使用 [mdBook][mdbook] 构建 HTML 页面。

### 在线浏览

本项目目前使用 GitHub Pages 进行托管，可以访问 [RM-CV Wiki - GitHub Pages](https://muc-rm-cv.github.io/wiki/) 进行浏览。

### 自行构建

用户可以自行在本机上进行页面的构建和浏览。

首先将本项目 下载 / 克隆 至本地，之后：

- 下载 [mdBook][mdbook] 二进制文件，将其所在路径添加进 `PATH` 环境变量；
- 切换到项目根目录，执行 `mdbook serve` 命令；
- 在浏览器中访问 [localhost:3000](http://localhost:3000) 即可阅览页面。

`mdbook serve` 默认侦听 `localhost:3000`。如需允许网络下其他设备访问，则需允许 mdbook 通过防火墙，并将 mdbook 的侦听地址设置为 `0.0.0.0`，端口可自定义。参考命令如下：

```console
$ mdbook serve -n 0.0.0.0 -p 3000
```

之后其他设备可以通过在浏览器中访问 `http://[设备IP地址]:[端口号]` 浏览页面。

亦可执行 `mdbook build` 命令，而后手动打开 `book` 目录下的 `index.html` 文件，开始阅览。

[mdbook]: https://github.com/rust-lang/mdBook

## 版权声明

除特别注明外，项目中除代码外的部分均在 [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.zh) 协议之条款下提供。
