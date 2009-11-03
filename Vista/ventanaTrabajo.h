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
#include <gtkmm/filechooserdialog.h>
#include <iostream>
#include "../Controlador/controlador.h"

#define PATH_VISTA "Vista/interfaz.glade"
#define CIRCUITO "Circuito "
#define NOMBRE_PROGRAMA " - Bk201"

/**
 * Ventana de principal de trabajo para el usuario.
 */
class VentanaTrabajo {
       
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
  void guardar();
  void guardarComo();
  void cerrar();
  void rotar90();
  void borrar();
  void simular();
  void verTablas();
  void about();
		
  /*TOOLBAR*/
  void loadToolBar();
		
  Gtk::Window *window;
  bool on_delete_event(GdkEventAny *event);

  Gtk::FileChooserDialog *filechooserdialog_open;
  void on_response_open(int response_id);

  Gtk::FileChooserDialog *filechooserdialog_saveas;
  void on_response_saveas(int response_id);

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
