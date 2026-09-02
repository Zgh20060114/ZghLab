cmake_minimum_required(VERSION 4.4)
# cmake -S . -B build
# cmake --build build
# 基于target设置不同的继承权限是现代cmake的一大核心.之前不带target的link/include会全局污染
# ctest --test-dir build 在build文件夹下寻找可执行文件进行ctest测试.
# cmake -S . -B build -DENABLE_TEST=ON 通过-D添加参数.
# set()

project(
  cmake_tutorial
  LANGUAGES CXX C
  DESCRIPTION "this is a cmake tutorial."
  VERSION 0.1
)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# add_executable(tutorial src/main.cpp)
add_subdirectory(3rdlibs)

aux_source_directory(./src lib_src)
file(GLOB_RECURSE lib_inc ./inc/*.hpp)

message(${lib_src})
add_library(tutorial_lib STATIC ${lib_src} ${lib_inc})
target_include_directories(tutorial_lib PUBLIC inc)
target_link_libraries(tutorial_lib PUBLIC glfw)
target_compile_features(tutorial_lib PUBLIC cxx_std_17)
# 预编译头文件
target_precompile_headers(tutorial_lib PUBLIC ./inc/pch.hpp)

add_executable(tutorial src/main.cpp)
target_link_libraries(tutorial PUBLIC tutorial_lib  toml++)
target_precompile_headers(tutorial REUSE_FROM tutorial_lib)

option(ENABLE_TEST "should enable test or not" FALSE)
if(ENABLE_TEST OR PROJECT_IS_TOP_LEVEL)
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif()
