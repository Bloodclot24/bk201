#include "Compuerta.h"

Compuerta::Compuerta(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  label= "Compuerta";
  tipo= AND;
  tiempoT= "0";
  ancho= alto= DIMENSION_COMPUERTA;
  vCentro.x= supIzqX + (ancho/2);
  vCentro.y= supIzqY + (alto/2);
}

void Compuerta::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  this->vSupIzq= vSupIzq;
  cargarNuevosPines(vSupIzq);
}

std::string Compuerta::getTiempoT() {
  return tiempoT;
}

void Compuerta::setTiempoT(const std::string& tiempoT) {
  this->tiempoT= tiempoT;
}
