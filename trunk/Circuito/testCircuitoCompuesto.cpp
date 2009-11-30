#include "Circuito.h"
#include "../Gates/GateAnd.h"
#include "../Gates/GateOr.h"
#include "../Gates/GateXor.h"
#include "../Gates/GateNot.h"
#include "../Gates/GateBuffer.h"
 
/**
 * Sumador completo de 1 bit
 * http://www.unicrom.com/dig_suma_binaria_completo.asp 
 *
 */
class Sumador:public Circuito{
public:
  Sumador():Circuito(3,2){
    agregarComponente(new GateXor());
    agregarComponente(new GateAnd());
    agregarComponente(new GateXor());
    agregarComponente(new GateAnd());
    agregarComponente(new GateOr());
	  
    agregarConexion(-1,0,0,0);
    agregarConexion(-1,0,1,0);
    agregarConexion(-1,1,0,1);
    agregarConexion(-1,1,1,1);
    agregarConexion(-1,2,2,1);
    agregarConexion(-1,2,3,1);
    agregarConexion(0,2,2,0);
    agregarConexion(0,2,3,0);
    agregarConexion(1,2,4,1);
    agregarConexion(2,2,-1,3);
    agregarConexion(3,2,4,0);
    agregarConexion(4,2,-1,4);
  }
     
};

/** 
 * Sumador de N bits.
 * 
 */
class SumadorN:public Circuito{
public:
  SumadorN(unsigned bits):Circuito(bits*2,bits+1){
    unsigned entradas = bits*2;
    for(unsigned i=0;i<bits;i++){
      agregarComponente(new Sumador);
      agregarConexion(-1,i,i,0); //a1
      agregarConexion(-1,i+bits,i,1); //bi
      agregarConexion(i,3,-1,i+(entradas)); //ai+bi
    }
    for(unsigned i=0;i<bits-1;i++)
      agregarConexion(i,4,i+1,2); //carry de ai+bi

    unsigned i=bits-1;
    agregarConexion(i,4,-1,entradas+bits); //carry de ai+bi (carry final)
  }

};

int main(){

  std::cout << "Sumador de 1 bit:" << std::endl;
  Sumador S1;
  S1.simularTodo(500);

  Circuito Suma(3,2);     
  std::cout << std::endl << "Sumador de 1 bit encapsulado en un circuito: " << std::endl;

  Suma.agregarComponente(new Sumador());
  Suma.agregarConexion(-1,0,0,0);
  Suma.agregarConexion(-1,1,0,1);
  Suma.agregarConexion(-1,2,0,2);
  Suma.agregarConexion(0,3,-1,3);
  Suma.agregarConexion(0,4,-1,4);
  Suma.simularTodo(500);

  std::cout << std::endl << "Sumador de 2 bits: ba+dc = BA , C=Carry" << std::endl;
  Circuito Sumador2(4,3);
  Sumador2.agregarComponente(new Sumador());
  Sumador2.agregarComponente(new Sumador());
  Sumador2.agregarConexion(-1,0,0,0);
  Sumador2.agregarConexion(-1,1,1,0);
  Sumador2.agregarConexion(-1,2,0,1);
  Sumador2.agregarConexion(-1,3,1,1);
  Sumador2.agregarConexion(0,3,-1,4);
  Sumador2.agregarConexion(0,4,1,2); //acarreo parcial
  Sumador2.agregarConexion(1,3,-1,5);
  Sumador2.agregarConexion(1,4,-1,6); // acarreo final

  Sumador2.simularTodo(500);

  std::cout << std::endl << "Sumador de 4 bits:" << std::endl;
     
  SumadorN Sn(4);
  Sn.simularTodo(500);

  return 0;
}
