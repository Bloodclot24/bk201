#include "Server.h"

Server::Server(int puerto=SERVER_PUERTO_DEFECTO):s("localhost", puerto){
     aceptor = new ThreadAceptor(&s,this);
}

bool Server::escuchar(){
     if(!s.esValido())
	  return false;
     if(!s.enlazar())
	  return false;
     if(!s.escuchar())
	  return false;
     return true;
}

void Server::nuevoCliente(Socket *s){
     return;
}

