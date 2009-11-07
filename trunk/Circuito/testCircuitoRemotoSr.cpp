#include <sstream>
#include "../Red/Mensajero.h"

int main(int argc, char** argv){
     int puerto=1234;

     if(argc > 1){
	  puerto = atoi(argv[1]);
	  if(puerto == 0)
	       puerto = 1234;
     }
     
     std::cout << "Usando puerto " << puerto << std::endl;
     
     Socket sock("localhost" , puerto);

     sock.enlazar();

     sock.escuchar();
     
     Socket *ns = sock.aceptar();

     Mensajero m(ns);

     Soap *s;

     s = m.recibirMensaje();
     if(s != NULL){
	  std::cout << s->getNombre() << std::endl;
	  if(s->getNombre().compare("SeleccionarCircuito")==0){
	       std::cout << "Seleccionando circuito " << s->getParametro("Nombre") << std::endl;
	       bool salir=false;
	       delete s;
	       while(!salir){
		    s = m.recibirMensaje();
		    if(s== NULL)
			 break;
		    std::string comando = s->getNombre();

		    std::cout << "Mensaje: " << comando << std::endl;

		    if(comando.compare("SetPin")==0){
			 std::cout << "Setear pin " << s->getParametroNumerico("Numero") << \
			      " en " << s->getParametroNumerico("Valor") << std::endl; 
		    }

		    if(comando.compare("SetEntrada")==0){
			 std::cout << "Setear entrada " << s->getParametroNumerico("Numero") << \
			      " en " << s->getParametroNumerico("Valor") << std::endl; 
		    }

		    if(comando.compare("EsEstable")==0){
			 std::cout << "Es estable " << std::endl;
			 Soap res("EsEstableResponse");
			 res.setParametro("Estado", 1);
			 m.enviarRespuesta(&res);
		    }


		    if(comando.compare("GetEntrada")==0){
			 std::cout << "Get entrada " << s->getParametroNumerico("Numero") << std::endl;
			 Soap res("GetEntradaResponse");
			 res.setParametro("Numero", s->getParametroNumerico("Numero"));
			 res.setParametro("Valor", 1);
			 m.enviarRespuesta(&res);
		    }

		    if(comando.compare("GetSalida")==0){
			 std::cout << "Get salida " << s->getParametroNumerico("Numero") << std::endl;
			 Soap res("GetSalidaResponse");
			 res.setParametro("Numero", s->getParametroNumerico("Numero"));
			 res.setParametro("Valor", 1);
			 m.enviarRespuesta(&res);
			 salir = true;
		    }


		    if(comando.compare("GetPin")==0){
			 std::cout << "Get pin " << s->getParametroNumerico("Numero") << std::endl;
			 Soap res("GetPinResponse");
			 res.setParametro("Numero", s->getParametroNumerico("Numero"));
			 res.setParametro("Valor", 1);
			 m.enviarRespuesta(&res);
			 salir = true;
		    }

		    if(comando.compare("Reset")==0){
			 std::cout << "Reset" << std::endl;
		    }

		    if(comando.compare("GetCantidadEntradas")==0){
			 std::cout << "Get entradas " << std::endl;
			 Soap res("GetCantidadEntradasResponse");
			 res.setParametro("Valor", 5);
			 m.enviarRespuesta(&res);
			 salir = true;
		    }

		    if(comando.compare("GetCantidadSalidas")==0){
			 std::cout << "Get salidas " << std::endl;
			 Soap res("GetCantidadSalidasResponse");
			 res.setParametro("Valor", 5);
			 m.enviarRespuesta(&res);
			 salir = true;
		    }

		    if(comando.compare("GetTProximoEvento")==0){
			 std::cout << "Get T proximo evento " << std::endl;
			 Soap res("GetTProximoEventoResponse");
			 res.setParametro("Valor", 10);
			 m.enviarRespuesta(&res);
			 salir = true;
		    }

		    if(comando.compare("Simular")==0){
			 std::cout << "Simular " << s->getParametroNumerico("Tiempo") <<std::endl;
		    }
		    salir = false;

		    delete s;
	       }
	  }
     }

     delete ns;

     return 1;

}
