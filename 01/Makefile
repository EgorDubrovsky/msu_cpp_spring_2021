CC=g++
FLAGS=-std=c++17 -Wall

all: my_prog

my_prog: tests.o allocator.o
	$(CC) $(FLAGS) tests.o allocator.o -o my_prog

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

allocator.o: allocator.cpp
	$(CC) $(FLAGS) -c allocator.cpp
	
test: my_prog
	valgrind ./my_prog

clean:
	rm -rf *.o tests
