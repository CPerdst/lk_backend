cmake_minimum_required(VERSION 3.29)

project(server)

set(CMAKE_CXX_STANDARD 17)

# 设置输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 二进制文件输出路径

file(GLOB SERVER_SOURCE "src/*.cpp")

add_subdirectory(lknet)

add_executable(server ${SERVER_SOURCE})

target_include_directories(server PRIVATE lknet/src/include lknet/lklog/src/include)

target_link_directories(server PRIVATE ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(server PRIVATE lknet lklog)


