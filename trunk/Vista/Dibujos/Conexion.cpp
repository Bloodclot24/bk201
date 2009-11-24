#include "Conexion.h"

ConexionDibujo::ConexionDibujo(int vInicialX, int vInicialY, int vFinalX, int vFinalY): Dibujo::Dibujo(vInicialX, vInicialY) {

  label= "Conexion";
  vFinal.x= vFinalX;
  vFinal.y= vFinalY;
  int deltaX= vFinalX-vInicialX;
  int deltaY= vFinalY-vInicialY;
  vCentro.x= vInicialX + deltaX/2;
  vCentro.y= vInicialY + deltaY/2;
  ancho= deltaX;
  alto= deltaY;
  generarPoligonos();
}

void ConexionDibujo::generarPoligonos() {

  Vertice v;
  poligonos.clear();
  v.x= vSupIzq.x;
  v.y= vSupIzq.y;
  poligonos.push_back(v);
  v.x= vCentro.x;
  v.y= vSupIzq.y;
  poligonos.push_back(v);
  v.x= vCentro.x;
  v.y= vCentro.y;
  poligonos.push_back(v);
  v.x= vCentro.x;
  v.y= vFinal.y;
  poligonos.push_back(v);
  v.x= vFinal.x;
  v.y= vFinal.y;
  poligonos.push_back(v);
}

void ConexionDibujo::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

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

  if(seleccionado)
    dibujarSeleccion(context);

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

