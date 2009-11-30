#include "ThreadSimulador.h"

ThreadSimulador::ThreadSimulador(ControladorVentana* cv):cv(cv){
}

void ThreadSimulador::run(){
  std::string errores;
  /* obtengo el circuito */
  Circuito* c = cv->getCircuito(&errores);

  std::list<uint32_t> tabla;
  /* si tengo el circuito, simulo */
  if(c)
    tabla = c->simularTodo(500);

  /* envio la tabla con los resultados y los errores */
  cv->recibirTablaSimulacion(tabla, errores);
  /* pido que me maten */
  cv->eliminarThread(this);
}
