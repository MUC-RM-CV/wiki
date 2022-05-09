// Date.hpp

// 头文件需要进行保护，目的是避免重复包含

#ifndef DATE_HPP
#define DATE_HPP

// 头文件中不能包含具体的定义
// 由于头文件可能会被多个 cpp （编译单元）包含
// 如果头文件中包含具体的定义，这些编译单元在最后链接过程中，会出现多个重复的符号
// 如果确需在头文件中包含具体函数的定义，需要声明为 inline（内联）

class Date {
    int y;
    int m;
    int d;
    bool is_leap(int year) {
        return (year % 4 ==0 && year % 100 != 0) || year % 400 == 0;
    }

public:
    // 类的声明中直接书写的函数是 inline 的
    Date(int y_, int m_, int d_) : y(y_), m(m_), d(d_) {}

    // 也可以只写声明，再在 cpp 文件中实现这个函数
    int get_days();
};


#endif // DATE_HPP
