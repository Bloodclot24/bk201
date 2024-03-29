#include "Server.h"
#include "../Circuito/CircuitoRemotoServidor.h"
#include "../XML/Persistidor.h"


Server::Server(int puerto=SERVER_PUERTO_DEFECTO):s("localhost", puerto){
  aceptor = new ThreadAceptor(&s,this);
  limpieza = new ThreadLimpieza();
}

bool Server::escuchar(){
  limpieza->start();

  if(!s.esValido())
    return false;
  if(!s.enlazar())
    return false;
  if(!s.escuchar())
    return false;
  aceptor->comenzar();

  return true;
}

/** 
 * Crea un nuevo cliente asociado a un socket (obtenido en el accept).
 * 
 * @param s El socket a utilizar.
 */
void Server::nuevoCliente(Socket *s){
  CircuitoRemotoServidor *sr = new CircuitoRemotoServidor(s, this);
  /* registro el cliente, para forzar la salida del mismo si
   * todavia no terminó cuando termina el servidor */
  limpieza->registrarCliente(sr);
  sr->start();
  return;
}

void Server::finalizarCliente(CircuitoRemotoServidor *sr){
  /* elimino el cliente definitivamente */
  limpieza->limpiarCliente(sr);
}

/** 
 * Leo del directorio actual los archivos de circuito y arma una lista
 * con los nombres.
 * 
 * @return La lista de circuitos.
 */
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
  delete limpieza;
}
