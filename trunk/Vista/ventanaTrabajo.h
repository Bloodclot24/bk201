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
#include <gtkmm/table.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/button.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm/dragcontext.h>

#include <iostream>
#include "areaDibujo.h"
#include "../Controlador/controlador.h"

#define PATH_VISTA "Vista/interfaz.glade"
#define CIRCUITO "Circuito "
#define NOMBRE_PROGRAMA " - Bk201"

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
  void guardar();
  void guardarComo();
  void cerrar();
  void rotar90D();
  void rotar90I();
  void borrar();
  void simular();
  void verTablas();
  void about();
		
  /*TOOLBAR*/
  Gtk::ToolButton* bAnd;
  Gtk::ToolButton* bOr;
  void loadToolBar();

  /*TARGETS*/
  std::list<Gtk::TargetEntry> listTargets;
		
  Gtk::Window *window;
  bool on_delete_event(GdkEventAny *event);

  Gtk::FileChooserDialog *filechooserdialog_open;
  void on_response_open(int response_id);

  Gtk::FileChooserDialog *filechooserdialog_saveas;
  void on_response_saveas(int response_id);

  /*AREADIBUJO*/
  AreaDibujo areaDibujo;

  virtual ~VentanaTrabajo() {};

protected:
  //Signal handlers
  void on_drag_data_get(
          const Glib::RefPtr<Gdk::DragContext>& context,
          Gtk::SelectionData& selection_data, guint info, guint time);
  void on_label_drop_drag_data_received(
          const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
          const Gtk::SelectionData& selection_data, guint info, guint time);
  void on_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);

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
