cmake_minimum_required(VERSION 3.0)

project(kdebug)
enable_testing()

# c/c++ options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -O3")
add_definitions(-DKDEBUG_MESSAGE)

# source
file(GLOB SOURCE src/kdebug/*.cpp)
# header
file(GLOB HEADER src/kdebug/*.h src/kdebug/*.hpp)
add_library(kdebug ${SOURCE} ${HEADER})
target_compile_options(kdebug BEFORE PRIVATE -g -Wall -Wextra -O3 -std=c++11)

# installation
install(FILES ${HEADER} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kdebug)
install(TARGETS kdebug DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# test builds
include_directories(src)

# basic test
add_executable(kdebug_unit_test test/kdebug_unit_test.cpp)
add_dependencies(kdebug_unit_test kdebug)
target_link_libraries(kdebug_unit_test kdebug)

# # link test
file(GLOB LINK_TEST_SOURCE test/link*.cpp)
add_executable(link_test ${LINK_TEST_SOURCE})
add_dependencies(link_test kdebug)
target_link_libraries(link_test kdebug)

# c test
add_executable(kdebug_test_c test/kdebug_test.c)
add_dependencies(kdebug_test_c kdebug)
target_link_libraries(kdebug_test_c kdebug)

add_test(cpp_debug_test ./kdebug_unit_test)
add_test(cpp_link_test ./link_test)
add_test(c_debug_test ./kdebug_test_c)
