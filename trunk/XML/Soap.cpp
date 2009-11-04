#include "Soap.h"
#include "Xml.h"
#include <string>
#include <iostream>

Soap::Soap(){

     Xml documento("Envelope");
     documento.getRaiz()->setPropiedad("encodingStyle", "http://www.w3.org/2001/12/soap-encoding");

     XmlNS ns(documento.getRaiz(), "soap", "http://www.w3.org/2001/12/soap-envelope");

     documento.getRaiz()->setNameSpace(ns);

     XmlNodo body("Body", ns);

     XmlNS bns(&body, "m", "http://www.bk201.com/mensajes");

     body.setNameSpace(bns);

     documento.getRaiz()->agregarHijo(body);

     XmlNodo mensaje("Simular", bns);
     
     body.agregarHijo(mensaje);

     std::string *s=documento.toString();

     std::cout << *s;
     delete s;
}
