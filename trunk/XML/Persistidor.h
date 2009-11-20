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
						XmlNodo componente(comp, "");
						//guardo el tipo de componente
						componente.setPropiedad("type", Util::intToString(comp->getType()));
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
				Xml xml(nombreArchivo);
				unsigned entradas = atoi(xml.getRaiz()->getPropiedad("entradas"));
				unsigned salidas = atoi(xml.getRaiz()->getPropiedad("salidas"));
				Circuito* circuito = new Circuito(entradas,salidas);
				XmlNodo componente = xml.getRaiz()->obtenerHijo();
				std::string tipo;
				int indice = 0;
				while(componente.getNombre().compare("Componente") == 0){
						tipo = componente.getPropiedad("type");
						switch(tipo){
							case "and":
										Componente* comp = new GateAnd();
							case "or":
										Componente* comp = new GateOr();
							case "buffer":
										Componente* comp = new GateBuffer();
							case "xor":
										Componente* comp = new GateXor();
							case "not":
										Componente* comp = new GateNot();
							default:
								break; 
							
						}
						//Cargo el map para que al levantar las conexiones
						// sepa a cual de los componentes pertenecen.
						componentesCargados[indice] = comp;
						
						 = componente.getPropiedad("x")
						 = componente.getPropiedad("y");
						 = componente.getPropiedad("alfa");
						 = componente.getPropiedad("label");
						if(tipo.compare("Circuito") == 0){
							std::string servidor = componente.getPropiedad("Servidor");
							std::string puerto = componente.getPropiedad("Puerto");
							Componente* comp = new CircuitoRemoto(servidor,puerto);
							= componente.getPropiedad("NombreArchivo");
						}else = componente.getPropiedad("tr");
						componente = componente.obtenerHermano();
						indice++;
				}
				int c = 0;
				int p = 0;
				while(componente.getNombre().compare("Conexion") == 0){
					c = atoi(componente.getPropiedad("c1"));
					Componente* comp1 = componentesCargados[c];
					p = atoi(componente.getPropiedad("p1");
					c = atoi(componente.getPropiedad("c2"));
					Componente* comp2 = componentesCargados[c];
					p = atoi(componente.getPropiedad("p2");
					componente = componente.obtenerHermano();
				}
						
				
			}else std::cerr << "No se pudo abrir el archivo: " << nombreArchivo+extension << std::endl;
			archivo.close();
			#warning "Devuelvo NULL para que compile" ;
			//TODO Armo el circuito y se lo paso al controlador usando la funcion:
			// void pasarCircuito(Circuito* c)
			return NULL;
		};
	
};

#endif /*PERSISTIDOR_H_*/

