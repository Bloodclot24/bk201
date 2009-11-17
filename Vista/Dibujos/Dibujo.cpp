#include "Dibujo.h"

Dibujo::Dibujo(int xUp, int yUp): vCentro(), vSupIzq() {

  vSupIzq.x= xUp;
  vSupIzq.y= yUp;
  angulo= 0;
}

Vertice Dibujo::getVerticeCentro() {

  return vCentro;
}

Vertice Dibujo::getVerticeSupIzq() {

  return vSupIzq;
}

void Dibujo::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x+20;
  vCentro.y= vSupIzq.y+20;
  this->vSupIzq= vSupIzq;
}

int Dibujo::getAngulo() {

  return angulo;
}

void Dibujo::setAngulo(int angulo) {

  this->angulo+= angulo;
}
