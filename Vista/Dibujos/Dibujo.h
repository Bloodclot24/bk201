#ifndef DIBUJO_H_
#define DIBUJO_H_

#include <gtkmm/widget.h>
#include <cairomm/context.h>
#include <list>
#include <vector>
#include <math.h>
#include "Constantes.h"
#include "Vertice.h"

#include <iostream>

#define TOLERANCIA 5
#define PI 3.141592654

/**
 * El Dibujo es una clase madre que deben cumplir todos aquellos dibujos que quieran
 * ser dibujados en el area de dibujo.
 */
class Dibujo{
  friend class VentanaTrabajo;

protected:
  Vertice               vCentro;
  Vertice               vSupIzq;
  int                   angulo;
  int                   ancho;
  int                   alto;
  bool                  seleccionado;
  std::vector<Vertice>  pines;
  std::string           label;
  bool                  examinar;
  std::string           tipo;

  virtual void dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context);

  virtual void mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto) { };

  Vertice rotarPin(int x, int y);

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
  virtual void setAngulo(int angulo);

  /**
   * Devuelve true si el dibujo esta seleccionado, en caso contrario
   * devuelve false.
   *
   */
  bool getSeleccionar() {return seleccionado;};

  /**
   * Deselecciona el dibujo en cuestion.
   */
  void deseleccionar();

  /**
   * Selecciona el dibujo en cuestion.
   *
   */
  void seleccionar();

  /**
   * Se fija si el dibujo esta en el rango que se pasa por
   * como parametro, en caso de ser asi, retorna true y se marca
   * como seleccionado; en caso contrario retorna false.
   *
   * @param x Es el valor en x en el cual se hizo click.
   * @param y Es el valor en y en el que se hizo click.
   */
  virtual bool setSeleccionado(int x, int y);


  /**
   * Se fija si el dibujo esta en el rango que se pasa por
   * como parametro, en caso de ser asi, retorna true;
   * en caso contrario retorna false.
   *
   * @param x Es el valor en x en el cual se hizo click.
   * @param y Es el valor en y en el que se hizo click.
   */
  virtual bool estaCercano(int x, int y);

  /**
   * Obtiene el pin mas cercano al punto que se le pasa como parametro
   * retornando el numero de dicho pin.
   *
   * @param x Valor en x del punto al cual se le quiere obtener el pin mas cercano.
   * @param y Valor en y del punto al cual se le quiere obtener el pin mas cercano.
   *
   */
  int obtenerPinMasCercano(int x, int y);


  /**
   * Dado un numero de pin, obtiene el Vertice correspondiente.
   *
   * @param numPin El numero de pin del que se quiere obtener el Vertice.
   *
   */
  Vertice obtenerPin(int numPin);

  /**
   * Obtiene la etiqueta o label del dibujo.
   *
   */
  std::string getLabel();

  /**
   * Setea la etiqueta o label del dibujo.
   *
   */
  void setLabel(const std::string& label);

  /**
   * Devuelve true en caso de que el dibujo se pueda ver mas en detalle,
   * por ejemplo un circuito remoto; en caso contrario devuelve false.
   *
   */
  bool getExaminar();

  /**
   * Calcula las nuevas posiciones de los pines, por ejemplo por si hay
   * que rotarlos.
   *
   */
  virtual void cargarNuevosPines() { };

  /**
   * Devuelve el tipo del que es el dibujo en cuestion.
   *
   */
  std::string getTipo();

  /**
   * Devuelve el ancho del dibujo en cuestion.
   *
   */
  int getAncho();

  /**
   * Devuelve el alto del dibujo en cuestion.
   *
   */
  int getAlto();

  /**
   * Setea el movimiento en x y en y que se le aplica
   * al dibujo.
   *
   * @param deltax Es cuanto voy a desplazar el dibujo en x.
   * @param deltay Es cuanto voy a desplazar el dibujo en y.
   *
   */
  virtual void setVerticesMotion(int deltax, int deltay);

  /**
   * Dibuja el dibujo en el contexto que recibe por parametro, este metodo se
   * utiliza para imprimir el dibujo.
   *
   * @param context El contexto sobre el cual se va a dibujar el dibujo.
   *
   */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) { };

  /**
   * Muestra la etiqueta con los atributos del dibujo.
   *
   * @param context El contexto sobre el cual se va a dibujar el dibujo.
   */
  void mostrarEtiqueta(const Cairo::RefPtr<Cairo::Context>& context);
};

#endif /* DIBUJO_H_ */
