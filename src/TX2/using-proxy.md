# 在 TX2 上使用代理

在 TX2 上使用代理和在其他 Linux 系统上是类似的。

也许读者在其他平台有过使用代理的经历，那样也请暂时放下已有的经验，参考一下本教程的方法。

本教程将会介绍 [Clash][clash] 这样一款基于规则的代理软件。其支持多种协议，如 VMess、Shadowsocks、Trojan 协议。

## 订阅和订阅链接

一般的，在用户购买服务后，网络代理服务商需要将代理服务器的连接信息提供给用户，一般为某种代理软件所支持的配置文件格式，且通常会提供适用于多种软件的配置文件。

此外，这些信息一般是以“订阅”的形式提供的。我们通过“订阅链接”，可以随时获取到最新的代理服务器信息。比如，我们可以通过“Clash 订阅链接”获得到适用于 Clash 的配置文件。

需要注意，一定要**保护好自己的订阅链接**，不得在公共网络上明文传输。

## TX2 本机上运行代理软件

读者可能已经使用过类似 [Clash for Windows](https://github.com/Fndroid/clash_for_windows_pkg) 这样的图形化软件。[Clash][clash] 本身是一款 CLI 程序（命令行界面程序），但是有很多应用程序为其设计了图形化界面前端。

> 至于为什么使用 Clash 命令行程序，是因为很多图形前端没有适用于 ARM64 架构（也就是 TX2 处理器的架构）的版本。

接下来，将介绍 [Clash][clash] 的使用。

### 下载程序

首先我们需要下载适用于本机的 Clash 发行版。我们在 [Clash 的发布页][clash-release] 找到对应机器平台的构建，比如 TX2 上运行的是 Linux for Tegra(L4T)，其处理器架构为 ARM，因此我们下载文件名种有 `linux-armv8` 字样的压缩包。

笔者书写文章时，最新版本为 1.8.0，因此我们下载名为 `clash-linux-armv8-v1.8.0.gz` 的文件（压缩包）。

之后，解压软件的压缩包，得到可执行程序文件。由于我们下载的为适用于 Linux 系统 + ARMv8 架构的二进制程序，因此可执行程序的名字为 `clash-linux-armv8`。

> 注意：由于大部分情况下，下载过程本身需要相应的网络条件，建议先在具备网络条件的环境下载好软件后，将软件复制到 TX2 上，可以使用 U 盘也可以使用 `scp`（如果 USB 接口比较紧缺）。

新建一个名为 `clash` 的目录，将解压得到的文件放入 `clash` 目录下。

这里假设 `clash` 目录位于用户目录下，则最终可执行文件将位于 `~/clash/` 中。

接着，进入 `clash` 目录，并为可执行程序添加执行权限。

```console
$ cd ~/clash/
$ chmod +x clash-linux-armv8
```

为了方便使用，可以对可执行文件的名字进行更改。这里我们将其名称修改为 `clash`。

```console
$ mv clash-linux-armv8 clash
```

### 获取配置文件

接下来，我们需要将从订阅链接获得到的 Clash 配置文件，放入同目录下。

一种方法是直接在浏览器中访问订阅链接，在打开的页面的上下文菜单选择“另存为”，将得到的内容保存为 `config.yaml` 并存储在 `clash` 目录下。

> 如果是使用 SSH 远程连接的情况，直接在主机上全选网页内容，复制到粘贴板；之后在对应位置新建 `config.yaml` 文件，再使用 `vi` 或 `vim` 等编辑器将内容粘贴到文件中。

另一种方法是使用 `wget` 命令获取订阅链接的内容。建议将订阅链接包含于一对引号 `''` 中，以便 shell 程序将其视作一个整体。

```console
$ cd ~/.config/clash/
$ wget -O config.yaml '订阅链接'
```

<figure>

![在终端中使用 wget 命令获取订阅链接的内容](https://mxwljsq.com/theme/malio/img/tutorial/linux-clash-2.jpg)
<figcaption>在终端中使用 wget 命令获取订阅链接的内容</figcaption>
</figure>

> 此外，也可以将配置文件置于用户目录下的配置文件夹中，即 `~/.config/clash/` 目录下。如果目录不存在，需要先创建对应目录。

### 运行 clash 程序

之后，在终端中执行 Clash 可执行程序即可：

```console
$ cd ~/clash/
$ ./clash -d .
```

也可以在后台执行 Clash 程序（详见 [bash 作业控制](https://tsagaanbar.github.io/Newly-Programmer-ABC/begin-programming/cli/common-commands.html#任务控制)）：

```console
$ cd ~/clash/
$ ./clash -d . &
```

> 如果在上一步中将配置文件置于 `~/.config/clash/` 下，则可以直接启动 Clash 程序而无需额外的参数：
> ```console
> $ ~/clash/clash
> ```

启动程序后，可以访问 [Clash Dashboard](http://clash.razord.top/) 进行切换节点、测延迟等操作。

### 使用代理

程序启动后，默认侦听本机的 7890 端口，也就是 `127.0.0.1:7890`。我们将程序的网络请求转发到这个位置，就能实现代理了。

比如，我们新建一个终端，在该次会话中增加 `http_proxy` 和 `https_proxy` 两个环境变量：

```console
$ export http_proxy='http://127.0.0.1:7890'
$ export https_proxy='http://127.0.0.1:7890'
```

之后，再在这个终端中启动程序（比如 `git clone` 或者 `firefox`），一般就会使用到相应的代理配置了。

```console
$ git clone 仓库链接
```

此外，也可以将其**设置为系统代理**。以 Ubuntu 系统为例，打开系统设置，选择网络，点击网络代理右边的 <kbd>⚙</kbd> 按钮，选择手动，填写 HTTP 和 HTTPS 代理为 `127.0.0.1:7890`，填写 Socks 主机为 `127.0.0.1:7891`，即可启用系统代理。

<figure>

![在 Ubuntu 的图形化设置界面中配置代理](https://mxwljsq.com/theme/malio/img/tutorial/linux-clash-5.jpg)
<figcaption>在 Ubuntu 的图形化设置界面中配置代理</figcaption>
</figure>

当不再使用代理时，可以在 clash 运行的终端里按下 <kbd>Control</kbd> + <kbd>C</kbd> 以退出程序。程序结束后，需要记得取消系统代理，不然会出现无法正常访问网络的情况。

[clash]: https://github.com/Dreamacro/clash
[clash-release]: https://github.com/Dreamacro/clash/releases

## 规则代理

（未完待续）

## 使用局域网内其他机器上的代理

（未完待续）

## 参考链接

- <https://mxwljsq.com/user/tutorial?os=linux&client=clash>
