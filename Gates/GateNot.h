#ifndef __GATENOT_H_INCLUDED
#define __GATENOT_H_INCLUDED

#include "Gate.h"

/** 
 * Compuerta NOT.
 */
class GateNot:public Gate{
public:
     GateNot(){
          tPropagacion = 10;
	  tReset=10;
          tRestante = tReset;
 	  entradas.push_back(false);
	  salidas.push_back(false);
     }

     virtual void simular(uint64_t tiempo){
	  if(tRestante <= tiempo){
	       tRestante = 0;
		    salidas[0] = !entradas[0];
	  }
	  else
	       tRestante -= tiempo;
     }

};

#endif //__GATENOT_H_INCLUDED
