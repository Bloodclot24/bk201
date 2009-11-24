#include "Compuerta.h"

Compuerta::Compuerta(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  label= "Compuerta";
  ancho= alto= DIMENSION_COMPUERTA;
  vCentro.x= supIzqX + (ancho/2);
  vCentro.y= supIzqY + (alto/2);
}

void Compuerta::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  this->vSupIzq= vSupIzq;
  cargarNuevosPines(vSupIzq);
}

int Compuerta::obtenerPinMasCercano(int x, int y) {

  bool encontrado= false;
  int size= pines.size();
  int i;
  for(i= 0; i<size && !encontrado; i++) {
    if( ((x >= pines[i].x-TOLERANCIA) && (x <= pines[i].x+TOLERANCIA)) && ((y >= pines[i].y-TOLERANCIA) && (y <= pines[i].y+TOLERANCIA)) ) {
      encontrado= true;
      break;
    }
  }
  if(!encontrado)
    return -1;

  return i;
}
