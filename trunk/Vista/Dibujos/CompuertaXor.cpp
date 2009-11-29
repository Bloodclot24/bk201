#include "CompuertaXor.h"

CompuertaXor::CompuertaXor(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) { 
     cargarNuevosPines();
}

void CompuertaXor::cargarNuevosPines() {

  pines.clear();
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y+10));
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y+30));
  pines.push_back(rotarPin(vSupIzq.x+40, vSupIzq.y+20));
}

void CompuertaXor::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+5, vSupIzq.y);
  context->line_to(vSupIzq.x+10, vSupIzq.y+20);
  context->move_to(vSupIzq.x+10, vSupIzq.y+20);
  context->line_to(vSupIzq.x+5, vSupIzq.y+40);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->line_to(vSupIzq.x+15, vSupIzq.y+20);
  context->move_to(vSupIzq.x+15, vSupIzq.y+20);
  context->line_to(vSupIzq.x+10, vSupIzq.y+40);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->curve_to(vSupIzq.x+38, vSupIzq.y+5, vSupIzq.x+38, vSupIzq.y+35, vSupIzq.x+10, vSupIzq.y+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+10);
  context->line_to(vSupIzq.x+13, vSupIzq.y+10);
  context->move_to(vSupIzq.x, vSupIzq.y+30);
  context->line_to(vSupIzq.x+13, vSupIzq.y+30);
  //salida
  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);

  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);
}

void CompuertaXor::dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) {

  this->dibujar(context);
}
