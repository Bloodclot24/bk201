#include "controlador.h"

Controlador::Controlador() {
        
	this->ventanaTrabajo= new VentanaTrabajo(this);	
}

Controlador::~Controlador() {

	delete ventanaTrabajo;
}

void Controlador::correr() {
        
	ventanaTrabajo->correr();
}