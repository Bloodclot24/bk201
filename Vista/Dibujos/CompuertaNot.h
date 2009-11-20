#ifndef COMPUERTANOT_H_
#define COMPUERTANOT_H_

#include <iostream>
#include "Compuerta.h"

class CompuertaNot: public Compuerta {

protected:
  virtual void cargarNuevosPins(Vertice vSupIzq);

public:
  /**
    * Crea una compuerta Not.
    *
    * @param xUp La componente x del vertice superior izquierdo de la compuerta.
    * @param yUp La componente y del vertice superior izquierdo de la compuerta.
    */
  CompuertaNot(int xUp, int yUp);

  /**
    * Se dibuja la compuerta Not en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);
};

#endif /* COMPUERTANOT_H_ */
