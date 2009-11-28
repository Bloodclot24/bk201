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
#include "../Vista/Dibujos/Conexion.h"

/** 
 * Clase que se utiliza para guardar/cargar el estado del modelo en
 * disco
 */
class Persistidor{
private:
     std::string nombre;
     std::string extension;
     std::ofstream archivo;
     std::map<Componente*,int> mapaComponentes;
     std::map<int,Componente*> componentesCargados;
		
public:
     /** 
      * Crea un persistidor y le asocia un nombre de archivo.
      * 
      * @param nombre El nombre del archivo.
      */
     Persistidor(const std::string& nombre){
	  this->nombre=nombre;
	  this->extension = ".bk";
	  /* Si no tiene la extension se la agrego */
	  if(nombre.size()>3 && nombre.substr(nombre.size()-3,3).compare(".bk")!=0)
	       this->nombre+=extension;
     };
		
     void persistir(ControladorVentana *c){
	  if(c){
	       /* abro el archivo */
	       archivo.open(nombre.c_str(),std::fstream::out | std::fstream::trunc);
	       if(archivo.good()){
				  
		    //Creo el archivo, establezco la raiz con sus propiedades
		    Xml xml("Circuito");
		    int entradas=0,salidas=0;

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
			      componente.setPropiedad("alfa",Util::intToString(dc->c->getAngulo()).c_str());
			      componente.setPropiedad("label",(dc->c->getLabel()).c_str());
			      componente.setPropiedad("tr",(dc->c->getTiempoT()).c_str());
			      xml.getRaiz()->agregarHijo(componente);
			 }
		    }
		    
		    //Serializo los circuitos
		    std::map<Dibujo*, DatosCircuitoRemoto*>::iterator it2 = c->circuitos.begin();
		    for(;it2 != c->circuitos.end(); it2++){
			 DatosCircuitoRemoto * dcr = (*it2).second;
			 if(dcr != NULL){
			      XmlNodo componente("CircuitoRemoto");
			      //guardo el tipo de componente
			      componente.setPropiedad("x",Util::intToString(dcr->c->getVerticeSupIzq().x).c_str());
			      componente.setPropiedad("y",Util::intToString(dcr->c->getVerticeSupIzq().y).c_str());
			      componente.setPropiedad("alfa", Util::intToString(dcr->c->getAngulo()).c_str());
			      componente.setPropiedad("label",dcr->c->getLabel().c_str());
			      componente.setPropiedad("servidor", dcr->c->getServidor().c_str());
			      componente.setPropiedad("puerto", dcr->c->getPuerto().c_str());
			      componente.setPropiedad("nombre", dcr->c->getNombre().c_str());
			      componente.setPropiedad("cantidadEntradas", Util::intToString(dcr->c->getCantidadEntradas()).c_str());
			      componente.setPropiedad("cantidadSalidas", Util::intToString(dcr->c->getCantidadSalidas()).c_str());
			      xml.getRaiz()->agregarHijo(componente);
			 }
		    }

		    //Serializo los pines
		    std::map<Dibujo*, EntradaSalida*>::iterator it4 = c->pines.begin();
		    for(;it4 != c->pines.end(); it4++){
			 EntradaSalida * es = (*it4).second;
			 if(es != NULL){
			      XmlNodo componente("EntradaSalida");
			      //guardo el tipo de componente
			      componente.setPropiedad("x",Util::intToString(es->getVerticeSupIzq().x).c_str());
			      componente.setPropiedad("y",Util::intToString(es->getVerticeSupIzq().y).c_str());
			      componente.setPropiedad("alfa", Util::intToString(es->getAngulo()).c_str());
			      componente.setPropiedad("label",es->getLabel().c_str());
			      componente.setPropiedad("tipoPin",es->getTipoPin().c_str());
			      if(es->getTipoPin().compare("IN") == 0)
				   entradas++;
			      else salidas++;
			      xml.getRaiz()->agregarHijo(componente);
			 }
		    }

		    //Serializo las conexiones
		    std::map<Dibujo*, ConexionDibujo*>::iterator it3 = c->pistas.begin();
		    for(;it3 != c->pistas.end(); it3++){
			 ConexionDibujo * pista = (*it3).second;
			 if(pista != NULL){
			      XmlNodo componente("Conexion");
			      //guardo el tipo de componente
			      componente.setPropiedad("x1",Util::intToString(pista->getVerticeSupIzq().x).c_str());
			      componente.setPropiedad("y1",Util::intToString(pista->getVerticeSupIzq().y).c_str());
			      componente.setPropiedad("x2",Util::intToString(pista->getVerticeInfDer().x).c_str());
			      componente.setPropiedad("y2",Util::intToString(pista->getVerticeInfDer().y).c_str());
			      componente.setPropiedad("alfa", Util::intToString(pista->getAngulo()).c_str());
			      componente.setPropiedad("label",pista->getLabel().c_str());
			      xml.getRaiz()->agregarHijo(componente);
			 }
		    }

		    xml.getRaiz()->setPropiedad("entradas",Util::intToString(entradas).c_str());
		    xml.getRaiz()->setPropiedad("salidas",Util::intToString(salidas).c_str());

		    std::string *resultado=xml.toString();
		    /* escribo el XML a disco */
		    archivo.write(resultado->c_str(), resultado->size());
		    delete resultado;
		    xml.liberar();
	       }else std::cerr << "No se pudo abrir el archivo: " << nombre+extension << std::endl;
	       archivo.close();
	  }
     };

     DescripcionCircuito obtenerDescripcion(){
	  std::ifstream archivo;
	  archivo.open(nombre.c_str(), std::fstream::in);
	  DescripcionCircuito d;
	  if(archivo.good()){
	       std::string buffer, bufferlinea;
	       /* leo el archivo */
	       while(archivo.good()){
		    std::getline(archivo,bufferlinea);
		    buffer+=bufferlinea;
	       }

	       d.nombre = nombre;
	       /* decodifico el XML */
	       Xml xml(buffer.c_str(), buffer.size());
	       d.cantidadEntradas = atoi(xml.getRaiz()->getPropiedad("entradas").c_str());
	       d.cantidadSalidas = atoi(xml.getRaiz()->getPropiedad("salidas").c_str());
	       xml.liberar();
	  }else std::cerr << "No se pudo abrir el archivo: " << nombre << std::endl;
	  archivo.close();
	  return d;
     };

		
     /** 
      * Recupera el estado del modelo desde disco.
      * 
      * @param c El controlador a restablecer.
      */
     bool recuperar(ControladorVentana *c){
	  std::ifstream archivo;
	  bool rv=false;
	  archivo.open(nombre.c_str(), std::fstream::in);
	  if(archivo.good()){
	       rv=true;
	       std::string buffer, bufferlinea;
	       /* leo el archivo */
	       while(archivo.good()){
		    std::getline(archivo,bufferlinea);
		    buffer+=bufferlinea;
	       }
	       /* decodifico el XML */
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
			 dc->c->setLabel(componente.getPropiedad("label"));
		    }
		    if(componente.getNombre().compare("CircuitoRemoto")==0){
			 DatosCircuitoRemoto* dcr = c->cargarCircuito();
			 Vertice v;
			 int entradas=0, salidas=0;
			 v.x = atoi(componente.getPropiedad("x").c_str());
			 v.y = atoi(componente.getPropiedad("y").c_str());
			 entradas = atoi(componente.getPropiedad("cantidadEntradas").c_str());
			 salidas = atoi(componente.getPropiedad("cantidadSalidas").c_str());
			 dcr->c->setEntradasSalidas(entradas,salidas);
			 dcr->c->setVerticeSupIzq(v);
			 dcr->c->setAngulo(atoi(componente.getPropiedad("alfa").c_str()));
			 dcr->c->setLabel(componente.getPropiedad("label"));
			 dcr->c->setServidor(componente.getPropiedad("servidor"));
			 dcr->c->setPuerto(componente.getPropiedad("puerto"));
			 dcr->c->setNombre(componente.getPropiedad("nombre"));
		    }
		    if(componente.getNombre().compare("Conexion")==0){
			 ConexionDibujo *pista = c->cargarConexion();
			 Vertice v;
			 v.x = atoi(componente.getPropiedad("x1").c_str());
			 v.y = atoi(componente.getPropiedad("y1").c_str());
			 pista->setVerticeSupIzq(v);
			 v.x = atoi(componente.getPropiedad("x2").c_str());
			 v.y = atoi(componente.getPropiedad("y2").c_str());
			 pista->setVerticeInfDer(v);
			 pista->setAngulo(atoi(componente.getPropiedad("alfa").c_str()));
			 pista->setLabel(componente.getPropiedad("label"));
		    }
		    if(componente.getNombre().compare("EntradaSalida")==0){
			 EntradaSalida *pin = c->cargarEntradaSalida();
			 Vertice v;
			 v.x = atoi(componente.getPropiedad("x").c_str());
			 v.y = atoi(componente.getPropiedad("y").c_str());
			 pin->setVerticeSupIzq(v);
			 pin->setAngulo(atoi(componente.getPropiedad("alfa").c_str()));
			 pin->setLabel(componente.getPropiedad("label"));
			 pin->setTipoPin(componente.getPropiedad("tipoPin"));
		    }

		    componente = componente.obtenerHermano();
	       }
	       xml.liberar();
	  }else std::cerr << "No se pudo abrir el archivo: " << nombre << std::endl;
	  archivo.close();
	  return rv;
     };
     
};

#endif /*PERSISTIDOR_H_*/
