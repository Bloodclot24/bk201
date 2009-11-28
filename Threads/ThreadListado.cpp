#include "ThreadListado.h"
#include "../Red/Socket.h"
#include "../Red/Mensajero.h"
#include "../XML/Soap.h"

ThreadListado::ThreadListado(ControladorVentana& control, const std::string& host, int puerto):control(control){
     this->host = host;
     this->puerto = puerto;
}

void ThreadListado::run(){
     std::list<DescripcionCircuito> lista;
     Socket s(host, puerto);
     std::cout << "valido: " << s.esValido() << std::endl;
     if(!s.esValido()){
	  control.notificarLista(lista);
	  return;
     }
     s.conectar(15);
     if(s.esValido()){
	  std::cout << "Conectado" << std::endl;
	  Mensajero m(&s);
	  Soap mensaje("GetListado");
	  m.enviarMensaje(&mensaje);
	  std::cout << "Envio el pedido.\n";
	  Soap *respuesta = m.recibirRespuesta();

	  std::cout << "Ya tengo la respuesta.\n";

	  if(respuesta != NULL && \
	     respuesta->getNombre().compare("GetListadoResponse") == 0){
	       
	       XmlNodo cuerpo = respuesta->getCuerpo().obtenerHijo();
	       for(;cuerpo.getNombre().size()>0;cuerpo=cuerpo.obtenerHermano()){
		    if(cuerpo.getNombre().compare("Circuito")==0){
			 DescripcionCircuito d;
			 d.nombre =cuerpo.getPropiedad("nombre");
			 d.cantidadEntradas = atoi(cuerpo.getPropiedad("cantidadEntradas").c_str());
			 d.cantidadSalidas =  atoi(cuerpo.getPropiedad("cantidadSalidas").c_str());
			 lista.push_back(d);
		    }
	       }
	  }
	  delete respuesta;
     }
     else{
	  std::cout << "Timeouttttttttttttttttttttttt\n";
     }
     control.notificarLista(lista);
}
