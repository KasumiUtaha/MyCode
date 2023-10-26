cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,536870912")
set(CMAKE_CXX_STANDARD 14)


add_executable(test MyVector.cpp)
