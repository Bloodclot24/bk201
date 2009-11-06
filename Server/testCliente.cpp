#include "../Red/Socket.h"
#include "../HTTP/HttpRequest.h"
#include "../XML/Soap.h"
#include <iostream>
#include <string>

int main(int argc, char**  argv){
     
     int puerto=1234;

     if(argc > 1){
	  puerto = atoi(argv[1]);
	  if(puerto == 0)
	       puerto = 1234;
     }

     std::cout << "Usando puerto " << puerto << std::endl;

     Socket s("localhost",puerto);

     if(!s.conectar()){
	  std::cout << "No se pudo conectar al servidor: " << s.obtenerError() << std::endl;
	  return -1;
     }

     Soap mensaje("MensajeDePrueba");
     mensaje.setParametro("nombre", "ns/nc");

     HttpRequest req("localhost/mensajes");

     std::string *smensaje = mensaje.toString();

     req.setContentLength(smensaje->size());

     std::string sreq = req.getRequest();

     s.enviar(sreq.c_str(), sreq.length());




     s.enviar(smensaje->c_str(), smensaje->length());

     delete smensaje;
     return 0;
}
