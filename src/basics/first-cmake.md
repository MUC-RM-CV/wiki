# CMake 基本使用

## 构建工具

在 [上一节的例子](./multi-files-programming.md#使用头文件) 中, 生成可执行文件 `main` 的过程, 就叫做**构建** (build).

在这个过程中, 我们的 *目标* 是生成可执行程序 `main`.

简单来说, 生成这个目标需要 `main.cpp`, `foo.h` 以及 `foo.cpp` 三个文件.

> 更具体地说, 生成可执行程序 `main` *依赖* `main.o` 和 `foo.o` 两个目标文件, 而这两个目标文件, 又分别由对应的 `cpp` 文件生成.

其中, `main.cpp` 和 `foo.cpp` 又依赖于 `foo.h` 文件 (因为包含了前二者包含了后者 `foo.h`).

假如目标文件对应的 `cpp` 文件发生了更改 (或者其所包含的头文件发生了更改), 都需要重新生成相应的目标文件, 才能保证最终链接之后生成的可执行程序是最新的.

不同于曾经的单文件, 现在要构建一个目标涉及到了多个文件. 有些问题需要解决:

- 每次都需要输入多条命令才能完成编译链接;
- 希望减少编译的时间, 只希望编译发生了更改的部分, 因此需要判断哪些文件发生了更改, 从而只对有必要重新编译的文件进行编译;
- ...

如果项目更多, 项目之间有依赖关系等等, 则可能需要输入更多更复杂的命令, 也需要留意更多的文件. 如果全由用户来做, 很容易出现差错.

构建工具可以帮助我们自动化上述的流程. 我们告诉构建工具生成目标需要哪些依赖, 构建工具就可以在每次我们需要重新构建目标时, 检测需要重新生成的文件, 并完成构建流程. 

> 一些 IDE 会有自己的构建工具, 但对于初学者, 这个过程并不是那么明显. 往往, 用户将源代码添加进一个 "项目" 中, IDE 便将其视作生成该项目的依赖, 而不需用户显式指定. 

## 使用外部库

接下来将通过一个使用外部库的例子, 来介绍之后的内容. 该示例所使用的代码也可以在 [gitlab.com/tsagaanbar/cpp-multi-file-demo](https://gitlab.com/tsagaanbar/cpp-multi-file-demo/) 查看.

### 提取代码成库

假设我们现在有这样一个 C++ 文件 [single_file_demo.cpp](assets/2/single_file_demo.cpp), 发现其中的 `Date` 相关代码有复用的价值, 因此计划将其拆分出来, 单独成库.

```cpp
{{#include assets/2/single_file_demo.cpp}}
```

具体来说, 可以将代码中相关的 `is_leap` 和 `calc_days` 等函数, 变成 `Date` 类的成员方法. 结果如下:

[Date/Date.hpp](assets/2/Date/Date.hpp)

```cpp
{{#include assets/2/Date/Date.hpp}}
```

[Date/Date.cpp](assets/2/Date/Date.cpp)

```cpp
{{#include assets/2/Date/Date.cpp}}
```

### 调用外部库

那么该怎么调用这个外部库呢? 有多种情况, 一般来讲, 应当将该库的源代码与项目一同进行编译; 也有的时候, 库的开发者不提供源代码, 只有编译好的二进制文件和对应的头文件.

不管属于哪种情况, 都需要包含对应的头文件. 前者需要在链接时提供需要的目标文件, 后者则需要指定需要链接的库文件.

在编译这些使用了外部库的项目时, 由于需要包含外部的头文件, 而外部头文件的位置则是千差万别, 因此一般需要给编译器指定头文件搜索的路径. 

> 关于 `#include` 命令的搜索范围: 当使用双引号 `""` 包含头文件时, 编译器首先查找当前工作目录或源代码目录, 然后再在标准位置查找. 而使用尖括号 `<>` 时, 编译器将在系统的头文件目录中查找. 

比如, 下面的 [demo.cpp](assets/2/demo.cpp) 使用了 `Date` 库, 但是 `#include` 命令只是写出了 `Date.hpp` 的相对路径 (一般也建议这样做), 因此编译时需要指定头文件的搜索路径: 

```cpp
{{#include assets/2/demo.cpp}}
```

假设 `Date.hpp` 和 `Date.cpp` 都位于和 `demo.cpp` 同目录下的 `Date` 目录中:

```console
$ c++ demo.cpp -c -o demo.o -I ./Date   # 编译 demo.cpp
$ c++ Date/Date.cpp -c -o ./Date.o      # 编译 Date.cpp
$ c++ demo.o Date.o -o demo             # 链接生成可执行程序 demo
```

## CMake

经过上述的例子, 可见手动完成构建是很复杂的. 当然, 可以使用构建工具, 并编写 Make 等构建工具的脚本, 但是由于其适用性不广, 以下只介绍使用 CMake 的方法.

使用 CMake 这样一个构建管理工具, 只需编写一个 `CMakeLists.txt` 文件, 便可以生成用于不同构建工具的脚本. 

首先, 为 `Date` 库编写一个 CMake 脚本. 下面的例子定义了一个名为 `Date` 的生成 "库 (library)" 的目标.

[Date/CMakeLists.txt](assets/2/Date/CMakeLists.txt)

```cmake
{{#include assets/2/Date/CMakeLists.txt}}
```

之后, 如果要使用这个库, 便不再需要逐一指明目标 demo 需要的源文件: 因为之前已经定义了生成库目标的规则, 之后只需要包含对应的目录 (作为子项目引入), 即可直接使用这个目标:

[CMakeLists.txt](assets/2/CMakeLists.txt)

```cmake
{{#include assets/2/CMakeLists.txt}}
```

> 如果 `add_library` 时给出 `OBJECT` 参数, CMake 将不会生成库文件, 效果等同于逐一指明目标 `demo` 需要的源文件.
> 
> ```cmake
> add_library(Date OBJECT "Date.hpp" "Date.cpp")
> ```
