#include "Soap.h"
#include <iostream>
#include <fstream>

int main(){
//     Soap s("lalala");

//     std::cout << *s.toString() << std::endl;

     std::string linea, buffer;

     std::ifstream archivo("pepe");

     while(std::getline(archivo, linea))
	  buffer += linea + '\n';

     Soap s(buffer.c_str(), buffer.size());

     std::cout << "nombre: " << s.getNombre() << std::endl;


     std::cout << *s.toString() << std::endl;

     return 1;
}
