#include "EntradaSalida.h"

EntradaSalida::EntradaSalida(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  tipo= TIPO_PIN;
  tipoPin= TIPO_ENTRADA;
  label= "I/O";
  ancho= alto= DIMENSION_IO;
  vCentro.x= supIzqX +(ancho/2);
  vCentro.y= supIzqY +(alto/2);
  pines.clear();
  pines.push_back(vCentro);
}

void EntradaSalida::setVerticeSupIzq(Vertice vSupIzq) {

  this->vSupIzq= vSupIzq;
  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  pines.clear();
  pines.push_back(vCentro);
}

void EntradaSalida::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y+10);
  context->begin_new_sub_path();
  context->arc(vSupIzq.x+10, vSupIzq.y+10, 4.0, 0.0, 2*M_PI);
  context->fill();
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);
}

std::string EntradaSalida::getTipoPin() {
  return tipoPin;
}

void EntradaSalida::setTipoPin(std::string tipoPin) {
  this->tipoPin= tipoPin;
}

void EntradaSalida::mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto) {
  context->move_to(vSupIzq.x, yTexto);
  context->show_text(label);
  context->move_to(vSupIzq.x, yTexto+15);
  context->show_text("Tipo: ");
  context->show_text(tipoPin);
  context->stroke();
};

void EntradaSalida::dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) {

  this->dibujar(context);
}
