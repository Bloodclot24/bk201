#ifndef COMPUERTA_H_
#define COMPUERTA_H_

#include "Dibujo.h"

#define DIMENSION_COMPUERTA 40
#define UNIDAD_TIEMPO " ns"

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

  virtual void setVerticeSupIzq(Vertice vSupIzq);

  std::string getTiempoT();
  void setTiempoT(const std::string& tiempoT);

  /**
    * Se dibuja la compuerta And en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context) { };

  virtual int getCantidadEntradas(){ return 2; }
  virtual int getCantidadSalidas(){ return 1; }

  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) { };

};

#endif /* COMPUERTA_H_ */
