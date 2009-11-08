#include "ThreadAceptor.h"

ThreadAceptor::ThreadAceptor(Socket *socket, Server* servidor){
     this->socket = socket;
     this->servidor = servidor;
}

void ThreadAceptor::comenzar(){
     start();
}

void ThreadAceptor::finish(void){
     if(isRunning()){
	  socket->setTimeout(0,1);
	  Thread::finish();
	  socket->cerrar();
     }
}

void ThreadAceptor::run(){
     while(isRunning()){
	  Socket *sck=NULL;
	  sck = socket->aceptar();  //Acepto el cliente
	  if(sck){
	       servidor->nuevoCliente(sck);
	  }
     }
}

ThreadAceptor::~ThreadAceptor(){
     delete socket;
}
