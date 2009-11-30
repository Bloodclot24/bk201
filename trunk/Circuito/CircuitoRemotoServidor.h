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
 * Clase que representa una instancia de un circuito del lado del
 * servidor. Este circuito se utiliza para proveer informacion a un
 * cliente del otro lado de la red acerca del estado de la simulacion
 * de un circuito en particular.
 * 
 */
class CircuitoRemotoServidor: public Thread{
private:
  Socket *ns;		/**< Socket a utilizar */
  Mensajero m;
  Soap *s;
  Circuito *c;
  Server *server;
  ControladorVentana *controlador;
public:

  /** 
   * Crea un nuevo circuito remoto (del lado del servidor) que provee
   * datos al cliente del otro lado de la red.
   * 
   * @param s El socket para comunicarnos con el cliente.
   * @param serv El servidor que acepto la conexion del cliente.
   * 
   */
  CircuitoRemotoServidor(Socket *s, Server *serv){
    ns=s;
    m.setSocket(s);
    ns->setTimeout(10,0);
    server = serv;
    controlador=NULL;
    c=NULL;
  }

  /** 
   * Metodo principal de la clase.
   * @see Thread
   */
  void run();

  ~CircuitoRemotoServidor();
};

#endif //__CIRCUITO_REMOTO_SERVIDOR__
