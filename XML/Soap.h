#ifndef __SOAP_H_INCLUDED__
#define __SOAP_H_INCLUDED__

#include "Xml.h"

class Soap{
private:
     Xml documento;
     XmlNodo body, mensaje;
public:
     Soap(const char* nombre);
     Soap(const char* buffer, int size);
     void setParametro(const char* nombre, const char* valor);
     void setParametro(const char* nombre, uint64_t valor);
     std::string getParametro(const char* nombre);
     uint64_t getParametroNumerico(const char* nombre);
     std::string* toString(){return documento.toString();}
     ~Soap(){
	  documento.liberar();
     }
};

#endif //__SOAP_H_INCLUDED__
