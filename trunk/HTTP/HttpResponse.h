#ifndef HTTPRESPONSE_H_INCLUDED
#define HTTPRESPONSE_H_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

/****************************************************************************/
/* 
 * Clase para parsear la respuesta HTTP 
 */
class HttpResponse{

private:
     std::string response;
     unsigned offsetVersion, offsetCode;
     unsigned longitudContenido;
     unsigned offsetContenido;
     std::string contentType;
     unsigned contentLength;
     unsigned codigo;
     unsigned comienzoDatos;
     bool valido;

     HttpResponse();

public:
     /**
      * Dado un string con la respuesta, lo parsea obteniendo los
      * datos que nos interesan.
      * 
      * @param respuesta Respuesta a parsear.
      */
     HttpResponse(unsigned codigo);

     std::string& getResponse();
     
     void setContentLength(unsigned length);

     /**
      * Devuelve la longitud del area de datos de la respuesta.
      * 
      * @return La longitud del contenido.
      */
     int getContentLength();

     HttpResponse(const std::string& datos);

     bool esValido();
};

/****************************************************************************/
#endif //HTTPRESPONSE_H_INCLUDED
