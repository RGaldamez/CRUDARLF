#pragma once 

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
};