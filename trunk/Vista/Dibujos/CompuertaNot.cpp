#include "CompuertaNot.h"

CompuertaNot::CompuertaNot(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) {

  cargarNuevosPins(vSupIzq);
}

void CompuertaNot::cargarNuevosPins(Vertice vSupIzq) {

  pins.clear();
  Vertice v;
  v.x= vSupIzq.x;
  v.y= vSupIzq.y+20;
  pins.push_back(v);
  v.x= vSupIzq.x+40;
  v.y= vSupIzq.y+20;
  pins.push_back(v);
}

void CompuertaNot::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+7.5, vSupIzq.y);
  context->line_to(vSupIzq.x+7.5, vSupIzq.y+40);
  context->move_to(vSupIzq.x+7.5, vSupIzq.y);
  context->line_to(vSupIzq.x+24.5, vSupIzq.y+20);
  context->move_to(vSupIzq.x+24.5, vSupIzq.y+20);
  context->line_to(vSupIzq.x+7.5, vSupIzq.y+40);
  context->move_to(vSupIzq.x+28.5, vSupIzq.y+20);
  context->begin_new_sub_path();
  context->arc(vSupIzq.x+28.5, vSupIzq.y+20, 3.0, 0.0, 2*M_PI);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+20);
  context->line_to(vSupIzq.x+7, vSupIzq.y+20);
  //salida
  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);

  context->set_source_rgb(1.0, 0.0, 0.0);
  std::list<Vertice>::iterator it;
  for(it= pins.begin(); it != pins.end(); it++) {
    context->move_to(it->x, it->y);
    context->line_to(it->x, it->y+5);
  }
  context->stroke();
  
  //Muestro la etiqueta
  //TODO ver como se va a permitirle al usuario editar la etiqueta.
  mostrarEtiqueta(context,vSupIzq.y,alto,"");
}

