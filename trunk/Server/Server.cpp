#include "Server.h"
#include "../Circuito/CircuitoRemotoServidor.h"

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
     aceptor->comenzar();
     return true;
}

void Server::nuevoCliente(Socket *s){
     CircuitoRemotoServidor *sr = new CircuitoRemotoServidor(s);
     sr->start();
     return;
}

void Server::finalizarCliente(CircuitoRemotoServidor *sr){
     delete sr;
}
