cmake_minimum_required(VERSION 2.8.12)
project(math_eval)
add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories(include)
subdirs(src demo)

install(DIRECTORY include/ DESTINATION include)
