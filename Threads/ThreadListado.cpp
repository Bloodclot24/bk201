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

     // DescripcionCircuito d={"Circuito1", 1,2};
     // DescripcionCircuito e={"Circuito2", 4,1};
     // DescripcionCircuito f={"Circuito3", 5,3};
     // DescripcionCircuito g={"Circuito4", 3,3};

     // std::cout << "Agrego los circuitos a la lista\n";

     // lista.push_back(d);
     // lista.push_back(e);
     // lista.push_back(f);
     // lista.push_back(g);

     // sleep(2);

     // std::cout << "Notifico a la ventana\n";
     // control.notificarLista(lista);
     // return;

     Socket s(host, puerto);
     s.conectar();
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
     control.notificarLista(lista);
}
