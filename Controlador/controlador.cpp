#include "controlador.h"

Controlador::Controlador() {
        
}

Controlador::~Controlador() {

}

void Controlador::correr() {

	VentanaTrabajo *ventana= new VentanaTrabajo(this, 0);	
	ventanasTrabajo.insert( std::pair<unsigned int, VentanaTrabajo*>(0,ventana));
	ventana->correr(true);
}

void Controlador::crearNuevaVentana() {

	unsigned int id= ventanasTrabajo.size();	
	VentanaTrabajo *ventana= new VentanaTrabajo(this, id);	
	ventanasTrabajo.insert( std::pair<unsigned int, VentanaTrabajo*>(id,ventana) );
	ventana->correr();
}

void Controlador::cerrarVentana(unsigned int id) {
	
	std::map<unsigned int, VentanaTrabajo*>::iterator it;
	it= ventanasTrabajo.find(id);
  ventanasTrabajo.erase(it); 
  
	if(ventanasTrabajo.empty())
		Gtk::Main::quit();	
}