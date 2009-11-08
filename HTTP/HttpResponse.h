#ifndef HTTPRESPONSE_H_INCLUDED
#define HTTPRESPONSE_H_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

/** 
 * Clase que crea cabeceras de respuesta HTTP
 * 
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
     HttpResponse& operator=(const HttpResponse& );
     HttpResponse(const HttpResponse&);

public:
     /** 
      * Crea una respuesta HTTP con el codigo solicitado.
      * 
      * @param codigo Codigo de la respuesta (200, 400, etc)
      */
     HttpResponse(unsigned codigo);

     /** 
      * Devuelve un string con la respuesta HTTP. Cada llamada
      * destruye la respuesta anterior. Si se quiereconservar se debe
      * copiar elstring antes de la siguiente llamada.
      * 
      * @return La respuesta HTTP.
      */
     std::string& getResponse();
     
     /** 
      * Indica el tamaño de los datos de la respuesta HTTP.
      * 
      * @param length La longitud de los datos.
      */
     void setContentLength(unsigned length);

     /**
      * Devuelve la longitud del area de datos de la respuesta.
      * 
      * @return La longitud del contenido.
      */
     int getContentLength();

     /** 
      * Decodifica una respuesta HTTP de un buffer de datos.
      * 
      * @param datos El string que contiene la cabecera a decodificar.
      */
     HttpResponse(const std::string& datos);

     /** 
      * Indica si los datos contenidos en la respuesta son validos o
      * no.
      * 
      * @return TRUE si es valido.
      */
     bool esValido();
};

/****************************************************************************/
#endif //HTTPRESPONSE_H_INCLUDED
