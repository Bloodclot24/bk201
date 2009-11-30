#include "ThreadSimulador.h"

ThreadSimulador::ThreadSimulador(ControladorVentana* cv):cv(cv){
}

void ThreadSimulador::run(){
     std::string errores;
     Circuito* c = cv->getCircuito(&errores);

     std::list<uint32_t> tabla;
     if(c)
	  tabla = c->simularTodo(500);

     cv->recibirTablaSimulacion(tabla, errores);
     cv->eliminarThread(this);
}
