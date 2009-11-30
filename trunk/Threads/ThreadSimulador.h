#ifndef __THREADSIMULADOR_H_INCLUDED__
#define __THREADSIMULADOR_H_INCLUDED__

class ThreadSimulador;

#include "Threads.h"
#include "../Controlador/ControladorVentana.h"

class ThreadSimulador:public Thread{

     ControladorVentana* cv;

public:
     ThreadSimulador(ControladorVentana* cv);
     void run();
};

#endif //__THREADSIMULADOR_H_INCLUDED__
