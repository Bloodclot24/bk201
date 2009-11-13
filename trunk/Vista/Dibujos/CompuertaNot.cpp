#include "CompuertaNot.h"

CompuertaNot::CompuertaNot(int xUp, int yUp): Dibujo::Dibujo(xUp, yUp) { }

void CompuertaNot::dibujar(Cairo::RefPtr<Cairo::Context> context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp+10, yUp);
  context->line_to(xUp+10, yUp+40);
  context->move_to(xUp+10, yUp);
  context->line_to(xUp+32, yUp+20);
  context->move_to(xUp+32, yUp+20);
  context->line_to(xUp+10, yUp+40);
  context->move_to(xUp+36, yUp+20);
  context->begin_new_sub_path();
  context->arc(xUp+36, yUp+20, 3.0, 0.0, 2*M_PI);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp+10, yUp+10);
  context->line_to(xUp, yUp+10);
  context->move_to(xUp+10, yUp+30);
  context->line_to(xUp, yUp+30);
  //salida
  context->move_to(xUp+40, yUp+20);
  context->line_to(xUp+50, yUp+20);

  context->stroke();
}
