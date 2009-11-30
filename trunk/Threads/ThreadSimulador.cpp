#include "ThreadSimulador.h"

ThreadSimulador::ThreadSimulador(ControladorVentana* cv):cv(cv){
}

void ThreadSimulador::run(){
     Circuito* c = cv->getCircuito();

     std::list<uint32_t> tabla = c->simularTodo(500);

     cv->recibirTablaSimulacion(tabla);
     return;
}
