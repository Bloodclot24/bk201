#include "CompuertaBuffer.h"

CompuertaBuffer::CompuertaBuffer(int xUp, int yUp): Dibujo::Dibujo(xUp, yUp) { }

void CompuertaBuffer::dibujar(Cairo::RefPtr<Cairo::Context> context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp+10, yUp);
  context->line_to(xUp+10, yUp+40);
  context->move_to(xUp+10, yUp);
  context->line_to(xUp+40, yUp+20);
  context->move_to(xUp+40, yUp+20);
  context->line_to(xUp+10, yUp+40);
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
