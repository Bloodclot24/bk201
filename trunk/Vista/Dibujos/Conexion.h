#ifndef CONEXION_H_
#define CONEXION_H_

class ConexionDibujo;

#include "Dibujo.h"
#include "../AreaDibujoGenerica.h"
#include <list>

#include <iostream>

/**
 * Clase encargada de dibujar las conexiones del circuito.
 *
 */
class ConexionDibujo: public Dibujo {
  friend class AreaDibujo;

private:
  Dibujo*               dibujoPin1;
  int                   nroPin1;
  Vertice               vInfDer;
  Dibujo*               dibujoPin2;
  int                   nroPin2;
  std::list<Vertice>    poligonos;
  AreaDibujoGenerica*   areaDibujo;

protected:
  virtual void dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context);
  void generarPoligonos();
  void calcularAtributos();

public:
  /**
   * Crea una conexion.
   *
   * @param supIzqX La componente x del vertice superior izquierdo.
   * @param supIzqY La componente y del vertice superior izquierdo.
   */
  ConexionDibujo(int vInicialX, int vInicialY, Vertice vFinal, AreaDibujoGenerica *areaDibujo);

  virtual ~ConexionDibujo() { };

  /**
   * Se dibuja la conexion en el contexto dado por parametro.
   *
   * @param context El contexto del area de dibujo.
   */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  /**
   * Se fija si la conexion esta en el rango que se pasa por
   * como parametro, en caso de ser asi, retorna true y se marca
   * como seleccionado; en caso contrario retorna false.
   *
   * @param x Es el valor en x en el cual se hizo click.
   * @param y Es el valor en y en el que se hizo click.
   */
  virtual bool setSeleccionado(int x, int y);

  /**
   * Se fija si la conexion esta en el rango que se pasa por
   * como parametro, en caso de ser asi, retorna true;
   * en caso contrario retorna false.
   *
   * @param x Es el valor en x en el cual se hizo click.
   * @param y Es el valor en y en el que se hizo click.
   */
  virtual bool estaCercano(int x, int y);

  /**
   * Setea el angulo de la conexion.
   *
   */
  virtual void setAngulo(int angulo) { };

  /**
   * Setea el valor del vertice superior izquierdo de la conexion, el mismo
   * se utilizara luego para poder dibujarlo, entre otras cosas.
   *
   * @param vSupIzq El nuevo vertice superior izquierdo del circuito.
   *
   */
  virtual void setVerticeSupIzq(Vertice vSupIzq);

  /**
   * Setea el vertice final de la conexion.
   *
   * @param vertice Es el vertice que va a ser el vertice en
   *                el cual finaliza la conexion.
   *
   */
  void setVerticeFinal(Vertice vertice);

  /**
   * Setea el valor del vertice inferior derecho de la conexion, el mismo
   * se utilizara luego para poder dibujarlo, entre otras cosas.
   *
   * @param vInfDer El nuevo vertice inferior derecho de la conexion.
   *
   */
  void setVerticeInfDer(Vertice vInfDer);

  /**
   * Devuelve el vertice inferior derecho de la conexion.
   *
   */
  Vertice getVerticeInfDer();

  /**
   * Setea el area de dibujo sobre el cual se va a dibujar
   * la conexion.
   *
   * @param area Es el area de dibujo sobre la cual se van a dibujar.
   *
   */
  void setAreaDibujo(AreaDibujoGenerica *area);

  /**
   * Setea el movimiento en x y en y que se le aplica
   * a la conexion.
   *
   * @param deltax Es cuanto voy a desplazar la conexion en x.
   * @param deltay Es cuanto voy a desplazar la conexion en y.
   *
   */
  virtual void setVerticesMotion(int deltax, int deltay);

  /**
   * Dibuja la conexion en el contexto que recibe por parametro, este metodo se
   * utiliza para imprimir la conexion.
   *
   * @param context El contexto sobre el cual se va a dibujar la conexion.
   *
   */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);


};

#endif /* CONEXION_H_ */
