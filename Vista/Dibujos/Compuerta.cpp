#include "Compuerta.h"

Compuerta::Compuerta(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  label= tipo= COMPUERTA;
  tiempoT= "0";
  ancho= alto= DIMENSION_COMPUERTA;
  vCentro.x= supIzqX + (ancho/2);
  vCentro.y= supIzqY + (alto/2);
}

void Compuerta::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  this->vSupIzq= vSupIzq;
  cargarNuevosPines();
}

std::string Compuerta::getTiempoT() {
  return tiempoT;
}

void Compuerta::setTiempoT(const std::string& tiempoT) {
  this->tiempoT= tiempoT;
}

void Compuerta::mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto) {

  context->move_to(vSupIzq.x, yTexto);
  context->show_text(label);
  context->move_to(vSupIzq.x, yTexto+15);
  context->show_text(tiempoT);
  context->show_text(UNIDAD_TIEMPO);
  context->stroke();
};
