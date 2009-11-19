#include "Compuerta.h"

Compuerta::Compuerta(int supIzqX, int supIzqY): Dibujo::Dibujo(supIzqX, supIzqY) {

  vCentro.x= supIzqX +(DIMENSION_COMPUERTA/2);
  vCentro.y= supIzqY +(DIMENSION_COMPUERTA/2);
  ancho= alto= DIMENSION_COMPUERTA;
}

