#include "Editorial.hpp"
#include <cstring>

Editorial::Editorial(){
	//por definir
}
Editorial::Editorial(unsigned int EditorialID, char* Nombre, char* Direccion){
	this->EditorialID = EditorialID;
	strcpy(this->Nombre, Nombre);
	strcpy(this->Direccion, Direccion);
}
Editorial::~Editorial(){
//por definir
}

//Setters
void Editorial::setEditorialID(unsigned int EditorialID){
	this->EditorialID = EditorialID;
}
void Editorial::setNombre(char* Nombre){
	strcpy(this->Nombre, Nombre);
}
void Editorial::setDireccion(char* Direccion){
	strcpy(this->Direccion, Direccion);
}
//Getters
const unsigned int Editorial::getEditorialID(){
	return this->EditorialID;
}
const char* Editorial::getNombre(){
	return this->Nombre;
}
const char* Editorial::getDireccion(){
	return this->Direccion;
}

