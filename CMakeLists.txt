cmake_minimum_required(VERSION 4.1)

project(DataStructure)

set(CMAKE_CXX_STANDARD 20)

# 收集 algorithm 目录下所有源文件
file(GLOB ALGORITHM_SOURCES
        "CppSrc/algorithm/*.cpp"
        "CSrc/algorithm/*.c"
)

# 收集 structure 目录下所有源文件
file(GLOB STRUCTURE_SOURCES
        "CppSrc/structure/*.cpp"
        "CSrc/structure/*.c"
)

# 收集 CInc 目录下所有头文件，并标记为项目头文件
file(GLOB_RECURSE PROJECT_HEADERS
        "CInc/*.h"
        "CppInc/*.hpp"
)
set_source_files_properties(${PROJECT_HEADERS} PROPERTIES HEADER_FILE_ONLY ON)

# 合并所有源文件
list(APPEND ALL_SOURCES ${ALGORITHM_SOURCES} ${STRUCTURE_SOURCES})

# 生成可执行文件
add_executable(DataStructure ${ALL_SOURCES}
        ${PROJECT_HEADERS}
        CSrc/structure/LinkedList.c
        CSrc/structure/Stack.c)

target_include_directories(DataStructure PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/CppInc"
)
