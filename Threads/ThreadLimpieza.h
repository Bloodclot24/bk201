#ifndef __THREADLIMPIEZA_H_INCLUDED__
#define __THREADLIMPIEZA_H_INCLUDED__

class ThreadLimpieza;

#include "Threads.h"
#include "../Circuito/CircuitoRemotoServidor.h"

/**
 * Clase encargada de realizar la limpieza de los hilos
 * de los clientes. Los va dando de alta para luego
 * poder forzarlos a eliminarse en el momento que sea
 * necesario.
 */
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

  /**
   * Recibe el hilo del cliente que debe registrar (darse de alta)
   * para ser eliminado a futuro.
   *
   * @param crs El cliente que va a "darse" de alta para ser eliminado
   *            a futuro.
   *
   */
  void registrarCliente(Thread* crs);

  /**
   * Recibe el hilo del cliente que debe ser eliminado, y lo elimina
   * ya sea porque logra que termine o forzandolo a salir.
   *
   * @param crs El cliente que va a eliminarse.
   */
  void limpiarCliente(Thread* crs);


  virtual void run();


  virtual ~ThreadLimpieza();
};

#endif //__THREADLIMPIEZA_H_INCLUDED__
