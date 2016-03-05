#include "Header.hpp"

Header::Header(long int availList,int sizeOfCampo,int RecordCount,bool DirtyBit){
	this->availList = availList;
	this->size = sizeOfCampo;
	this->recordCount = RecordCount;
	this->dirtyBit = DirtyBit;
}
void Header::setAvailList(long int availList){
	this->availList = availList;
}
void Header::setSize(int size){
	this->size = size;

}
void Header::setDirty(bool Dirty){
	this->dirtyBit = Dirty;

}
void Header::setRecordCount(int RecordCount){
	this->recordCount = RecordCount;
}
long int Header::getAvailList(){
	return this->availList;
}
int Header::getSize(){
	return this->size;
}
bool Header::getDirty(){
	return this->dirtyBit;
}
int Header::getRecordCount(){
	return this->recordCount;
}