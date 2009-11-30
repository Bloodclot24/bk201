#include <string>
#include <iostream>
#include "../HTTP/HttpRequest.h"
#include "../Red/Socket.h"
#include "Server.h"
#include "../Util/Util.h"


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

  return 0;
}
