CC=g++
FLAGS=-std=c++17 -Wall

all: my_prog

my_prog: tests.o bigint.o 
	$(CC) $(FLAGS) tests.o bigint.o -o my_prog

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

bigint.o: bigint.cpp
	$(CC) $(FLAGS) -c bigint.cpp
	
test: my_prog
	valgrind ./my_prog

clean:
	rm -rf *.o tests
