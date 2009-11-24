#ifndef DIBUJO_H_
#define DIBUJO_H_

#include <gtkmm/widget.h>
#include <cairomm/context.h>
#include "Constantes.h"
#include <list>
#include <vector>
#include "Vertice.h"

#include <iostream>

#define TOLERANCIA 5
#define UNIDAD_TIEMPO " ns"

/**
 * El Dibujo es una clase madre que deben cumplir todos aquellos dibujos que quieran
 * ser dibujados en el area de dibujo.
 */
class Dibujo: public Gtk::Widget {

protected:
  Vertice               vCentro;
  Vertice               vSupIzq;
  int                   angulo;
  int                   ancho;
  int                   alto;
  bool                  seleccionado;
  std::vector<Vertice>  pines;
  std::string           label;
  std::string           tiempoT;
  bool                  examinar;
  virtual void dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context);

  void mostrarEtiqueta(const Cairo::RefPtr<Cairo::Context>& context, int vSupIzq_y, int alto);

public:
  /**
    * Crea un dibujo.
    *
    * @param xUp La componente x del vertice superior izquierdo del dibujo.
    * @param yUp La componente y del vertice superior izquierdo del dibujo.
    */
  Dibujo(int xUp, int yUp);

  virtual ~Dibujo() { };

  /**
    * Se dibuja el dibujo en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context) { };

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
  virtual void setVerticeSupIzq(Vertice vSupIzq) { };

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


  bool getSeleccionar() {return seleccionado;};

  void deseleccionar();
  void seleccionar();
  virtual bool setSeleccionado(int x, int y);

  int obtenerPinMasCercano(int x, int y);
  Vertice obtenerPin(int numPin);

  std::string getLabel();
  void setLabel(const std::string& label);
  std::string getTiempoT();
  void setTiempoT(const std::string& tiempoT);

  bool getExaminar();
};

#endif /* DIBUJO_H_ */
