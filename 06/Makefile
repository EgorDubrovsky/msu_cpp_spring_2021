CC=g++
FLAGS=-std=c++17 -Wall

all: my_prog

my_prog: tests.o format.o 
	$(CC) $(FLAGS) tests.o format.o -o my_prog

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

format.o: format.cpp
	$(CC) $(FLAGS) -c format.cpp
	
test: my_prog
	valgrind ./my_prog

clean:
	rm -rf *.o tests
