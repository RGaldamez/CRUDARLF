#include "indexFile.hpp"
#include <cstring>
#include <fstream>
using std::ifstream;
using std::ofstream;


indexFile::indexFile(){

}

indexFile::indexFile(char* llave,long int offset){
	strcpy(this->llave,llave);
	this->offset = offset; 
}
indexFile::~indexFile(){
	//por definir
}
char* indexFile::getLlave(){
	return this->llave;
}
long int indexFile::getOffset(){
	return this->offset;
}
void indexFile::setLlave(char*Llave){
	strcpy(this->llave,llave);
}
void indexFile::setOffset(long int offset){
	this->offset = offset;
}

void indexFile::createIndex(){
	
}