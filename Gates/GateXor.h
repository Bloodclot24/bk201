#ifndef __GATEXOR_H_INCLUDED
#define __GATEXOR_H_INCLUDED

#include "Gate.h"

/** 
 * Compuerta XOR.
 */
class GateXor:public Gate{
public:
     GateXor(){
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
	       salidas[0] = entradas[0] ^ entradas[1];
	  }
	  else
	       tRestante -= tiempo;
     }

};

/** 
 * Compuerta XNOR
 */
class GateXnor:public Gate{
public:
     GateXnor(){
          tPropagacion = 10;
	  tReset=10;
          tRestante = tReset;
 	  entradas.push_back(false);
          entradas.push_back(false);
	  salidas.push_back(false);
     }

     virtual void simular(uint64_t tiempo){
	  if(tRestante <= tiempo){
	       tRestante = 0;
	       salidas[0] = !(entradas[0] ^ entradas[1]);
	  }
	  else
	       tRestante -= tiempo;
     }

};


#endif //__GATEXOR_H_INCLUDED
