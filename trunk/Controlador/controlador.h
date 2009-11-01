#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "../Vista/ventanaTrabajo.h"

/**
 * El controlador de la aplicacion.
 */
class Controlador {

	private:
		VentanaTrabajo *ventanaTrabajo;
                
	public:
	/**
    * Crea un controlador. 
 		*/
		Controlador(); 
            
	/**
    * Destruye el controlador. 
		*/
		~Controlador();

	/**
    * Comienza a correr la aplicacion, tanto la vista como el modelo. 
		*/
		void correr();
};

#endif /*CONTROLADOR_H_*/
class Controlador;
