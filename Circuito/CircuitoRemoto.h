#ifndef __CIRCUITOREMOTO_H_INCLUDED__
#define __CIRCUITOREMOTO_H_INCLUDED__

#include "../Componente/Componente.h"
#include "../Red/Socket.h"
#include "../Red/Mensajero.h"
#include "../XML/Soap.h"

/** 
 * Tipo de componente que representa un circuito en otro servidor.
 */
class CircuitoRemoto: public Componente{
     Socket *s;			/**< Socket por el cual me conecto  */
     Mensajero mensajero;
     unsigned entradas,salidas;
     std::string nombre;
public:
     CircuitoRemoto(const std::string& host, int puerto, const std::string& nombre){
	  s = new Socket(host,puerto);
	  mensajero.setSocket(s);
	  entradas= salidas= (unsigned) -1;
	  this->nombre = nombre;
     }

     bool conectar(){
	  s->conectar();
	  Soap mensaje("SeleccionarCircuito");
	  mensaje.setParametro("Nombre", nombre.c_str());
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("SeleccionarCircuitoResponse")){
	       valor = respuesta->getParametroNumerico("Estado");
	       delete respuesta;
	  }
	  return valor;
     }

     bool esEstable(){
	  if(!s->esValido())
	       return false;
	  Soap mensaje("EsEstable");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("EsEstableResponse")){
	       valor = respuesta->getParametroNumerico("Estado");
	       delete respuesta;
	  }
	  return valor;

     }

     void setEntrada(unsigned numero, bool estado){
	  if(!s->esValido())
	       return;
	  Soap mensaje("SetEntrada");
	  mensaje.setParametro("Numero", numero);
	  mensaje.setParametro("Valor", estado);
	  mensajero.enviarMensaje(&mensaje);
     }

     bool getEntrada(unsigned numero){
	  if(!s->esValido())
	       return false;
	  Soap mensaje("GetEntrada");
	  mensaje.setParametro("Numero", numero);
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta!= NULL &&					\
	     !respuesta->getNombre().compare("GetEntradaResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	       delete respuesta;
	  }
	  return valor;
     }

     bool getSalida(unsigned numero){
	  if(!s->esValido())
	       return false;
	  Soap mensaje("GetSalida");
	  mensaje.setParametro("Numero", numero);
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  bool valor=false;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("GetSalidaResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	       delete respuesta;
	  }
	  return valor;
     }

     bool getPin(unsigned numero){
	  if(!s->esValido())
	       return false;

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
	  if(!s->esValido())
	       return;
	  Soap mensaje("SetPin");
	  mensaje.setParametro("Numero", numero);
	  mensaje.setParametro("Valor", estado);
	  mensajero.enviarMensaje(&mensaje);
     }

     void reset(){
	  if(!s->esValido())
	       return;
	  Soap mensaje("Reset");
	  mensajero.enviarMensaje(&mensaje);
     }

     unsigned getCantidadEntradas(){
	  if(entradas != (unsigned)-1)
	       return entradas;
	  if(!s->esValido())
	       return 0;
	  Soap mensaje("GetCantidadEntradas");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  unsigned valor=0;
	  if(respuesta != NULL  &&					\
	     !respuesta->getNombre().compare("GetCantidadEntradasResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	       delete respuesta;
	  }
	  entradas=valor;
	  return valor;
     }
     
     unsigned getCantidadSalidas(){
	  if(salidas != (unsigned)-1)
	       return salidas;
	  if(!s->esValido())
	       return 0;
	  Soap mensaje("GetCantidadSalidas");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  unsigned valor=0;
	  if(respuesta != NULL &&					\
	     !respuesta->getNombre().compare("GetCantidadSalidasResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	       delete respuesta;
	  }
	  salidas=valor;
	  return valor;
     }
     
     uint64_t getTProximoEvento(){
	  if(!s->esValido())
	       return (uint64_t)-1;
	  Soap mensaje("GetTProximoEvento");
	  mensajero.enviarMensaje(&mensaje);
	  Soap *respuesta = mensajero.recibirRespuesta();
	  uint64_t valor=(uint64_t)-1;
	  if(respuesta != NULL  &&					\
	     !respuesta->getNombre().compare("GetTProximoEventoResponse")){
	       valor = respuesta->getParametroNumerico("Valor");
	       delete respuesta;
	  }
	  return valor;
     }

     void simular(uint64_t tiempo){
	  if(!s->esValido())
	       return;
	  Soap mensaje("Simular");
	  mensaje.setParametro("Tiempo", tiempo);
	  mensajero.enviarMensaje(&mensaje);
     }

     virtual ~CircuitoRemoto(){
	  if(s->esValido()){
	       Soap mensaje("Desconectar");
	       mensajero.enviarMensaje(&mensaje);
	  }

	  delete s;
     }

};

#endif //__CIRCUITOREMOTO_H_INCLUDED__
