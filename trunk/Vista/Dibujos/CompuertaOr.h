#ifndef COMPUERTAOR_H_
#define COMPUERTAOR_H_

#include <iostream>
#include "Compuerta.h"

/**
 * Clase encargada de dibujar la compuerta OR.
 *
 */
class CompuertaOr: public Compuerta {

protected:
  virtual void cargarNuevosPines();

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

  /**
    * Dibuja el circuito en el contexto que recibe por parametro, este metodo se
    * utiliza para imprimir el circuito.
    *
    * @param context El contexto sobre el cual se va a dibujar el circuito.
    *
    */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

};

#endif /* COMPUERTAOR_H_ */
