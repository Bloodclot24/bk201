#include "EntradaSalida.h"

EntradaSalida::EntradaSalida(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  label= "I/O";
  ancho= alto= DIMENSION_IO;
  vCentro.x= supIzqX +(ancho/2);
  vCentro.y= supIzqY +(alto/2);
  pines.clear();
  pines.push_back(vCentro);
}

void EntradaSalida::setVerticeSupIzq(Vertice vSupIzq) {

  this->vSupIzq= vSupIzq;
  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  pines.clear();
  pines.push_back(vCentro);
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

  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);
}

