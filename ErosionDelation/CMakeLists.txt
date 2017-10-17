cmake_minimum_required(VERSION 3.8)
project(ErosionDelation)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp)
add_executable(ErosionDelation ${SOURCE_FILES})
target_link_libraries(ErosionDelation ${OpenCV_LIBS})