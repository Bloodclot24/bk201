#include "Circuito.h"
#include "../Gates/GateAnd.h"
#include "../Gates/GateOr.h"
#include "../Gates/GateXor.h"
#include "../Gates/GateNot.h"
#include "../Gates/GateBuffer.h"


int main(){
     std::cout << "Circuito 1: " << std::endl;

     Circuito C1(2,1);
     C1.agregarComponente(new GateAnd());
     C1.agregarComponente(new GateAnd());
     C1.agregarComponente(new GateAnd());

     C1.agregarConexion(0,2,2,0);
     C1.agregarConexion(1,2,2,1);
     C1.agregarConexion(-1,0,0,0);
     C1.agregarConexion(-1,1,0,1);
     C1.agregarConexion(-1,0,1,0);
     C1.agregarConexion(-1,1,1,1);
     C1.agregarConexion(2,2,-1,2);
     C1.simularTodo(500);

     std::cout << std::endl << "Circuito 2: " << std::endl;

     Circuito C2(4,1);
     C2.agregarComponente(new GateAnd());
     C2.agregarComponente(new GateAnd());
     C2.agregarComponente(new GateAnd());

     C2.agregarConexion(0,2,2,0);
     C2.agregarConexion(1,2,2,1);
     C2.agregarConexion(-1,0,0,0);
     C2.agregarConexion(-1,1,0,1);
     C2.agregarConexion(-1,2,1,0);
     C2.agregarConexion(-1,3,1,1);
     C2.agregarConexion(2,2,-1,4);
     C2.simularTodo(500);

     std::cout << std::endl << "Circuito 3: " << std::endl;

     Circuito C3(4,3);
     C3.agregarComponente(new GateOr());
     C3.agregarComponente(new GateXor());
     C3.agregarComponente(new GateAnd());

     C3.agregarConexion(0,2,2,0);
     C3.agregarConexion(1,2,2,1);
     C3.agregarConexion(-1,0,0,0);
     C3.agregarConexion(-1,1,0,1);
     C3.agregarConexion(-1,2,1,0);
     C3.agregarConexion(-1,3,1,1);
     C3.agregarConexion(0,2,-1,4);
     C3.agregarConexion(1,2,-1,5);
     C3.agregarConexion(2,2,-1,6);
     C3.simularTodo(500);

     std::cout << std::endl << "Circuito 4: " << std::endl;

     Circuito C4(3,2);
     C4.agregarComponente(new GateAnd());
     C4.agregarComponente(new GateOr());
     C4.agregarComponente(new GateNot());
     C4.agregarComponente(new GateBuffer());


     C4.agregarConexion(0,2,1,0);
     C4.agregarConexion(1,2,2,0);
     C4.agregarConexion(1,2,3,0);
     C4.agregarConexion(-1,0,0,0);
     C4.agregarConexion(-1,1,0,1);
     C4.agregarConexion(-1,2,1,1);
     C4.agregarConexion(2,1,-1,3);
     C4.agregarConexion(3,1,-1,4);
     C4.simularTodo(500);

     std::cout << std::endl << "Circuito 5: " << std::endl;

     Circuito C5(2,1);
     C5.agregarComponente(new GateXor());
     C5.agregarComponente(new GateBuffer());


     C5.agregarConexion(-1,0,0,0);
     C5.agregarConexion(-1,1,0,1);
     C5.agregarConexion(0,2,-1,2);
     C5.agregarConexion(0,2,1,0);
     C5.agregarConexion(1,1,0,0);
     C5.setExtendido(true);
     C5.simularTodo(500);

     std::cout << std::endl << "Circuito 6: FlipFlop" << std::endl;

     Circuito C6(2,2);
     C6.agregarComponente(new GateNor());
     C6.agregarComponente(new GateNor());


     C6.agregarConexion(0,2,-1,2);
     C6.agregarConexion(0,2,1,0);
     C6.agregarConexion(1,2,0,1);
     C6.agregarConexion(1,2,-1,3);
     C6.agregarConexion(-1,0,0,0);     
     C6.agregarConexion(-1,1,1,1);

     C6.setExtendido(true);
     
     C6.simularTodo(500);
     
     return 0;
}
