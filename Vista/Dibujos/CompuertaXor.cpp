#include "CompuertaXor.h"

CompuertaXor::CompuertaXor(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) {

  cargarNuevosPines(vSupIzq);
}

void CompuertaXor::cargarNuevosPines(Vertice vSupIzq) {

  pines.clear();
  Vertice v;
  v.x= vSupIzq.x;
  v.y= vSupIzq.y+10;
  pines.push_back(v);
  v.x= vSupIzq.x;
  v.y= vSupIzq.y+30;
  pines.push_back(v);
  v.x= vSupIzq.x+40;
  v.y= vSupIzq.y+20;
  pines.push_back(v);
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

//  context->set_source_rgb(1.0, 0.0, 0.0);
//  std::list<Vertice>::iterator it;
//  for(it= pins.begin(); it != pins.end(); it++) {
//    context->move_to(it->x, it->y);
//    context->line_to(it->x, it->y+5);
//  }
//  context->stroke();
  
  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);
}
