#ifndef __GATEAND_H_INCLUDED
#define __GATEAND_H_INCLUDED

#include "Gate.h"

/** 
 * Compuerta AND.
 */
class GateAnd:public Gate{
public:
     GateAnd(){
          tPropagacion = 10;
          tRestante = 0;
	  tReset=10;
 	  entradas.push_back(false);
          entradas.push_back(false);
	  salidas.push_back(false);
     }

     /**
      * Realiza la simulacion.
      *
      * @param tr Tiempo de propagacion.
      */
     virtual void simular(uint64_t tiempo){
	  if(tRestante <= tiempo){
	       tRestante = 0;
	       salidas[0] = entradas[0] & entradas[1];
	  }
	  else
	       tRestante -= tiempo;
     }

};

/** 
 * Compuerta NAND.
 */
class GateNand:public Gate{
public:
     GateNand(){
          tPropagacion = 10;
          tRestante = 10;
	  tReset=10;
 	  entradas.push_back(false);
          entradas.push_back(false);
	  salidas.push_back(false);
     }

     virtual void simular(uint64_t tiempo){
	  if(tRestante <= tiempo){
	       tRestante = 0;
	       salidas[0] = !(entradas[0] & entradas[1]);
	  }
	  else
	       tRestante -= tiempo;
     }

};

#endif //__GATEAND_H_INCLUDED
