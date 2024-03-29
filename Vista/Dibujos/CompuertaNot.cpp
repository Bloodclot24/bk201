#include "CompuertaNot.h"

CompuertaNot::CompuertaNot(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) { 
  cargarNuevosPines();
}

void CompuertaNot::cargarNuevosPines() {

  pines.clear();
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y+20));
  pines.push_back(rotarPin(vSupIzq.x+40, vSupIzq.y+20));
}

void CompuertaNot::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+7.5, vSupIzq.y);
  context->line_to(vSupIzq.x+7.5, vSupIzq.y+40);
  context->move_to(vSupIzq.x+7.5, vSupIzq.y);
  context->line_to(vSupIzq.x+24.5, vSupIzq.y+20);
  context->move_to(vSupIzq.x+24.5, vSupIzq.y+20);
  context->line_to(vSupIzq.x+7.5, vSupIzq.y+40);
  context->move_to(vSupIzq.x+28.5, vSupIzq.y+20);
  context->begin_new_sub_path();
  context->arc(vSupIzq.x+28.5, vSupIzq.y+20, 3.0, 0.0, 2*M_PI);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+20);
  context->line_to(vSupIzq.x+7, vSupIzq.y+20);
  //salida
  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);
}

void CompuertaNot::dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) {

  this->dibujar(context);
}
