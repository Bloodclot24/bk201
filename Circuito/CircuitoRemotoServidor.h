#ifndef __CIRCUITO_REMOTO_SERVIDOR__
#define __CIRCUITO_REMOTO_SERVIDOR__

class CircuitoRemotoServidor;

#include "Circuito.h"
#include "../Red/Mensajero.h"
#include "../Threads/Threads.h"
#include "../Gates/Gates.h"
#include "../Util/Util.h"
#include "../Server/Server.h"
#include <list>
#include <fstream>
#include "../Controlador/ControladorVentana.h"


/**
 * Sumador completo de 1 bit
 * http://www.unicrom.com/dig_suma_binaria_completo.asp 
 *
 */
class Sumador:public Circuito{
public:
     Sumador():Circuito(3,2){
	  agregarComponente(new GateXor());
	  agregarComponente(new GateAnd());
	  agregarComponente(new GateXor());
	  agregarComponente(new GateAnd());
	  agregarComponente(new GateOr());
	  
	  agregarConexion(-1,0,0,0);
	  agregarConexion(-1,0,1,0);
	  agregarConexion(-1,1,0,1);
	  agregarConexion(-1,1,1,1);
	  agregarConexion(-1,2,2,1);
	  agregarConexion(-1,2,3,1);
	  agregarConexion(0,2,2,0);
	  agregarConexion(0,2,3,0);
	  agregarConexion(1,2,4,1);
	  agregarConexion(2,2,-1,3);
	  agregarConexion(3,2,4,0);
	  agregarConexion(4,2,-1,4);
     }
     
};


class CircuitoRemotoServidor: public Thread{
private:
     Socket *ns;		/**< Socket a utilizar */
     Mensajero m;
     Soap *s;
     Circuito *c;
     Server *server;
     ControladorVentana *controlador;
public:

     CircuitoRemotoServidor(Socket *s, Server *serv){
	  ns=s;
	  m.setSocket(s);
	  ns->setTimeout(10,0);
	  server = serv;
	  controlador=NULL;
	  c=NULL;
     }

     void run();

     ~CircuitoRemotoServidor();
};

#endif //__CIRCUITO_REMOTO_SERVIDOR__
