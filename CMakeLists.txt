cmake_minimum_required(VERSION 4.1)

project(DataStructure LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# 收集 algorithm 目录下所有源文件（包含 main）
file(GLOB ALGORITHM_SOURCES
        "Algorithm/*.cpp"
)

# 收集 structure 目录下所有源文件
file(GLOB STRUCTURE_SOURCES
        "C/Src/*.c"
)

# 收集 CInc 目录下所有头文件，并标记为项目头文件
file(GLOB_RECURSE PROJECT_HEADERS
        "C/Inc/*.h"
        "Cpp/*.hpp"
)
set_source_files_properties(${PROJECT_HEADERS} PROPERTIES HEADER_FILE_ONLY ON)

# 合并所有源文件
list(APPEND ALL_SOURCES ${ALGORITHM_SOURCES} ${STRUCTURE_SOURCES})

# 生成可执行文件
add_executable(DataStructure ${ALL_SOURCES}
        ${PROJECT_HEADERS}
)

target_include_directories(DataStructure PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/C/Inc"
        "${CMAKE_CURRENT_SOURCE_DIR}/Cpp"
)
