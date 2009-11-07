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
     paquete.clear();

     std::string host, dir;

     int auxiliar = strlen("http://");
     if(url.compare(0,auxiliar,"http://") != 0){
	  auxiliar = 0;
     }

     host = url.substr(auxiliar, url.find_first_of("/",auxiliar)-auxiliar);
     if(url.find('/',auxiliar) != std::string::npos)
	  dir  = url.substr(url.find('/',auxiliar));

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
     limite=datos.find("\r\n\r\n");
     if(limite == std::string::npos)
	  return;

     if(datos.compare(0,4,"POST")==0)
	  tipo="POST";
     else if(datos.compare(0,3,"GET")==0)
	  tipo="GET";
     else return ;

//     std::cout << "Tipo: " << tipo << std::endl;

     size_t pos = datos.find("\r\nContent-Type:");
     if(pos < limite){
	  contentType=datos.substr(datos.find(':',pos)+1,datos.find(";",pos)-datos.find(':',pos)-1);
//	  std::cout << "content type:" << contentType << std::endl;
	  size_t pos = datos.find("\r\nContent-Length:");
	  if(pos < limite){
	       size_t pos2 = pos+strlen("\r\nContent-Lrngth:");
	       contentLength = atoi(datos.c_str()+pos2);
//	       std::cout << "tamaño de datos: " << contentLength << std::endl;
	  }
     }

     comienzoDatos = limite+strlen("\r\n\r\n");

//     std::cout << "Comienzo de los datos: " << comienzoDatos << std::endl;

     valido = true;
}
