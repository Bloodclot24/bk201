#ifndef __THREADLIMPIEZA_H_INCLUDED__
#define __THREADLIMPIEZA_H_INCLUDED__

class ThreadLimpieza;

#include "Threads.h"
#include "../Circuito/CircuitoRemotoServidor.h"

class ThreadLimpieza:public Thread{
private:
     std::list<CircuitoRemotoServidor*> clientesABorrar;
     std::map<CircuitoRemotoServidor*, CircuitoRemotoServidor*> clientesRegistrados;
     Mutex mutexClientes;
     CVariable variableClientes;
public:
     ThreadLimpieza();
     void registrarCliente(CircuitoRemotoServidor* crs);
     void limpiarCliente(CircuitoRemotoServidor* crs);
     virtual void run();
     virtual ~ThreadLimpieza();
};

#endif //__THREADLIMPIEZA_H_INCLUDED__
