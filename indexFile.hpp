#pragma once 
#include <string>
using std::string;

class indexFile{
private:
	char llave[14];
	long int offset;
public:
	indexFile();
	indexFile(char* llave,long int offset);
	~indexFile();
 	char* getLlave();
	long int getOffset();
	void setLlave(char*);
	void setOffset(long int);
	void createIndex();
	const string toString();
	const indexFile& operator=(const indexFile&); 

};