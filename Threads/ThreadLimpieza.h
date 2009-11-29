#ifndef __THREADLIMPIEZA_H_INCLUDED__
#define __THREADLIMPIEZA_H_INCLUDED__

class ThreadLimpieza;

#include "Threads.h"
#include "../Circuito/CircuitoRemotoServidor.h"

class ThreadLimpieza:public Thread{
private:
     std::list<CircuitoRemotoServidor*> clientes;
     Mutex mutexClientes;
     CVariable variableClientes;
public:
     ThreadLimpieza();
     void agregarCliente(CircuitoRemotoServidor* crs);
     virtual void run();
     virtual ~ThreadLimpieza();
};

#endif //__THREADLIMPIEZA_H_INCLUDED__
