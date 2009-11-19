#include "EntradaSalida.h"

EntradaSalida::EntradaSalida(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  vCentro.x= supIzqX +(DIMENSION_IO/2);
  vCentro.y= supIzqY +(DIMENSION_IO/2);
  ancho= alto= DIMENSION_IO;
}

void EntradaSalida::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y+10);
  context->begin_new_sub_path();
  context->arc(vSupIzq.x+10, vSupIzq.y+10, 4.0, 0.0, 2*M_PI);
  context->fill();
  context->stroke();
}
