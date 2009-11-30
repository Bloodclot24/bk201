#ifndef __SERVER_H_INCLUDED__
#define __SERVER_H_INCLUDED__

class Server;

#include "../Red/Socket.h"
#include <string>
#include <iostream>
#include "../HTTP/HttpRequest.h"
#include "../Threads/ThreadAceptor.h"
#include "../Circuito/CircuitoRemotoServidor.h"
#include "../Controlador/ControladorVentana.h"
#include <dirent.h>
#include "../Threads/ThreadLimpieza.h"

#define SERVER_PUERTO_DEFECTO  1234

/**
 * Esta clase es la aplicacion servidor.
 *
 * Se encarga de crear nuevos clientes, eliminar
 * clientes y escuchar conexiones entrantes;
 * asi mismo tambien permite obtener la lista de circuitos
 * que posee.
 *
 */
class Server{
     ThreadAceptor *aceptor;	/**< Thread para escuchar las
				 * conexiones entrantes */
     Socket s;			/**< Socket donde espero conexiones */

     ThreadLimpieza* limpieza;
     std::list<CircuitoRemotoServidor*> clientes;
public:

     /** 
      * Crea un nuevo server que recibe clientes en el puerto
      * indicado.
      * 
      * @param puerto Puerto por donde espero conexiones.
      */
     Server(int puerto);
     
     /** 
      * Intenta escuchar conexiones entrantes. 
      * 
      * @return TRUE si se pueden recibir conexiones. FALSE en caso de
      * error.
      */
     bool escuchar();

     /** 
      * Agrega un nuevo cliente al servidor.
      * 
      * @param s El socket para comunicarme al cliente.
      */
     void nuevoCliente(Socket *s);

     /**
      * Finaliza (elimina) el cliente definitivamente.
      *
      * @param src El cliente a ser eliminado.
      */
     void finalizarCliente(CircuitoRemotoServidor *sr);

     /**
      * Obtiene la lista de circuitos que posee el servidor.
      *
      */
     std::list<DescripcionCircuito> getListaCircuitos();

     ~Server();

};

#endif //__SERVER_H_INCLUDED__
