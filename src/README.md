# 前言

欢迎来到 RM-CV Wiki。

该网页使用 [mdBook](https://github.com/rust-lang/mdBook) 构建。

## 导航

<!-- 可以使用如下的方式在页面中引用其他的页面 -->
<!-- 对 *.md 文件的引用链接，会转换为对同名 *.html 的引用 -->
<!-- 即目录下的 *.md 文件，都会被会转换为 *.html，但是 README.md 会被转换为 index.html -->
<!-- 因此对某目录下 README 的引用，需要写作 <目录名>/index.html 或者简写作 <目录名>/ -->
<!-- 注意 “<目录名>/” 最后的 / 不能省却，不然对应页面下相对资源的访问就会出错 -->
<!-- 可以使用 #TAG 来引用页面下的子标题。具体的转写应参见 mdBook 生成的 HTML 中标题的链接 -->

<!-- 以上都是针对生成 HTML 而言。但是对于普通文件系统来说，<path>/ 这样的链接是不能访问到对应文件的 -->
<!-- 可以使用 <path>/README.md，这样转换之后变为 <path>/index.html，不影响两种情况下的访问 -->
<!-- 但由于目前 mdBook 不会转换 *.md#TAG 这样的链接为 *.html#TAG，所以标题跳转将无法使用（会提示 404，因为输出的 HTML 里没有 md 文件） -->
<!-- 综上所述，由于 mdBook 最终目的是生成 HTML 以供阅读，因此可以不考虑在普通文件系统上使用的情况？ -->

- [基础知识](./basics/)
    - [C++ 多文件编程](./basics/multi-files-programming.md)

- [开发环境配置和使用](./tools/)
    - [Visual Studio Code 中 CMake 插件的基本使用](./tools/vscode-cmake-extension.md)
    - [Windows 下使用 vcpkg + CMake 进行开发](./tools/dev-with-vcpkg-cmake-win.md)

- [编程技巧](./coding-tips/)
    - [C++ 浮点数转为字符串](./coding-tips/float-to-string.md)

- [TX2 使用笔记](./TX2/)
    - [初识 TX2](./TX2/new-to-tx2.md)
    - [在 TX2 上使用代理](./TX2/using-proxy.md)


## 友情链接

- [程序员入门指南](https://tsagaanbar.github.io/Newly-Programmer-ABC/)

## 版权声明

除特别注明外，项目中除代码外的部分均在 [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.zh) 协议之条款下提供。
