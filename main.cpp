#include <iostream>
using namespace std;

#include "Libro.hpp"
#include "Header.hpp"
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
			char defaultAvail[] = "-1";
			char ISBN [14];
			char ISBNTemp[23];
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

			}else{
				long int offset = (header.getAvailList()*sizeof(Libro)) + sizeof(Header);
				streampos pos = offset;
				ifstream infile = ("libros.bin", ios::binary);
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
							newposition+= deletedISBN[contador];
						}
					}
				}
				long int nuevoElementoAvail = static_cast<long int>(&newposition);
				header.setAvailList(nuevoElementoAvail);

				ofstream outfile("libros.bin", ios::binary);
				outfile.seekp(pos);
				outfile.write(reinterpret_cast<char*>(&libroTemp), sizeof(Libro));
				outfile.close();
				
			}
				
		
		}else if(seleccionMenu==2){
			ifstream infile("libros.bin",std::ifstream::binary);
			Libro libro;

			while(!infile.eof()){
				infile.read(reinterpret_cast<char*>(&libro),sizeof(Libro));	
				int contador = 0;
				if (!infile.eof()){
					contador++;
					cout<<contador<<": ";
					cout<<libro.getISBN()<<endl;
					cout<<libro.getNombre()<<endl;
					cout<<libro.getAutor()<<endl;
					cout<<libro.getEditorialID()<<endl;
				}
			}
			infile.close();
			
			

		}else if (seleccionMenu==3){


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
			
		}

	}while (seleccionMenu!=6);	
		
	return 0;
}


int menu(){
	int seleccion;
	do{
		cout<<"1)Escribir en un archivo"<<endl;
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

