
#include "CircuitoRemotoServidor.h"

void CircuitoRemotoServidor::run(){

     while(isRunning()){
	  // recibo mensajes hasta que cierre la conexion
	  s = m.recibirMensaje();
	  if(s== NULL){
	       std::cout << "El mensaje es NULL\n";
	       stop();
	       continue; //TODO: hacer algo (cerrar la conexion)
	  }
	  std::string comando = s->getNombre();
	       
	  std::cout << "Mensaje: " << comando << std::endl;

	  //me fijo de que tipo es el mensaje
	  if(comando.compare("SeleccionarCircuito")==0){
	       std::cout << "Seleccionando circuito " << s->getParametro("Nombre") << std::endl;
	       controlador= new ControladorVentana();
	       bool respuesta;
	       if(controlador->cargar(s->getParametro("Nombre"))){
		    respuesta = 1;
		    c = controlador->getCircuito();
	       }
	       else{
		    respuesta = 0;
		    delete controlador;
	       }
	       Soap res("SeleccionarCircuitoResponse");
	       res.setParametro("Estado", respuesta);
	       m.enviarRespuesta(&res);
    
	  }
	  else if(comando.compare("GetListado")==0){
	       std::cout << "Listado de circuitos: " << std::endl;
	       Soap res("GetListadoResponse");
	       XmlNodo &cuerpo = res.getCuerpo();
	       std::list<DescripcionCircuito> circuitos = server->getListaCircuitos();
	       while(circuitos.size()>0){
		    DescripcionCircuito d = circuitos.front();
		    circuitos.pop_front();
		    XmlNodo nodo("Circuito");
		    nodo.setPropiedad("nombre", d.nombre.c_str());
		    nodo.setPropiedad("cantidadEntradas", Util::intToString(d.cantidadEntradas).c_str());
		    nodo.setPropiedad("cantidadSalidas", Util::intToString(d.cantidadSalidas).c_str());
		    cuerpo.agregarHijo(nodo);

	       }
	       m.enviarRespuesta(&res);
	       stop();
	  }
	  else if(comando.compare("ObtenerCircuito")==0){
	       std::cout << "Obtener un circuito: " << s->getParametro("nombre") << std::endl;
	       std::ifstream archivo(s->getParametro("nombre").c_str(), std::ifstream::in);
	       std::string buffer, linea;
	       if(archivo.is_open()){
		    while(archivo.good()){
			 std::getline(archivo, linea);
			 buffer += linea;
		    }
	       }
	       Soap res("ObtenerCircuitoResponse");
	       if(buffer.size() > 0)
		    res.setParametro("archivo", buffer.c_str());

	       m.enviarRespuesta(&res);
	       stop();
	  }
	  else if(comando.compare("SetPin")==0){
	       std::cout << "Setear pin " << s->getParametroNumerico("Numero") << \
		    " en " << s->getParametroNumerico("Valor") << std::endl;
	       c->setPin(s->getParametroNumerico("Numero"), s->getParametroNumerico("Valor"));
	  }

	  else if(comando.compare("SetEntrada")==0){
	       std::cout << "Setear entrada " << s->getParametroNumerico("Numero") << \
		    " en " << s->getParametroNumerico("Valor") << std::endl; 
	       c->setEntrada(s->getParametroNumerico("Numero"), s->getParametroNumerico("Valor"));
	  }

	  else if(comando.compare("EsEstable")==0){
	       std::cout << "Es estable " << std::endl;
	       bool estado = c->esEstable();
	       Soap res("EsEstableResponse");
	       res.setParametro("Estado", estado);
	       m.enviarRespuesta(&res);
	  }


	  else if(comando.compare("GetEntrada")==0){
	       std::cout << "Get entrada " << s->getParametroNumerico("Numero") << std::endl;
	       bool estado = c->getEntrada(s->getParametroNumerico("Numero"));
	       Soap res("GetEntradaResponse");
	       res.setParametro("Numero", s->getParametroNumerico("Numero"));
	       res.setParametro("Valor", estado);
	       m.enviarRespuesta(&res);
	  }

	  else if(comando.compare("GetSalida")==0){
	       std::cout << "Get salida " << s->getParametroNumerico("Numero") << std::endl;
	       bool estado = c->getSalida(s->getParametroNumerico("Numero"));
	       Soap res("GetSalidaResponse");
	       res.setParametro("Numero", s->getParametroNumerico("Numero"));
	       res.setParametro("Valor", estado);
	       m.enviarRespuesta(&res);
	  }


	  else if(comando.compare("GetPin")==0){
	       std::cout << "Get pin " << s->getParametroNumerico("Numero") << std::endl;
	       bool estado = c->getPin(s->getParametroNumerico("Numero"));
	       Soap res("GetPinResponse");
	       res.setParametro("Numero", s->getParametroNumerico("Numero"));
	       res.setParametro("Valor", estado);
	       m.enviarRespuesta(&res);
	  }

	  else if(comando.compare("Reset")==0){
	       c->reset();
	       std::cout << "Reset" << std::endl;
	  }

	  else if(comando.compare("GetCantidadEntradas")==0){
	       std::cout << "Get entradas " << std::endl;
	       int cantidad = c->getCantidadEntradas();
	       Soap res("GetCantidadEntradasResponse");
	       res.setParametro("Valor", cantidad);
	       m.enviarRespuesta(&res);
	  }

	  else if(comando.compare("GetCantidadSalidas")==0){
	       std::cout << "Get salidas " << std::endl;
	       int cantidad = c->getCantidadSalidas();
	       Soap res("GetCantidadSalidasResponse");
	       res.setParametro("Valor", cantidad);
	       m.enviarRespuesta(&res);
	  }

	  else if(comando.compare("GetTProximoEvento")==0){
	       std::cout << "Get T proximo evento " << std::endl;
	       int cantidad = c->getTProximoEvento();
	       Soap res("GetTProximoEventoResponse");
	       res.setParametro("Valor", cantidad);
	       m.enviarRespuesta(&res);
	  }

	  else if(comando.compare("Simular")==0){
	       std::cout << "Simular " << s->getParametroNumerico("Tiempo") <<std::endl;
	       c->simular(s->getParametroNumerico("Tiempo"));
	  }

	  else if(comando.compare("Desconectar")==0){
	       std::cout << "Desconectar" << std::endl;
	       delete c;
	       finish();
	  }


	  delete s;
     }
     delete ns;

     server->finalizarCliente(this);
}
