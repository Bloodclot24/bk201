#ifndef PERSISTIDOR_H_
#define PERSISTIDOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include "../Componente/Componente.h"
#include "../XML/Xml.h"

class Persistidor
{
	private:
		std::string nombre;
		//std::string ruta;
		std::string extension;
		std::fstream archivo;
	public:
		Persistidor(std::string nombre){
			this->nombre = nombre;
			//TODO: definir la ruta...
			//this->ruta = "";
			this->extension = ".bk";
			//Creo el archivo donde voy a guardar los datos del circuito
			this->archivo.open(/*ruta+*/nombre+extension, std::fstream out);
			if(!archivo.good()) std::cerr << "Se produjo un error al crear el archivo: " << nombre+extension << std::endl;
			this->archivo.close();
		};
		
		void persistir(Circuito* circuito){
			if(circuito){
				archivo.open(/*ruta+*/nombre+extension,std::fstream::in | std::fstream::out);
				if(archivo.good()){
					//TODO
					//Guardar los componenetes en el archivo
					
					//Creo el archivo, establezco la raiz con sus propiedades
					Xml xml(circuito->nombre.c_str());
					xml.getRaiz()->setPropiedad("entradas",circuito->getCantidadEntradas());
					xml.getRaiz()->setPropiedad("salidas",circuito->getCantidadSalidas());
					//Serializo los componentes del circuito
					//TODO ver que pasa si el componente es un circuito y no
					//una compuerta
					for(int i = 0; i < circuito->getComponentes().size(); i++){
						Componente* comp = circuito->getComponentes()[i];
						XmlNodo componente(comp, "");
						componente.setPropiedad("x",comp->getX());
						componente.setPropiedad("y",comp->getY());
						componente.setPropiedad("alfa", comp->getAlfa());
						componente.setPropiedad("label",comp->getLabel());
						componente.setPropiedad("tr",comp->getTiempoRetardo());
						xml.getRaiz()->agregarHijo(componente);
					}
					
					//TODO ver tema de las lineas que conforman la conexion
					//Serializo las conexiones
					for(int i = 0; i < circuito->getConexiones().size(); i++){
						Conexion* conex = circuito->getConexiones()[i];
						XmlNodo conexion(conex,"");
						
					} 
						
				}else std::cerr << "No se pudo abrir el archivo: " << nombre+extension << std::endl;
				archivo.close();
			}
		};
		
		Circuito* recuperar(std::string nombreArchivo){
			archivo.open(/*ruta+*/nombreArchivo+extensio, std::fstream::in);
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

