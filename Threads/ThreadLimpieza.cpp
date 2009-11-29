#include "ThreadLimpieza.h"

ThreadLimpieza::ThreadLimpieza():variableClientes(&mutexClientes){

}

void ThreadLimpieza::run(){
     mutexClientes.lock();
     while(isRunning()){
	  variableClientes.wait();
	  while(clientesABorrar.size()>0){
	       CircuitoRemotoServidor* crs = clientesABorrar.front();
	       clientesABorrar.pop_front();
	       std::cout << "Finalizando el cliente....\n";
	       delete crs;
	  }
     }
     mutexClientes.unlock();
}

void ThreadLimpieza::limpiarCliente(CircuitoRemotoServidor* crs){
     mutexClientes.lock();
     if(clientesRegistrados.count(crs) == 0)
	  std::cerr << "Error: se intento eliminar un cliente que nunca se registro.\n";
     else{
	  clientesRegistrados.erase(crs);
     }
     clientesABorrar.push_back(crs);
     variableClientes.signal();
     mutexClientes.unlock();
}

void ThreadLimpieza::registrarCliente(CircuitoRemotoServidor* crs){
     mutexClientes.lock();
     clientesRegistrados[crs]=crs;
     variableClientes.signal();
     mutexClientes.unlock();
}


ThreadLimpieza::~ThreadLimpieza(){
     stop();
     mutexClientes.lock();
     std::map<CircuitoRemotoServidor*, CircuitoRemotoServidor*>::iterator it;
     for(it=clientesRegistrados.begin();it!=clientesRegistrados.end();it++){
	  it->second->stop();
     }

     variableClientes.signal();
     mutexClientes.unlock();
     join();
}
