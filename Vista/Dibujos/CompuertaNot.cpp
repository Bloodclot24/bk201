#include "CompuertaNot.h"

CompuertaNot::CompuertaNot(int xUp, int yUp): Dibujo::Dibujo(xUp, yUp) {

  vCentro.x= xUp+20;
  vCentro.y= yUp+20;
}

void CompuertaNot::dibujar(Cairo::RefPtr<Cairo::Context> context) {

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
  context->move_to(vSupIzq.x, vSupIzq.y+10);
  context->line_to(vSupIzq.x+7, vSupIzq.y+10);
  context->move_to(vSupIzq.x, vSupIzq.y+30);
  context->line_to(vSupIzq.x+7, vSupIzq.y+30);
  //salida
  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();
}