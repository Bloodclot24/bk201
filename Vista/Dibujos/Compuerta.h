#ifndef COMPUERTA_H_
#define COMPUERTA_H_

#include "Dibujo.h"

#define DIMENSION_COMPUERTA 40
#define UNIDAD_TIEMPO " ns"

/**
 * Clase compuerta, es una compuerta generica, de esta clase heredan
 * todas las compuertas que pueden formar parte del circuito.
 *
 */
class Compuerta: public Dibujo {

  std::string   tiempoT;

protected:
  virtual void cargarNuevosPines() {};
  virtual void mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto);

public:
  /**
    * Crea una compuerta.
    *
    * @param supIzqX La componente x del vertice superior izquierdo de la compuerta.
    * @param supIzqY La componente y del vertice superior izquierdo de la compuerta.
    */
  Compuerta(int supIzqX, int supIzqY);

  virtual ~Compuerta() { };

  /**
    * Setea el valor del vertice superior izquierdo del circuito, el mismo
    * se utilizara luego para poder dibujarlo, entre otras cosas.
    *
    * @param vSupIzq El nuevo vertice superior izquierdo del circuito.
    *
    */
  virtual void setVerticeSupIzq(Vertice vSupIzq);

  /**
   * Obtiene el tiempo de transicion de la compuerta.
   *
   */
  std::string getTiempoT();

  /**
   * Setea el tiempo de transicion de la compuerta.
   *
   * @param tiempoT El nuevo tiempo de transicion de la compuerta.
   *
   */
  void setTiempoT(const std::string& tiempoT);

  /**
    * Se dibuja la compuerta And en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context) { };

  /**
    * Obtiene la cantidad de entradas.
    *
    */
  virtual int getCantidadEntradas(){ return 2; }

  /**
    * Obtiene la cantidad de salidas.
    *
    */
  virtual int getCantidadSalidas(){ return 1; }


  /**
     * Dibuja el circuito en el contexto que recibe por parametro, este metodo se
     * utiliza para imprimir el circuito.
     *
     * @param context El contexto sobre el cual se va a dibujar el circuito.
     *
     */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) { };

};

#endif /* COMPUERTA_H_ */
