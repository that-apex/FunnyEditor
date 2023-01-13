cmake_minimum_required(VERSION 3.24)
project(FunnyEditor)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(FFmpeg REQUIRED COMPONENTS
        avutil
        avdevice
        avfilter
        avformat
        avcodec
        swscale)

find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory("src")
add_subdirectory("executable")

