#ifndef ENTRADASALIDA_H_
#define ENTRADASALIDA_H_

#include "Dibujo.h"

#define DIMENSION_IO 20

class EntradaSalida: public Dibujo {

public:
  /**
    * Crea una entrada o una salida.
    *
    * @param supIzqX La componente x del vertice superior izquierdo.
    * @param supIzqY La componente y del vertice superior izquierdo.
    */
  EntradaSalida(int supIzqX, int supIzqY);

  virtual void setVerticeSupIzq(Vertice vSupIzq);

  /**
    * Se dibuja la entrada o la salida en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);
  
  virtual ~EntradaSalida(){ };
};

#endif /* ENTRADASALIDA_H_ */
