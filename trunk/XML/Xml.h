#ifndef __XML_H_INCLUDED__
#define __XML_H_INCLUDED__

#include "libxml/parser.h"
#include <string>

class XmlNodo;
class XmlNS;
class Xml;

/** 
 * Encapsulacion de un nodo XML.
 * 
 */
class XmlNodo{
private:
  xmlNodePtr nodo;
  XmlNodo(){}

  XmlNodo(xmlNodePtr nuevo){
    nodo = nuevo;
  }

public:
  /** 
   * Crea un nodo con un nombre y NameSpace dado.
   * 
   * @param nombre Nombre del nodo.
   * @param ns El namespace
   */
  XmlNodo(const char* nombre, XmlNS& ns);

  /** 
   * Crea un nuevo nodo.
   * 
   * @param nombre El nombre del nodo.
   */
  XmlNodo(const char* nombre);

  /** 
   * Agrega o cambia una propiedad con su valor al nodo.
   * 
   * @param nombre El nombre de la propiedad.
   * @param valor El valor de la propiedad.
   */
  void setPropiedad(const char* nombre, const char* valor);


  /** 
   * Agrega o cambia una propiedad perteneciente a un namespace con su
   * valor al nodo.
   * 
   * @param ns El namespace al que pertenece la propiedad.
   * @param nombre El nombre de la propiedad.
   * @param valor El valor de la propiedad.
   */
  void setPropiedad(XmlNS& ns, const char* nombre, const char* valor);

  /** 
   * Agrega un nodo hijo.
   * 
   * @param hijo El nodo a agregar.
   */
  void agregarHijo(XmlNodo& hijo);

  /** 
   * Obtiene el primer hijo del nodo.
   * 
   * @return El primer hijo.
   */
  XmlNodo obtenerHijo();

  /** 
   * Devuelve el pimer hermano del nodo.
   * 
   * @return El primer hermano.
   */
  XmlNodo obtenerHermano();

  /** 
   * Devuelve el namespace asociado al nodo.
   * 
   * @return El namespace asociado.
   */
  XmlNS getNameSpace();

  
  XmlNS getNameSpaceDef();
  
  /** 
   * Devuelve el nombre del nodo.
   * 
   * @return Nombre del nodo.
   */
  std::string getNombre();

  /** 
   * Devuelve el valor de una propiedad del nodo.
   * 
   * @param nombre Nombre de la propiedad.
   * 
   * @return Valor de la propiedad.
   */
  std::string getPropiedad(const char* nombre);

  /** 
   * Devuelve el valor de una propiedad asociada a un namespace del
   * nodo.
   * 
   * @param nombre Nombre de la propiedad.
   * @param nsUri La URI del namespace.
   *
   * @return Valor de la propiedad.
   */
  std::string getPropiedad(const char* nombre, const char* nsUri);

  /** 
   * Asigna un namespace al nodo.
   * 
   * @param ns El namespace a asignar.
   */
  void setNameSpace(XmlNS& ns);

  friend class Xml;
  friend class XmlNS;
  friend class Soap;
};

/** 
 * Encapsulacion de namespaces XML.
 * 
 * @param ns 
 */
class XmlNS{
private:
  xmlNsPtr ns;

  XmlNS(xmlNsPtr ns){
    this->ns = ns;
  }
public:
  /** 
   * Crea un nuevo namespace.
   * 
   * @param nodo Nodo a asociar el namespace.
   * @param nameSpace Nombre del namespace.
   * @param nsDesc URI del namespace.
   */
  XmlNS(XmlNodo* nodo, const char* nameSpace, const char* nsDesc);

  friend class XmlNodo;
};

/** 
 * Encapsulacion de documentos XML
 * 
 */
class Xml{
private:
  xmlDocPtr documento;
  XmlNodo raiz;
  Xml(){};
public:
  /** 
   * Crea un nuevo Xml a partir de un xmlDocPtr de libxml2.
   * 
   * @param doc el xmlDocPtr.
   */
  Xml(xmlDocPtr doc):documento(doc),raiz(xmlDocGetRootElement(doc)){
  }

  /** 
   * Crea un nuevo Xml.
   * 
   * @param nombreBase Nombre del elemento raiz.
   */
  Xml(const char* nombreBase);

  /** 
   * Devuelve el nodo raiz del documento.
   * 
   * @return El nombre del elemento raiz.
   */
  XmlNodo* getRaiz();

  /** 
   * Convierte el documento XML a un string y lo devuelve. La
   * liberacion del string es responsabilidad del usuario.
   * 
   * @return El string con el contenido del XML.
   */
  std::string* toString();
  
  /** 
   * Libera las estructuras internas utilizadas por libxml2.
   * 
   */
  void liberar(){
    xmlFreeDoc(documento);
  }

  /** 
   * Crea un documento Xml a partir de un buffer de texto.  Parsea el
   * buffer y lo transforma,si es posible, en un documento XML.
   * 
   * @param buffer El buffer con el documento.
   * @param size El tamanio del buffer.
   */
  Xml(const char* buffer, int size){
    documento = xmlReadMemory(buffer, size, NULL, NULL,0);
    XmlNodo r(xmlDocGetRootElement(documento));
    raiz = r;
  }
};


#endif //__XML_H_INCLUDED__
