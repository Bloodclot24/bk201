#include "Xml.h"
#include <string>

Xml::Xml(const char* nombreBase):raiz(nombreBase){
     documento = xmlNewDoc((const xmlChar*)"1.0");
     xmlDocSetRootElement(documento, raiz.nodo);
}

XmlNodo* Xml::getRaiz(){
     return &raiz;
}

std::string* Xml::toString(){
     char *buffer; int tamanio;
     xmlDocDumpFormatMemory(documento,  (xmlChar**)&buffer, &tamanio, 0);
     std::string *final = new std::string(buffer,tamanio);
     xmlFree(buffer);
     return final;
}

XmlNS::XmlNS(XmlNodo* nodo, const char* nameSpace, const char* nsDesc){
     ns = xmlNewNs(nodo->nodo,(xmlChar*)nsDesc,(xmlChar*)nameSpace);
}

XmlNodo::XmlNodo(const char* nombre, XmlNS& ns){
     nodo = xmlNewNode(ns.ns, (xmlChar*)nombre);
}

XmlNodo::XmlNodo(const char* nombre){
     nodo = xmlNewNode(NULL, (xmlChar*)nombre);
}

void XmlNodo::setPropiedad(const char* nombre, const char* valor){
     xmlSetProp(nodo,(xmlChar*)nombre, (xmlChar*)valor);
}

void XmlNodo::setPropiedad(XmlNS& ns, const char* nombre, const char* valor){
     xmlSetNsProp(nodo, ns.ns, (xmlChar*)nombre, (xmlChar*)valor);
}

void XmlNodo::agregarHijo(XmlNodo& hijo){
     xmlAddChild(nodo, hijo.nodo);
}

void XmlNodo::setNameSpace(XmlNS& ns){
     xmlSetNs(nodo, ns.ns);
}
