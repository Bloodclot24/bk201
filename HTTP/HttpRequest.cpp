#include "HttpRequest.h"

/****************************************************************************/
HttpRequest::HttpRequest(std::string direccion):url(direccion){
     valido = true;
     contentLength=0;
     comienzoDatos=0;
}

void HttpRequest::setContentLength(unsigned length){
     contentLength=length;
}

/*--------------------------------------------------------------------------*/
std::string& HttpRequest::getRequest(void){
     /* borro la cabecera anterior */
     paquete.clear();

     std::string host, dir;

     /* intento decodificar el host */
     int auxiliar = strlen("http://");
     if(url.compare(0,auxiliar,"http://") != 0){
	  auxiliar = 0;
     }

     host = url.substr(auxiliar, url.find_first_of("/",auxiliar)-auxiliar);
     if(url.find('/',auxiliar) != std::string::npos)
	  dir  = url.substr(url.find('/',auxiliar));

     /* simplemente armo la cabecera */
     paquete += "POST ";
     paquete += dir;
     paquete += " HTTP/1.1\r\n";
     paquete += "Host: ";
     paquete += host;
     if(contentLength > 0){
	  paquete += "\r\nContent-Type: application/soap+xml; charset=utf-8\r\n";
	  paquete += "Content-Length: ";
	  std::stringstream n;
	  n << contentLength;
	  paquete += n.str();
     }
     paquete+= "\r\n\r\n";

     return paquete;
}

/****************************************************************************/

HttpRequest::HttpRequest(){
     valido = false;
     contentLength=0;
}

bool HttpRequest::esValido(){ return valido;}

HttpRequest::HttpRequest(const std::string& datos, bool otro){
     valido = false;
     size_t limite;

     /* busco el final de la cabecera */
     limite=datos.find("\r\n\r\n");
     
     /* si no lo encuentro, seguro que no es valido, salgo */
     if(limite == std::string::npos)
	  return;

     /* Busco el tipo de request */
     if(datos.compare(0,4,"POST")==0)
	  tipo="POST";
     else if(datos.compare(0,3,"GET")==0)
	  tipo="GET";
     else return ;

     /* busco la longitud y comienzo del area de datos */
     size_t pos = datos.find("\r\nContent-Type:");
     if(pos < limite){
	  contentType=datos.substr(datos.find(':',pos)+1,datos.find(";",pos)-datos.find(':',pos)-1);
	  size_t pos = datos.find("\r\nContent-Length:");
	  if(pos < limite){
	       size_t pos2 = pos+strlen("\r\nContent-Lrngth:");
	       contentLength = atoi(datos.c_str()+pos2);
	  }
     }

     comienzoDatos = limite+strlen("\r\n\r\n");

     valido = true;
}
