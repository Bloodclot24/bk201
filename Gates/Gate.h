#ifndef __GATE_H_INCLUDED__
#define __GATE_H_INCLUDED__

#include <vector>
#include <stdint.h>
#include <iostream>

#include "../Componente/Componente.h"

/** 
 * Clase para representar compuertas logicas.
 */
class Gate:public Componente{
private:
  Gate(const Gate&){}
protected:
  uint64_t tPropagacion;	/**< Tiempo desde que se cambian las
				 * entradas hasta que se obtiene una
				 * salida estable. */
  uint64_t tRestante;	/**< Tiempo restante para que las
			 * salidas se estabilizen. */

public:     

  Gate(){
    tPropagacion = 0;
    tRestante = 0;
    tReset=0;
  }

  /** 
   * Modifica el estado de una de las entradas. Si el nuevo estado
   * de la entrada difiere del anterior la compuerta pasa a poseer
   * salidas inestables.
   * 
   * @param numero El numero de entrada a alterar.
   * @param estado El nuevo estado de la entrada.
   */
  void setEntrada(unsigned numero, bool estado){
    if(numero < getCantidadEntradas()){
      if(entradas[numero] != estado){
	entradas[numero]=estado;
	tRestante = tPropagacion;
      }
    }
  }
     
  /** 
   * Regresa el estado de las entradas y salidas a nivel bajo.
   * 
   */
  virtual void reset(){
    Componente::reset();
    tRestante=tReset;
  }
     
  /** 
   * Devuelve el maximo tiempo que debe simularse para que se
   * produzca un evento.
   * 
   * @return El tiempo hasta el proximo evento en la simulacion.
   */
  uint64_t getTProximoEvento(){
    if(esEstable())
      return -1;
    return tRestante;
  }
     
  /** 
   * Indica si las salidas de la compuerta son o no estables.
   *
   * @return TRUE si las salidas son estables, FALSE si no lo son.
   */
  virtual bool esEstable(){return tRestante==0;}
     

  /**
   * Realiza la simulacion.
   *
   * @param tiempo Tiempo de propagacion.
   */
  virtual void simular(uint64_t tiempo)=0;

  /**
   * Setea el tiempo de propagacion de la compuerta.
   *
   * @param tr Es el tiempo de propagacion q se le va a setear a la compuerta.
   *
   */
  void setTPropagacion(uint64_t tr){
    tPropagacion = tr;
  }
};

#endif //__GATE_H_INCLUDED__
