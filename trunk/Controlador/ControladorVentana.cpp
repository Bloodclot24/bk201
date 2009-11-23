#include "ControladorVentana.h"
#include "../Gates/GateAnd.h"
#include "../Gates/GateOr.h"
#include "../Gates/GateXor.h"
#include "../Gates/GateNot.h"
#include "../Gates/GateBuffer.h"
#include "../Circuito/CircuitoRemoto.h"
#include "../Circuito/Circuito.h"
#include "../XML/Persistidor.h"
#include "../Threads/ThreadListado.h"
#include "../Threads/ThreadObtenerCircuito.h"

#define TIPO_PISTA            "Conexion" 
#define TIPO_COMPUERTA_AND    "And"
#define TIPO_COMPUERTA_OR     "Or"
#define TIPO_COMPUERTA_XOR    "Xor"
#define TIPO_COMPUERTA_NOT    "Not"
#define TIPO_COMPUERTA_BUFFER "Buffer"
#define TIPO_PIN              "IO"
#define TIPO_CIRCUITO         "Circuito"

void ControladorVentana::crearComponente(Compuerta* d, const std::string& tipo){

     DatosCompuerta *D = new DatosCompuerta;
     D->tipo = tipo;
     D->c = d;
     D->tr=10;

     if(tipo.compare(TIPO_COMPUERTA_AND)==0){
	  D->g = new GateAnd();
     }
     else if(tipo.compare(TIPO_COMPUERTA_OR)==0){
	  D->g = new GateOr();
     }
     else if(tipo.compare(TIPO_COMPUERTA_XOR)==0){
	  D->g = new GateXor();
     }
     else if(tipo.compare(TIPO_COMPUERTA_NOT)==0){
	  D->g = new GateNot();
     }
     else if(tipo.compare(TIPO_COMPUERTA_BUFFER)==0){
	  D->g = new GateBuffer();
     }
     else{
	  delete D;
	  D=NULL;
     }
     if(D != NULL)
	  compuertas[d] = D;
}

void ControladorVentana::crearComponente(CircuitoDibujo* d){
     DatosCircuitoRemoto *D = new DatosCircuitoRemoto;
     D->cantidadEntradas = D->cantidadSalidas = 1;
     //D->cr = new CircuitoRemoto(D->servidor, D->puerto, D->nombre);
     D->c = d;
     D->puerto = 0;
     circuitos[d] = D;
}

DatosCircuitoRemoto* ControladorVentana::cargarCircuito(){
     DatosCircuitoRemoto* dcr = new DatosCircuitoRemoto;
     dcr->c = new CircuitoDibujo(10,10,10,3);
     circuitos[dcr->c]=dcr;
     ventana->agregarDibujo(dcr->c);
     return dcr;
}

DatosCompuerta* ControladorVentana::cargarCompuerta(const std::string& tipo){

     DatosCompuerta* dc = new DatosCompuerta;

     dc->tipo = tipo;
     dc->tr = 10;
     std::cout << "cargo compuerta " << tipo << std::endl;
     if(tipo.compare(TIPO_COMPUERTA_AND)==0){
	  dc->g = new GateAnd();
	  dc->c= new CompuertaAnd(10, 10);
     }
     else if(tipo.compare(TIPO_COMPUERTA_OR)==0){
	  dc->g = new GateOr();	  
	  dc->c= new CompuertaOr(10, 10);
     }
     else if(tipo.compare(TIPO_COMPUERTA_XOR)==0){
	  dc->g = new GateXor();
	  dc->c= new CompuertaXor(10, 10);
     }
     else if(tipo.compare(TIPO_COMPUERTA_NOT)==0){
	  dc->g = new GateNot();
	  dc->c= new CompuertaNot(10, 10);
     }
     else if(tipo.compare(TIPO_COMPUERTA_BUFFER)==0){
	  dc->g = new GateBuffer();
	  dc->c= new CompuertaBuffer(10, 10);
     }
     else{
	  delete dc->c;
	  delete dc;
	  dc = NULL;
     }
     
     if(dc != NULL){
	  dc->c->setTiempoT("10");
	  compuertas[dc->c] = dc;
	  ventana->agregarDibujo(dc->c);
	  std::cout << "Cargado OK\n";
     }

     return dc;
}

void ControladorVentana::eliminarComponente(Dibujo* d){
     if(compuertas[d] != NULL){
	  delete compuertas[d]->g;
	  delete compuertas[d];
	  compuertas[d] = NULL;
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

void ControladorVentana::obtenerListaServidor(const std::string& servidor, int puerto){
     ThreadListado *listado = new ThreadListado(*this,servidor, puerto);
     listado->run();
}
void ControladorVentana::obtenerCircuitoServidor(const std::string& nombre, const std::string& servidor, int puerto){
     ThreadObtenerCircuito *obtener = new ThreadObtenerCircuito(*this,nombre, servidor, puerto);
     obtener->run();
}

std::list<uint64_t> ControladorVentana::obtenerTabla(){
     std::list<uint64_t> l;
     return l;
}

void ControladorVentana::guardar(const std::string& nombreArchivo){
     Persistidor p(nombreArchivo);
     p.persistir(this);
}

void ControladorVentana::cargar(const std::string& nombreArchivo){
     Persistidor p(nombreArchivo);
     p.recuperar(this);
}

void ControladorVentana::notificarLista(std::list<DescripcionCircuito> lista){
     ventana->recibirListaCircuitos(lista);
     return;
}
