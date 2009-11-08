#ifndef THREADACEPTOR_H_
#define THREADACEPTOR_H_

class  ThreadAceptor;

#include "../Red/Socket.h"
#include "Threads.h"
#include "../Server/Server.h"


/** 
 * Clase que en un Thread aparte escucha conexiones del exterior y las
 * conecta.
 */
class ThreadAceptor:public Thread{
private:
     Socket *socket;		/**< El socket por el cual se escuchan
				 * las conexiones entrantes */
     Server *servidor;
public:
     /** 
      * Crea un nuevo ThreadAceptor.
      * 
      * @param socket El socket para escuchar conexiones.
      */
     ThreadAceptor(Socket *socket, Server* servidor);

     /** 
      * Comienza el thread.
      */
     void comenzar();

     /** 
      * Finaliza el thread.
      */
     void finish(void);

     /** 
      * Metodo principal del Thread.
      *
      * @see Thread 
      */
     virtual void run();

     /** 
      * Finaliza el Thread y libera los recursos asociados.
      */
     ~ThreadAceptor();

};
   
#endif /*THREADACEPTOR_H_*/
