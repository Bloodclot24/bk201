#include "ThreadObtenerCircuito.h"
#include "../Red/Socket.h"
#include "../Red/Mensajero.h"
#include "../XML/Soap.h"
#include <fstream>

ThreadObtenerCircuito::ThreadObtenerCircuito(ControladorVentana& control, const std::string& nombre, const std::string& host, int puerto):control(control),nombre(nombre){
  this->host = host;
  this->puerto = puerto;
}

void ThreadObtenerCircuito::run(){
  Socket s(host, puerto);
  s.conectar(15);
  if(s.esValido()){
    std::cout << "Conectado" << std::endl;
    Mensajero m(&s);
    Soap mensaje("ObtenerCircuito");
    mensaje.setParametro("nombre", nombre.c_str());
    m.enviarMensaje(&mensaje);
    std::cout << "Envio el pedido.\n";
    Soap *respuesta = m.recibirRespuesta();
	  
    std::cout << "Ya tengo la respuesta.\n";

    if(respuesta != NULL &&					\
       respuesta->getNombre().compare("ObtenerCircuitoResponse") == 0){
	       
      std::string contenido = respuesta->getParametro("archivo");
      int numero = rand()*100+rand()%100;
      std::string nombreTemporal="$$temporal" + Util::intToString(numero) +".bk";
      std::cout << "Archivo temporal: " << nombreTemporal << std::endl;
      std::ofstream temporal(nombreTemporal.c_str());
      temporal.write(contenido.c_str(), contenido.size());
      temporal.close();
      std::cout << "Aviso la llegada del circuito \n";
      control.notificarCircuito(nombreTemporal, nombre);
    }
    else{
      std::cout << "Respuesta es NULL.\n";
      std::string vacio;
      control.notificarCircuito(vacio, nombre);
    }
	  
    delete respuesta;
  }
  else{
    std::string vacio;
    control.notificarCircuito(vacio, nombre);
  }
  control.eliminarThread(this);
}
