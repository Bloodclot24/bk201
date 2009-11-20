#include "Circuito.h"

Circuito::Circuito(int supIzqX, int supIzqY, int entradas, int salidas): Dibujo::Dibujo(supIzqX, supIzqY) {

  this->entradas= entradas;
  this->salidas= salidas;

  int mayor;
  if(entradas >= salidas) {
    mayor= entradas;
    pasoEntrada= 10;
    pasoSalida= pasoPinesMenor(entradas, salidas);
  } else {
    mayor= salidas;
    pasoSalida= 10;
    pasoEntrada= pasoPinesMenor(salidas, entradas);
  }

  ancho= alto= mayor*SEPARACION+10;

  vCentro.x= supIzqX + (ancho/2);
  vCentro.y= supIzqY + (alto/2);

  cargarNuevosPins(vSupIzq);
}

int Circuito::pasoPinesMenor(int mayor, int menor) {

  int paso= (mayor*SEPARACION+10)/menor;
  int mod= paso % 10;
  if(mod != 0 && (menor%2)==0 && (mayor%menor)==0)
    paso+= mod;
  else
    paso-= mod;

  return paso;
}

void Circuito::cargarNuevosPins(Vertice vSupIzq) {

  pins.clear();
  Vertice v;
  //entrada
  for(int i= 0; i<entradas; i++) {
    v.x= vSupIzq.x;
    v.y= vSupIzq.y+i*pasoEntrada+10;
    pins.push_back(v);
  }
  //salida
  for(int i= 0; i<salidas; i++) {
    v.x= vSupIzq.x+ancho-10;
    v.y= vSupIzq.y+i*pasoSalida+10;
    pins.push_back(v);
  }
}

void Circuito::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  this->vSupIzq= vSupIzq;
  cargarNuevosPins(vSupIzq);
}

void Circuito::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y+10);
  context->line_to(vSupIzq.x+ancho-10, vSupIzq.y+10);
  context->move_to(vSupIzq.x+ancho-10, vSupIzq.y+10);
  context->line_to(vSupIzq.x+ancho-10, vSupIzq.y+alto-10);
  context->move_to(vSupIzq.x+ancho-10, vSupIzq.y+alto-10);
  context->line_to(vSupIzq.x+10, vSupIzq.y+alto-10);
  context->move_to(vSupIzq.x+10, vSupIzq.y+alto-10);
  context->line_to(vSupIzq.x+10, vSupIzq.y+10);
  context->stroke();
  //entradas y salidas
  context->set_source_rgb(0.0, 0.0, 0.0);
  std::list<Vertice>::iterator it;
  for(it= pins.begin(); it != pins.end(); it++) {
    context->move_to(it->x, it->y);
    context->line_to(it->x+10, it->y);
  }
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);

  context->set_source_rgb(1.0, 0.0, 0.0);
  for(it= pins.begin(); it != pins.end(); it++) {
    context->move_to(it->x, it->y);
    context->line_to(it->x, it->y+5);
  }
  context->stroke();
};
