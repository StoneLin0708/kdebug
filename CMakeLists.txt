cmake_minimum_required(VERSION 3.0)

project(kdebug)
enable_testing()

# c/c++ options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MESSAGE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -O3 -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG_MESSAGE")

# source
file(GLOB SOURCE src/kdebug/*.c src/kdebug/*.cpp)
# header
file(GLOB HEADER src/kdebug/*.h src/kdebug/*.hpp)
add_library(kdebug ${SOURCE} ${HEADER})
target_compile_options(kdebug BEFORE PRIVATE -g -Wall -Wextra -O3 -std=c++11)
# installation
install(FILES ${HEADER} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kdebug)
install(TARGETS kdebug DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# test builds
include_directories(./src)

# basic test
add_executable(debug_test test/debug_test.cpp)
add_dependencies(debug_test kdebug)

# time test
add_executable(debug_test_update_time test/debug_test_update_time.cpp)
add_dependencies(debug_test_update_time kdebug)

# link test
add_executable(link_test test/link_test.cpp test/link1.cpp test/link2.cpp)
add_dependencies(link_test kdebug)

# c test
add_executable(debug_test_c test/debug_test.c)
add_dependencies(debug_test_c kdebug)

target_link_libraries(debug_test kdebug)
target_link_libraries(debug_test_update_time kdebug)
target_link_libraries(link_test kdebug)
target_link_libraries(debug_test_c kdebug)

add_test(cpp_debug_test ./debug_test)
add_test(cpp_link_test ./link_test)
add_test(c_debug_test ./debug_test_c)
