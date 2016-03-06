#include <iostream>
using namespace std;

#include "Libro.hpp"
#include "Header.hpp"
#include "indexFile.hpp"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <cstring>

#include <fstream>
using std::ifstream;
using std::ofstream;


int menu();
int main(int argc, char const *argv[]){
	//Editorial editoriales[30];
	int seleccionMenu;
	bool headerExists = false;
	bool repeat = true;
	ifstream infileLibros("libros.bin",ios::binary);
	ifstream infileIndex("index.bin",ios::binary);
	Header tempHeader;
	infileLibros.seekg(0);
	infileLibros.read(reinterpret_cast<char*>(&tempHeader), sizeof(Header));
	
	if ((infileLibros.good() && !infileIndex.good()) 
		|| (infileLibros.good() && infileIndex.good() && tempHeader.getDirty())){
		vector<char*> PrimaryKeys;
		vector<long int> offsets;
		char tempKey[14];
		int DIF = 9;
		infileLibros.seekg(sizeof(Header));
		Libro libroTemp;
		long int contadorPos = 0;
		while (!infileLibros.eof()){
			infileLibros.read(reinterpret_cast<char*>(&libroTemp), sizeof(Libro));

			if (!infileLibros.eof()){
				if(libroTemp.getISBN()[7] == '-'){
					for (int i = 0; i < 14; ++i){
						tempKey[i] = libroTemp.getISBN()[i + DIF];
					}
					PrimaryKeys.push_back(new char[14]);
					strcpy(PrimaryKeys.at(PrimaryKeys.size()-1), tempKey);
					offsets.push_back(contadorPos*sizeof(Libro) + sizeof(Header));
					contadorPos++;

				}else{
					contadorPos++;
				}
			}
			
			vector<indexFile*> newIndex; 
			//indexFile* tempRegistry;
			for (int i = 0; i < PrimaryKeys.size(); ++i){
				newIndex.push_back(new indexFile(PrimaryKeys.at(i), offsets.at(i)));
				//delete tempRegistry;

				//char stringTemp[14];
				//strcpy(stringTemp,PrimaryKeys.at(i));
				//indexFile tempRegistry(stringTemp,offsets.at(i));
				//newIndex.push_back(tempRegistry);
			}
			ofstream index("index.bin",ios::binary| ios::trunc | ios::out);
			for (int i = 0; i < newIndex.size(); ++i){
				index.write(reinterpret_cast<char*>(&newIndex.at(i)), sizeof(indexFile));
			}
			index.close();
			

		}

	}

	infileLibros.close();
	infileIndex.close();

	do {
		seleccionMenu = menu();
		cout<<seleccionMenu<<endl;
		ifstream infile("libros.bin",ios::binary);
		Header header(-1, sizeof(Libro),0,false);
		if (!headerExists){
			if(!infile.good()){
				infile.close();
				ofstream fileWrite("libros.bin",ios::binary| ios::trunc | ios::out);
				//int availList,int sizeOfCampo,int RecordCount,bool DirtyBit
				//fileWrite.write(reinterpret_cast<char*>(&header,sizeof(Header)));
				fileWrite.write(reinterpret_cast<char*>(&header),sizeof(Header));
				fileWrite.close();
				headerExists = true;
				
			}else{
				ifstream infile("libros.bin",ios::binary);			
				infile.read(reinterpret_cast<char*>(&header),sizeof(Header));
				infile.close();
				headerExists = true;
			}
		}

		if(seleccionMenu==1){
			char defaultAvail[] = "0000000-1";
			char ISBN [23];
			char ISBNTemp[14];
			char Nombre[76];
			char Autor[76];
			unsigned int editorialID;
			getchar();
			cout<<"Porfavor ingrese el ISBN del libro: ";
			cin.getline(ISBNTemp,14);
			strcpy(ISBN,defaultAvail);
			strcat(ISBN,ISBNTemp);
			cout<<endl;
			cout<<"Porfavor ingrese el nombre del libro: ";
			cin.getline(Nombre,76);
			cout<<endl;
			cout<<"Porfavor ingrese el nombre del autor del libro: ";
			cin.getline(Autor,76);
			cout<<endl;
			cout<<"porfavor ingrese un ID: ";
			cin>>editorialID;
			Libro libroTemp(ISBN,Nombre,Autor,editorialID);


			if (header.getAvailList()==-1){
				ofstream outfile("libros.bin",ios::binary | ios::app | ios::ate);
				outfile.write(reinterpret_cast<char*>(&libroTemp),sizeof(Libro));
				outfile.close();
				header.setRecordCount(header.getRecordCount()+1);
				header.setDirty(true);

			}else{
				long int offset = (header.getAvailList()*sizeof(Libro)) + sizeof(Header);
				streampos pos = offset;
				ifstream infile("libros.bin", ios::binary);
				infile.seekg(pos);
				Libro temp;
				infile.read(reinterpret_cast<char*>(&temp),sizeof(Libro));
				char deletedISBN[23];
				strcpy(deletedISBN,temp.getISBN());
				char newposition[7];

				int contador = 0;
				int contadorAsterisco = 0;
				int debug;
				while(contadorAsterisco<2){
					if(deletedISBN[contador]=='*'){
						contadorAsterisco++;
					}else{
						if(contador==1){
							newposition[0] = deletedISBN[contador+1];
						}else{
							newposition[contador+1] = deletedISBN[contador];
						}
					}
				}
				//long int nuevoElementoAvail = static_cast<long int>(&newposition);
				long int nuevoElementoAvail = (long int) newposition;
				header.setAvailList(nuevoElementoAvail);

				ofstream outfile("libros.bin", ios::binary);
				outfile.seekp(pos);
				outfile.write(reinterpret_cast<char*>(&libroTemp), sizeof(Libro));
				outfile.close();
				header.setDirty(true);
				header.setRecordCount(header.getRecordCount() +1 );

				
			}
				
		
		}else if(seleccionMenu==2){
			ifstream infile("libros.bin",ios::binary);
			Libro libro;
			infile.seekg(sizeof(Header));
			while(!infile.eof()){
				char actualISBN[23];
				char ISBNfinal[14];
				int contadorFinal=0;
				int contadorAsterisco=0;
				

				infile.read(reinterpret_cast<char*>(&libro),sizeof(Libro));	
				strcpy(actualISBN,libro.getISBN());

				if (actualISBN[0] == '*'){
					for (int i = 0; i < strlen(actualISBN); ++i){
						if(actualISBN[i] == '*'){
							contadorAsterisco++;
						}
						if(contadorAsterisco == 2){
							ISBNfinal[contadorFinal] = actualISBN[i];
							contadorFinal++;
						}
					}
				}
				char ISBNToShow[14];
				int contadorToShow=0;
				if(ISBNfinal[7] == '-'){
					
					for (int i = 0; i < strlen(ISBNfinal); ++i){
						if (i>1){
							ISBNToShow[contadorToShow] = ISBNfinal[i];
							contadorToShow++;
						}
					}
					ISBNToShow[contadorToShow] = '\0';
					int contador = 0;
					if (!infile.eof() && actualISBN[0] != '*'){
						contador++;
						cout<<endl;
						cout<<contador<<": ";
						cout<<ISBNToShow<<endl;
						cout<<libro.getNombre()<<endl;
						cout<<libro.getAutor()<<endl;
						cout<<libro.getEditorialID()<<endl<<endl;
					}

				}else{
					char ISBNToShow[14];
					int contadorshow = 0;
					for (int i = 0; i < strlen(libro.getISBN()); ++i){
						if (i>8){
							ISBNToShow[contadorshow] = libro.getISBN()[i];
							contadorshow++;
						}
					}
					int contador = 0;
					if (!infile.eof() && actualISBN[0] != '*'){
						contador++;
						cout<<contador<<": ";
						cout<<ISBNToShow<<endl;
						cout<<libro.getNombre()<<endl;
						cout<<libro.getAutor()<<endl;
						cout<<libro.getEditorialID()<<endl;
					}

				}

					
			}
			infile.close();
			
			

		}else if (seleccionMenu==3){

			//Modificar





		}else if (seleccionMenu==4){


		}else if (seleccionMenu == 5){
			streampos begin, end;
			ifstream infile("libros.bin", std::ifstream::binary);
			begin = infile.tellg();
			infile.seekg(0,ios::end);
			end = infile.tellg();
			infile.close();
			if(end-begin<=1){
				cout<<"El tamaño del archivo es de : "<<end-begin<<" byte"<<endl;
			}else{
				cout<<"El tamaño del archivo es de : "<<end-begin<<" bytes"<<endl;
			}
			
		}else if(seleccionMenu == 6){
			if (header.getDirty()){
				ofstream outfile("libros.bin",ios::binary);
				outfile.seekp(0);
				outfile.write(reinterpret_cast<char*>(&header),sizeof(Header));
				outfile.close();
			}
			repeat = false;
		}

	}while (repeat);		
		
	return 0;
	
}


int menu(){
	int seleccion;
	do{
		cout<<"1)Escribir en el archivo"<<endl;
		cout<<"2)Listar registros"<<endl;
		cout<<"3)Modificar un registro"<<endl;
		cout<<"4)Eliminar un registro"<<endl;
		cout<<"5)Obtener el tamaño del archivo (opcion de desarrollo)"<<endl;
		cout<<"6)Salir"<<endl;
		cout<<"Porfavor haga su eleccion:";
		cin>>seleccion;
		cout<<endl;
		if(seleccion>6 || seleccion<1){
			cout<<"Porfavor ingrese un numero valido"<<endl;
		}
	}while(seleccion>6 || seleccion<1);
	return seleccion;
}

