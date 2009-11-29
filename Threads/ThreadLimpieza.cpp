#include "ThreadLimpieza.h"

ThreadLimpieza::ThreadLimpieza():variableClientes(&mutexClientes){

}

void ThreadLimpieza::run(){
     mutexClientes.lock();
     while(isRunning()){
	  variableClientes.wait();
	  while(clientes.size()>0){
	       CircuitoRemotoServidor* crs = clientes.front();
	       clientes.pop_front();
	       std::cout << "Finalizando el cliente....\n";
	       crs->join();
	       delete crs;
	  }
     }
     mutexClientes.unlock();
}

void ThreadLimpieza::agregarCliente(CircuitoRemotoServidor* crs){
     mutexClientes.lock();
     clientes.push_back(crs);
     variableClientes.signal();
     mutexClientes.unlock();
}

ThreadLimpieza::~ThreadLimpieza(){
     stop();
     mutexClientes.lock();
     variableClientes.signal();
     mutexClientes.unlock();
     join();
}
