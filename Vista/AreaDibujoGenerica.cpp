#include "AreaDibujoGenerica.h"

void AreaDibujoGenerica::agregarDibujo(Dibujo* dibujo){
     agregarComponente(dibujo);
}

void AreaDibujoGenerica::agregarComponente(Dibujo* dibujo) {
  deseleccionar();
  dibujo->seleccionar();
  dibujos.push_back(dibujo);
  dibujoSeleccionados.clear();
  dibujoSeleccionados.push_back(dibujo);
  seleccion= true;
  selected= false;
  redibujar();
}

void AreaDibujoGenerica::redibujar(){
     //fuerzo al redibujado
     if(window) {
	  Gdk::Rectangle r(0, 0, get_allocation().get_width(),
			   get_allocation().get_height());
	  window->invalidate_rect(r, false);
     }
}

void AreaDibujoGenerica::deseleccionar() {
  //libero los componentes
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++)
       (*it)->deseleccionar();
}


void AreaDibujoGenerica::agregarDibujo(ConexionDibujo* dibujo){
     dibujo->setAreaDibujo(this);
     agregarDibujo((Dibujo*) dibujo);
};

Dibujo* AreaDibujoGenerica::buscarDibujo(int x, int y) {

  std::list<Dibujo*>::iterator it;
  bool encontrado= false;

  for(it= dibujos.begin(); it != dibujos.end() && !encontrado; it++) {
    encontrado= (*it)->setSeleccionado(x,y);
    if(encontrado)
      break;
  }
  if(!encontrado)
    return NULL;
  return *it;
}

Dibujo* AreaDibujoGenerica::buscarDibujoCercano(Dibujo *origen, int x, int y) {

  std::list<Dibujo*>::iterator it;
  bool encontrado= false;

  for(it= dibujos.begin(); it != dibujos.end() && !encontrado; it++) {
    encontrado= (*it)->estaCercano(x,y);
    if(encontrado && *it != origen)
	 break;
    else encontrado=false;
  }
  if(!encontrado)
    return NULL;
  return *it;
}

bool AreaDibujoGenerica::existeDibujo(Dibujo* d){
     std::list<Dibujo*>::iterator it;
     bool encontrado= false;

     for(it= dibujos.begin(); it != dibujos.end() && !encontrado; it++) {
	  encontrado= (*it) == d;
     }

     return encontrado;
}

void AreaDibujoGenerica::vaciarListaDibujos(){
	if(dibujos.size()) dibujos.clear();
}

uint32_t AreaDibujoGenerica::getAncho(){
     std::list<Dibujo*>::iterator it;
     uint32_t xMax=0;
     for(it = dibujos.begin(); it!=dibujos.end();it++){
	  if(xMax < (uint32_t)(*it)->getVerticeSupIzq().x)
	       xMax=(*it)->getVerticeSupIzq().x;
     }
     return xMax+50;
}

uint32_t AreaDibujoGenerica::getAlto(){
     std::list<Dibujo*>::iterator it;
     uint32_t yMax=0;
     for(it = dibujos.begin(); it!=dibujos.end();it++){
	  if(yMax < (uint32_t)(*it)->getVerticeSupIzq().y)
	       yMax= (*it)->getVerticeSupIzq().y;
     }
     return yMax+50;

}
