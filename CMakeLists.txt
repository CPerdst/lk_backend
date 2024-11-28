cmake_minimum_required(VERSION 3.29)

project(server)

set(CMAKE_CXX_STANDARD 17)

# 设置输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 二进制文件输出路径

# --------------
# 首先编译依赖模块
# --------------

add_subdirectory(lknet)

# 获取 server 源码
file(GLOB SERVER_SOURCE "src/*.cpp")

# --------------------
# 编译 server 可执行文件
# --------------------

# 添加源码
add_executable(server ${SERVER_SOURCE})

# 指定头文件路径
target_include_directories(server PRIVATE lknet/src/include lknet/lklog/src/include)

# 指定链接库路径
target_link_directories(server PRIVATE ${CMAKE_BINARY_DIR}/lib)

# 链接库文件
target_link_libraries(server PRIVATE lknet lklog)


