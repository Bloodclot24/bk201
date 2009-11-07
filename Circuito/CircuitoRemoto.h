#ifndef __CIRCUITOREMOTO_H_INCLUDED__
#define __CIRCUITOREMOTO_H_INCLUDED__

#include "../Componente/Componente.h"
#include "../Red/Socket.h"
#include "../Red/Mensajero.h"
#include "../XML/Soap.h"

class CircuitoRemoto: public Componente{
     Socket *s;
     Mensajero mensajero;

public:
     CircuitoRemoto(const std::string& host, const std::string& nombre){
	  s = new Socket(host,0);
	  s->conectar();
	  mensajero.setSocket(s);
	  Soap mensaje("SeleccionarCircuito");
	  mensaje.setParametro("Nombre", nombre.c_str());
	  mensajero.enviarMensaje(&mensaje);
     }

     bool esEstable(){
	  Soap mensaje("EsEstable");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("EsEstableResponse")){
	       valor = respuesta->getParametroNumerico("Estado");
	  }
	  return valor;

     }

     void setEntrada(unsigned numero, bool estado){
	  Soap mensaje("SetEntrada");
	  mensaje.setParametro("Numero", numero);
	  mensaje.setParametro("Valor", estado);
	  mensajero.enviarMensaje(&mensaje);
     }

     bool getEntrada(unsigned numero){
	  Soap mensaje("GetEntrada");
	  mensaje.setParametro("Numero", numero);
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta!= NULL &&					\
	     !respuesta->getNombre().compare("GetEntradaResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	  }
	  return valor;
     }

     bool getSalida(unsigned numero){
	  Soap mensaje("GetSalida");
	  mensaje.setParametro("Numero", numero);
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("GetSalidaResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	  }
	  return valor;
     }

     bool getPin(unsigned numero){
	  Soap mensaje("GetPin");
	  mensaje.setParametro("Numero", numero);
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta != NULL &&				\
	     !respuesta->getNombre().compare("GetPinResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	       delete respuesta;
	  }
	  return valor;
     }

     void setPin(unsigned numero, bool estado){
	  Soap mensaje("SetPin");
	  mensaje.setParametro("Numero", numero);
	  mensaje.setParametro("Valor", estado);
	  mensajero.enviarMensaje(&mensaje);
     }

     void reset(){
	  Soap mensaje("Reset");
	  mensajero.enviarMensaje(&mensaje);
     }

     unsigned getCantidadEntradas(){
	  Soap mensaje("GetCantidadEntradas");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  unsigned valor=0;
	  if(respuesta != NULL  &&					\
	     !respuesta->getNombre().compare("GetCantidadEntradasResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	  }
	  return valor;
     }
     
     unsigned getCantidadSalidas(){
	  Soap mensaje("GetCantidadSalidas");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  unsigned valor=0;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("GetCantidadSalidasResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	  }
	  return valor;
     }
     
     uint64_t getTProximoEvento(){
	  Soap mensaje("GetTProximoEvento");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  uint64_t valor=(uint64_t)-1;
	  if(respuesta != NULL  &&					\
	     !respuesta->getNombre().compare("GetTProximoEventoResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	  }
	  return valor;
     }

     void simular(uint64_t tiempo){
	  Soap mensaje("Simular");
	  mensaje.setParametro("Tiempo", tiempo);
	  mensajero.enviarMensaje(&mensaje);
     }

     ~CircuitoRemoto(){
	  delete s;
     }

};

#endif //__CIRCUITOREMOTO_H_INCLUDED__
