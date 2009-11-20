#include "ControladorVentana.h"
#include "../Gates/GateAnd.h"
#include "../Gates/GateOr.h"
#include "../Gates/GateXor.h"
#include "../Gates/GateNot.h"
#include "../Gates/GateBuffer.h"
#include "../Circuito/CircuitoRemoto.h"
#include "../Circuito/Circuito.h"
#include "../XML/Persistidor.h"

#define TIPO_PISTA            "Conexion" 
#define TIPO_COMPUERTA_AND    "And"
#define TIPO_COMPUERTA_OR     "Or"
#define TIPO_COMPUERTA_XOR    "Xor"
#define TIPO_COMPUERTA_NOT    "Not"
#define TIPO_COMPUERTA_BUFFER "Buffer"
#define TIPO_PIN              "Pin"
#define TIPO_CIRCUITO         "Circuito"

void ControladorVentana::crearComponente(Dibujo* d, const std::string& tipo){
     if(tipo.compare(TIPO_PISTA)==0){
	  
     }
     else if(tipo.compare(TIPO_COMPUERTA_AND)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateAnd();
	  D->c = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_OR)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateOr();
	  D->c = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_XOR)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateXor();
	  D->c = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_NOT)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateNot();
	  D->c = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_BUFFER)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateBuffer();
	  D->c = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_PIN)==0){

     }
     else if(tipo.compare(TIPO_CIRCUITO)==0){
	  DatosCircuitoRemoto *D = new DatosCircuitoRemoto;
	  D->cantidadEntradas = D->cantidadSalidas = 1;
	  D->cr = new CircuitoRemoto(D->servidor, D->puerto, D->nombre);
	  D->c = d;
	  circuitos[d] = D;
     }
}

void ControladorVentana::eliminarComponente(Dibujo* d){
     if(compuertas[d] != NULL){
	  delete compuertas[d]->g;
	  delete compuertas[d];
	  compuertas[d]=NULL;
     }
     else if(circuitos[d] != NULL){
	  delete circuitos[d]->cr;
	  delete circuitos[d];
	  circuitos[d] = NULL;
     }
     else if(pistas[d] != NULL){
	  delete pistas[d];
	  pistas[d] = NULL;
     }
     else if(pines[d] != NULL){
	  delete pines[d];
	  pines[d] = NULL;
     }
}

void ControladorVentana::simular(){
     if(circuito.c != NULL)
	  delete circuito.c;
     circuito.c = new Circuito(circuito.cantidadEntradas, circuito.cantidadSalidas);
     
     std::map<Dibujo*, DatosCompuerta*>::iterator it=compuertas.begin();
     for(;it != compuertas.end(); it++){
	  circuito.c->agregarComponente((*it).second->g);
     }
     std::map<Dibujo*, DatosCircuitoRemoto*>::iterator it2=circuitos.begin();
     for(;it2 != circuitos.end(); it2++){
	  circuito.c->agregarComponente((*it2).second->cr);
     }

}

std::list<std::string> ControladorVentana::obtenerListaServidor(const std::string& servidor, int puerto){
     
}

std::list<uint64_t> ControladorVentana::obtenerTabla(){

}

void ControladorVentana::setAtributo(Dibujo* d, const std::string& nombre, const std::string& valor){

}

std::string ControladorVentana::getAtributo(Dibujo* d, const std::string& nombre){

}

void ControladorVentana::guardar(const std::string& nombreArchivo){
     Persistidor p(nombreArchivo);
     p.persistir(this);
}
