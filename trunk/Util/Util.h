#ifndef UTIL_H_
#define UTIL_H_

#include <sstream>
#include <string>
#include <stdint.h>

/** 
 * Clase con funciones comunes para el programa.
 */
class Util {
	
public:

  /**
   * Convierte de int a string.
   *
   * @param numero El numero entero que se quiere convertir a string.
   */
  static std::string intToString(int numero);
};

#endif /*UTIL_H_*/
