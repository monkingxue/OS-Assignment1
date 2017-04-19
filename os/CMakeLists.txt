cmake_minimum_required(VERSION 3.6)
project(os)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cc define.h yoroutine.cc yoroutine.h scheduler.cc scheduler.h tool.h test/step_by_step.h test/test.h test/p_to_c.h)
add_executable(os ${SOURCE_FILES})