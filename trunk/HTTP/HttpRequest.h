#ifndef HTTPREQUEST_H_INCLUDED
#define HTTPREQUEST_H_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

/** 
 * Clase para construir un request HTTP 
 * 
 */
class HttpRequest{

private:
     std::string url;
     std::string paquete;
     unsigned contentLength;
     std::string tipo;
     std::string contentType;
     unsigned comienzoDatos;
     bool valido;
     

     HttpRequest();
     HttpRequest(const HttpRequest&);
     HttpRequest& operator=(const HttpRequest&);

public:
     /**
      * Crea un nuevo request HTTP con la url indicada y sin parametros.
      * 
      * @param direccion Direccion destino del request.
      */
     HttpRequest(std::string direccion);

     /** 
      * Especifica la longitud del area de datos.
      * 
      * @param length Longitud del contenido.
      */
     void setContentLength(unsigned length);
     
     /** 
      * Devuelve la longitud del area de datos.
      * 
      * @return Longitud de los datos.
      */
     unsigned getContentLength(){ return contentLength; }
     
     /**
      * Devuelve un nuevo string con el request completo (la cabecera
      * HTTP). Cada nueva llamada destruye el string creado
      * anteriormente, si se quisiera conservar deberia copiarse antes
      * de la proxima llamada.
      * 
      * @return El request.
      */
     std::string& getRequest();

     /** 
      * Decodifica una cabecera HTTP.
      * 
      * @param datos El buffer con la cabecera.
      * @param otro Solo sirve para distinguirlo del otro constructor.
      */
     HttpRequest(const std::string& datos, bool otro);

     /** 
      * Indica si los datos contenidos en el request son validos o
      * no. Esto sirve, por ejemplo, si se decodifico una cabecera
      * HTTP y se quiere saber si se tuvo exito o no.
      * 
      * 
      * @return True si la cabecera es valida.
      */
     bool esValido();
};

/****************************************************************************/
#endif //HTTPREQUEST_H_INCLUDED
