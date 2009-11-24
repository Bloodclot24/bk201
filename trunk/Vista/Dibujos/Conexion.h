#ifndef CONEXION_H_
#define CONEXION_H_

class ConexionDibujo;

#include "Dibujo.h"
#include "../AreaDibujo.h"
#include <list>

#include <iostream>

class ConexionDibujo: public Dibujo {
  friend class AreaDibujo;

private:
  Dibujo*               dibujoPin1;
  int                   nroPin1;
  Vertice               vFinal;
  Dibujo*               dibujoPin2;
  int                   nroPin2;
  std::list<Vertice>    poligonos;
  AreaDibujo*           areaDibujo;

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
  ConexionDibujo(int vInicialX, int vInicialY, Dibujo* dibujoPin1, int nroPin1, AreaDibujo *areaDibujo);

  virtual ~ConexionDibujo() { };

  /**
    * Se dibuja la conexion en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  virtual bool setSeleccionado(int x, int y);

  virtual void setVerticeSupIzq(Vertice vSupIzq);
  void setVerticeFinal(Vertice vertice, Dibujo* dibujoPin2, int nroPin2);
};

#endif /* CONEXION_H_ */
