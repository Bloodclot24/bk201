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
     //D->cr = new CircuitoRemoto(D->servidor, D->puerto, D->nombre);
     D->c = d;
     circuitos[d] = D;
}

void ControladorVentana::crearComponente(ConexionDibujo* d){
     pistas[d] = d;
}

void ControladorVentana::crearComponente(EntradaSalida* d){
     pines[d] = d;
}

DatosCircuitoRemoto* ControladorVentana::cargarCircuito(){
     DatosCircuitoRemoto* dcr = new DatosCircuitoRemoto;
     dcr->c = new CircuitoDibujo(10,10,10,3);
     circuitos[dcr->c]=dcr;
     if(ventana)
	  ventana->agregarDibujo(dcr->c);
     return dcr;
}

DatosCompuerta* ControladorVentana::cargarCompuerta(const std::string& tipo){

     DatosCompuerta* dc = new DatosCompuerta;

     dc->tipo = tipo;
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
	  compuertas[dc->c] = dc;
	  if(ventana)
	       ventana->agregarDibujo(dc->c);
	  std::cout << "Cargado OK\n";
     }

     return dc;
}

ConexionDibujo* ControladorVentana::cargarConexion(){
     ConexionDibujo* d = new ConexionDibujo(0,0,NULL,0,NULL);
     pistas[d]=d;
     if(ventana)
	  ventana->agregarDibujo(d);
     return d;
}

EntradaSalida* ControladorVentana::cargarEntradaSalida(){
     EntradaSalida* es = new EntradaSalida(0,0);
     pines[es] = es;
     if(ventana)
	  ventana->agregarDibujo(es);
     return es;
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

     
     circuito.cantidadEntradas = 0;
     circuito.cantidadSalidas = 0;
     std::map<Dibujo*, EntradaSalida*>::iterator it;
     /* cuento cantidad de entradas y salidas*/
     for(it=pines.begin();it!=pines.end();it++){
	  if((*it).second->getTipoPin().compare("IN")==0)
	       circuito.cantidadEntradas++;
	  else circuito.cantidadSalidas++;
     }
     
     circuito.c = new Circuito(circuito.cantidadEntradas, circuito.cantidadSalidas);
     /* agrego las compuertas al circuito */
     std::map<Dibujo*, DatosCompuerta*>::iterator itg=compuertas.begin();
     for(;itg != compuertas.end(); itg++){
	  circuito.c->agregarComponente((*itg).second->g);
     }
     
     /* agrego los circuitos al circuito */
     std::map<Dibujo*, DatosCircuitoRemoto*>::iterator itc=circuitos.begin();
     for(;itc != circuitos.end(); itc++){
	  circuito.c->agregarComponente((*itc).second->cr);
	  //(*itc).second->cr->conectar();
     }

     itg=compuertas.begin();
     uint32_t numero=0;
     /* recorro las compuertas y busco con quienes se conectan */
     for(numero=0;itg != compuertas.end(); itg++,numero++){
	  int entradas,salidas;
	  Compuerta *g = (*itg).second->c;
	  entradas = g->getCantidadEntradas();
	  salidas = g->getCantidadSalidas();
	  /* busco en cada pin */
	  std::cout << "CANTIDADDEENTRADAS: " << entradas << std::endl; 
	  for(int i=0;i<entradas+salidas;i++){
	       Vertice v = g->obtenerPin(i);
	       std::map<Dibujo*, ConexionDibujo*>::iterator itp;
	       /* comparo la posicion del pin con las lineas */
	       for(itp = pistas.begin(); itp!=pistas.end();itp++){
		    ConexionDibujo* pista = (*itp).second;
		    if(pista->setSeleccionado(v.x,v.y)){
			 if(pista->getVerticeSupIzq()==v || pista->getVerticeInfDer()==v){
			      /* Este componente conecta con la linea*/
			      std::list<Vertice> puntosConexion;
			      /* busco todos los puntos de conexion de la linea */
			      buscarExtremos(pista, v, puntosConexion ,NULL);
			      crearConexiones(numero, i, i<entradas?false:true, puntosConexion);
			 }
		    }
	       }
	  }
     }
     // itc=circuitos.begin();
     // for(;itc != circuitos.end(); itc++){
     // 	  circuito.c->agregarComponente((*itc).second->cr);
     // 	  //(*itc).second->cr->conectar();
     // }

     circuito.c->simularTodo(500);
}

void ControladorVentana::crearConexiones(uint32_t componente, uint32_t pin, bool esSalida, const std::list<Vertice> &lista){
     std::map<Dibujo*, DatosCompuerta*>::iterator itc;

     uint32_t numero;
     /* recorro la lista de compuertas */
     for(numero=0,itc=compuertas.begin(); itc!=compuertas.end(); itc++,numero++){
	  std::list<Vertice>::const_iterator itv;
	  /* por cada una verifico todos los puntos */
	  for(itv=lista.begin();itv!=lista.end();itv++){
	       /* si algun pin coincide */
	       if(int pin2=(*itc).second->c->obtenerPinMasCercano((*itv).x, (*itv).y) != -1){
		    if(esSalida){
			 circuito.c->agregarConexion(componente, pin, numero,pin2);
			 std::cout << "Conecto " << componente << ":" << pin << " , con " << numero << ":" << pin2 << std::endl;
		    }
		    else{
			 circuito.c->agregarConexion(numero,pin2, componente, pin);
			 std::cout << "Conecto " << numero << ":" << pin2 << " , con " << componente << ":" << pin << std::endl;
		    }
	       }
	  }

     }
     /* recorro la lista de circuitos */
     std::map<Dibujo*, DatosCircuitoRemoto*>::iterator itcir;
     for(numero=0,itcir=circuitos.begin(); itcir!=circuitos.end(); itcir++,numero++){
	  std::list<Vertice>::const_iterator itv;
	  /* por cada uno verifico todos los puntos */
	  for(itv=lista.begin();itv!=lista.end();itv++){
	       /* si algun pin coincide */
	       if(int pin2=(*itcir).second->c->obtenerPinMasCercano((*itv).x, (*itv).y) != -1){
		    if(esSalida){
			 circuito.c->agregarConexion(componente, pin, numero,pin2);
		    }
		    else{
			 circuito.c->agregarConexion(numero,pin2, componente, pin);
		    }
	       }
	  }

     }
     /* recorro la lista de pines */
     int nentrada=0,nsalida=0;
     std::map<Dibujo*, EntradaSalida*>::iterator itpin;
     for(numero=0,itpin=pines.begin(); itpin!=pines.end(); itpin++,numero++){
	  int pin2;
	  /* proceso entradas/salidas */
	  std::cout << "nentrada: " << nentrada << " nsalida: " << nsalida << "<---"<< (*itpin).second->getTipoPin() << std::endl;
	  
	  if((*itpin).second->getTipoPin().compare("IN")==0){
	       pin2 = nentrada;
	       nentrada++;
	  }
	  else{
	       pin2=circuito.cantidadEntradas+nsalida;
	       nsalida++;
	  }

	  std::list<Vertice>::const_iterator itv;
	  /* por cada uno verifico todos los puntos */
	  for(itv=lista.begin();itv!=lista.end();itv++){
	       /* si algun pin coincide */
	       if((*itpin).second->obtenerPinMasCercano((*itv).x, (*itv).y) != -1){
		    /* agrego la conexion */
		    if(esSalida){
			 circuito.c->agregarConexion(componente, pin, -1,pin2);
			 std::cout << "Conecto " << componente << ":" << pin << " , con -1"  << ":" << pin2 << std::endl;
		    }
		    else{
			 circuito.c->agregarConexion(-1,pin2, componente, pin);
			 std::cout << "Conecto -1" << ":" << pin2 << " , con " << componente << ":" << pin << std::endl;
		    }
	       }
	  }
     }
}

void ControladorVentana::buscarExtremos(ConexionDibujo* pista, Vertice v, std::list<Vertice> &lista, std::map<ConexionDibujo*, ConexionDibujo*> *listaRecorridos){
     std::map<Dibujo*, ConexionDibujo*>::iterator it;
     Vertice final;

     bool liberar=false;

     if(listaRecorridos == NULL){
	  listaRecorridos=new std::map<ConexionDibujo*, ConexionDibujo*>;
	  liberar=true;
     }

     if((*listaRecorridos)[pista] != NULL)
	  return; /* este ya lo recorri */
     (*listaRecorridos)[pista] = pista;

     Vertice auxiliar = pista->getVerticeInfDer();
     if(auxiliar==v)
	  auxiliar = pista->getVerticeSupIzq();

     /* lo pongo como extremo posible */
     lista.push_back(auxiliar);
     
     /* busco si se conecta a otra conexion */
     for(it=pistas.begin();it!=pistas.end();it++){
	  ConexionDibujo *pista2 = (*it).second;
	  if(pista2->getVerticeSupIzq() == auxiliar || pista2->getVerticeInfDer() == auxiliar){
	       buscarExtremos(pista, auxiliar, lista, listaRecorridos);
	  }
     }

     if(liberar)
	  delete listaRecorridos;
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
     if(ventana)
	  ventana->recibirListaCircuitos(lista);
     return;
}
