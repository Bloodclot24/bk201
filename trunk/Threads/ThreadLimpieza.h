#ifndef __THREADLIMPIEZA_H_INCLUDED__
#define __THREADLIMPIEZA_H_INCLUDED__

class ThreadLimpieza;

#include "Threads.h"
#include "../Circuito/CircuitoRemotoServidor.h"

class ThreadLimpieza:public Thread{
private:
     std::list<Thread*> clientesABorrar;
     std::map<Thread*, Thread*> clientesRegistrados;
     Mutex mutexClientes;
     CVariable variableClientes;
     Mutex mutexSalida;
     CVariable variableSalida;

public:
     ThreadLimpieza();
     void registrarCliente(Thread* crs);
     void limpiarCliente(Thread* crs);
     virtual void run();
     virtual ~ThreadLimpieza();
};

#endif //__THREADLIMPIEZA_H_INCLUDED__
