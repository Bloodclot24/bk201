#include "Dibujo.h"

Dibujo::Dibujo(int xUp, int yUp): vCentro(), vSupIzq() {

  vSupIzq.x= xUp;
  vSupIzq.y= yUp;
  angulo= 0;
  seleccionado= true;
  examinar= false;
  tipo= "";
}

Vertice Dibujo::getVerticeCentro() {
  return vCentro;
}

Vertice Dibujo::getVerticeSupIzq() {
  return vSupIzq;
}

int Dibujo::getAngulo() {
  return angulo;
}

void Dibujo::setAngulo(int angulo) {
  this->angulo+= angulo;
}

void Dibujo::seleccionar() {
  seleccionado= true;
}

void Dibujo::deseleccionar() {
  seleccionado= false;
}

bool Dibujo::setSeleccionado(int x, int y) {

  if((x >= vSupIzq.x) && ((x <= vSupIzq.x+ancho)) && (y >= vSupIzq.y) && (y <= (vSupIzq.y+alto)))
    seleccionado= true;
  else
    seleccionado= false;

  return seleccionado;
}

void Dibujo::dibujarSeleccion(const Cairo::RefPtr<Cairo::Context>& context) {

  context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
  context->rectangle(vSupIzq.x-2, vSupIzq.y-2, ancho+4, alto+4);
  context->fill();
  context->stroke();
  context->set_source_rgba(0, 0, 0, 0.5);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y-3.5, 7, 7);
  context->rectangle(vSupIzq.x+ancho+-3.5, vSupIzq.y-3.5, 7, 7);
  context->rectangle(vSupIzq.x-3.5, vSupIzq.y+alto-3.5, 7, 7);
  context->rectangle(vSupIzq.x+ancho-3.5, vSupIzq.y+alto-3.5, 7, 7);
  context->stroke();
}

void Dibujo::mostrarEtiqueta(const Cairo::RefPtr<Cairo::Context>& context, int vSupIzq_y, int alto) {
  int yTexto = 0;

  if((vSupIzq.y - 25) <= 0)
    yTexto = vSupIzq.y + alto + 25;
  else
    yTexto = vSupIzq.y -25;

  context->set_source_rgb(1.0, 0.0, 0.0);
  context->set_identity_matrix();
  context->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
  context->set_font_size(12);
  mostrarAtributos(context, yTexto);
}

Vertice Dibujo::rotarPin(int x, int y, const Cairo::RefPtr<Cairo::Context>& context) {

  Vertice v;
  v.x= x;
  v.y= y;
  double xi=v.x;
  double yi=v.y;
  context->user_to_device(xi,yi);
  v.x= xi;
  v.y= yi;

  return v;
}

std::string Dibujo::getLabel() {
  return label;
}

void Dibujo::setLabel(const std::string& label) {
  this->label= label;
}

bool Dibujo::getExaminar() {
  return examinar;
}

int Dibujo::obtenerPinMasCercano(int x, int y) {

  bool encontrado= false;
  int size= pines.size();
  int i;
  for(i= 0; i<size && !encontrado; i++) {
    if( ((x >= pines[i].x-TOLERANCIA) && (x <= pines[i].x+TOLERANCIA)) && ((y >= pines[i].y-TOLERANCIA) && (y <= pines[i].y+TOLERANCIA)) ) {
      encontrado= true;
      break;
    }

    std::cout << "pines[i].x: " << pines[i].x << std::endl;
    std::cout << "pines[i].y: " << pines[i].y << std::endl;
  }
  if(!encontrado)
    return -1;

  return i;
}

Vertice Dibujo::obtenerPin(int numPin) {
  return pines[numPin];
};


std::string Dibujo::getTipo() {
  return tipo;
}

int Dibujo::getAncho() {
  return ancho;
}

int Dibujo::getAlto() {
  return alto;
}
