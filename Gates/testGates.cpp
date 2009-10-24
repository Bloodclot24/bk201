#include "GateAnd.h"
#include "GateOr.h"
#include "GateXor.h"
#include "GateNot.h"
#include "GateBuffer.h"
#include <iostream>

/** 
 * Prueba de compuertas. Crea una compuerta de cada tipo y corre la
 * simulacion en cada una, informando de los resultados por pantalla.
 * 
 */
int main(int argc, char** argv){

     std::vector<Gate*> gates;
     std::vector<std::string> nombres;

   
     /* Creo las compuertas */
     gates.push_back(new GateNot());
     nombres.push_back("NOT");
     gates.push_back(new GateBuffer());
     nombres.push_back("BUFFER");
     gates.push_back(new GateAnd());
     nombres.push_back("AND");
     gates.push_back(new GateNand());
     nombres.push_back("NAND");
     gates.push_back(new GateOr());
     nombres.push_back("OR");
     gates.push_back(new GateNor());
     nombres.push_back("NOR");
     gates.push_back(new GateXor());
     nombres.push_back("XOR");
     gates.push_back(new GateXnor());
     nombres.push_back("XNOR");

     /* Por cada compuerta */
     for(unsigned contador=0;contador < gates.size();contador++){

	  Gate* gate = gates[contador];
	  /* Obtengo su nombre y lo muestro */
	  std::cout << "Compuerta " << nombres[contador] << std::endl;
	  unsigned entradas, salidas;
	  entradas = gate->getCantidadEntradas();
	  salidas = gate->getCantidadSalidas();
	  
	  /* obtengo la cantidad maxima de combinaciones posibles para
	   * las entradas */
	  uint64_t combinaciones = 2;
	  for(unsigned i=1;i<entradas;i++,combinaciones *= 2);
	  
	  for(unsigned i=0;i<entradas;i++)
	       std::cout << " " << (char)('a'+i) << " |";
	  
	  for(unsigned j=0;j<salidas;j++)
	       std::cout << "| " << (char)('A'+j) << " " ;
	  std::cout << std::endl;
	  
	  for(unsigned k=0;k<(entradas+salidas)*4;k++)
	       std::cout << "=";
	  std::cout << std::endl;
	  
	  
	  /* Por cada combinacion */
	  for(uint64_t i=0;i<combinaciones;i++){
	       /* Cambio las entradas */
	       for(unsigned j=0;j<entradas;j++)
		    gate->setEntrada(j, i&1<<j);
	  
	       /* Simulo hasta que se estabilize */
	       while(!gate->esEstable())
		    gate->simular(gate->getTProximoEvento());
	  
	       /* Muestro los resultados por pantalla */
	       for(unsigned k=0;k<entradas;k++)
		    std::cout << " " << ((i&1<<k)!=0) << " |";
	  
	       for(unsigned l=0;l<salidas;l++)
		    std::cout << "| " << gate->getSalida(l) << " ";
	  
	       std::cout << std::endl;
	  }
	  std::cout << std::endl;
	  delete gate;
     }
     

     return 0;
}
