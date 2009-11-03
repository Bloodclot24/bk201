#include "controlador.h"

Controlador::Controlador() {

  this->cantVentanas= 0;
}

Controlador::~Controlador() {

}

void Controlador::correr() {

  VentanaTrabajo *ventana= new VentanaTrabajo(this, cantVentanas);
  ventanasTrabajo.insert( std::pair<unsigned int, VentanaTrabajo*>(cantVentanas,ventana));
  ventana->correr(true);
}

void Controlador::crearNuevaVentana() {

  cantVentanas++;
  VentanaTrabajo *ventana= new VentanaTrabajo(this, cantVentanas);
  ventanasTrabajo.insert( std::pair<unsigned int, VentanaTrabajo*>(cantVentanas,ventana) );
  ventana->correr();
}

void Controlador::cerrarVentana(unsigned int id) {

  std::map<unsigned int, VentanaTrabajo*>::iterator it;
  it= ventanasTrabajo.find(id);
  ventanasTrabajo.erase(it); 
  
  if(ventanasTrabajo.empty())
    Gtk::Main::quit();
}
