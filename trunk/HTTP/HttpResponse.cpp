#include "HttpResponse.h"

/****************************************************************************/
HttpResponse::HttpResponse(unsigned codigo){
  this->codigo = codigo;
}


/*--------------------------------------------------------------------------*/
int HttpResponse::getContentLength(){
  return contentLength;
}

void HttpResponse::setContentLength(unsigned length){
  contentLength=length;
}

std::string& HttpResponse::getResponse(){
  response.clear();

  response+= "HTTP/1.1 ";
  std::stringstream numero;
  numero << codigo;
  response += numero.str();
  if(codigo == 200)
    response+= " OK";
  else if(codigo == 400)
    response+= " ERROR";
  else response+= " DESCONOCIDO";
  response += "\r\n";

  if(contentLength > 0){
    response+= "Content-Type: application/soap+xml; charset=utf-8\r\n";
    response+= "Content-Length: ";

    std::stringstream numero;
    numero << contentLength;
    response += numero.str();
    response += "\r\n";
  }
	  
  response+="\r\n";

  return response;
}

HttpResponse::HttpResponse(){
  valido=false;
}

bool HttpResponse::esValido(){ return valido; }

HttpResponse::HttpResponse(const std::string& datos){
  valido = false;
  size_t limite;

  if(datos.compare(0,4,"HTTP") != 0)
    return;

  codigo = atoi(datos.c_str()+strlen("HTTP/X.X "));

  limite=datos.find("\r\n\r\n");
  if(limite == std::string::npos)
    return;

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

  valido=true;
}
