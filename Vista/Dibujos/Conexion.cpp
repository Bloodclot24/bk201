#include "Conexion.h"

ConexionDibujo::ConexionDibujo(int vInicialX, int vInicialY, Dibujo* dibujoPin1, int nroPin1, AreaDibujo *areaDibujo): Dibujo::Dibujo(vInicialX, vInicialY) {

  label= "Conexion";
  this->dibujoPin1= dibujoPin1;
  this->nroPin1= nroPin1;
  this->areaDibujo= areaDibujo;
}

void ConexionDibujo::generarPoligonos(const Cairo::RefPtr<Cairo::Context>& context) {

  poligonos.clear();

//  Vertice v;
  //  v.x= vSupIzq.x;
  //  v.y= vSupIzq.y;
  //  poligonos.push_back(v);
  //  v.x= vCentro.x;
  //  v.y= vSupIzq.y;
  //  poligonos.push_back(v);
  //  v.x= vCentro.x;
  //  v.y= vCentro.y;
  //  poligonos.push_back(v);
  //  v.x= vCentro.x;
  //  v.y= vFinal.y;
  //  poligonos.push_back(v);
  //  v.x= vFinal.x;
  //  v.y= vFinal.y;
  //  poligonos.push_back(v);

  poligonos.push_back(rotarPin(vSupIzq.x, vSupIzq.y, context));
  poligonos.push_back(rotarPin(vCentro.x, vSupIzq.y, context));
  poligonos.push_back(rotarPin(vCentro.x, vCentro.y, context));
  poligonos.push_back(rotarPin(vCentro.x, vFinal.y, context));
  poligonos.push_back(rotarPin(vFinal.x, vFinal.y, context));
}

void ConexionDibujo::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //si tengo algun extremo suelto, veo si tengo un
  //pin cercano
//  if(!dibujoPin1) {
//    dibujoPin1= areaDibujo->buscarDibujo(vSupIzq.x, vSupIzq.y);
//    if(dibujoPin1) {
//      nroPin1= dibujoPin1->obtenerPinMasCercano(vSupIzq.x,vSupIzq.y);
//      if(nroPin1 == -1)
//        dibujoPin1= NULL;
//    }
//  }
//  if(!dibujoPin2) {
//    dibujoPin2= areaDibujo->buscarDibujo(vFinal.x, vFinal.y);
//
//    std::cout << dibujoPin2 << std::endl;
//
//
//    if(dibujoPin2) {
//      nroPin2= dibujoPin2->obtenerPinMasCercano(vFinal.x,vFinal.x);
//
//      std::cout << "nroPin2:" << nroPin2 << std::endl;
//
//      if(nroPin2 == -1)
//        dibujoPin2= NULL;
//    }
//  }
  //busco cambios en la ubicacion de los pines a los que
  //estoy unido

  if(dibujoPin1) {
    vSupIzq= dibujoPin1->obtenerPin(nroPin1);
  }
  if(dibujoPin2) {
    vFinal= dibujoPin2->obtenerPin(nroPin2);
  }
  calcularAtributos(context);

  //regenero las trayectorias
  generarPoligonos(context);

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

  context->set_source_rgb(1.0, 0.0, 0.0);
  context->move_to(vCentro.x, vCentro.y);
  context->line_to(vCentro.x, vCentro.y+5);
  context->stroke();
  
  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);
}

void ConexionDibujo::dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
  context->move_to(vSupIzq.x-3.5, vSupIzq.y-3.5);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y-3.5, 7, 7);
  context->move_to(vFinal.x-3.5, vFinal.y-3.5);
  context->rectangle(vFinal.x-3.5, vFinal.y-3.5, 7, 7);
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

void ConexionDibujo::calcularAtributos(const Cairo::RefPtr<Cairo::Context>& context) {

  int deltaX= vFinal.x-vSupIzq.x;
  int deltaY= vFinal.y-vSupIzq.y;
  vCentro.x= vSupIzq.x + deltaX/2;
  vCentro.y= vSupIzq.y + deltaY/2;
  ancho= deltaX;
  alto= deltaY;
  pines.clear();
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y, context));
  pines.push_back(rotarPin(vFinal.x, vFinal.y, context));
}

void ConexionDibujo::setVerticeSupIzq(Vertice vSupIzq) {

  this->vSupIzq= vSupIzq;
}

void ConexionDibujo::setVerticeFinal(Vertice vertice, Dibujo* dibujoPin2, int nroPin2) {

  vFinal= vertice;
  this->dibujoPin2= dibujoPin2;
  this->nroPin2= nroPin2;
}
