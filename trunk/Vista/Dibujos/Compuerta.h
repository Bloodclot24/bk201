#ifndef COMPUERTA_H_
#define COMPUERTA_H_

#include "Dibujo.h"

#define DIMENSION_COMPUERTA 40

class Compuerta: public Dibujo {

protected:
  virtual void cargarNuevosPins(Vertice vSupIzq) {  std::cout << "Boluda x2" << std::endl; };

public:
  /**
    * Crea una compuerta.
    *
    * @param supIzqX La componente x del vertice superior izquierdo de la compuerta.
    * @param supIzqY La componente y del vertice superior izquierdo de la compuerta.
    */
  Compuerta(int supIzqX, int supIzqY);

  virtual void setVerticeSupIzq(Vertice vSupIzq);

  /**
    * Se dibuja la compuerta And en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context) { };


  virtual Vertice* obtenerPin(int x, int y);
  
  virtual std::string getEtiqueta();
  
  virtual void setEtiqueta(const std::string& etiqueta);
  
  virtual ~Compuerta(){ };
};

#endif /* COMPUERTA_H_ */