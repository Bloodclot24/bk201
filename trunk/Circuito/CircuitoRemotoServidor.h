#ifndef __CIRCUITO_REMOTO_SERVIDOR__
#define __CIRCUITO_REMOTO_SERVIDOR__

#include "Circuito.h"
#include "../Red/Mensajero.h"
#include "../Threads/Threads.h"
#include "../Gates/Gates.h"
#include "../Util/Util.h"

/**
 * Sumador completo de 1 bit
 * http://www.unicrom.com/dig_suma_binaria_completo.asp 
 *
 */
class Sumador:public Circuito{
public:
     Sumador():Circuito(3,2){
	  agregarComponente(new GateXor());
	  agregarComponente(new GateAnd());
	  agregarComponente(new GateXor());
	  agregarComponente(new GateAnd());
	  agregarComponente(new GateOr());
	  
	  agregarConexion(-1,0,0,0);
	  agregarConexion(-1,0,1,0);
	  agregarConexion(-1,1,0,1);
	  agregarConexion(-1,1,1,1);
	  agregarConexion(-1,2,2,1);
	  agregarConexion(-1,2,3,1);
	  agregarConexion(0,2,2,0);
	  agregarConexion(0,2,3,0);
	  agregarConexion(1,2,4,1);
	  agregarConexion(2,2,-1,3);
	  agregarConexion(3,2,4,0);
	  agregarConexion(4,2,-1,4);
     }
     
};


class CircuitoRemotoServidor: public Thread{
private:
     Socket *ns;		/**< Socket a utilizar */
     Mensajero m;
     Soap *s;
     Circuito *c;
public:

     CircuitoRemotoServidor(Socket *s){
	  ns=s;
	  m.setSocket(s);
     }

     void run(){
	  while(isRunning()){
	       s = m.recibirMensaje();
	       if(s== NULL){
//		    std::cout << "El mensaje es NULL\n";
		    stop();
		    continue; //TODO: hacer algo (cerrar la conexion)
	       }
	       std::string comando = s->getNombre();
	       
	       std::cout << "Mensaje: " << comando << std::endl;

	       if(comando.compare("SeleccionarCircuito")==0){
		    std::cout << "Seleccionando circuito " << s->getParametro("Nombre") << std::endl;
		    c = new Sumador();
	       }
	       else if(comando.compare("GetListado")==0){
		    std::cout << "Listado de circuitos: " << std::endl;
		    Soap res("GetListadoResponse");
		    XmlNodo &cuerpo = res.getCuerpo();
		    for(int i=0;i<rand()%10+1;i++){
			 XmlNodo nodo("Circuito");
			 nodo.setPropiedad("nombre", "lalalalala");
			 nodo.setPropiedad("cantidadEntradas", Util::intToString(rand()%6+1).c_str());
			 nodo.setPropiedad("cantidadSalidas", Util::intToString(rand()%6+1).c_str());
			 cuerpo.agregarHijo(nodo);
		    }
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
     }

};

#endif //__CIRCUITO_REMOTO_SERVIDOR__
