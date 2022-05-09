project(My-Date)

cmake_minimum_required(VERSION 3.13)

# 指定 C++ 版本
set(CMAKE_CXX_STANDARD 14)

# 创建一个库目标, 使用 Date.hpp, Date.cpp 两个源文件; 默认生成的是静态链接库
add_library(Date "Date.hpp" "Date.cpp")

# 设定库目标的包含路径
target_include_directories(Date PUBLIC .)
