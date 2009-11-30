#ifndef __GATEBUFFER_H_INCLUDED
#define __GATEBUFFER_H_INCLUDED

#include "Gate.h"
/** 
 * Compuerta BUFFER.
 */
class GateBuffer:public Gate{
public:
     GateBuffer(){
          tPropagacion = 10;
          tRestante = 0;
	  tReset=10;
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
		    salidas[0] = entradas[0];
	  }
	  else
	       tRestante -= tiempo;
     }

};

#endif //__GATEBUFFER_H_INCLUDED
