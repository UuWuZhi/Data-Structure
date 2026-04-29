cmake_minimum_required(VERSION 4.1)

project(DataStructure LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 收集 Algorithm 目录下所有源文件
file(GLOB ALGORITHM_SOURCES
        "Algorithm/*.cpp"
)

# 收集 C 结构实现源文件
file(GLOB STRUCTURE_SOURCES
        "C/Src/*.c"
)

# 收集项目头文件并标记为头文件
file(GLOB_RECURSE PROJECT_HEADERS
        "C/Inc/*.h"
        "Cpp/*.hpp"
)
set_source_files_properties(${PROJECT_HEADERS} PROPERTIES HEADER_FILE_ONLY ON)

# Algorithm 下每个 .cpp 生成一个可执行目标
foreach(ALGORITHM_SOURCE IN LISTS ALGORITHM_SOURCES)
    get_filename_component(ALGORITHM_NAME "${ALGORITHM_SOURCE}" NAME_WE)
    string(MAKE_C_IDENTIFIER "${ALGORITHM_NAME}" ALGORITHM_ID)
    set(TARGET_NAME "algorithm_${ALGORITHM_ID}")

    file(READ "${ALGORITHM_SOURCE}" ALGORITHM_CONTENTS)
    set(EXCLUDE_SWITCH "")
    if(NOT ALGORITHM_CONTENTS MATCHES "(^|[\r\n])[ \t]*int[ \t]+main[ \t]*\\(")
        # 没有 main 的算法源文件仍然建目标，但不参与默认 all 构建
        set(EXCLUDE_SWITCH EXCLUDE_FROM_ALL

        )
        message(WARNING "Algorithm source ${ALGORITHM_SOURCE} has no main(), target ${TARGET_NAME} is EXCLUDE_FROM_ALL.")
    endif()

    add_executable(${TARGET_NAME} ${EXCLUDE_SWITCH}
            "${ALGORITHM_SOURCE}"
            ${STRUCTURE_SOURCES}
            ${PROJECT_HEADERS}
    )

    target_include_directories(${TARGET_NAME} PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/C/Inc"
            "${CMAKE_CURRENT_SOURCE_DIR}/Cpp"
    )

    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${ALGORITHM_NAME}")
endforeach()
