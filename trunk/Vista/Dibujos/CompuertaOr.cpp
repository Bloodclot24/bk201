#include "CompuertaOr.h"

CompuertaOr::CompuertaOr(int xUp, int yUp): Dibujo::Dibujo(xUp, yUp) { }

void CompuertaOr::dibujar(Cairo::RefPtr<Cairo::Context> context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp+10, yUp);
  context->curve_to(xUp+20, yUp+5, xUp+20, yUp+35, xUp+10, yUp+40);
  context->move_to(xUp+10, yUp);
  context->curve_to(xUp+50, yUp+5, xUp+50, yUp+35, xUp+10, yUp+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp+15, yUp+10);
  context->line_to(xUp, yUp+10);
  context->move_to(xUp+15, yUp+30);
  context->line_to(xUp, yUp+30);
  //salida
  context->move_to(xUp+40, yUp+20);
  context->line_to(xUp+50, yUp+20);
  context->stroke();
}
