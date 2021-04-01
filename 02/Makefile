CC=g++
FLAGS=-std=c++17 -Wall

all: my_prog

my_prog: tests.o parser.o callback_functions.o
	$(CC) $(FLAGS) tests.o parser.o callback_functions.o -o my_prog

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

parser.o: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp
	
callback_functions.o: callback_functions.cpp
	$(CC) $(FLAGS) -c callback_functions.cpp
	
test: my_prog
	valgrind ./my_prog

clean:
	rm -rf *.o tests
