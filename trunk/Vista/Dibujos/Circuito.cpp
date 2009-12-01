#include "Circuito.h"

CircuitoDibujo::CircuitoDibujo(int supIzqX, int supIzqY, int entradas, int salidas): Dibujo::Dibujo(supIzqX, supIzqY) {

  tipo= label= TIPO_CIRCUITO;
  setEntradasSalidas(entradas, salidas);
  vCentro.x= supIzqX + (ancho/2);
  vCentro.y= supIzqY + (alto/2);
  examinar= true;
}

void CircuitoDibujo::setEntradasSalidas(int entradas, int salidas){
  this->entradas= entradas;
  this->salidas= salidas;
     
  int mayor;
  if(entradas > salidas) {
    mayor= entradas;
    pasoEntrada= 10;
    pasoSalida= pasoPinesMenor(entradas, salidas);
  } else if(entradas < salidas) {
    mayor= salidas;
    pasoSalida= 10;
    pasoEntrada= pasoPinesMenor(salidas, entradas);
  } else if(entradas == salidas) {
    mayor= salidas;
    pasoEntrada= pasoSalida= 10;
  }
     
  ancho= alto= mayor*SEPARACION+10;
          
  cargarNuevosPines(vSupIzq);
}

int CircuitoDibujo::pasoPinesMenor(int mayor, int menor) {

  int paso= (mayor*SEPARACION+10)/menor;
  int mod= paso % 10;
  if(mod != 0 && (menor%2)==0 && (mayor%menor)==0)
    paso+= mod;
  else
    paso-= mod;

  return paso;
}

void CircuitoDibujo::cargarNuevosPines(Vertice vSupIzq) {

  pines.clear();
  Vertice v;
  //entrada
  for(int i= 0; i<entradas; i++) {
    v.x= vSupIzq.x;
    v.y= vSupIzq.y+i*pasoEntrada+10;
    pines.push_back(rotarPin(v.x, v.y));
  }
  //salida
  for(int i= 0; i<salidas; i++) {
    v.x= vSupIzq.x+ancho-10;
    v.y= vSupIzq.y+i*pasoSalida+10;
    pines.push_back(rotarPin(v.x, v.y));

  }
}

void CircuitoDibujo::setVerticeSupIzq(Vertice vSupIzq) {

  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  this->vSupIzq= vSupIzq;
  cargarNuevosPines(vSupIzq);
}


void CircuitoDibujo::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {
  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y+10);
  context->line_to(vSupIzq.x+ancho-10, vSupIzq.y+10);
  context->move_to(vSupIzq.x+ancho-10, vSupIzq.y+10);
  context->line_to(vSupIzq.x+ancho-10, vSupIzq.y+alto-10);
  context->move_to(vSupIzq.x+ancho-10, vSupIzq.y+alto-10);
  context->line_to(vSupIzq.x+10, vSupIzq.y+alto-10);
  context->move_to(vSupIzq.x+10, vSupIzq.y+alto-10);
  context->line_to(vSupIzq.x+10, vSupIzq.y+10);
  context->stroke();
  //entradas y salidas
  context->set_source_rgb(0.0, 0.0, 0.0);
  int size= pines.size();
  int auxiliar=angulo;
  angulo=-angulo;
  for(int i= 0; i<size; i++) {
    Vertice temporal=pines[i];
    temporal = rotarPin(temporal.x, temporal.y);
    context->move_to(temporal.x, temporal.y);
    context->line_to(temporal.x+10, temporal.y);
  }
  angulo=auxiliar;
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);
};

std::string CircuitoDibujo::getServidor() {
  return servidor;
}

void CircuitoDibujo::setServidor(std::string servidor) {
  this->servidor= servidor;
}

std::string CircuitoDibujo::getPuerto() {
  return puerto;
}

void CircuitoDibujo::setPuerto(std::string puerto) {
  this->puerto= puerto;
}

void CircuitoDibujo::setAngulo(int angulo){
  this->angulo+=angulo;
  vCentro.x= vSupIzq.x + (ancho/2);
  vCentro.y= vSupIzq.y + (alto/2);
  cargarNuevosPines(vSupIzq);
}

void CircuitoDibujo::mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto) {

  context->move_to(vSupIzq.x, yTexto);
  context->show_text(label);
  context->move_to(vSupIzq.x, yTexto+15);
  context->show_text("Servidor: ");
  context->show_text(servidor);
  context->show_text(":");
  context->show_text(puerto);
  context->stroke();
};

int CircuitoDibujo::getCantidadEntradas() {
  return entradas;
}

int CircuitoDibujo::getCantidadSalidas() {
  return salidas;
}

void CircuitoDibujo::agregarDatos(const std::string &servidor, const std::string &puerto, const std::string &nombre) {
  this->servidor= servidor;
  this->puerto= puerto;
  this->nombre= nombre;
  this->label= nombre;
}

std::string CircuitoDibujo::getNombre() {
  return this->nombre;
}

void CircuitoDibujo::dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context) {

  this->dibujar(context);
}
