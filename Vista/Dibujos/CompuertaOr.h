#ifndef COMPUERTAOR_H_
#define COMPUERTAOR_H_

#include <iostream>
#include "Dibujo.h"

class CompuertaOr: public Dibujo {

public:
  /**
    * Crea una compuerta Or.
    *
    * @param xUp La componente x del vertice superior izquierdo de la compuerta.
    * @param yUp La componente y del vertice superior izquierdo de la compuerta.
    */
  CompuertaOr(int xUp, int yUp);

  /**
    * Se dibuja la compuerta Or en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(Cairo::RefPtr<Cairo::Context> context);
};

#endif /* COMPUERTAOR_H_ */
