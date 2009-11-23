#ifndef __XML_H_INCLUDED__
#define __XML_H_INCLUDED__

#include "libxml/parser.h"
#include <string>

class XmlNodo;
class XmlNS;
class Xml;


class XmlNodo{
private:
     xmlNodePtr nodo;
     XmlNodo(){}

     XmlNodo(xmlNodePtr nuevo){
	  nodo = nuevo;
     }

public:
     XmlNodo(const char* nombre, XmlNS& ns);

     XmlNodo(const char* nombre);

     void setPropiedad(const char* nombre, const char* valor);

     void setPropiedad(XmlNS& ns, const char* nombre, const char* valor);

     void agregarHijo(XmlNodo& hijo);

     XmlNodo obtenerHijo();

     XmlNodo obtenerHermano();

     XmlNS getNameSpace();

     XmlNS getNameSpaceDef();

     std::string getNombre();

     std::string getPropiedad(const char* nombre);

     std::string getPropiedad(const char* nombre, const char* nsUri);

     void setNameSpace(XmlNS& ns);

     friend class Xml;
     friend class XmlNS;
     friend class Soap;
};

class XmlNS{
private:
     xmlNsPtr ns;

     XmlNS(xmlNsPtr ns){
	  this->ns = ns;
     }
public:
     XmlNS(XmlNodo* nodo, const char* nameSpace, const char* nsDesc);

     friend class XmlNodo;
};

class Xml{
private:
     xmlDocPtr documento;
     XmlNodo raiz;
     Xml(){};
public:
     Xml(xmlDocPtr doc):documento(doc),raiz(xmlDocGetRootElement(doc)){
     }
     Xml(const char* nombreBase);
     XmlNodo* getRaiz();
     std::string* toString();
     void liberar(){
	  xmlFreeDoc(documento);
     }

     Xml(const char* buffer, int size){
	  documento = xmlReadMemory(buffer, size, NULL, NULL,0);
	  XmlNodo r(xmlDocGetRootElement(documento));
	  raiz = r;
     }
};


#endif //__XML_H_INCLUDED__
