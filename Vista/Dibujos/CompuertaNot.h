#ifndef COMPUERTANOT_H_
#define COMPUERTANOT_H_

#include <iostream>
#include "Compuerta.h"

/**
 * Clase encargada de dibujar una compuerta NOT.
 *
 */
class CompuertaNot: public Compuerta {

protected:
  virtual void cargarNuevosPines();

public:
  /**
   * Crea una compuerta Not.
   *
   * @param xUp La componente x del vertice superior izquierdo de la compuerta.
   * @param yUp La componente y del vertice superior izquierdo de la compuerta.
   */
  CompuertaNot(int xUp, int yUp);

  virtual ~CompuertaNot() { };

  /**
   * Se dibuja la compuerta Not en el contexto dado por parametro.
   *
   * @param context El contexto del area de dibujo.
   */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  /**
   * Obtiene la cantidad de entradas de la compuerta.
   *
   */
  int getCantidadEntradas(){ return 1; }

  /**
   * Dibuja la compuerta en el contexto que recibe por parametro, este metodo se
   * utiliza para imprimir la compuerta.
   *
   * @param context El contexto sobre el cual se va a dibujar la compuerta.
   *
   */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

};

#endif /* COMPUERTANOT_H_ */
