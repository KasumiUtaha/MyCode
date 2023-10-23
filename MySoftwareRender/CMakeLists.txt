cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,536870912")
set(CMAKE_CXX_STANDARD 14)
set(SOURCES
SoftwareRender/SoftwareRender.cpp
SoftwareRender/SoftwareRender.h
SoftwareRender/Geometry/Triangle.h
SoftwareRender/Geometry/Triangle.cpp
SoftwareRender/math/Matrix.cpp
SoftwareRender/math/Matrix.h
SoftwareRender/math/Vector.cpp
SoftwareRender/math/Vector.h
SoftwareRender/Color.cpp
SoftwareRender/Color.h
SoftwareRender/Geometry/Cube.h
SoftwareRender/Geometry/Cube.cpp
)

add_executable(test TestPPM.cpp ${SOURCES})
