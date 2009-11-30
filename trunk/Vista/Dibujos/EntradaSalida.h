#ifndef ENTRADASALIDA_H_
#define ENTRADASALIDA_H_

#include "Dibujo.h"

#define DIMENSION_IO 20

class EntradaSalida: public Dibujo {

private:
  std::string   tipoPin;

protected:
  virtual void mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto);

public:
  /**
   * Crea una entrada o una salida.
   *
   * @param supIzqX La componente x del vertice superior izquierdo.
   * @param supIzqY La componente y del vertice superior izquierdo.
   */
  EntradaSalida(int supIzqX, int supIzqY);

  virtual ~EntradaSalida() { };

  /**
   * Setea el valor del vertice superior izquierdo de la entradaSalida, el mismo
   * se utilizara luego para poder dibujarlo, entre otras cosas.
   *
   * @param vSupIzq El nuevo vertice superior izquierdo de la entradaSalida.
   *
   */
  virtual void setVerticeSupIzq(Vertice vSupIzq);

  /**
   * Se dibuja la entrada o la salida en el contexto dado por parametro.
   *
   * @param context El contexto del area de dibujo.
   */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  /**
   * Devuelve el tipo de pin(si es una entrada o una salida).
   *
   */
  std::string getTipoPin();

  /**
   * Setea el tipo de pin de la entrada/salida.
   *
   * @param tipoPin Es el tipo de de pin, entrada o salida.
   */
  void setTipoPin(std::string tipoPin);

  /**
   * Dibuja la entrada/salida en el contexto que recibe por parametro, este metodo se
   * utiliza para imprimir la entrada/salida.
   *
   * @param context El contexto sobre el cual se va a dibujar la entrada/salida.
   *
   */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

};
#endif /* ENTRADASALIDA_H_ */
