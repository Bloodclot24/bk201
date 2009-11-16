#ifndef PERSISTIDOR_H_
#define PERSISTIDOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include "../Componente/Componente.h"

class Persistidor
{
	private:
		std::string nombre;
		std::string ruta;
		std::string extension;
		std::fstream archivo;
	public:
		Persistidor(std::string nombre){
			this->nombre = nombre;
			//TODO: definir la ruta...
			//this->ruta = "";
			this->extension = ".bk";
			//Creo el archivo donde voy a guardar los datos del circuito
			this->archivo.open(ruta+nombre+extension, std::fstream out);
			if(!archivo.good()) std::cerr << "Se produjo un error al crear el archivo: " << nombre+extension << std::endl;
			this->archivo.close();
		};
		
		void persistir(Componente* componente){
			if(componente){
				archivo.open(ruta+nombre+extension,std::fstream::in | std::fstream::out);
				if(archivo.good()){
					//TODO
					//Guardar los componenetes en el archivo	
				}else std::cerr << "No se pudo abrir el archivo: " << nombre+extension << std::endl;
				archivo.close();
			}
		};
		
		Componente* recuperar(std::string nombreArchivo){
			archivo.open(ruta+nombreArchivo+extensio, std::fstream::in);
			if(archivo.good()){
				//TODO
				//Leer del archivo y crear el componente con todos
				//sus atributos, volver a crear el circuito guardado
				
			}else std::cerr << "No se pudo abrir el archivo: " << nombreArchivo+extension << std::endl;
			archivo.close();
			#warning "Devuelvo NULL para que compile" ;
			return NULL;
		};
	
};

#endif /*PERSISTIDOR_H_*/

