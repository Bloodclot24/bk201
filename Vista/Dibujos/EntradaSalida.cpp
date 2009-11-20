#include "EntradaSalida.h"

EntradaSalida::EntradaSalida(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  ancho= alto= DIMENSION_IO;
  vCentro.x= supIzqX +(ancho/2);
  vCentro.y= supIzqY +(alto/2);
  pins.clear();
  pins.push_back(vCentro);
}

void EntradaSalida::setVerticeSupIzq(Vertice vSupIzq) {

  this->vSupIzq= vSupIzq;
  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  pins.clear();
  pins.push_back(vCentro);
}

void EntradaSalida::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y+10);
  context->begin_new_sub_path();
  context->arc(vSupIzq.x+10, vSupIzq.y+10, 4.0, 0.0, 2*M_PI);
  context->fill();
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

}
