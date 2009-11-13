#ifndef DIBUJO_H_
#define DIBUJO_H_

#include <cairomm/context.h>

/**
 * El Dibujo es una clase madre que deben cumplir todos aquellos dibujos que quieran
 * ser dibujados en el area de dibujo.
 */
class Dibujo {

protected:
  int xUp;
  int yUp;

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
    * Se modifica la componente x del vertice superior izquierdo del dibujo.
    *
    * @param xUp La nueva componente x.
    */
  void setXSupIzq(int xUp);

  /**
    * Se modifica la componente y del vertice superior izquierdo del dibujo.
    *
    * @param yUp La nueva componente y.
    */
  void setYSupIzq(int yUp);
};

#endif /* DIBUJO_H_ */
