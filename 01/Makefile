CC=g++
FLAGS=-std=c++17 -Wall

all: sphere01.hpp tests.cpp
	$(CC) $(FLAGS) -o tests sphere01.hpp tests.cpp 

test: tests
	valgrind ./tests

clean:
	rm -rf *.o tests
