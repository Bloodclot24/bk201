#ifndef DIBUJO_H_
#define DIBUJO_H_

#include <cairomm/context.h>
#include "Vertice.h"

/**
 * El Dibujo es una clase madre que deben cumplir todos aquellos dibujos que quieran
 * ser dibujados en el area de dibujo.
 */
class Dibujo {

protected:
  Vertice       vCentro;
  Vertice       vSupIzq;
  int angulo;

public:
  /**
    * Crea un dibujo.
    *
    * @param xUp La componente x del vertice superior izquierdo del dibujo.
    * @param yUp La componente y del vertice superior izquierdo del dibujo.
    */
  Dibujo(int xUp, int yUp);

  /**
    * Se dibuja el dibujo en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(Cairo::RefPtr<Cairo::Context> context) { };

  /**
    * Se devuelve el vertice del centro del dibujo.
    *
    * @return vCentro El vertice del centro del dibujo.
    */
  Vertice getVerticeCentro();

  /**
    * Se devuelve el vertice superior izquierdo del dibujo.
    *
    * @return vSupIzq El vertice superior.
    */
  Vertice getVerticeSupIzq();

  /**
    * Se modifica el vertice superior izquierdo del dibujo.
    *
    * @param vSupIzq El vertice superior.
    */
  void setVerticeSupIzq(Vertice vSupIzq);

  /**
    * Se devuelve el angulo de rotacion del dibujo.
    *
    * @return angulo El del dibujo.
    */
  int getAngulo();

  /**
    * Se modifica el componente angulo de rotacion del dibujo.
    *
    * @param angulo La cantidad en grados a modificar el angulo.
    */
  void setAngulo(int angulo);

};

#endif /* DIBUJO_H_ */
