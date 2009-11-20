#ifndef CONEXION_H_
#define CONEXION_H_

#include "Dibujo.h"
#include <list>

#include <iostream>

class Conexion: public Dibujo {

private:
  Vertice vFinal;
  std::list<Vertice> poligonos;

protected:
  virtual void dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context);
  void generarPoligonos();

public:
  /**
    * Crea una conexion.
    *
    * @param supIzqX La componente x del vertice superior izquierdo.
    * @param supIzqY La componente y del vertice superior izquierdo.
    */
  Conexion(int vInicialX, int vInicialY, int vFinalX, int vFinalY);

  /**
    * Se dibuja la conexion en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  virtual bool setSeleccionado(int x, int y);
	
  virtual ~Conexion(){ };
};

#endif /* CONEXION_H_ */
