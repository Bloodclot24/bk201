#ifndef COMPUERTAOR_H_
#define COMPUERTAOR_H_

#include <iostream>
#include "Compuerta.h"

class CompuertaOr: public Compuerta {

protected:
  virtual void cargarNuevosPines(const Cairo::RefPtr<Cairo::Context>& context);

public:
  /**
    * Crea una compuerta Or.
    *
    * @param xUp La componente x del vertice superior izquierdo de la compuerta.
    * @param yUp La componente y del vertice superior izquierdo de la compuerta.
    */
  CompuertaOr(int xUp, int yUp);

  virtual ~CompuertaOr() { };

  /**
    * Se dibuja la compuerta Or en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);
};

#endif /* COMPUERTAOR_H_ */
