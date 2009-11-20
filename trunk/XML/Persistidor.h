#ifndef PERSISTIDOR_H_
#define PERSISTIDOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../Componente/Componente.h"
#include "../XML/Xml.h"
#include "../Util/Util.h"

class Persistidor
{
	private:
		std::string nombre;
		//std::string ruta;
		std::string extension;
		std::fstream archivo;
		std::map<Componente*,int> mapaComponentes;
		std::map<int,Componente*> componentesCargados;
		
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
					for(int i = 0; i < circuito->getComponentes().size(); i++){
						Componente* comp = circuito->getComponentes()[i];
						//guardo el tipo de componente
						XmlNodo componente(comp, "");
						componente.setPropiedad("x",Util::intToString(comp->getX()));
						componente.setPropiedad("y",Util::intToString(comp->getY()));
						componente.setPropiedad("alfa", Util::intToString(comp->getAlfa()));
						componente.setPropiedad("label",Util::intToString(comp->getLabel()));
						//Si es un circuito remoto guardo los datos del servidor
						//en el q se encuentra
						if(comp->getType().compare("Circuito") == 0){
							componente.setPropiedad("Servidor",Util::intToString(comp->getServidor());
							componente.setPropiedad("Puerto",Util::intToString(comp->getPuerto());
							//TODO: ver como se va a obtener el nombre del archivo 
							//en caso de tratarse de un circuito remoto
							componente.setPropiedad("NombreArchivo",Util::intToString( ));
						}else componente.setPropiedad("tr",Util::intToString(comp->getTiempoRetardo()));
						//inserto en el mapa de componentes para mantener el orden en
						//el q son guardados.
						mapaComponentes[comp] = i;
						xml.getRaiz()->agregarHijo(componente);
						
					}
					
					//guardo las conexiones que posee dicho componente
					for(int j = 0; j < circuito->getConexiones().size(); j++){
						Conexion* conex = circuito->getConexiones()[j];
						XmlNodo conexion(conex,"");
						Componente* c1 = conex->getComponente();
						for(int i = 0; i < conex->getComponentes().size(); i++){
							conexion.setPropiedad("c1",Util::intToString(mapaComponentes[c1]));
							conexion.setPropiedad("p1",Util::intToString(conex->getPin1()[i]));
							Componente* c2 = conex->getComponentes()[i];
							conexion.setPropiedad("c2",Util::intToString(mapaComponentes[c2]));
							conexion.setPropiedad("p2",Util::intToString(conex->getPin2()[i]));
						}
							
						xml.getRaiz()->agregarHijo(conexion);
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
			//TODO Armo el circuito y se lo paso al controlador usando la funcion:
			// void pasarCircuito(Circuito* c)
			return NULL;
		};
	
};

#endif /*PERSISTIDOR_H_*/

