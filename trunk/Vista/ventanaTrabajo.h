#ifndef VENTANATRABAJO_H_
#define VENTANATRABAJO_H_

#include <gtkmm/window.h>
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/main.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/stock.h>
#include <gtkmm/aboutdialog.h>
#include <iostream>
#include "../Controlador/controlador.h"

#define PATH_VISTA "Vista/interfaz.glade"

/**
 * Ventana de principal de trabajo para el usuario.
 */
class VentanaTrabajo: public Gtk::Window {
       
private:
  Glib::RefPtr<Gtk::Builder> refXml;
  Controlador *controlador;
  unsigned int id;
		
  /*MENUBAR*/
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  void loadMenuBar(Gtk::Window *main_window);
  void nuevo();
  void abrir();
  void cerrar();
  void about();
		
  /*TOOLBAR*/
  void loadToolBar();
		
  Gtk::Window *window;

protected:
  bool on_delete_event(GdkEventAny *event);

public:
  /**
    * Crea una ventana de trabajo nueva.
    *
    * @param controlador Controlador del modelo.
    */
    VentanaTrabajo(Controlador *controlador, unsigned int id);
               
  /**
    * Comienza a correr la interfaz grafica.
    */
    void correr(bool primeraVez= false);
};

#endif /*VENTANATRABAJO_H_*/
class VentanaTrabajo;
