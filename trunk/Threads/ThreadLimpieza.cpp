#include "ThreadLimpieza.h"

ThreadLimpieza::ThreadLimpieza():variableClientes(&mutexClientes),variableSalida(&mutexSalida){
}

void ThreadLimpieza::run(){
  mutexClientes.lock();
  while(isRunning() || clientesRegistrados.size()>0){
    variableClientes.wait();
    while(clientesABorrar.size()>0){
      Thread* crs = clientesABorrar.front();
      clientesABorrar.pop_front();
      delete crs;
    }
  }
  mutexClientes.unlock();
  mutexSalida.lock();
  variableSalida.signal();
  mutexSalida.unlock();
}

void ThreadLimpieza::limpiarCliente(Thread* crs){

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

void ThreadLimpieza::registrarCliente(Thread* crs){

  if(isRunning()){
    mutexClientes.lock();
    clientesRegistrados[crs]=crs;
    variableClientes.signal();
    mutexClientes.unlock();
  }
}


ThreadLimpieza::~ThreadLimpieza(){
  mutexClientes.lock();
  std::map<Thread*, Thread*>::iterator it;
  for(it=clientesRegistrados.begin();it!=clientesRegistrados.end();it++){
    it->second->stop();
  }
  stop();
  mutexSalida.lock();
  variableClientes.signal();
  mutexClientes.unlock();
  variableSalida.wait();
  mutexSalida.unlock();
  join();
}
