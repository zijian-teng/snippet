cmake_minimum_required(VERSION 3.5.0)
project(zsnippet VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
include(CTest)
enable_testing()

add_executable(pimpl cpp/01-idioms/01-pimpl/MyInterface.cpp cpp/01-idioms/01-pimpl/pimpl.cpp)
add_executable(singleton cpp/02-design-pattern/01-singleton.cpp)
add_executable(observer cpp/02-design-pattern/02-observer.cpp)
add_executable(condvar cpp/03-concurrency-and-parallel/01-sync-with-condvar.cpp)
add_executable(promise_future cpp/03-concurrency-and-parallel/02-sync-with-promise-future.cpp)
add_executable(time_elapsed cpp/04-time-and-chrono/01-time-elapsed.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
