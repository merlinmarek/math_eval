project(libmath_eval)

add_library(math_eval STATIC src/math_eval.cc)

target_include_directories(math_eval PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

#target_compile_features NEEDS C++11 SUPPORT

install(TARGETS math_eval EXPORT MathEvalConfig
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT MathEvalConfig DESTINATION share/MathEval/cmake)

export(TARGETS math_eval FILE MathEvalConfig.cmake)

#install(TARGETS math_eval DESTINATION lib)
