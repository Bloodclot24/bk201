#include "Server.h"
#include "../Circuito/CircuitoRemotoServidor.h"
#include "../XML/Persistidor.h"

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
     CircuitoRemotoServidor *sr = new CircuitoRemotoServidor(s, this);
     sr->start();
     return;
}

void Server::finalizarCliente(CircuitoRemotoServidor *sr){
     delete sr;
}

std::list<DescripcionCircuito> Server::getListaCircuitos(){
     DIR* directory;                              
     struct dirent* entry;                        
     
     std::list<DescripcionCircuito> lista;

     DescripcionCircuito d;

     if( (directory =opendir(".")) ==NULL)
	  return lista;
     while((entry=readdir(directory))!=NULL){
	  std::string nombreCompleto(entry->d_name);
	  if(nombreCompleto.size()>3 &&					\
	     nombreCompleto.compare(nombreCompleto.size()-3, 3, ".bk")==0){
	       std::cout << "Agregar el archivo: " << nombreCompleto << "\n";
	       Persistidor persistidor(nombreCompleto);
	       d = persistidor.obtenerDescripcion();
	       if(d.nombre.size() > 0)
		    lista.push_back(d);
	  }
     }
     closedir(directory);
     return lista;
}



Server::~Server(){

//     delete aceptor;
}
