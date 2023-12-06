cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

set(lib_src_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#set(lib_build_DIR $ENV{HOME}/tmp/${ANDROID_ABI})
set(lib_build_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/${ANDROID_ABI})
file(MAKE_DIRECTORY ${lib_build_DIR})

add_subdirectory(${lib_src_DIR}/assimp ${lib_build_DIR}/assimp)