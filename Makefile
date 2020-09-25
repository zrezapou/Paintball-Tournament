all: main.o main_functions.o paintball_implementation.o
	g++ main.o main_functions.o paintball_implementation.o

paintball_implementation.o: paintball_implementation.cpp paintball_class.h
	g++ -c main.cpp main_functions.cpp paintball_implementation.cpp

main.o: main.cpp main_functions.cpp main_header.h paintball_implementation.cpp paintball_class.h
	g++ -c main.cpp

main_functions.o: main_functions.cpp paintball_implementation.cpp main_header.h paintball_class.h
	g++ -c main.cpp main_functions.cpp


clean:
	rm *o
