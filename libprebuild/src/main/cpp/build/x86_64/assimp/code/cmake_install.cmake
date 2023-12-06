# Install script for directory: D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/ApplicationManage/dev/android/Android SDK/ndk/22.1.7171670/toolchains/llvm/prebuilt/windows-x86_64/bin/x86_64-linux-android-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.3.0x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/build/intermediates/cxx/RelWithDebInfo/274y586j/obj/x86_64/libassimp.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/ApplicationManage/dev/android/Android SDK/ndk/22.1.7171670/toolchains/llvm/prebuilt/windows-x86_64/bin/llvm-strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.3.0x" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/anim.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/aabb.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ai_assert.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/camera.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/color4.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/color4.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/x86_64/assimp/code/../include/assimp/config.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ColladaMetaData.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/commonMetaData.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/defs.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/cfileio.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/light.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/material.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/material.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/matrix3x3.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/matrix3x3.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/matrix4x4.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/matrix4x4.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/mesh.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ObjMaterial.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/pbrmaterial.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/GltfMaterial.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/postprocess.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/quaternion.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/quaternion.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/scene.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/metadata.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/texture.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/types.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/vector2.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/vector2.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/vector3.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/vector3.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/version.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/cimport.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/AssertHandler.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/importerdesc.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Importer.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/DefaultLogger.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ProgressHandler.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/IOStream.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/IOSystem.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Logger.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/LogStream.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/NullLogger.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/cexport.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Exporter.hpp"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/DefaultIOStream.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/DefaultIOSystem.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SceneCombiner.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/fast_atof.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/qnan.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/BaseImporter.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Hash.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ParsingUtils.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/StreamReader.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/StreamWriter.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/StringComparison.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/StringUtils.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SGSpatialSort.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/GenericProperty.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SpatialSort.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SmallVector.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SmoothingGroups.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/SmoothingGroups.inl"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/StandardShapes.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/RemoveComments.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Subdivision.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Vertex.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/LineSplitter.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/TinyFormatter.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Profiler.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/LogAux.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Bitmap.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/XMLTools.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/IOStreamBuffer.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/CreateAnimMesh.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/XmlParser.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/BlobIOSystem.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/MathFunctions.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Exceptional.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/ByteSwapper.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Compiler/poppack1.h"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

