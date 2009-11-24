#include "CompuertaBuffer.h"

CompuertaBuffer::CompuertaBuffer(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) {

  cargarNuevosPines(vSupIzq);
}

void CompuertaBuffer::cargarNuevosPines(Vertice vSupIzq) {

  pines.clear();
  Vertice v;
  v.x= vSupIzq.x;
  v.y= vSupIzq.y+20;
  pines.push_back(v);
  v.x= vSupIzq.x+40;
  v.y= vSupIzq.y+20;
  pines.push_back(v);
}

void CompuertaBuffer::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->line_to(vSupIzq.x+10, vSupIzq.y+40);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->line_to(vSupIzq.x+30, vSupIzq.y+20);
  context->move_to(vSupIzq.x+30, vSupIzq.y+20);
  context->line_to(vSupIzq.x+10, vSupIzq.y+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+20);
  context->line_to(vSupIzq.x+10, vSupIzq.y+20);
  //salida
  context->move_to(vSupIzq.x+30, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);

  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);
}
