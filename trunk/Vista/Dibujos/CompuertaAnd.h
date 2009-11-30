#ifndef COMPUERTAAND_H_
#define COMPUERTAAND_H_

#include <iostream>
#include "Compuerta.h"

/**
 * Clase encargada de dibujar una compuerta AND.
 *
 */
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

  /**
   * Dibuja la compuerta en el contexto que recibe por parametro, este metodo se
   * utiliza para imprimir la compuerta.
   *
   * @param context El contexto sobre el cual se va a dibujar la compuerta.
   *
   */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

};

#endif /* COMPUERTAAND_H_ */
