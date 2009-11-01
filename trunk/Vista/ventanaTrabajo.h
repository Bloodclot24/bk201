#ifndef VENTANATRABAJO_H_
#define VENTANATRABAJO_H_

#include <gtkmm.h>
#include <iostream>
#include "../Controlador/controlador.h"

#define PATH_VISTA "Vista/interfaz.glade"

/**
 * Ventana de principal de trabajo para el usuario.
 */
class VentanaTrabajo {
       
	private:
		Glib::RefPtr<Gtk::Builder> refXml;
		Controlador *controlador;
		
		/*MENUBAR*/
    Glib::RefPtr<Gtk::UIManager> m_refUIManager;
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
		void loadMenuBar(Gtk::Window *main_window);
		
		/*TOOLBAR*/
		void loadToolBar();
		
	public:
	/**
    * Crea una ventana de trabajo nueva.
    *
    * @param controlador Controlador del modelo.
		*/
		VentanaTrabajo(Controlador *controlador);
               
	/**	
		* Comienza a correr la interfaz grafica.
    */
		void correr();
};

#endif /*VENTANATRABAJO_H_*/
class VentanaTrabajo;