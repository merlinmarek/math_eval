cmake_minimum_required(VERSION 2.8.12)
project(math_eval)

# this can be replaced with target_compile_features if cmake version >= 3.1 is available
add_compile_options(-std=c++11) 

add_subdirectory(libmath_eval)
add_subdirectory(demo)
