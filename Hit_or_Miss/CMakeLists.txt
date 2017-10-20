cmake_minimum_required(VERSION 3.8)
project(Hit_or_Miss)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)

add_executable(Hit_or_Miss ${SOURCE_FILES})

target_link_libraries(Hit_or_Miss ${OpenCV_LIBS})