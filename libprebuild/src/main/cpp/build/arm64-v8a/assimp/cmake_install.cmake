# Install script for directory: D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/assimp

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
  set(CMAKE_OBJDUMP "D:/ApplicationManage/dev/android/Android SDK/ndk/22.1.7171670/toolchains/llvm/prebuilt/windows-x86_64/bin/aarch64-linux-android-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.3.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3" TYPE FILE FILES
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/generated/assimpConfig.cmake"
    "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/generated/assimpConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.3.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3/assimpTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3/assimpTargets.cmake"
         "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/CMakeFiles/Export/lib/cmake/assimp-5.3/assimpTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3/assimpTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3/assimpTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3" TYPE FILE FILES "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/CMakeFiles/Export/lib/cmake/assimp-5.3/assimpTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-5.3" TYPE FILE FILES "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/CMakeFiles/Export/lib/cmake/assimp-5.3/assimpTargets-relwithdebinfo.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.3.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/assimp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/contrib/zlib/cmake_install.cmake")
  include("D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/code/cmake_install.cmake")
  include("D:/dev/work/project/github/tomcan/JNI/android_jni/libprebuild/src/main/cpp/build/arm64-v8a/assimp/test/cmake_install.cmake")

endif()

