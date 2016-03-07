main:	main.o Libro.o Editorial.o Header.o	indexFile.o
	g++ -std=c++11 main.o Libro.o Editorial.o Header.o indexFile.o -o main

main.o:	main.cpp Libro.hpp Editorial.hpp indexFile.hpp
	g++ -c main.cpp

Libro.o: Libro.cpp Libro.hpp
	g++ -c Libro.cpp

Editorial.o: Editorial.cpp Editorial.hpp
	g++ -c Editorial.cpp

Header.o:	Header.cpp	Header.hpp	Libro.hpp
	g++ -c Header.cpp

indexFile.o: indexFile.cpp	indexFile.hpp
	g++ -c indexFile.cpp


clean:
	rm *.o main	libros.bin	index.bin