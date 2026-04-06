cmake_minimum_required(VERSION 4.1)
project(DataStructure)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataStructure
        Src/backward_algorithm.cpp
        Src/CircularQueue.cpp
        Src/Deque.cpp
        Src/Stack.cpp
        Src/LinkedStack.cpp
        Src/DoubleCircularList.cpp
        Src/LinkedList.cpp
)
