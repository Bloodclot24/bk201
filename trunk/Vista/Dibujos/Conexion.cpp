#include "Conexion.h"

Conexion::Conexion(int vInicialX, int vInicialY, int vFinalX, int vFinalY): Dibujo::Dibujo(vInicialX, vInicialY) {

  vFinal.x= vFinalX;
  vFinal.y= vFinalY;
  int deltaX= vFinalX-vInicialX;
  int deltaY= vFinalY-vInicialY;
  vCentro.x= vInicialX + deltaX/2;
  vCentro.y= vInicialY + deltaY/2;
  ancho= deltaX;
  alto= deltaY;
}

void Conexion::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y);
  context->line_to(vCentro.x, vSupIzq.y);
  context->move_to(vCentro.x, vSupIzq.y);
  context->line_to(vCentro.x, vCentro.y);
  context->move_to(vCentro.x, vCentro.y);
  context->line_to(vCentro.x, vFinal.y);
  context->move_to(vCentro.x, vFinal.y);
  context->line_to(vFinal.x, vFinal.y);
  context->stroke();
}
