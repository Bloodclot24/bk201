#include "CompuertaOr.h"

CompuertaOr::CompuertaOr(int xUp, int yUp): Dibujo::Dibujo(xUp, yUp) {

  vCentro.x= xUp+20;
  vCentro.y= yUp+20;
}

void CompuertaOr::dibujar(Cairo::RefPtr<Cairo::Context> context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+5, vSupIzq.y);
  context->line_to(vSupIzq.x+10, vSupIzq.y+20);
  context->move_to(vSupIzq.x+10, vSupIzq.y+20);
  context->line_to(vSupIzq.x+5, vSupIzq.y+40);
  context->move_to(vSupIzq.x+5, vSupIzq.y);
  context->curve_to(vSupIzq.x+38, vSupIzq.y+5, vSupIzq.x+38, vSupIzq.y+35, vSupIzq.x+5, vSupIzq.y+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+10);
  context->line_to(vSupIzq.x+7, vSupIzq.y+10);
  context->move_to(vSupIzq.x, vSupIzq.y+30);
  context->line_to(vSupIzq.x+7, vSupIzq.y+30);
  //salida
  context->move_to(vSupIzq.x+31, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();
}
