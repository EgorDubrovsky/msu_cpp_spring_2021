CC=g++
FLAGS=-std=c++17 -Wall

all: my_prog

my_prog: tests.o matrix.o 
	$(CC) $(FLAGS) tests.o matrix.o -o my_prog

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

matrix.o: matrix.cpp
	$(CC) $(FLAGS) -c matrix.cpp
	
test: my_prog
	valgrind ./my_prog

clean:
	rm -rf *.o tests
