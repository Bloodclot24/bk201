#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include <map>
#include "../Vista/ventanaTrabajo.h"
#include "../Util/Util.h"

/**
 * El controlador de la aplicacion.
 */
class Controlador {

private:
  std::map<unsigned int, VentanaTrabajo*> ventanasTrabajo;
  unsigned int cantVentanas;

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

  /**
    * Crea una nueva ventana de trabajo. 
    */
    void crearNuevaVentana();

 /**
   * Cierra una ventana de trabajo.
   */
    void cerrarVentana(unsigned int id);
};

#endif /*CONTROLADOR_H_*/
class Controlador;
