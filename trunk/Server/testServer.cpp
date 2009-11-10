#include <string>
#include <iostream>
#include "../HTTP/HttpRequest.h"
#include "../Red/Socket.h"
#include "Server.h"


int main(int argc, char** argv){

     int puerto=1234;

     if(argc > 1){
	  puerto = atoi(argv[1]);
	  if(puerto == 0)
	       puerto = 1234;
     }

     std::cout << "Usando puerto " << puerto << std::endl;

     Server S(puerto);

     if(!S.escuchar()){
	  std::cout << "No se puede escuchar conexiones en el puerto " << puerto << std::endl;
	  return -1;
     }
     char c=0;
     while(c != 'q'){
	  std::cin >> c;
	  
     };
     // Socket s("localhost",puerto);

     // s.enlazar();
     // s.escuchar();
     // Socket *s2 = s.aceptar();

     // char c=0;
     // bool salida=false;
     // std::string mensaje;

     // while(!salida){
     // 	  s2->recibir(&c ,1);
     // 	  mensaje +=c;
	  
     // 	  if(mensaje.size()>=4){
     // 	       if(mensaje.compare(mensaje.size()-4, 4, "\r\n\r\n")==0)
     // 		    salida=true;
     // 	  }
     // }

     // HttpRequest req(mensaje.c_str(),1);

     // if(!req.esValido()){
     // 	  std::cout << "El request recibido no es valido.\n";
     // 	  delete s2;
     // 	  return -1;
     // }

     // char* datos = new char[req.getContentLength()+1];
     // datos[req.getContentLength()] = 0;
     
     // s2->recibir(datos, req.getContentLength());
     
     // std::cout << "Datos recibidos: \n";
     // std::cout << datos << std::endl;

     return 0;
}
