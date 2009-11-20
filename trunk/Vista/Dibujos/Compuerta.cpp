#include "Compuerta.h"

Compuerta::Compuerta(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  ancho= alto= DIMENSION_COMPUERTA;
  vCentro.x= supIzqX + (ancho/2);
  vCentro.y= supIzqY + (alto/2);
}

void Compuerta::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  this->vSupIzq= vSupIzq;
  cargarNuevosPins(vSupIzq);
}

Vertice* Compuerta::obtenerPin(int x, int y) {

  std::list<Vertice>::iterator it;
  bool encontrado= false;
  for(it= pins.begin(); it != pins.end() && !encontrado; it++) {

    if( ((x >= it->x-TOLERANCIA) && (x <= it->x+TOLERANCIA)) && ((y >= it->y-TOLERANCIA) && (y <= it->y+TOLERANCIA)) ) {
      encontrado= true;
      break;
    }
  }
  if(!encontrado)
    return NULL;

  Vertice *v= new Vertice();
  v->x= it->x;
  v->y= it->y;

  return v;
}

std::string Compuerta::getEtiqueta(){
	return this->etiqueta;
}
  
void Compuerta::setEtiqueta(const std::string& etiqueta){
	this->etiqueta = etiqueta;
}

