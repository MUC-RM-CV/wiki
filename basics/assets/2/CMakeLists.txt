project(CPP-Multi-File-Demo)

add_executable(single_file_demo "single_file_demo.cpp")

# 子目录 Date 中的 CMakeLists.txt 中包含生成 Date 这个目标, 引入后便可以使用
add_subdirectory(Date)

# 创建一个名为 demo 的生成可执行文件的目标, 使用 demo.cpp 源文件
add_executable(demo "demo.cpp")

# 将 demo 和 "Date" 库进行链接
target_link_libraries(demo Date)
