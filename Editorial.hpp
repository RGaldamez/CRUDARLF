#pragma once 

class Editorial{
	public:
		Editorial();
		Editorial(unsigned int EditorialID, char* Nombre, char* Direccion);
		~Editorial();
		//Setters
		void setEditorialID(unsigned int EditorialID);
		void setNombre(char* Nombre);
		void setDireccion(char* Direccion);
		//Getters
		const unsigned int getEditorialID();
		const char* getNombre();
		const char* getDireccion();

	private:
		unsigned int EditorialID;
		char Nombre[76];
		char Direccion[76];

};