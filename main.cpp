#include <iostream>
using namespace std;

#include "Libro.hpp"
#include "Header.hpp"
#include "indexFile.hpp"
#include "Editorial.hpp"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <cstring>

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstdlib>

#include <cstdio>
using std::rename;

#include <ctime>


int menu();
void crearIndice();
int main(int argc, char const *argv[]){
	//Editorial editoriales[30];
	int seleccionMenu;
	bool headerExists = false;
	bool repeat = true;
	bool headerDirty = false;
	bool dirtyHeader = false;
	bool indexExists = false;
	Header header(-1, sizeof(Libro),0,false);
	bool noWrite = false;
	//editorialID nombre Direccion

	//creating index, attempt 2
	ifstream infileLibros("libros.bin",ios::binary);
	ifstream infileIndex("index.bin",ios::binary);
	ifstream infileEditorial("editoriales.bin", ios::binary | ios::in);
	Header jader;
	int aHierro = 0;
	char nombreEditoriales[21][25] = {"Alfaguara", "Algaida", "Almadraba", "Algar", "Almuzara",
	 "Anaya", "Apila","Buen Paso","Bambu","Berenice",
	 "Barcanova","Brosquil","Casals","Bromera",
	 "Coco Books","ComaNegra","Creagem","Edebe","Edelvives","Destino"};
	char direccionEditoriales[21][25] = {"La Canoa","Puerto Rico","Las Hadas","Las Uvas","Villa Olimpica",
	"Kennedy","Kansas","California","Romania","Grecia",
	"Francia","Alemania","Los Tostones","Mexico","Canada",
	"China","Portugal","Chile","Colombia","Venezuela"};

	if(!infileEditorial.good()){
		infileEditorial.close();
		ofstream edit("editoriales.bin", ios::binary| ios::out | ios::trunc);
		Editorial* editor;
		for (int i = 1; i < 21; ++i){
				editor = new Editorial(i,nombreEditoriales[i],direccionEditoriales[i]);
				edit.write(reinterpret_cast<char*>(&editor), sizeof(Editorial));
				delete editor;
		}
		edit.close();
	}else{
		infileEditorial.close();
	}










	if (infileLibros.good()){
		infileLibros.seekg(0);
		infileLibros.read(reinterpret_cast<char*>(&jader), sizeof(Header));
		dirtyHeader = jader.getDirty();
		if (dirtyHeader == true){
			aHierro = 1;
		}
	}

	infileLibros.close();
	infileIndex.close();

	if (aHierro == 1){
		cout<<"Creando Index..."<<endl;
		ifstream Registry("libros.bin", ios::binary);
		Registry.seekg(sizeof(Header));
		Libro bookTemp;
		vector<char*> keys;
		vector<long int> offsets;
		int contadorRegistros= 0;

		while(!Registry.eof()){
			Registry.read(reinterpret_cast<char*>(&bookTemp),sizeof(Libro));
			if(!Registry.eof()){
				if(!bookTemp.getDeleted()){
					keys.push_back(new char[14]);
					char finalKey[14] ;
					for (int i = 0; i < 13; ++i){
						finalKey[i] = bookTemp.getISBN()[i+9];
					}
					finalKey[14] = '\0';
					strcpy(keys.at(keys.size()-1),finalKey);
					offsets.push_back(contadorRegistros*sizeof(Libro) + sizeof(header));
					contadorRegistros++;

					}else{
						contadorRegistros++;
					}
				}
					
		}
	

		vector<indexFile*> newRegistros;

		for (int i = 0; i < keys.size(); ++i){
			newRegistros.push_back(new indexFile(keys.at(i),offsets.at(i)));
		}

		//ORDENANDO LA LISTA DE newRegistros
		long int key1;
		long int key2;
		char keyTemp[14];
		long int offsetTemp;
		bool isI;
		bool isJ;
		indexFile indexTemp;
		vector<int> erasedPos;
		if(newRegistros.size()>1){
			for (int i = 0; i < newRegistros.size()-1; ++i){
				for (int j = 1; j < newRegistros.size(); ++j){
						
					key1 = atol(newRegistros.at(i)->getLlave());
					key2 = atol(newRegistros.at(j)->getLlave());

					if(key2<key1){
						//indexTemp = *newRegistros.at(i);
						//newRegistros.at(i) = newRegistros.at(j);
						//&newRegistros.at(j) = indexTemp;
						strcpy(keyTemp,newRegistros.at(i)->getLlave());
						//cout<<"Este es el KeyTemp: "<<keyTemp<<endl;
						offsetTemp = newRegistros.at(i)->getOffset();
						//cout<<"Este es su offset: "<<offsetTemp<<endl;
						delete newRegistros.at(i);
						newRegistros.at(i) = new indexFile(newRegistros.at(j)->getLlave(),newRegistros.at(j)->getOffset());
						delete newRegistros.at(j);
						newRegistros.at(j) = new indexFile(keyTemp,offsetTemp);






						/*
						isI = false;
						isJ = false;
						for (int k = 0; k < erasedPos.size(); ++k){
							if(i == erasedPos.at(k)){
								isI = true;
								break;
							}
						}
						for (int k = 0; k < erasedPos.size(); ++k){
							if(j == erasedPos.at(k)){
								isJ = true;
								break;
							}
						}

						if(!isI){
							erasedPos.push_back(i);
						}
						if(!isJ){
							erasedPos.push_back(j);
						}
						*/
					}
				}	
			}
		}


		ofstream indice("index.bin",ios::binary| ios::trunc | ios::out);
		for (int i = 0; i < newRegistros.size(); ++i){
			indice.write(reinterpret_cast<char*>(newRegistros.at(i)),sizeof(indexFile));
		}
		indice.close();

		for (int i = 0; i < keys.size(); ++i){
			delete keys.at(i);
		}
		//bool deleteR;
		//for (int i = 0; i < newRegistros.size(); ++i){
			/*deleteR = true;
			for (int j = 0; j < erasedPos.size(); ++j){
				if(i == erasedPos.at(j)){
					deleteR = false;
					break;
				}
			}
			if(deleteR){
				delete newRegistros.at(i);
			}
			*/
		//	delete newRegistros.at(i);
		//}
			for (int i = 0; i < newRegistros.size(); ++i){
				delete newRegistros.at(i);
			}




	}

	bool RealDirty = false;
	int contadorAle = 0;

	do {

		ifstream ifstreamer("libros.bin", ios::binary | ios::in);
		Header temptemptemp;
		ifstreamer.seekg(0);
		ifstreamer.read(reinterpret_cast<char*>(&temptemptemp), sizeof(Header));
		ifstreamer.close();
		cout<<"Avail List = "<<temptemptemp.getAvailList()<<endl;

		seleccionMenu = menu();
		cout<<seleccionMenu<<endl;
		ifstream infile("libros.bin",ios::binary);
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
			contadorAle++;
			char defaultAvail[] = "0000000-1";
			char ISBN [23];
			char ISBNTemp[14];
			char Nombre[76];
			char Autor[76];
			unsigned int editorialID;
			cin.ignore();
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
			cout<<"porfavor ingrese un ID (1 - 20) : ";
			cin>>editorialID;
			Libro libroTemp(ISBN,Nombre,Autor,editorialID);
			Header Heather;

			ifstream heath("libros.bin", ios::binary | ios::in);
			heath.seekg(0);
			heath.read(reinterpret_cast<char*>(&Heather), sizeof(Header));
			heath.close();




			if (Heather.getAvailList()==-1){
				ofstream outfile("libros.bin",ios::binary | ios::app | ios::ate);
				outfile.write(reinterpret_cast<char*>(&libroTemp),sizeof(Libro));
				outfile.close();
				header.setRecordCount(header.getRecordCount()+1);
				headerDirty = true;
				RealDirty = true;

			}else{
				long int offset = Heather.getAvailList();
				long int nextOffset;
				ifstream readFile("libros.bin", ios::binary | ios::in);
				Libro Book;
				readFile.seekg(offset);
				readFile.read(reinterpret_cast<char*>(&Book), sizeof(Libro));
				readFile.close();
				nextOffset = Book.getAvail();


				fstream outfile("libros.bin", ios::binary | ios::in | ios::out);
				outfile.seekp(offset);
				outfile.write(reinterpret_cast<char*>(&libroTemp), sizeof(Libro));

				Heather.setAvailList(nextOffset);
				outfile.seekp(0);
				outfile.write(reinterpret_cast<char*>(&Heather), sizeof(Header));
				outfile.close();


				header.setRecordCount(header.getRecordCount()+1);
				headerDirty = true;
				RealDirty = true;






				/*
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

				fstream outfile("libros.bin", ios::binary | ios::out | ios::in);
				outfile.seekp(pos);
				outfile.write(reinterpret_cast<char*>(&libroTemp), sizeof(Libro));
				outfile.close();
				headerDirty = true;
				header.setRecordCount(header.getRecordCount()+1);
				RealDirty = true;
				*/

				
			}

				
		
		}else if(seleccionMenu==2){
			ifstream infile("libros.bin",ios::binary);
			Libro libro;
			infile.seekg(sizeof(Header));
			int contador = 0;
			while(!infile.eof()){
				char actualISBN[23];
				char ISBNfinal[14];
				int contadorFinal=0;
				int contadorAsterisco=0;
				

				infile.read(reinterpret_cast<char*>(&libro),sizeof(Libro));	
				strcpy(actualISBN,libro.getISBN());

				/*if (actualISBN[0] == '*'){
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
				*/
				char ISBNToShow[14];
				int contadorToShow=0;
				if(ISBNfinal[7] == '-'){
					for (int i = 0; i < 14; ++i){
						ISBNToShow[i] = libro.getISBN()[i+9];
					}
					ISBNToShow[14] = '\0';
					
					
					if (!infile.eof() && libro.getMark() != '*'){
						contador++;
						cout<<endl;
						cout<<contador<<": ";
						cout<< "ISBN: "<<ISBNToShow<<endl;
						cout<<"Nombre del Libro: "<<libro.getNombre()<<endl;
						cout<<"Autor: "<<libro.getAutor()<<endl;
						cout<<"ID Editorial: "<<libro.getEditorialID()<<endl<<endl;

					}

				}else{
					char ISBNToShow[14];
					int contadorshow = 0;
					/*
					for (int i = 0; i < strlen(libro.getISBN()); ++i){
						if (i>8){
							ISBNToShow[contadorshow] = libro.getISBN()[i];
							contadorshow++;
						}
					}
					*/
					for (int i = 0; i < 14; ++i){
						ISBNToShow[i] = libro.getISBN()[i+9];
					}
					ISBNToShow[14] = '\0';
					if (!infile.eof() && libro.getMark() != '*'){
						contador++;
						cout<<contador<<": ";
						cout<< "ISBN: "<<ISBNToShow<<endl;
						cout<<"Nombre del Libro: "<<libro.getNombre()<<endl;
						cout<<"Autor: "<<libro.getAutor()<<endl;
						cout<<"ID Editorial: "<<libro.getEditorialID()<<endl<<endl;
					}

				}

					
			}
			infile.close();
			
			

		}/*else if (seleccionMenu==3){

			//Modificar
			char busquedaLibro[14];
			cout<<endl<<"Porfavor ingrese el ISBN del libro que desea modificar: ";
			cin.ignore();
			cin.getline(busquedaLibro,14);
			cout<<endl;
			ifstream index("index.bin",ios::binary|ios::in);
			indexFile indexTemp;
			long int offset;
			bool found = false;
			while(!index.eof()){
				index.read(reinterpret_cast<char*>(&indexTemp),sizeof(indexFile));
				if(!index.eof()){
					if(strcmp(busquedaLibro,indexTemp.getLlave()) == 0){
						cout<<"Se encontro el Libro: "<<endl;
						offset = indexTemp.getOffset();
						found = true;
						break;
					}
				}
			}
			index.close();

			if(found){
				Libro actual;
				ifstream libroFile("libros.bin", ios::binary | ios::in);
				libroFile.seekg(offset);
				libroFile.read(reinterpret_cast<char*>(&actual), sizeof(Libro));
				char toShow[14];
				int eleccionMod;
				for (int i = 0; i < 14; ++i){
					toShow[i] = actual.getISBN()[i+9];
				}
				toShow[14] = '\0';

				cout<< "ISBN: "<<toShow<<endl;
				cout<<"Nombre del Libro: "<<actual.getNombre()<<endl;
				cout<<"Autor: "<<actual.getAutor()<<endl;
				cout<<"ID Editorial: "<<actual.getEditorialID()<<endl<<endl;

				cout<<"Desea cambiar el ISBN junto a los otros datos? "<<endl;
				cout<<"1) Si"<<endl;
				cout<<"2) No"<<endl;
				cin>>eleccionMod;
				if(eleccionMod == 1){
					char ISBNTemp[14];
					char TempNombre[76];
					char TempAutor[76];
					unsigned int TempEditorial;
					cin.ignore();
					cout<<"Porfavor ingrese el ISBN del libro: ";
					cin.getline(ISBNTemp,14);
					char temptemp[23];
					strcpy(temptemp, actual.getISBN());
					for (int i = 0; i < 14; ++i){
						temptemp[i+9] = ISBNTemp[i];
					}
					actual.setISBN(temptemp);
					cout<<endl;
					cout<<"Porfavor ingrese el nombre del libro: ";
					cin.getline(TempNombre,76);
					cout<<endl;
					cout<<"Porfavor ingrese el nombre del autor del libro: ";
					cin.getline(TempAutor,76);
					cout<<endl;
					cout<<"porfavor ingrese un ID: ";
					cin>>TempEditorial;
					actual.setNombre(TempNombre);
					actual.setAutor(TempAutor);
					actual.setEditorialID(TempEditorial);

					fstream bookMod("libros.bin", ios::binary | ios::in | ios::out);
					bookMod.seekp(offset);
					bookMod.write(reinterpret_cast<char*>(&actual), sizeof(Libro));
					bookMod.close();
					headerDirty = true;
				}else{
					char TempNombre[76];
					char TempAutor[76];
					unsigned int TempEditorial;
					cin.ignore();
					cout<<endl;
					cout<<"Porfavor ingrese el nombre del libro: ";
					cin.getline(TempNombre,76);
					cout<<endl;
					cout<<"Porfavor ingrese el nombre del autor del libro: ";
					cin.getline(TempAutor,76);
					cout<<endl;
					cout<<"porfavor ingrese un ID: ";
					cin>>TempEditorial;
					actual.setNombre(TempNombre);
					actual.setAutor(TempAutor);
					actual.setEditorialID(TempEditorial);
					cout<<"temp editorial: "<<actual.getEditorialID()<<endl;

					fstream bookMod("libros.bin", ios::binary | ios::in | ios::out);
					bookMod.seekp(offset);
					bookMod.write(reinterpret_cast<char*>(&actual), sizeof(Libro));
					bookMod.close();
				}
			}else{
				cout<<"Lo siento no pude encontrar ese libro :( "<<endl;
			}

		}*/else if (seleccionMenu==3){
			crearIndice();
			

			char busquedaLibro[14];
			cout<<endl<<"Porfavor ingrese el ISBN del libro que desea eliminar: ";
			cin.ignore();
			cin.getline(busquedaLibro,14);
			long int offset;
			bool found = false;
			cout<<endl;
			indexFile indexTemp1;
			ifstream indexito("index.bin", ios::binary | ios::in);
			
		
			while(!indexito.eof()){
				indexito.read(reinterpret_cast<char*>(&indexTemp1),sizeof(indexFile));
				if(!indexito.eof()){
					if(strcmp(busquedaLibro,indexTemp1.getLlave()) == 0){
						cout<<"Se encontro el Libro: "<<endl;
						offset = indexTemp1.getOffset();
						found = true;
						break;
					}
				}
			}
			indexito.close();
			if (found){
				int erase;
				Libro actual;
				ifstream libroFile("libros.bin", ios::binary | ios::in);
				libroFile.seekg(offset);
				libroFile.read(reinterpret_cast<char*>(&actual), sizeof(Libro));
				libroFile.close();
				char toShow[14];
				int eleccionMod;
				for (int i = 0; i < 14; ++i){
					toShow[i] = actual.getISBN()[i+9];
				}
				toShow[14] = '\0';

				cout<< "ISBN: "<<toShow<<endl;
				cout<<"Nombre del Libro: "<<actual.getNombre()<<endl;
				cout<<"Autor: "<<actual.getAutor()<<endl;
				cout<<"ID Editorial: "<<actual.getEditorialID()<<endl<<endl;

				cout<<endl<<"De verdad quiere borrar este libro?"<<endl;
				cout<<"1) SI"<<endl;
				cout<<"2) NO"<<endl;
				cin >> erase;
				cin.ignore();

				if(erase == 1){
					

					Header headercito;
					ifstream MaxHeader("libros.bin" , ios::binary | ios::in);
					MaxHeader.read(reinterpret_cast<char*>(&headercito), sizeof(Header));
					if (headercito.getAvailList() == -1){

						headercito.setAvailList(offset);
						actual.setAvail(-1);
					}else{
						actual.setAvail(headercito.getAvailList());
						headercito.setAvailList(offset);
					}
					MaxHeader.close();

					fstream borrar("libros.bin", ios::binary| ios::in | ios::out);
					borrar.seekg(0);
					borrar.write(reinterpret_cast<char*>(&headercito), sizeof(Header));
					borrar.seekg(offset);
					actual.setDeleted(true);
					actual.setMark('*');
					borrar.write(reinterpret_cast<char*>(&actual), sizeof(Libro));
					borrar.flush();
					borrar.close();
					headerDirty = true;
				}


			}
			noWrite = true;

	

		}else if (seleccionMenu == 4){
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
			



		}/*else if(seleccionMenu == 6){
			ifstream infile("index.bin", ios::binary);
			indexFile index;
			if(infile.good()){
				while(!infile.eof()){
					infile.read(reinterpret_cast<char*>(&index), sizeof(indexFile));
					if(!infile.eof()){
						cout<<endl<<"Esta es la llave: "<<index.getLlave()<<endl;
						cout<<"este es el offset: "<<index.getOffset()<<endl;
					}	
				}
				cout<<endl;
			}else{
				cout<<"no hay index/ el index esta corrupto"<<endl;
			
			}
			infile.close();


		}*/
		else if(seleccionMenu == 5){
			Libro temp;
			ofstream compact("libros2.bin", ios::binary | ios::out | ios::trunc);
			compact.write(reinterpret_cast<char*>(&header), sizeof(Header));
			ifstream original("libros.bin", ios::binary | ios::in);
			original.seekg(sizeof(Header));
			compact.seekp(sizeof(Header));
			while (!original.eof()){
				original.read(reinterpret_cast<char*>(&temp), sizeof(Libro));
				if (!original.eof() && !temp.getDeleted()){
					compact.write(reinterpret_cast<char*>(&temp), sizeof(Libro));
				}
			}
			compact.close();
			original.close();
			int successf=remove("libros.bin");
			rename("libros2.bin","libros.bin");
			headerDirty = true;

			
		}else if(seleccionMenu == 6){
			int cantidadAGenerar;
			cout<<"Cuantos Libros desea generar?: ";
			cin>>cantidadAGenerar;
			cout<<endl;


			srand(time(0));
			char PrimerNombre[20][25] = {"The Famous", "The Dead","The Dangerous","The","The Amazing",
			"The Perfect","The Inconvenient","The Terrible","The Sexy","The Scary","The Horrid",
			"The Lovely","The Useless","The Skinny","The Obese","The Animated","The Ambivalent",
			"The Plastic","The Motorized"};

			char SegundoNombre[20][30] = {" Hands"," Spine"," Spoon", " Knife", " Glass", " Spray", " Crime",
			" Dog"," Cat", " Mammal", " Computer", " Key", " Doctor", " Engineer", " Teacher", " Cheese",
			" Beer", " Television", " Cellphone"};

			char autores[20][60] = {"Angelina Jolie", "Brad Pitt", "Channing Tatum", "Edward Norton",
			"Hillary Clinton", "Nicolas Cage", "Robert DeNiro", "Dakota Fanning", "John Travolta", 
			"Katy Perry", "Scarlett Johansson", "Jennifer Lawrence", "Leonardo DiCaprio", "Will Smith","Johnny Depp",
			"Taylor Swift","Kanye West", "Jim Morrison","John Lennon"};
			ofstream lib("libros.bin", ios::binary | ios::out | ios::trunc);
			lib.seekp(0);
			header.setDirty(true);
			lib.write(reinterpret_cast<char*>(&header),sizeof(Header));
			char Titulo[76];
			char Autor [76];
			long int ISBN;
			char app[]="0000000-1";
			char pasar[14];
			char final[23];
			int Editorial;
			for (int i = 0; i < cantidadAGenerar; ++i){
				strcpy(Titulo,PrimerNombre[rand()%19]);
				strcat(Titulo,SegundoNombre[rand()%19]);
				strcpy(Autor,autores[rand()%19]);
				ISBN = 1000000000000+rand()%99999999999999;
				Editorial = 1+rand()%20;
				string s = to_string(ISBN);
				const char* c = s.c_str();
				strcpy(pasar,c);
				strcpy(final,app);
				strcat(final,pasar);
				final[23] = '\0';
				Titulo[strlen(Titulo)] = '\0';
				Autor[strlen(Autor)] = '\0';
				//Libro(char* ISBN,char* Nombre,char* Autor,unsigned int EditorialID);
				Libro libro(final,Titulo,Autor,Editorial);
				lib.write(reinterpret_cast<char*>(&libro),sizeof(Libro));
			}
			lib.close();
			headerDirty = true;




		}else if(seleccionMenu == 7){
			ifstream dirtyRead("libros.bin", ios::binary | ios::in);
			Header coco;
			long int offset;
			bool found = false;
			char busquedaLibro[14];
			dirtyRead.seekg(0);
			dirtyRead.read(reinterpret_cast<char*>(&coco),sizeof(Header));
			dirtyRead.close();

			if (coco.getDirty()){
				crearIndice();
			}
			cin.ignore();
			cout<<"Porfavor ingrese el ISBN del libro que desea buscar: ";
			cin.getline(busquedaLibro,14);
			indexFile inElement;
			ifstream indexRead("index.bin", ios::binary | ios::in);
			
			while(!indexRead.eof() && !found){
				indexRead.read(reinterpret_cast<char*>(&inElement), sizeof(indexFile));
				if(!indexRead.eof()){
					if (strcmp(busquedaLibro, inElement.getLlave()) == 0){
						found = true;
						offset = inElement.getOffset();
					}
				}

			}
			if (found){
				ifstream Adobe("libros.bin" , ios::binary | ios::in);
				Libro Bookito;
				cout<<"Encontre este Libro: "<<endl<<endl;
				Adobe.seekg(offset);
				Adobe.read(reinterpret_cast<char*>(&Bookito), sizeof(Libro));
				char ISBNToShow[14];

				for (int i = 0; i < 14; ++i){
					ISBNToShow[i] = Bookito.getISBN()[i+9];
				}
				cout<<"ISBN "<<ISBNToShow<<endl;
				cout<<"Nombre: "<<Bookito.getNombre()<<endl;
				cout<<"Autor: "<<Bookito.getAutor()<<endl;
				cout<<"ID editorial: "<<Bookito.getEditorialID()<<endl<<endl;

			}else{
				cout<<"Lo siento, no encontre ese libro"<<endl;
			}
			

		}else if(seleccionMenu == 8){

			crearIndice();
			cout<<"Creando Indice......."<<endl;

		}else if(seleccionMenu == 9){
			if (!noWrite){
				Header cabeza;
				ifstream ifs("libros.bin", ios::binary | ios::in);
				ifs.read(reinterpret_cast<char*>(&cabeza), sizeof(Header));
				ifs.close();
				if (headerDirty){



					fstream outfile("libros.bin",ios::binary| ios::out | ios::in);
					outfile.seekp(0);
					cabeza.setDirty(true);
					outfile.write(reinterpret_cast<char*>(&cabeza),sizeof(Header));
					outfile.close();
				}else{
					fstream outfile("libros.bin",ios::binary| ios::out | ios::in);
					outfile.seekp(0);
					cabeza.setDirty(false);
					outfile.write(reinterpret_cast<char*>(&cabeza),sizeof(Header));
					outfile.close();
				}
			}
				
			repeat = false;

		}

	}while (repeat);		
		
	return 0;
	
}



int menu(){
	int seleccion;
	do{
		cout<<endl;
		cout<<"1)Escribir en el archivo"<<endl;
		cout<<"2)Listar registros"<<endl;
		cout<<"3)Eliminar un registro"<<endl;
		cout<<"4)Obtener el tamaño del archivo (opcion de desarrollo)"<<endl;
		cout<<"5)Compactar Archivo"<<endl;
		cout<<"6)Generar Libros"<<endl;
		cout<<"7)Busqueda usando ISBN"<<endl;
		cout<<"8)Crear indice"<<endl;
		cout<<"9)Salir"<<endl;
		cout<<"Porfavor haga su eleccion:";
		cin>>seleccion;
		cout<<endl;
		if(seleccion>9 || seleccion<1){
			cout<<"Porfavor ingrese un numero valido"<<endl;
		}
	}while(seleccion>9 || seleccion<1);
	return seleccion;
}

void crearIndice(){
	ifstream Registry("libros.bin", ios::binary);
	Registry.seekg(sizeof(Header));
	Libro bookTemp;
	vector<char*> keys;
	vector<long int> offsets;
	int contadorRegistros= 0;

	while(!Registry.eof()){
		Registry.read(reinterpret_cast<char*>(&bookTemp),sizeof(Libro));
		if(!Registry.eof()){
			if(!bookTemp.getDeleted()){
				keys.push_back(new char[14]);
				char finalKey[14] ;
				for (int i = 0; i < 13; ++i){
					finalKey[i] = bookTemp.getISBN()[i+9];
				}
				finalKey[14] = '\0';
				strcpy(keys.at(keys.size()-1),finalKey);
				offsets.push_back(contadorRegistros*sizeof(Libro) + sizeof(Header));
				contadorRegistros++;

				}else{
					contadorRegistros++;
				}
			}
				
	}


	vector<indexFile*> newRegistros;

	for (int i = 0; i < keys.size(); ++i){
		newRegistros.push_back(new indexFile(keys.at(i),offsets.at(i)));
	}

	//ORDENANDO LA LISTA DE newRegistros
	long int key1;
	long int key2;
	char keyTemp[14];
	long int offsetTemp;
	bool isI;
	bool isJ;
	indexFile indexTemp;
	vector<int> erasedPos;
	if(newRegistros.size()>1){
		for (int i = 0; i < newRegistros.size()-1; ++i){
			for (int j = 1; j < newRegistros.size(); ++j){
					
				key1 = atol(newRegistros.at(i)->getLlave());
				key2 = atol(newRegistros.at(j)->getLlave());

				if(key2<key1){
					//indexTemp = *newRegistros.at(i);
					//newRegistros.at(i) = newRegistros.at(j);
					//&newRegistros.at(j) = indexTemp;
					strcpy(keyTemp,newRegistros.at(i)->getLlave());
					//cout<<"Este es el KeyTemp: "<<keyTemp<<endl;
					offsetTemp = newRegistros.at(i)->getOffset();
					//cout<<"Este es su offset: "<<offsetTemp<<endl;
					delete newRegistros.at(i);
					newRegistros.at(i) = new indexFile(newRegistros.at(j)->getLlave(),newRegistros.at(j)->getOffset());
					delete newRegistros.at(j);
					newRegistros.at(j) = new indexFile(keyTemp,offsetTemp);

				}
			}	
		}
	}


	ofstream indice("index.bin",ios::binary| ios::trunc | ios::out);
	for (int i = 0; i < newRegistros.size(); ++i){
		indice.write(reinterpret_cast<char*>(newRegistros.at(i)),sizeof(indexFile));
	}
	indice.close();

	for (int i = 0; i < keys.size(); ++i){
		delete keys.at(i);
	}
	
	for (int i = 0; i < newRegistros.size(); ++i){
		delete newRegistros.at(i);
	}
}

