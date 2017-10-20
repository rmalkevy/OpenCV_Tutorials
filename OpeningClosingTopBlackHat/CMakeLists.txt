cmake_minimum_required(VERSION 3.8)
project(OpeningClosingTopBlackHat)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp)
add_executable(OpeningClosingTopBlackHat ${SOURCE_FILES})
target_link_libraries(OpeningClosingTopBlackHat ${OpenCV_LIBS})