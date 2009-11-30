#ifndef COMPUERTAXOR_H_
#define COMPUERTAXOR_H_

#include <iostream>
#include "Compuerta.h"


/**
 * Clase encargada de dibujar la compuerta XOR.
 *
 */
class CompuertaXor: public Compuerta {

protected:
  virtual void cargarNuevosPines();

public:
  /**
    * Crea una compuerta Xor.
    *
    * @param xUp La componente x del vertice superior izquierdo de la compuerta.
    * @param yUp La componente y del vertice superior izquierdo de la compuerta.
    */
  CompuertaXor(int xUp, int yUp);

  virtual ~CompuertaXor() { };

  /**
    * Se dibuja la compuerta Xor en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  /**
    * Dibuja la compuerta en el contexto que recibe por parametro, este metodo se
    * utiliza para imprimir la compuerta.
    *
    * @param context El contexto sobre el cual se va a dibujar la compuerta.
    *
    */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

};

#endif /* COMPUERTAXOR_H_ */
