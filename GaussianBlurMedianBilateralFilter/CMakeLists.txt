cmake_minimum_required(VERSION 3.8)
project(GaussianBlurMedianBilateralFilter)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(GaussianBlurMedianBilateralFilter ${SOURCE_FILES})
target_link_libraries(GaussianBlurMedianBilateralFilter ${OpenCV_LIBS})