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
  bool conectado;
public:
  CircuitoRemoto(const std::string& host, int puerto, const std::string& nombre){
    s = new Socket(host,puerto);
    mensajero.setSocket(s);
    entradas= salidas= (unsigned) -1;
    this->nombre = nombre;
    conectado = false;
  }

  /**
   * Se conecta al servidor en cuestion, en caso de no poder hacerlo
   * devuelve false. Si pudo conectarse, intenta seleccionar el circuito
   * si puede hacerlo devuelve true, en caso contrario devuelve false.
   *
   */
  bool conectar(){
    bool valor=false;
    if(!conectado)
      conectado = s->conectar(15);
    if(conectado){
      Soap mensaje("SeleccionarCircuito");
      mensaje.setParametro("Nombre", nombre.c_str());
      mensajero.enviarMensaje(&mensaje);
      Soap *respuesta = mensajero.recibirRespuesta();
      if(respuesta != NULL &&					\
	 !respuesta->getNombre().compare("SeleccionarCircuitoResponse")){
	valor = respuesta->getParametroNumerico("Estado");
	delete respuesta;
      }
    }
	  
    return valor;
  }

  /**
   * Devuelve true en caso de que el circuito
   * sea estable, en caso contrario devuelve false.
   *
   */
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

  /**
   * Obtiene el estado de la entrada solicitada.
   *
   * @param numero Es el numero de entrada de la cual se quiere obtener el estado.
   *
   */
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

  /**
   * Obtiene el estado de la salida solicitada.
   *
   * @param numero Es el numero de salida de la cual se quiere obtener el estado.
   *
   */
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

  /**
   * Obtiene el estado del pin solicitado.
   *
   * @param numero Es el numero de pin de la cual se quiere obtener el estado.
   *
   */
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

  /**
   * Setea el estado al pin en cuestion.
   *
   * @param numero Es el numero de pin al que se le quiere setear el estado.
   * @param estado Es el estado a setearle al pin.
   *
   */
  void setPin(unsigned numero, bool estado){
    if(!s->esValido())
      return;
    Soap mensaje("SetPin");
    mensaje.setParametro("Numero", numero);
    mensaje.setParametro("Valor", estado);
    mensajero.enviarMensaje(&mensaje);
  }

  /**
   * Coloca todas las entradas y salidas del componente en estado
   * logico bajo.
   *
   */
  void reset(){
    if(!s->esValido())
      return;
    Soap mensaje("Reset");
    mensajero.enviarMensaje(&mensaje);
  }

  /**
   * Obtiene la cantidad de entradas del circuito.
   *
   */
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
     
  /**
   * Devuelve la cantidad de salidas del circuito.
   *
   */
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
     
  /**
   * Devuelve la cantidad de tiempo que debe transcurrir hasta que
   * se estabilize la salida del componente.
   *
   *
   * @return El tiempo hasta la estabilizacion.
   */
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

  /**
   * Corre la simulacion del componente.
   *
   * @param tiempo El tiempo de operacion a simular.
   */
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
