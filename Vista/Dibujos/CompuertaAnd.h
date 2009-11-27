#ifndef COMPUERTAAND_H_
#define COMPUERTAAND_H_

#include <iostream>
#include "Compuerta.h"

class CompuertaAnd: public Compuerta {

protected:
  virtual void cargarNuevosPines();

public:
  /**
    * Crea una compuerta And.
    *
    * @param xUp La componente x del vertice superior izquierdo de la compuerta.
    * @param yUp La componente y del vertice superior izquierdo de la compuerta.
    */
  CompuertaAnd(int xUp, int yUp);

  virtual ~CompuertaAnd(){};

  /**
    * Se dibuja la compuerta And en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);
};

#endif /* COMPUERTAAND_H_ */
