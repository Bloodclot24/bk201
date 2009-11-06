#include "Mensajero.h"

void Mensajero::setSocket(Socket *s){
     this->s = s;
}

Soap* Mensajero::recibirMensaje(){
     if(!s)
	  return NULL;
     char c=0;
     bool salida=false;

     std::string mensaje;

     while(!salida){
	  s->recibir(&c ,1);
	  mensaje +=c;
	  
	  if(mensaje.size()>=4){
	       if(mensaje.compare(mensaje.size()-4, 4, "\r\n\r\n")==0)
		    salida=true;
	  }
     }

     HttpRequest req(mensaje.c_str(),1);
     
     if(!req.esValido() || req.getContentLength() == 0)
	  return NULL;

     char* datos = new char[req.getContentLength()];

     s->recibir(datos, req.getContentLength());
     
     Soap *soap = new Soap(datos, req.getContentLength());
     
     delete datos;
     
     return soap;
}

Soap* Mensajero::recibirRespuesta(){
     if(!s)
	  return NULL;
     char c=0;
     bool salida=false;

     std::string mensaje;

     while(!salida){
	  s->recibir(&c ,1);
	  mensaje +=c;
	  
	  if(mensaje.size()>=4){
	       if(mensaje.compare(mensaje.size()-4, 4, "\r\n\r\n")==0)
		    salida=true;
	  }
     }

     HttpResponse res(mensaje.c_str());
     
     if(!res.esValido() || res.getContentLength() == 0)
	  return NULL;

     char* datos = new char[res.getContentLength()];

     s->recibir(datos, res.getContentLength());
     
     Soap *soap = new Soap(datos, res.getContentLength());
     
     delete datos;
     
     return soap;
}


int Mensajero::enviarMensaje(Soap* soap){
     if(soap == NULL)
	  return -1;

     std::string *soapString = soap->toString();

     HttpRequest req("localhost/mensajes");

     req.setContentLength(soapString->length());
     
     std::string sreq = req.getRequest();
     
     s->enviar(sreq.c_str(), sreq.length());

     s->enviar(soapString->c_str(), soapString->length());

     delete soapString;

     return 0;

}

int Mensajero::enviarRespuesta(Soap* soap){

     unsigned codigo = 400;
     unsigned longitud = 0;

     std::string *soapString = NULL;

     if(soap != NULL){
	  codigo = 200;
	  soapString = soap->toString();
	  longitud = soapString->length();
     }


     HttpResponse res(codigo);

     res.setContentLength(longitud);
     
     std::string sres = res.getResponse();
     
     s->enviar(sres.c_str(), sres.length());

     if(soap){
	  s->enviar(soapString->c_str(), longitud);
	  delete soapString;
     }

     return 0;
}



