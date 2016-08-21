set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MESSAGE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -O3 -std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG_MESSAGE")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(debug_test debug_test.cpp)
add_executable(link_test link_test.cpp link1.cpp link2.cpp)
add_executable(debug_test_c debug_test.c)

target_link_libraries(debug_test kdebug)
target_link_libraries(link_test kdebug)
