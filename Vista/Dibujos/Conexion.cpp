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

  if(seleccionado)
    dibujarSeleccion(context);
}

void Conexion::dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
  context->move_to(vSupIzq.x-3.5, vSupIzq.y-3.5);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y-3.5, 7, 7);
  context->move_to(vFinal.x-3.5, vFinal.y-3.5);
  context->rectangle(vFinal.x-3.5, vFinal.y-3.5, 7, 7);
  context->stroke();
}
