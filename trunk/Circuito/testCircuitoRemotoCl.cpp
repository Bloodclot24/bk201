#include "Circuito.h"
#include "CircuitoRemoto.h"
#include <sstream>

int main(int argc, char** argv){
     int puerto=1234;

     if(argc > 1){
	  puerto = atoi(argv[1]);
	  if(puerto == 0)
	       puerto = 1234;
     }
     
     std::cout << "Usando puerto " << puerto << std::endl;
     
     std::stringstream s;
     s << "localhost:";
     s << puerto;
     CircuitoRemoto *cr = new CircuitoRemoto(s.str(),puerto, "CircuitoDePrueba");

     Circuito c(3,2);
     c.agregarComponente(cr);
     
     c.agregarConexion(-1,0,0,0);
     c.agregarConexion(-1,1,0,1);
     c.agregarConexion(-1,2,0,2);
     c.agregarConexion(0,3,-1,3);
     c.agregarConexion(0,4,-1,4);

     c.simularTodo(30);

     return 1;

}
