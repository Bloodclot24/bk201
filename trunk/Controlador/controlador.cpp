#include "controlador.h"

Controlador::Controlador() {

  this->cantVentanas= 0;
}

Controlador::~Controlador() {

  std::map<unsigned int, VentanaTrabajo*>::iterator it;
  for(it= ventanasTrabajo.begin(); it != ventanasTrabajo.end(); it++)
    delete it->second;
}

void Controlador::correr() {

  ControladorVentana *controlador= new ControladorVentana();
  controlador->iniciar();
  VentanaTrabajo *ventana= new VentanaTrabajo(this, controlador, cantVentanas);
  controlador->setVentana(ventana);
  ventanasTrabajo.insert( std::pair<unsigned int, VentanaTrabajo*>(cantVentanas,ventana));
  ventana->correr(true);
}

void Controlador::crearNuevaVentana() {

  cantVentanas++;
  ControladorVentana *controlador= new ControladorVentana();
  controlador->iniciar();
  VentanaTrabajo *ventana= new VentanaTrabajo(this, controlador, cantVentanas);
  controlador->setVentana(ventana);
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
