#ifndef __CIRCUITO_REMOTO_SERVIDOR__
#define __CIRCUITO_REMOTO_SERVIDOR__

#include "Circuito.h"
#include "../Threads/Threads.h"

class CircuitoRemotoServidor:Thread{
private:
     Socket *ns;		/**< Socket a utilizar */
     Mensajero m;
     Soap *s;
     Circuito *c;
public:

     CircuitoRemotoServidor(Socket *s);

     void run(){
	  while(corriendo){
	       s = m.recibirMensaje();
	       if(s== NULL)
		    continue; //TODO: hacer algo (cerrar la conexion)
	       std::string comando = s->getNombre();
	       
	       std::cout << "Mensaje: " << comando << std::endl;

	       if(comando.compare("SeleccionarCircuito")==0)
		    std::cout << "Seleccionando circuito " << s->getParametro("Nombre") << std::endl;
	       
	       else if(comando.compare("SetPin")==0){
		    std::cout << "Setear pin " << s->getParametroNumerico("Numero") << \
			 " en " << s->getParametroNumerico("Valor") << std::endl; 
	       }

	       else if(comando.compare("SetEntrada")==0){
		    std::cout << "Setear entrada " << s->getParametroNumerico("Numero") << \
			 " en " << s->getParametroNumerico("Valor") << std::endl; 
	       }

	       else if(comando.compare("EsEstable")==0){
		    std::cout << "Es estable " << std::endl;
		    Soap res("EsEstableResponse");
		    res.setParametro("Estado", 1);
		    m.enviarRespuesta(&res);
	       }


	       else if(comando.compare("GetEntrada")==0){
		    std::cout << "Get entrada " << s->getParametroNumerico("Numero") << std::endl;
		    Soap res("GetEntradaResponse");
		    res.setParametro("Numero", s->getParametroNumerico("Numero"));
		    res.setParametro("Valor", 1);
		    m.enviarRespuesta(&res);
	       }

	       else if(comando.compare("GetSalida")==0){
		    std::cout << "Get salida " << s->getParametroNumerico("Numero") << std::endl;
		    Soap res("GetSalidaResponse");
		    res.setParametro("Numero", s->getParametroNumerico("Numero"));
		    res.setParametro("Valor", 1);
		    m.enviarRespuesta(&res);
	       }


	       else if(comando.compare("GetPin")==0){
		    std::cout << "Get pin " << s->getParametroNumerico("Numero") << std::endl;
		    Soap res("GetPinResponse");
		    res.setParametro("Numero", s->getParametroNumerico("Numero"));
		    res.setParametro("Valor", 1);
		    m.enviarRespuesta(&res);
	       }

	       else if(comando.compare("Reset")==0){
		    std::cout << "Reset" << std::endl;
	       }

	       else if(comando.compare("GetCantidadEntradas")==0){
		    std::cout << "Get entradas " << std::endl;
		    Soap res("GetCantidadEntradasResponse");
		    res.setParametro("Valor", 5);
		    m.enviarRespuesta(&res);
	       }

	       else if(comando.compare("GetCantidadSalidas")==0){
		    std::cout << "Get salidas " << std::endl;
		    Soap res("GetCantidadSalidasResponse");
		    res.setParametro("Valor", 5);
		    m.enviarRespuesta(&res);
	       }

	       else if(comando.compare("GetTProximoEvento")==0){
		    std::cout << "Get T proximo evento " << std::endl;
		    Soap res("GetTProximoEventoResponse");
		    res.setParametro("Valor", 10);
		    m.enviarRespuesta(&res);
	       }

	       else if(comando.compare("Simular")==0){
		    std::cout << "Simular " << s->getParametroNumerico("Tiempo") <<std::endl;
	       }

	       delete s;
	  }
     }

};

#endif //__CIRCUITO_REMOTO_SERVIDOR__
