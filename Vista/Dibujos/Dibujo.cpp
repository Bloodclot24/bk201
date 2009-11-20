#include "Dibujo.h"

Dibujo::Dibujo(int xUp, int yUp): vCentro(), vSupIzq(), pins() {

  vSupIzq.x= xUp;
  vSupIzq.y= yUp;
  angulo= 0;
  seleccionado= false;
}

Vertice Dibujo::getVerticeCentro() {

  return vCentro;
}

Vertice Dibujo::getVerticeSupIzq() {

  return vSupIzq;
}

int Dibujo::getAngulo() {

  return angulo;
}

void Dibujo::setAngulo(int angulo) {

  this->angulo+= angulo;
}

void Dibujo::seleccionar() {

  seleccionado= true;
}

void Dibujo::deseleccionar() {

  seleccionado= false;
}

bool Dibujo::setSeleccionado(int x, int y) {

  if((x >= vSupIzq.x) && ((x <= vSupIzq.x+ancho)) && (y >= vSupIzq.y) && (y <= (vSupIzq.y+alto)))
    seleccionado= true;
  else
    seleccionado= false;

  return seleccionado;
}

void Dibujo::dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
  context->rectangle(vSupIzq.x-2, vSupIzq.y-2, ancho+4, alto+4);
  context->fill();
  context->stroke();
  context->set_source_rgba(0, 0, 0, 0.5);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y-3.5, 7, 7);
  context->rectangle(vSupIzq.x+ancho+-3.5, vSupIzq.y-3.5, 7, 7);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y+alto-3.5, 7, 7);
  context->rectangle(vSupIzq.x+ancho-3.5, vSupIzq.y+alto-3.5, 7, 7);
  context->stroke();
}
