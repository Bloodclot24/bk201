#ifndef __THREADOBTENERCIRCUITO_H_INCLUDED__
#define __THREADOBTENERCIRCUITO_H_INCLUDED__

#include "Threads.h"
#include "../Controlador/ControladorVentana.h"

/**
 * Clase que dado un servidor, un puerto y el nombre del circuito
 * lo obtiene y lo notifica.
 *
 */
class ThreadObtenerCircuito:public Thread{
private:
  std::string host;
  int puerto;
  ControladorVentana& control;
  const std::string nombre;

public:
  ThreadObtenerCircuito(ControladorVentana& control, const std::string& nombre, const std::string& host, int puerto);
  virtual void run();
};

#endif //__THREADOBTENERCIRCUITO_H_INCLUDED__
