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
		const bool getDeleted();
		const char* getISBN();
		const char* getNombre();
		const char* getAutor();
		const unsigned int getEditorialID();

		//Setters
		void setDeleted(bool deleted);
		void setISBN(char* ISBN);
		void setNombre(char* Nombre);
		void setAutor(char* Autor);
		void setEditorialID(unsigned int Editorial);

		string toString(); 

	private:
		char ISBN[23];
		char Nombre[76];
		char Autor[76];
		unsigned int EditorialID;
		bool Deleted;
};