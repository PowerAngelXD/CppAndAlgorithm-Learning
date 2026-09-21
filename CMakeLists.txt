cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cppal)

add_executable(SingalList "ADT/Table/SingleList.cpp")

add_executable(DoubleList "ADT/Table/DoubleList.cpp")

add_executable(SeqList "ADT/Table/SeqList.cpp")

add_executable(Vector "ADT/Table/Vector.cpp")

add_executable(Stack "ADT/Stack/Stack.cpp")

add_executable(Queue "ADT/Queue/Queue.cpp")