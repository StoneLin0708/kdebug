set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MESSAGE")

file(GLOB_RECURSE DEBUG_HEADER
    ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp)
add_library(kdebug debug.cpp)

message("--> headers: ${DEBUG_HEADER}")
install(FILES ${DEBUG_HEADER} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS kdebug DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
