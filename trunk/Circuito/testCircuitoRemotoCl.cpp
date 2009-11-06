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
     CircuitoRemoto cr(s.str(), "CircuitoDePrueba");

     cr.getPin(0);
     
     

     return 1;

}
