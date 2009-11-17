#ifndef BUFFER_H_
#define BUFFER_H_

#include <iostream>
#include "Dibujo.h"

class CompuertaBuffer: public Dibujo {

public:
  /**
    * Crea una compuerta Buffer.
    *
    * @param xUp La componente x del vertice superior izquierdo de la compuerta.
    * @param yUp La componente y del vertice superior izquierdo de la compuerta.
    */
  CompuertaBuffer(int xUp, int yUp);

  /**
    * Se dibuja la compuerta Buffer en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);
};

#endif /* BUFFER_H_ */
