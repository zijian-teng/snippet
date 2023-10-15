cmake_minimum_required(VERSION 3.0.0)
project(zsnippet VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
include(CTest)
enable_testing()

add_executable(condvar cpp/concurrency_and_parallel/condvar.cpp)
add_executable(time_elapsed cpp/time_and_chrono/time_elapsed.cpp)
add_executable(singleton cpp/design_pattern/singleton.cpp)
add_executable(pimpl cpp/idioms/pimpl/MyInterface.cpp cpp/idioms/pimpl/pimpl.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
