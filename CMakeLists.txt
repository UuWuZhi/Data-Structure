cmake_minimum_required(VERSION 4.1)

project(DataStructure)

set(CMAKE_CXX_STANDARD 20)

# 收集 algorithm 目录下所有源文件
file(GLOB ALGORITHM_SOURCES
        "Src/algorithm/*.cpp"
        "Src/algorithm/*.c"
        "Src/algorithm/*.cc"
)

# 收集 structure 目录下所有源文件
file(GLOB STRUCTURE_SOURCES
        "Src/structure/*.cpp"
        "Src/structure/*.c"
        "Src/structure/*.cc"
)

# 合并所有源文件
list(APPEND ALL_SOURCES ${ALGORITHM_SOURCES} ${STRUCTURE_SOURCES})

# 生成可执行文件
add_executable(DataStructure ${ALL_SOURCES})