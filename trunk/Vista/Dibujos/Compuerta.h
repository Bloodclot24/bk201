#ifndef COMPUERTA_H_
#define COMPUERTA_H_

#include "Dibujo.h"

#define DIMENSION_COMPUERTA 40

class Compuerta: public Dibujo {

public:
  /**
    * Crea una compuerta.
    *
    * @param supIzqX La componente x del vertice superior izquierdo de la compuerta.
    * @param supIzqY La componente y del vertice superior izquierdo de la compuerta.
    */
  Compuerta(int supIzqX, int supIzqY);

  /**
    * Se dibuja la compuerta And en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context) { };
};

#endif /* COMPUERTA_H_ */
