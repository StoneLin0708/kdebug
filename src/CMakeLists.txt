set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -O3 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MESSAGE")

file(GLOB DEBUG_SOURCE
    ${CMAKE_SOURCE_DIR}/src/kdebug/*.h
    ${CMAKE_SOURCE_DIR}/src/kdebug/*.hpp
    ${CMAKE_SOURCE_DIR}/src/kdebug/*.c
    ${CMAKE_SOURCE_DIR}/src/kdebug/*.cpp)

add_library(kdebug ${DEBUG_SOURCE})
message("--> headers: ${DEBUG_SOURCE}")
install(FILES ${DEBUG_HEADER} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kdebug)
install(TARGETS kdebug DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
