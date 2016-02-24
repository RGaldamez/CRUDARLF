#include "Libro.hpp"
#include <cstring>
#include <sstream>
#include <string>
using std::string;
using std::stringstream;


Libro::Libro(){
	
}

Libro::Libro(char* ISBN, char* Nombre, char* Autor, unsigned int EditorialID){
	strcpy(this->ISBN, ISBN);
	strcpy(this->Nombre, Nombre);
	strcpy(this->Autor, Autor);
	this->EditorialID = EditorialID;
}

Libro::~Libro(){
//por definir
}

//Getters
char* Libro::getISBN(){
	return this->ISBN;
}

char* Libro::getNombre(){
	return this->Nombre;
}

char* Libro::getAutor(){
	return this->Autor;
}

unsigned int Libro::getEditorialID(){
	return this->EditorialID;
}
//Setters 
void Libro::setISBN(char* ISBN){
	strcpy(this->ISBN,ISBN);
}
void Libro::setNombre(char* Nombre){
	strcpy(this-> Nombre,Nombre);
}
void Libro::setAutor(char* Autor){
	strcpy(this->Autor, Autor);
}
void Libro::setEditorialID(unsigned int Editorial){
	this->EditorialID = EditorialID;
}

string Libro::toString(){
	stringstream ss;
	int size =14+(76*2)+sizeof(unsigned int);
	char temp[size];
	ss<<this->ISBN;
	ss<<this->Nombre;
	ss<<this->Autor;
	ss<<this->EditorialID;
	return ss.str();
}

