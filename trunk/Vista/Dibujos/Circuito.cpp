#include "Circuito.h"

Circuito::Circuito(int supIzqX, int supIzqY, int entradas, int salidas): Dibujo::Dibujo(supIzqX, supIzqY) {

  this->entradas= entradas;
  this->salidas= salidas;
  vCentro.x= supIzqX+20;
  vCentro.y= supIzqY+20;

  int mayor;
  if(entradas >= salidas)
    mayor= entradas;
  else
    mayor= salidas;

  ancho= alto= mayor*SEPARACION;
}

void Circuito::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x, vSupIzq.y);
  context->line_to(vSupIzq.x+ancho, vSupIzq.y);
  context->move_to(vSupIzq.x+ancho, vSupIzq.y);
  context->line_to(vSupIzq.x+ancho, vSupIzq.y+alto);
  context->move_to(vSupIzq.x+ancho, vSupIzq.y+alto);
  context->line_to(vSupIzq.x, vSupIzq.y+alto);
  context->move_to(vSupIzq.x, vSupIzq.y+alto);
  context->line_to(vSupIzq.x, vSupIzq.y);
  context->stroke();
//  //entradas
//  context->set_source_rgb(0.0, 0.0, 0.0);
//  context->move_to(vSupIzq.x, vSupIzq.y+20);
//  context->line_to(vSupIzq.x+7, vSupIzq.y+20);
//  //salida
//  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
//  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
//  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);
};
