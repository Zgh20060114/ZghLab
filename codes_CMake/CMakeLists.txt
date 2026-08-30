cmake_minimum_required(VERSION 4.4)
# cmake -S . -B build
# cmake --build build
# 基于target设置不同的继承权限是现代cmake的一大核心.之前不带target的link/include会全局污染
project(
  cmake_tutorial
  LANGUAGES CXX C
  DESCRIPTION "this is a cmake tutorial."
  VERSION 0.1
)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# add_executable(tutorial src/main.cpp)
add_library(tutorial_lib STATIC src/utils.cpp)
target_include_directories(tutorial_lib PUBLIC inc)
target_compile_features(tutorial_lib PUBLIC cxx_std_17)
add_executable(tutorial src/main.cpp)
target_link_libraries(tutorial PUBLIC tutorial_lib)
add_subdirectory(3rdlibs)
target_link_libraries(tutorial PUBLIC glfw)

include(CTest)
enable_testing()
add_subdirectory(test)
