# C++ 多文件编程

在上一节 ["项目与构建"](./projects-and-builds.md) 中说到, 现实中的项目通常较为复杂, 由若干模块组成. 本篇文章将简单介绍一下 C++ 中的多文件编程.

## 多文件编程的好处

将代码分区放在不同的文件中，可以方便对于代码的查找、管理和协同工作.

此外，将代码分别放在不同的区块 (也叫做 "翻译单元 (translation unit)") 中, 可以实现在修改一些文件时, 不至于重新编译整个工程.

## C++ 编译链接简介

先从最熟悉的单文件的情况说起. 下面是一个简单的 C++ 源文件，里面有一个 `foo` 函数和有一个 `main` 函数. 

> 一个 C++ 程序需要有 `main` 函数才能运行。

```cpp
// demo.cpp

int foo(int, int);  // foo 函数的声明

int main() {
    // main 函数是一个程序的起点
    int result = foo(3, 5);
    return 0;
}

int foo(int a, int b) {  // foo 函数的定义
    return 2 * a + b;
}
```

可以看到, 上述的代码中，`main` 函数调用了 `foo` 函数. 但这不是件理所当然的事.

事实上, 在 **编译** (compile) 过程中, 当编译器遇到 `foo(3, 5)` 这样的语句时, 会去查看是否存在这样的函数可供使用.

这个例子中, `foo` 函数的原型已在调用处之前声明, 因此编译器能够理解 `foo(3, 5)` 这样的语句.

```cpp
int foo(int, int);  // foo 函数的声明
```



具体来说, 对于该语句, 编译器会去查找，是否有一个名为 `foo` 的函数 **声明** (declaration). 满足参数为两个 `int` 型整数的情况 (或者参数列表中参数类型支持从 `int` 类型转换而得); 如果没有, 编译器就会报错, 提示这个符号 "还没有在作用中被声明 (was not declared in scope)", 或者说这是一个 "未声明标识符 (undeclared identifier)".

但是现在还不能生成最终的可执行程序, 因为我们还不清楚 `foo` 函数的具体定义. 为此, 编译器会将这个符号加入到 *未解决符号表* 中。

在这个例子中, 编译器接着往下分析文件中的内容, 就会发现 `foo` 函数的定义, 并将其出现的位置记录下来, 供之后 **链接** (Linking) 阶段的使用.

如此, 编译器就从源代码文件生成了目标文件. 在链接过程中, 编译器根据未解决符号表, 在每个编译得到的目标文件中查找对应的符号, 查找到之后, 就记录下相应的位置, 也就是将不同位置的代码 "链接" 起来.

在上面的例子中, `foo(3, 5)` 这个语句将会找到在 `main` 函数之后定义的 `foo` 函数, 因此被解决. 否则, 将会出现 "未解决的外部符号 (unresolved external symbol)" 或者 "未定义引用 (undefined reference)" 的错误.

> 也可以将函数和声明和函数定义写在一起, 比如下面这样:
> 
> ```cpp
> // demo.cpp
> 
> int foo(int, int) { return 2 * a + b; }
> 
> int main() {
>     int result = foo(3, 5);
>     return 0;
> }
> ```

我们将每一个 C/C++ 源文件称作一个翻译单元 (translation unit)。那么在上述的例子中，我们的翻译单元会提供一个 `int foo(int, int)` 和一个 `int main()` 的符号，并且有一个 `int foo(int, int)` 的符号待解决。经过了链接过程，未解决符号得到了解决，于是就可以生成可执行程序了。

## 将文件拆开

假如 `foo` 函数是一个经常会被用到的函数, 那么在单文件的情况时, 往往每编写一个新的程序, 都需要将其复制到新的源代码文件中.

这样做会产生很多重复的内容, 不利于对代码的维护, 并且有可能增加额外的编译时间.

通过之前的内容, 不难想到, 可以将 `foo` 函数单独存放在一个文件中. 如此, 只要提供声明, 其他的代码可以成功调用该函数, 只要确保 `foo` 函数编译后所在的目标文件也参与链接过程即可.

> 接下来的例子中涉及到通过命令行操作编译器。读者只需要明白操作的目的即可，实际使用中不必要手动输入这些命令。

下面的 `foo.cpp` 是一个包含 `foo` 函数的源代码文件:

```cpp
// foo.cpp

int foo(int a, int b) {
    return 2 * a + b;
}
```

让编译器编译 `foo.cpp` 生成目标文件 `foo.o`:

```console
$ c++ foo.cpp -c -o foo.o
```

不出意外的话, 当前目录下会多出一个名为 `foo.o` 的目标文件. 目标文件的内容一般不易为人类所阅读, 不过只要明白这个目标文件提供了 `int foo(int, int)` 这样一个符号即可.

而 `main.cpp` 将会写作下面的样子, 其中需要包含对 `foo` 函数的声明, 即可使用对应的函数, 并通过编译.

```cpp
// main.cpp

int foo(int, int);  // 只需要 foo 函数的声明

int main() {
    int result = foo(3, 5);
    return 0;
}
```

同样, 将 `main.cpp` 编译为目标文件:

```console
$ c++ main.cpp -c -o main.o
```

类似的, 这个目标文件提供了 `int main()` 这样一个符号，但有一个 `int foo(int, int)` 的符号待解决.

最后, 为了生成最后的可执行程序 `main`, 我们需要将这些目标文件链接起来:

```console
$ c++ main.o foo.o -o main
```

如果一切顺利, 将不会出现未解决符号, 可执行文件生成成功.

## 预处理指令

在编译之前, 编译器会先对代码文件进行预处理.

有很多预处理指令, 这些命令通常以 `#` 开始, 常见的有 `#define`、`#include` 等.

### 条件编译

一般来说, `define` 可以声明一个宏, 或者可以将代码中的宏名替换为相应的内容. 除此之外, `define` 也可以和 `ifndef`, `ifndef` 命令配合起来实现 "条件编译".

下面的代码中, 因为 `define` 过名为 `FLAG` 的宏 (macro), 因此 `ifdef` 命令条件为真, 故 `#ifdef FLAG` 和 `#endif` 之间的代码将会出现在预处理过的代码中; 反之, 如果没有定义过 `FLAG`, 其间的代码将不会出现在预处理之后的结果中.

```cpp
#define FLAG

int foo(int, int);

int main() {
#ifdef FLAG
    foo(3, 4);
#endif
    return 0;
}
```

`ifndef` 的作用和 `ifdef` 相反. 即, 没有定义过相应的宏名, 才会满足条件. 下面的代码中, `#ifndef FLAG` 和 `#endif` 之间的代码不会出现在预处理的结果中.

```cpp
#define FLAG

int foo(int, int);

int main() {
#ifndef FLAG
    foo(3, 4);
#endif
    return 0;
}
```

### `include` 包含命令

`include` 命令则会将被包含文件的内容原样复制到文件的对应位置里. 这里不再举例.

## 使用头文件

在前面的例子中, 我们在 `main.cpp` 中手动写入了 `int foo(int, int);` 的声明. 但当声明较多时，手动编写或复制仍是比较麻烦的.

`include` 命令可以轻松实现代码的包含引入.

为 `foo.cpp` 编写相应的头文件 (header) `foo.h` 之后, 便只需在调用处 --- 比如 `main.cpp` 中 --- 包含 (include) 对应的头文件即可。

还是使用前文用到的例子, 接下来将其拆分成以下三个文件, 并添加一些其他的内容:

- [foo.h][foo-h]
- [foo.cpp][foo-cpp]
- [main.cpp][main-cpp]

```cpp
// foo.h

{{#include assets/1/foo.h}}
```

注意，[foo.h][foo-h] 中使用 `ifndef` 等命令实现了该文件在每个翻译单元中仅会被包含一次。这叫做头文件保护 (header guards)。如果用户在一个源文件中不小心引用了两次头文件，或是包含的若干个头文件中都包含了某个头文件，那么将会出现同一个头文件在一个源文件中被引用多次的情况，即造成了重复声明。

此外，头文件中一般不能包含函数定义。试想，如果包含了函数定义的头文件被多个源代码文件包含，则这些源代码文件编译生成的目标文件中都会出现相同的符号。这会导致链接过程中链接器无法决定该使用哪一个符号。同理，也不应该使用 `include` 将函数定义的代码直接包含进源代码文件。

> 不过, 实际使用中也会出现需要将一些常用的函数放在头文件中的情况, 也就是说, 这一函数会在很多源文件中用到. 在经过编译后, 各个目标文件中均会出现这些相同的符号, 而我们不希望它们链接时发生冲突, 因此需要使用 `inline` 关键字修饰它们.
> 
> 另一种情况是, 我们希望一个函数仅在当前翻译单元可用, 而在不同的翻译单元中可能存在同名但定义不同的函数. 这时应用 `static` 关键字修饰它们. 
> 
> 需要注意, 类的声明中直接写出的函数都会被视作 `inline` 的来处理.

```cpp
// foo.cpp

{{#include assets/1/foo.cpp}}
```

在 [foo.cpp][foo-cpp] 中，同样引用了相对应的头文件，这是由于，头文件中可能包含了一些结构或类型的声明，或者包含其他的一些头文件。这时候，需要引用该头文件，否则编译时将会出现未声明符号的问题。

```cpp
// main.cpp

{{#include assets/1/main.cpp}}
```

最后，[main.cpp][main-cpp] 中只需要调用 [foo.h][foo-h] 中提供的符号即可。

[foo-h]: ./assets/1/foo.h
[foo-cpp]: ./assets/1/foo.cpp
[main-cpp]: ./assets/1/main.cpp

在编译的时候，分别生成目标文件：

```console
$ c++ foo.cpp -c -o foo.o
$ c++ main.cpp -c -o main.o
```

再执行链接操作：

```console
$ c++ main.o foo.o -o main
```

参考资料：

- <https://en.cppreference.com/w/c/language/storage_duration>
- <https://en.cppreference.com/w/cpp/language/storage_duration>

