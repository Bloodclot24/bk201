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
     Persistidor(const std::string& nombre){
	  this->nombre=nombre;
	  this->extension = ".bk";
	  if(nombre.substr(nombre.size()-3,3).compare(".bk")!=0)
	       this->nombre+=extension;
	  //Creo el archivo donde voy a guardar los datos del circuito
	  // archivo.open(this->nombre.c_str(), std::fstream::in);
	  // if(!archivo.good()) std::cerr << "Se produjo un error al crear el archivo: " << nombre+extension << std::endl;
	  // this->archivo.close();
     };
		
     void persistir(ControladorVentana *c){
	  if(c){
	       archivo.open(nombre.c_str(),std::fstream::out | std::fstream::trunc);
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
			 if(dc != NULL){
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
		    }
		    
		    std::map<Dibujo*, DatosCircuitoRemoto*>::iterator it2 = c->circuitos.begin();
		    for(;it2 != c->circuitos.end(); it2++){
			 DatosCircuitoRemoto * dcr = (*it2).second;
			 if(dcr != NULL){
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
		    }
		    std::string *resultado=xml.toString();
		    archivo.write(resultado->c_str(), resultado->size());
		    delete resultado;
	       }else std::cerr << "No se pudo abrir el archivo: " << nombre+extension << std::endl;
	       archivo.close();
	  }
     };
		
     void recuperar(ControladorVentana *c){
	  std::ifstream archivo;
	  archivo.open(nombre.c_str(), std::fstream::in);
	  std::cout << "Abro " << nombre << std::endl;
	  if(archivo.good()){
	       std::string buffer, bufferlinea;
	       while(archivo.good()){
		    std::getline(archivo,bufferlinea);
		    buffer+=bufferlinea;
	       }
	       Xml xml(buffer.c_str(), buffer.size());
	       c->circuito.cantidadEntradas = atoi(xml.getRaiz()->getPropiedad("entradas").c_str());
	       c->circuito.cantidadEntradas = atoi(xml.getRaiz()->getPropiedad("salidas").c_str());
	       XmlNodo componente = xml.getRaiz()->obtenerHijo();
	       while(componente.getNombre().size()>0){
		    
		    if(componente.getNombre().compare("Compuerta")==0){
			 DatosCompuerta* dc = c->cargarCompuerta(componente.getPropiedad("type"));
			 Vertice v;
 			 v.x = atoi(componente.getPropiedad("x").c_str());
			 v.y = atoi(componente.getPropiedad("y").c_str());
			 std::cout << "x: " << v.x << " y: " << v.y<< std::endl;
			 dc->c->setVerticeSupIzq(v);
			 dc->c->setAngulo(atoi(componente.getPropiedad("alfa").c_str()));
			 dc->c->setEtiqueta(componente.getPropiedad("label"));
		    }
		    if(componente.getNombre().compare("CircuitoRemoto")==0){
			 DatosCircuitoRemoto* dcr = c->cargarCircuito();
			 Vertice v;
			 v.x = atoi(componente.getPropiedad("x").c_str());
			 v.y = atoi(componente.getPropiedad("y").c_str());
			 dcr->c->setVerticeSupIzq(v);
			 dcr->c->setAngulo(atoi(componente.getPropiedad("alfa").c_str()));
			 dcr->c->setEtiqueta(componente.getPropiedad("label"));
		    }
		    componente = componente.obtenerHermano();
	       }
	       
	  }else std::cerr << "No se pudo abrir el archivo: " << nombre << std::endl;
	  archivo.close();
     };
     
};

#endif /*PERSISTIDOR_H_*/
