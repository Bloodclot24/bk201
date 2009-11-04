#ifndef __XML_H_INCLUDED__
#define __XML_H_INCLUDED__

#include "libxml/parser.h"
#include <string>

class XmlNodo;
class XmlNS;


class XmlNodo{
     xmlNodePtr nodo;

public:
     XmlNodo(const char* nombre, XmlNS& ns);

     XmlNodo(const char* nombre);

     void setPropiedad(const char* nombre, const char* valor);

     void setPropiedad(XmlNS& ns, const char* nombre, const char* valor);

     void agregarHijo(XmlNodo& hijo);

     void setNameSpace(XmlNS& ns);

     friend class Xml;
     friend class XmlNS;
};

class XmlNS{
private:
     xmlNsPtr ns;

public:
     XmlNS(XmlNodo* nodo, const char* nameSpace, const char* nsDesc);

     friend class XmlNodo;
};

class Xml{
private:
     xmlDocPtr documento;
     XmlNodo raiz;

public:
     Xml(const char* nombreBase);
     XmlNodo* getRaiz();
     std::string* toString();
};


#endif //__XML_H_INCLUDED__
