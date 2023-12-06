
#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

# configure import libs
#set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution) # CMAKE_CURRENT_SOURCE_DIR 为当前路径，/../为后退一个文件路径
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../distribution)

# ${ANDROID_ABI} is handy for our purpose here. Probably this ${ANDROID_ABI} is
# the most valuable thing of this sample, the rest are pretty much normal cmake
add_library(libassimp SHARED IMPORTED)
set_target_properties(libassimp PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/assimp/libs/${ANDROID_ABI}/libassimp.so)

add_library(libopencv_java4 SHARED IMPORTED)
set_target_properties(libopencv_java4 PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/opencv/libs/${ANDROID_ABI}/libopencv_java4.so)




# build application's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(AssimpMate SHARED
        JNIImpl.cpp
        JNIImpl.h
        ModelLoader.cpp
        ModelLoader.h
        core/AssimpMate.cpp
        core/AssimpMate.h
        common/misc.cpp
        common/misc.h
        utils/AssetHelper.cpp
        utils/AssetHelper.h
        core/GLMMate.cpp
        core/GLMMate.h
        gles/ShaderMate.cpp
        gles/ShaderMate.h
        gles/GLESMate.cpp
        gles/GLESMate.h
        )

target_include_directories(AssimpMate PRIVATE
        ${distribution_DIR}/assimp/include
        ${distribution_DIR}/opencv/include
        ${distribution_DIR}/glm/glm
        )


target_link_libraries(
        AssimpMate
        android
        EGL
        GLESv2
        libassimp
        libopencv_java4
        log)
