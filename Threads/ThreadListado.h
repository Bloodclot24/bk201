#ifndef __THREADLISTADO_H_INCLUDED__
#define __THREADLISTADO_H_INCLUDED__

#include "Threads.h"
#include "../Controlador/ControladorVentana.h"

/**
 * Clase encargada de obtener y notificar la lista de circuitos
 * disponibles de un servidor en particular.
 *
 */
class ThreadListado:public Thread{
private:
     std::string host;
     int puerto;
     ControladorVentana& control;

public:
     ThreadListado(ControladorVentana& control, const std::string& host, int puerto);
     virtual void run();
};

#endif //__THREADLISTADO_H_INCLUDED__
