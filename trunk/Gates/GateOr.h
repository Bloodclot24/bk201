#ifndef __GATEOR_H_INCLUDED
#define __GATEOR_H_INCLUDED

#include "Gate.h"

/** 
 * Compuerta OR.
 */
class GateOr:public Gate{
public:
     GateOr(){
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
       * @param tiempo Tiempo de propagacion.
       */
     virtual void simular(uint64_t tiempo){
	  if(tRestante <= tiempo){
	       tRestante = 0;
	       salidas[0] = entradas[0] | entradas[1];
	  }
	  else
	       tRestante -= tiempo;
     }

};

/** 
 * Compuerta NOR
 */
class GateNor:public Gate{
public:
     GateNor(){
          tPropagacion = 10;
          tRestante = 10;
	  tReset= 10;
 	  entradas.push_back(false);
          entradas.push_back(false);
	  salidas.push_back(false);
     }

     virtual void simular(uint64_t tiempo){
	  if(tRestante <= tiempo){
	       tRestante = 0;
	       salidas[0] = !(entradas[0] | entradas[1]);
	  }
	  else
	       tRestante -= tiempo;
     }

};


#endif //__GATEOR_H_INCLUDED
