
RELBIN = build/libdebug.a
TESTBIN = build/test

.PHONY: all test

all: $(RELBIN)

$(RELBIN): debug.cpp debug.hpp
	@mkdir -p build
	g++ -O3 -std=c++14 -c debug.cpp -o debug.o
	ar rcs $@ debug.o
	rm debug.o

test: $(TESTBIN)

$(TESTBIN): debug.cpp debug.hpp test.cpp
	g++ -O3 -std=c++14 debug.cpp test.cpp -o $@
