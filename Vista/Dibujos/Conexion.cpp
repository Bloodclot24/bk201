#include "Conexion.h"

ConexionDibujo::ConexionDibujo(int vInicialX, int vInicialY, Vertice vInfDer, AreaDibujoGenerica *areaDibujo): Dibujo::Dibujo(vInicialX, vInicialY) {

  this->tipo= this->label= TIPO_PISTA;
  this->vInfDer= vInfDer;
  this->areaDibujo= areaDibujo;
  this->dibujoPin1= NULL;
  this->dibujoPin2= NULL;
  generarPoligonos();
}

void ConexionDibujo::generarPoligonos() {

  poligonos.clear();
  poligonos.push_back(rotarPin(vSupIzq.x, vSupIzq.y));
  poligonos.push_back(rotarPin(vCentro.x, vSupIzq.y));
  poligonos.push_back(rotarPin(vCentro.x, vCentro.y));
  poligonos.push_back(rotarPin(vCentro.x, vInfDer.y));
  poligonos.push_back(rotarPin(vInfDer.x, vInfDer.y));
}

void ConexionDibujo::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //si tengo algun extremo suelto, veo si tengo un
  //pin cercano
  if(!dibujoPin1 && areaDibujo) {
    dibujoPin1= areaDibujo->buscarDibujoCercano(this, vSupIzq.x, vSupIzq.y);
    if(dibujoPin1) {
      nroPin1= dibujoPin1->obtenerPinMasCercano(vSupIzq.x,vSupIzq.y);

      if(nroPin1 == -1)
	dibujoPin1= NULL;
    }
  }
  if(!dibujoPin2 && areaDibujo) {
    dibujoPin2= areaDibujo->buscarDibujoCercano(this, vInfDer.x, vInfDer.y);
    if(dibujoPin2) {
      nroPin2= dibujoPin2->obtenerPinMasCercano(vInfDer.x, vInfDer.y);
      if(nroPin2 == -1)
	dibujoPin2= NULL;
    }
  }
  //busco cambios en la ubicacion de los pines a los que
  //estoy unido

  if(areaDibujo->existeDibujo(dibujoPin1)) {

    vSupIzq= dibujoPin1->obtenerPin(nroPin1);
  }
  else
    dibujoPin1=NULL;
  if(areaDibujo->existeDibujo(dibujoPin2)) {
    vInfDer= dibujoPin2->obtenerPin(nroPin2);
  }
  else
    dibujoPin2=NULL;
  calcularAtributos();
  //regenero las trayectorias
  generarPoligonos();

  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);

  //seteo matriz identidad
  context->set_identity_matrix();

  //dibujo de a poligonos
  context->set_source_rgb(0.0, 0.0, 0.0);
  bool primero= true;
  Vertice anterior;
  std::list<Vertice>::iterator it;
  for(it= poligonos.begin(); it != poligonos.end(); it++) {
    if(!primero) {
      context->move_to(anterior.x, anterior.y);
      context->line_to(it->x, it->y);
      anterior= *it;
    } else {
      primero= false;
      anterior= *it;
    }
  }
  context->stroke();
}

void ConexionDibujo::dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
  context->move_to(vSupIzq.x-3.5, vSupIzq.y-3.5);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y-3.5, 7, 7);
  context->move_to(vInfDer.x-3.5, vInfDer.y-3.5);
  context->rectangle(vInfDer.x-3.5, vInfDer.y-3.5, 7, 7);
  context->stroke();
}

bool ConexionDibujo::setSeleccionado(int x, int y) {

  bool primero= true;
  int menorX, mayorX;
  int menorY, mayorY;
  Vertice anterior;
  std::list<Vertice>::iterator it;
  for(it= poligonos.begin(); it != poligonos.end() && !seleccionado; it++) {

    if(!primero) {

      if(anterior.x < it->x) {
	menorX= anterior.x-5;
	mayorX= it->x+5;
      } else {
	menorX= it->x-5;
	mayorX= anterior.x+5;
      }

      if(anterior.y < it->y) {
	menorY= anterior.y-5;
	mayorY= it->y+5;
      } else {
	menorY= it->y-5;
	mayorY= anterior.y+5;
      }

      if((x >= menorX) && ((x <= mayorX)) && ((y >= menorY) && (y <= mayorY)))
	seleccionado= true;
      anterior= *it;
    } else {
      primero= false;
      anterior= *it;
    }
  }

  return seleccionado;
}

bool ConexionDibujo::estaCercano(int x, int y) {

  bool cercano= false;
  bool primero= true;
  int menorX, mayorX;
  int menorY, mayorY;
  Vertice anterior;
  std::list<Vertice>::iterator it;
  for(it= poligonos.begin(); it != poligonos.end() && !seleccionado; it++) {

    if(!primero) {

      if(anterior.x < it->x) {
	menorX= anterior.x-5;
	mayorX= it->x+5;
      } else {
	menorX= it->x-5;
	mayorX= anterior.x+5;
      }

      if(anterior.y < it->y) {
	menorY= anterior.y-5;
	mayorY= it->y+5;
      } else {
	menorY= it->y-5;
	mayorY= anterior.y+5;
      }

      if((x >= menorX) && ((x <= mayorX)) && ((y >= menorY) && (y <= mayorY)))
	cercano= true;
      anterior= *it;
    } else {
      primero= false;
      anterior= *it;
    }
  }

  return cercano;
}


void ConexionDibujo::calcularAtributos(){

  int deltaX= vInfDer.x-vSupIzq.x;
  int deltaY= vInfDer.y-vSupIzq.y;
  vCentro.x= vSupIzq.x + deltaX/2;
  vCentro.y= vSupIzq.y + deltaY/2;
  ancho= deltaX;
  alto= deltaY;
  pines.clear();
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y));
  pines.push_back(rotarPin(vInfDer.x, vInfDer.y));
}

void ConexionDibujo::setVerticeSupIzq(Vertice vSupIzq) {
  this->dibujoPin1 = NULL;;
  this->nroPin1= 0;
  this->vSupIzq= vSupIzq;
}

void ConexionDibujo::setVerticeInfDer(Vertice vInfDer) {
  this->vInfDer=vInfDer;
}

Vertice  ConexionDibujo::getVerticeInfDer() {
  return vInfDer;
}

void ConexionDibujo::setAreaDibujo(AreaDibujoGenerica *area) {
  areaDibujo= area;
}

void ConexionDibujo::setVerticesMotion(int deltax, int deltay) {
  Vertice vInicio;
  vInicio.x= vSupIzq.x + deltax;
  vInicio.y= vSupIzq.y + deltay;
  Vertice vFin;
  vFin.x= vInfDer.x + deltax;
  vFin.y= vInfDer.y + deltay;
  setVerticeSupIzq(vInicio);
  setVerticeInfDer(vFin);
}

void ConexionDibujo::dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) {
  //dibujo de a poligonos
  context->set_source_rgb(0.0, 0.0, 0.0);
  bool primero= true;
  Vertice anterior;
  std::list<Vertice>::iterator it;
  for(it= poligonos.begin(); it != poligonos.end(); it++) {
    if(!primero) {
      context->move_to(anterior.x, anterior.y);
      context->line_to(it->x, it->y);
      anterior= *it;
    } else {
      primero= false;
      anterior= *it;
    }
  }
  context->stroke();
}
