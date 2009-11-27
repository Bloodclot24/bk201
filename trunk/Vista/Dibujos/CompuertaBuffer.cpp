#include "CompuertaBuffer.h"

CompuertaBuffer::CompuertaBuffer(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) { 
     cargarNuevosPines();
}

void CompuertaBuffer::cargarNuevosPines() {

  pines.clear();
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y+20));
  pines.push_back(rotarPin(vSupIzq.x+40, vSupIzq.y+20));
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
