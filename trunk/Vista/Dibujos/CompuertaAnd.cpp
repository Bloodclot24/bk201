#include "CompuertaAnd.h"

CompuertaAnd::CompuertaAnd(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) {

  cargarNuevosPines(vSupIzq);
}

void CompuertaAnd::cargarNuevosPines(Vertice vSupIzq) {

  std::cout << "nuevos pines" << std::endl;

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

void CompuertaAnd::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->line_to(vSupIzq.x+10, vSupIzq.y+40);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->curve_to(vSupIzq.x+38, vSupIzq.y+5, vSupIzq.x+38, vSupIzq.y+35, vSupIzq.x+10, vSupIzq.y+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+10);
  context->line_to(vSupIzq.x+10, vSupIzq.y+10);
  context->move_to(vSupIzq.x, vSupIzq.y+30);
  context->line_to(vSupIzq.x+10, vSupIzq.y+30);
  //salida
  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);

  context->set_source_rgb(1.0, 0.0, 0.0);
  int size= pines.size();
  for(int i= 0; i<size; i++) {
    context->move_to(pines[i].x, pines[i].y);
    context->line_to(pines[i].x, pines[i].y+5);
  }
  context->stroke();
  
  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);
}
