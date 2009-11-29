#ifndef COMPUERTAXOR_H_
#define COMPUERTAXOR_H_

#include <iostream>
#include "Compuerta.h"

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

  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

};

#endif /* COMPUERTAXOR_H_ */
