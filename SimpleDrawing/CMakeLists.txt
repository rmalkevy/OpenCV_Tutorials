cmake_minimum_required(VERSION 3.8)
project(SimpleDrawing)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(SimpleDrawing ${SOURCE_FILES})
target_link_libraries(SimpleDrawing ${OpenCV_LIBS})