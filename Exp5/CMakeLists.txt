cmake_minimum_required(VERSION 3.20)
project(exp5)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR "E:\\opencv\\opencv\\mingw-build\\install")	# 这里填写你存放的 mingw-build 的文件夹目录
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(exp5 main.cpp
        color.h
        Seed-Filling.h
        Two-pass.h)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
target_link_libraries(exp5 ${OpenCV_LIBS})	# 链接 OpenCV 库


