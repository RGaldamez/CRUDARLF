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
	this->Deleted = false;
	this-> mark = '-';
	this-> avail = -1;
}

Libro::~Libro(){
//por definir
}

//Getters
const char* Libro::getISBN(){
	return this->ISBN;
}

const char* Libro::getNombre(){
	return this->Nombre;
}

const char* Libro::getAutor(){
	return this->Autor;
}

const unsigned int Libro::getEditorialID(){
	return this->EditorialID;
}
const bool Libro::getDeleted(){
	return this->Deleted;
}

const char Libro::getMark(){
	return this->mark;
}

const int Libro::getAvail(){
	return this->avail;
}
//Setters 
void Libro::setISBN(char* ISBN){
	strcpy(this->ISBN,ISBN);
}
void Libro::setNombre(char* Nombre){
	strcpy(this-> Nombre,Nombre);
}
void Libro::setMark(char mark){
	this->mark = mark;
}

void Libro::setAutor(char* Autor){
	strcpy(this->Autor, Autor);
}
void Libro::setEditorialID(unsigned int Editorial){
	this->EditorialID = Editorial;
}
void Libro::setDeleted(bool deleted){
	this->Deleted = deleted;
}
void Libro::setAvail(int avail){
	this-> avail = avail;
}

string Libro::toString(){
	stringstream ss;
	int size =18+(76*2)+sizeof(unsigned int);
	char temp[size];
	ss<<this->ISBN;
	ss<<this->Nombre;
	ss<<this->Autor;
	ss<<this->EditorialID;
	return ss.str();
}

