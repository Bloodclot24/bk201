#ifndef __COMPONENTE_H_INCLUDED__
#define __COMPONENTE_H_INCLUDED__

#include <vector>
#include <stdint.h>

/** 
 * Clase que representa un componente en un circuito.
 * 
 */
class Componente{
private:
     Componente(const Componente&){}
protected:
     std::vector<bool> entradas; /**< Entradas del componente */
     std::vector<bool>  salidas; /**< Salidas del componente */
     uint64_t tReset;		/**< Tiempo minimo que debe
				 * transcurrir desde un reset para
				 * poder utilizar la compuerta. */
     Componente(){tReset=0;}
     /** 
      * Cambia el valor de una de las entradas del componente.
      * 
      * @param numero EL numero de la entrada a modificar, numeradas
      * desde cero.
      *
      * @param estado El nuevo estado logico de la entrada.
      */

public:     
     virtual void setEntrada(unsigned numero, bool estado){
	  if(numero < getCantidadEntradas())
	       entradas[numero]=estado;
     }
     
     /** 
      * Devuelve el estado de una delas entradas del componente.
      * 
      * @param numero El numero de la entrada.
      * 
      * @return El estado de la entrada.
      */
     virtual bool getEntrada(unsigned numero){
	  if(numero < getCantidadEntradas())
	       return entradas[numero];
	  return false;
     }

     /** 
      * Devuelve el estado de una de las salidas del componente.
      * 
      * @param numero Numero de salida.
      * 
      * @return El estado de la salida.
      */
     bool getSalida(unsigned numero){
	  if(numero < getCantidadSalidas())
	       return salidas[numero];
	  return false;
     }
     
     /** 
      * Devuelve el estado de uno de los pines del componente.  Los
      * pines se numeran del cero en adelante. Primero se asigna
      * numero a las entradas y luego a las salidas. Por ejemplo, para
      * un componente con dos entradas y dos salidas,los pines 0 y 1
      * corresponden a las entradas y los pines 2 y 3 corresponden a
      * las salidas.
      * 
      * @param numero Numero de pin.
      * 
      * @return Estado del pin.
      */
     virtual bool getPin(unsigned numero){
	  if(numero < getCantidadSalidas()+getCantidadEntradas()) {
	       if(numero < getCantidadEntradas())
		    return entradas[numero];
	  } else return salidas[numero-getCantidadEntradas()];
	  return false;
     }
     
     /** 
      * Asigna un estado a uno de los pines del componente.
      * 
      * @param numero Numero de pin a modificar.
      * @param estado Estado a asignar.
      */
     virtual void setPin(unsigned numero, bool estado){
	  if(numero < getCantidadEntradas())
	       setEntrada(numero, estado);
     }
     
     /** 
      * Coloca todas las entradas y salidas del componente en estado
      * logico bajo.
      * 
      */
     virtual void reset(){
	  for(unsigned i=0;i<getCantidadEntradas();i++)
	       entradas[i] = false;
	  for(unsigned i=0;i<getCantidadSalidas();i++)
	       salidas[i] = false;
     }
     
     /** 
      * Devuelve la cantidad de entradas del componente.
      * 
      * @return El numero de entradas.
      */
     virtual unsigned getCantidadEntradas(){return entradas.size();}
     
     /** 
      * Devuelve el numero de salidas del componente.
      * 
      * @return Numero de salidas.
      */
     virtual unsigned getCantidadSalidas(){return salidas.size();}
     
     /** 
      * Devuelve la cantidad de tiempo que debe transcurrir hasta que
      * se estabilize la salida del componente.
      * 
      * 
      * @return El tiempo hasta la estabilizacion.
      */
     virtual uint64_t getTProximoEvento(){return -1;}
     
     /** 
      * Indica si las salidas del componente son o no estables.
      * 
      * @return TRUE si las salidas son estables, FALSE si no lo son.
      */
     virtual bool esEstable(){return true;}

     /** 
      * Corre la simulacion del componente.
      * 
      * @param tiempo El tiempo de operacion a simular.
      */
     virtual void simular(uint64_t tiempo)=0;

     virtual ~Componente(){}
};

#endif //__COMPONENTE_H_INCLUDED__
