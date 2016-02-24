main:	main.o Libro.o Editorial.o
	g++ main.o Libro.o Editorial.o -o main

main.o:	main.cpp Libro.hpp Editorial.hpp
	g++ -c main.cpp

Libro.o:	Libro.cpp Libro.hpp
	g++ -c Libro.cpp

Editorial.o:	Editorial.cpp Editorial.hpp
	g++	-c Editorial.cpp

clean:
	rm *.o main