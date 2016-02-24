#pragma once 
#include <cstring>
#include <string>
using std::string;

class Libro{
	public:
		//Constructor/Destructor
		Libro();
		Libro(char* ISBN,char* Nombre,char* Autor,unsigned int EditorialID);
		~Libro();

		//Getters
		char* getISBN();
		char* getNombre();
		char* getAutor();
		unsigned int getEditorialID();

		//Setters
		void setISBN(char* ISBN);
		void setNombre(char* Nombre);
		void setAutor(char* Autor);
		void setEditorialID(unsigned int Editorial);

		string toString(); 

	private:
		char ISBN[14];
		char Nombre[76];
		char Autor[76];
		unsigned int EditorialID;
};