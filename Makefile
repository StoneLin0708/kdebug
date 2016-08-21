CXX := g++
CXX_FLAGS := -g -std=c++11 -O3 -Wall -Wextra -fPIC
CXX_FLAGS := $(CXX_FLAGS) -DDEBUG_MESSAGE

TARGET := debug_test

all: $(TARGET)

debug_test: debug_test.o
	$(CXX) debug_test.o -o $@

debug_test.o: debug_test.cpp debug.hpp
	$(CXX) $(CXX_FLAGS) debug_test.cpp -c -o $@

clean:
	rm -rf *.o $(TARGET)

.phony: all clean
