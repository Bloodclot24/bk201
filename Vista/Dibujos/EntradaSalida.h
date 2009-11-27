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

  virtual void setVerticeSupIzq(Vertice vSupIzq);

  /**
    * Se dibuja la entrada o la salida en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  std::string getTipoPin();
  void setTipoPin(std::string tipoPin);

  virtual void setVerticesMotion(Vertice vertice);
};
#endif /* ENTRADASALIDA_H_ */
