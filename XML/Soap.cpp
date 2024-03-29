#include "Soap.h"
#include "Xml.h"
#include <string>
#include <sstream>
#include <iostream>

Soap::Soap(const char* nombreMensaje):documento("Envelope"){

  this->nombreMensaje = nombreMensaje;

  documento.getRaiz()->setPropiedad("encodingStyle", "http://www.w3.org/2001/12/soap-encoding");

  XmlNS ns(documento.getRaiz(), "soap", "http://www.w3.org/2001/12/soap-envelope");

  documento.getRaiz()->setNameSpace(ns);

  XmlNodo body("Body", ns);

  XmlNS bns(&body, "m", "http://www.bk201.com/mensajes");

  documento.getRaiz()->agregarHijo(body);

  XmlNodo mensaje(nombreMensaje, bns);
     
  body.agregarHijo(mensaje);
     
  this->body = body;
  this->mensaje = mensaje;
}

Soap::Soap(const char* buffer, int size):documento(buffer, size){
  XmlNodo *raiz = documento.getRaiz();
  body = raiz->obtenerHijo();
  mensaje  = body.obtenerHijo();
  this->nombreMensaje = mensaje.getNombre();
     
}

void Soap::setParametro(const char* nombre, const char* valor){
  mensaje.setPropiedad(nombre, valor);
}

void Soap::setParametro(const char* nombre, uint64_t valor){
  std::stringstream s;
  s << valor;
  mensaje.setPropiedad(nombre, s.str().c_str());
}

std::string Soap::getParametro(const char* nombre){
  return mensaje.getPropiedad(nombre);
}

uint64_t Soap::getParametroNumerico(const char* nombre){
  return strtoll(mensaje.getPropiedad(nombre).c_str(),NULL,10);
}

const std::string& Soap::getNombre(){
  return nombreMensaje;
}

