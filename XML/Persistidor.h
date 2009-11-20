#ifndef PERSISTIDOR_H_
#define PERSISTIDOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../Componente/Componente.h"
#include "../XML/Xml.h"
#include "../Util/Util.h"
#include "../Controlador/ControladorVentana.h"

class Persistidor
{
private:
     std::string nombre;
     std::string extension;
     std::ofstream archivo;
     std::map<Componente*,int> mapaComponentes;
     std::map<int,Componente*> componentesCargados;
		
public:
     Persistidor(std::string nombre){
	  this->nombre = nombre;
	  this->extension = ".bk";
	  //Creo el archivo donde voy a guardar los datos del circuito
	  archivo.open((nombre+extension).c_str(), std::fstream::out);
	  if(!archivo.good()) std::cerr << "Se produjo un error al crear el archivo: " << nombre+extension << std::endl;
	  this->archivo.close();
     };
		
     void persistir(ControladorVentana *c){
	  if(c){
	       archivo.open((nombre+extension).c_str(),std::fstream::out | std::fstream::trunc);
	       if(archivo.good()){
		    //TODO
		    //Guardar los componenetes en el archivo
				  
		    //Creo el archivo, establezco la raiz con sus propiedades
		    Xml xml("Circuito");
		    xml.getRaiz()->setPropiedad("entradas",Util::intToString(c->circuito.cantidadEntradas).c_str());
		    xml.getRaiz()->setPropiedad("salidas",Util::intToString(c->circuito.cantidadSalidas).c_str());

		    //Serializo las compuertas del circuito
		    std::map<Dibujo*, DatosCompuerta*>::iterator it = c->compuertas.begin();
		    for(;it != c->compuertas.end(); it++){
			 DatosCompuerta* dc = (*it).second;
			 XmlNodo componente("Compuerta");
			 //guardo el tipo de componente
			 componente.setPropiedad("type", dc->tipo.c_str());
			 componente.setPropiedad("x",Util::intToString(dc->c->getVerticeSupIzq().x).c_str());
			 componente.setPropiedad("y",Util::intToString(dc->c->getVerticeSupIzq().y).c_str());
			 componente.setPropiedad("alfa", Util::intToString(dc->c->getAngulo()).c_str());
			 componente.setPropiedad("label",dc->label.c_str());
			 componente.setPropiedad("tr",Util::intToString(dc->tr).c_str());
			 xml.getRaiz()->agregarHijo(componente);
		    }

		    std::map<Dibujo*, DatosCircuitoRemoto*>::iterator it2 = c->circuitos.begin();
		    for(;it2 != c->circuitos.end(); it2++){
			 DatosCircuitoRemoto * dcr = (*it2).second;
			 XmlNodo componente("CircuitoRemoto");
			 //guardo el tipo de componente
			 componente.setPropiedad("x",Util::intToString(dcr->c->getVerticeSupIzq().x).c_str());
			 componente.setPropiedad("y",Util::intToString(dcr->c->getVerticeSupIzq().y).c_str());
			 componente.setPropiedad("alfa", Util::intToString(dcr->c->getAngulo()).c_str());
			 componente.setPropiedad("label",dcr->label.c_str());
			 componente.setPropiedad("servidor", dcr->servidor.c_str());
			 componente.setPropiedad("puerto", Util::intToString(dcr->puerto).c_str());
			 componente.setPropiedad("nombre", dcr->nombre.c_str());
			 xml.getRaiz()->agregarHijo(componente);
		    }
		    std::string *resultado=xml.toString();
		    archivo.write(resultado->c_str(), resultado->size());
		    delete resultado;
	       }else std::cerr << "No se pudo abrir el archivo: " << nombre+extension << std::endl;
	       archivo.close();
	  }
     };
		
//      Circuito* recuperar(std::string nombreArchivo){
// 	  archivo.open(/*ruta+*/nombreArchivo+extensio, std::fstream::in);
// 	  if(archivo.good()){
// 	       //TODO
// 	       //Leer del archivo y crear el componente con todos
// 	       //sus atributos, volver a crear el circuito guardado
// 	       Xml xml(nombreArchivo);
// 	       unsigned entradas = atoi(xml.getRaiz()->getPropiedad("entradas"));
// 	       unsigned salidas = atoi(xml.getRaiz()->getPropiedad("salidas"));
// 	       Circuito* circuito = new Circuito(entradas,salidas);
// 	       XmlNodo componente = xml.getRaiz()->obtenerHijo();
// 	       std::string tipo;
// 	       int indice = 0;
// 	       while(componente.getNombre().compare("Componente") == 0){
// 		    tipo = componente.getPropiedad("type");
// 		    switch(tipo){
// 		    case "and":
// 			 Componente* comp = new GateAnd();
// 		    case "or":
// 			 Componente* comp = new GateOr();
// 		    case "buffer":
// 			 Componente* comp = new GateBuffer();
// 		    case "xor":
// 			 Componente* comp = new GateXor();
// 		    case "not":
// 			 Componente* comp = new GateNot();
// 		    default:
// 			 break; 
							
// 		    }
// 		    //Cargo el map para que al levantar las conexiones
// 		    // sepa a cual de los componentes pertenecen.
// 		    componentesCargados[indice] = comp;
						
// 		    = componente.getPropiedad("x")
// 			   = componente.getPropiedad("y");
// 		    = componente.getPropiedad("alfa");
// 		    = componente.getPropiedad("label");
// 		    if(tipo.compare("Circuito") == 0){
// 			 std::string servidor = componente.getPropiedad("Servidor");
// 			 std::string puerto = componente.getPropiedad("Puerto");
// 			 Componente* comp = new CircuitoRemoto(servidor,puerto);
// 			 = componente.getPropiedad("NombreArchivo");
// 		    }else = componente.getPropiedad("tr");
// 		    componente = componente.obtenerHermano();
// 		    indice++;
// 	       }
// 	       int c = 0;
// 	       int p = 0;
// 	       while(componente.getNombre().compare("Conexion") == 0){
// 		    c = atoi(componente.getPropiedad("c1"));
// 		    Componente* comp1 = componentesCargados[c];
// 		    p = atoi(componente.getPropiedad("p1");
// 			     c = atoi(componente.getPropiedad("c2"));
// 			     Componente* comp2 = componentesCargados[c];
// 			     p = atoi(componente.getPropiedad("p2");
// 				      componente = componente.obtenerHermano();
// 				      }
						
				
// 			     }else std::cerr << "No se pudo abrir el archivo: " << nombreArchivo+extension << std::endl;
// 		    archivo.close();
// #warning "Devuelvo NULL para que compile" ;
// 		    //TODO Armo el circuito y se lo paso al controlador usando la funcion:
// 		    // void pasarCircuito(Circuito* c)
// 		    return NULL;
// 	       };
	
};

#endif /*PERSISTIDOR_H_*/

