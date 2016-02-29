main:	main.o Libro.o Editorial.o Header.o
	g++ main.o Libro.o Editorial.o Header.o -o main

main.o:	main.cpp Libro.hpp Editorial.hpp
	g++ -c main.cpp

Libro.o:	Libro.cpp Libro.hpp
	g++ -c Libro.cpp

Editorial.o:	Editorial.cpp Editorial.hpp
	g++	-c Editorial.cpp

Header.o:	Header.cpp	Header.hpp
	g++ -c Header.cpp


clean:
	rm *.o main	libros.bin