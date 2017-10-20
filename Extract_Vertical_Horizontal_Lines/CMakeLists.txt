cmake_minimum_required(VERSION 3.8)
project(Extract_Vertical_Horizontal_Lines)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp)

add_executable(Extract_Vertical_Horizontal_Lines ${SOURCE_FILES})
target_link_libraries(Extract_Vertical_Horizontal_Lines ${OpenCV_LIBS})
