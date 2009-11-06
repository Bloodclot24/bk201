#ifndef __MENSAJERO_H_INCLUDED__
#define __MENSAJERO_H_INCLUDED__

#include "Socket.h"
#include "../XML/Soap.h"
#include "../HTTP/HttpRequest.h"
#include "../HTTP/HttpResponse.h"

class Mensajero{
private:
     Socket *s;
     Mensajero(const Mensajero&);
     Mensajero& operator=(const Mensajero&);
public:     
     Mensajero(){ s = NULL;}
     void setSocket(Socket *s);

     Soap* recibirMensaje();
     Soap* recibirRespuesta();

     int enviarMensaje(Soap* soap);
     int enviarRespuesta(Soap* soap);
};

#endif //__MENSAJERO_H_INCLUDED__
