#ifndef __MENSAJERO_H_INCLUDED__
#define __MENSAJERO_H_INCLUDED__

#include "Socket.h"
#include "../XML/Soap.h"
#include "../HTTP/HttpRequest.h"
#include "../HTTP/HttpResponse.h"

/** 
 * Clase que se utiliza para enviar y recibir mensajes SOAP.
 * 
 */
class Mensajero{
private:
     Socket *s;			/**< Socket a utilizar */
     Mensajero(const Mensajero&);
     Mensajero& operator=(const Mensajero&);
public:     
     /** 
      * Crea un mensajero con un socket.
      * 
      * @param s Elsocket a utilizar.
      */
     Mensajero(Socket* s){ this->s=s;}

     /** 
      * Crea un mensajero.
      */
     Mensajero(){ s = NULL;}

     /** 
      * Asigna un socket al mensajero.
      * 
      * @param s 
      */
     void setSocket(Socket *s);

     /** 
      * Recibe un request HTTP y devuelve (si existe) el mensaje SOAP
      * asociado.
      * 
      * @return Mensaje Soap.
      */
     Soap* recibirMensaje();

     /** 
      * Recibe un response HTTP y devuelve (si existe) el mensaje SOAP
      * asociado.
      * 
      * @return Mensaje SOAP.
      */
     Soap* recibirRespuesta();

     /** 
      * Envia un mensaje SOAP en un request HTTP.
      * 
      * @param soap El mensaje a enviar.
      * 
      * @return Codigo de error.
      */
     int enviarMensaje(Soap* soap);

     /** 
      * Envia un mensaje SOAP en un response HTTP.
      * 
      * @param soap El mensaje a enviar.
      * 
      * @return Codigo de error.
      */
     int enviarRespuesta(Soap* soap);
};

#endif //__MENSAJERO_H_INCLUDED__
