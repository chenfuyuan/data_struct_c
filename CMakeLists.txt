cmake_minimum_required(VERSION 3.20)
project(data_struct)

set(CMAKE_CXX_STANDARD 14)

# 遍历项目根目录及二级目录下所有的 .cpp 文件
file (GLOB files *.cpp */*.cpp */*/*.cpp */*/*/*.cpp)
foreach (file ${files})
    #运行名: 文件名 所有文件名不能重复
    #string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    #运行名: 文件目录-文件名 可避免重复
    string(REGEX REPLACE ".+/(.+)/(.+)\\..*" "\\1-\\2" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()

