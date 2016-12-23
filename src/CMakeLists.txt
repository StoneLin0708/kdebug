set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MESSAGE")

file(GLOB DEBUG_SOURCE
    ./kdebug/*.c
    ./kdebug/*.cpp)

file(GLOB DEBUG_HEADER
    ./kdebug/*.h
    ./kdebug/*.hpp)

add_library(kdebug ${DEBUG_SOURCE} ${DEBUG_HEADER})

install(FILES ${DEBUG_HEADER} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kdebug)
install(TARGETS kdebug DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
