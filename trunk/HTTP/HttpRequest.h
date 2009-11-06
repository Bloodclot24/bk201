#ifndef HTTPREQUEST_H_INCLUDED
#define HTTPREQUEST_H_INCLUDED

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>

/****************************************************************************/
/*
 * Clase para construir un request HTTP 
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

public:
     /**
      * Crea un nuevo request HTTP con la url indicada y sin parametros.
      * 
      * @param direccion Direccion a crearle el Http Request.
      */
     HttpRequest(std::string direccion);

     void setContentLength(unsigned length);
     
     unsigned getContentLength(){ return contentLength; }
     
     /**
      * Devuelve un nuevo string con el request completo. El string
      * debe ser liberado externamente luego de ser utilizado.
      * 
      * @return El request.
      */
     std::string& getRequest();

     HttpRequest(const std::string& datos, bool otro);

     bool esValido();
};

/****************************************************************************/
#endif //HTTPREQUEST_H_INCLUDED
