cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cppal)

add_executable(SingalList "ADT/List/SingleList.cpp")

add_executable(DoubleList "ADT/List/DoubleList.cpp")

add_executable(SeqList "ADT/List/SeqList.cpp")

add_executable(Vector "cpp-learning/STL-Learning/Vector/Vector.cpp")

add_executable(Stack "ADT/Stack/Stack.cpp")

add_executable(Queue "ADT/Queue/Queue.cpp")

add_executable(BF "Algorithm/String/BF.cpp")

add_executable(KMP "Algorithm/String/KMP.cpp")

add_executable(BFKMPBench "Algorithm/String/Benchmark.cpp")