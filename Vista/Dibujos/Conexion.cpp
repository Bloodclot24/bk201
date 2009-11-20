#include "Conexion.h"

Conexion::Conexion(int vInicialX, int vInicialY, int vFinalX, int vFinalY): Dibujo::Dibujo(vInicialX, vInicialY) {

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

void Conexion::generarPoligonos() {

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

void Conexion::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  std::cout << "adentro" << getSeleccionar() << std::endl;

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
  //TODO ver como se va a permitirle al usuario editar la etiqueta.
  mostrarEtiqueta(context,vSupIzq.y,alto,"");
}

void Conexion::dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
  context->move_to(vSupIzq.x-3.5, vSupIzq.y-3.5);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y-3.5, 7, 7);
  context->move_to(vFinal.x-3.5, vFinal.y-3.5);
  context->rectangle(vFinal.x-3.5, vFinal.y-3.5, 7, 7);
  context->stroke();
}

bool Conexion::setSeleccionado(int x, int y) {

  std::cout << "CONEXION" << std::endl;

  bool seleccionado= false;
  bool primero= true;
  int menorX, mayorX;
  int menorY, mayorY;
  Vertice anterior;
  std::list<Vertice>::iterator it;
  for(it= poligonos.begin(); it != poligonos.end() && !seleccionado; it++) {
    if(!primero) {

//      std::cout << "it->x: " << it->x << std::endl;
//      std::cout << "it->y: " << it->y << std::endl;
//      std::cout << "anterior.x: " << anterior.x << std::endl;
//      std::cout << "anterior.y: " << anterior.y << std::endl;

      if(anterior.x <= it->x) {
        menorX= anterior.x;
        mayorX= it->x;
      } else {
        menorX= it->x;
        mayorX= anterior.x;
      }

      if(anterior.y <= it->y) {
        menorY= anterior.y;
        mayorY= it->y;
      } else {
        menorY= it->y;
        mayorY= anterior.y;
      }
      if((x >= menorX) && ((x <= mayorX)) && ((y >= menorY) && (y <= mayorY))) {
         std::cout << "seleccionnadooooooooooooo" << std::endl;
         seleccionado= true;
       }
    } else {
      primero= false;
      anterior= *it;
    }
  }

  return seleccionado;
}
