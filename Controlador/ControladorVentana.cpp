#include "ControladorVentana.h"

#define TIPO_PISTA            "pista" 
#define TIPO_COMPUERTA_AND    "and"
#define TIPO_COMPUERTA_OR     "or"
#define TIPO_COMPUERTA_XOR    "xor"
#define TIPO_COMPUERTA_NOT    "not"
#define TIPO_COMPUERTA_BUFFER "buffer"
#define TIPO_PIN              "pin"
#define TIPO_CIRCUITO         "circuito"

void ControladorVentana::crearComponente(Dibujo* d, const std::string& tipo){
     if(tipo.compare(TIPO_PISTA)==0){
	  
     }
     else if(tipo.compare(TIPO_COMPUERTA_AND)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateAnd();
	  D->Compuerta = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_OR)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateOr();
	  D->Compuerta = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_XOR)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateXor();
	  D->Compuerta = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_NOT)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateNot();
	  D->Compuerta = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_COMPUERTA_BUFFER)==0){
	  DatosCompuerta *D = new DatosCompuerta;
	  D->tipo = tipo;
	  D->g = new GateBuffer();
	  D->Compuerta = d;
	  compuertas[d] = D;
     }
     else if(tipo.compare(TIPO_PIN)==0){

     }
     else if(tipo.compare(TIPO_CIRCUITO)==0){
	  DatosCirtuitoRemoto *D = new DatosCircuitoRemoto;
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
     
}

void ControladorVentana::pasarCircuito(Circuito* c){

}
