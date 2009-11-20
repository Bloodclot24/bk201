#ifndef VENTANATRABAJO_H_
#define VENTANATRABAJO_H_

#include <gtkmm/window.h>
#include <gtkmm/widget.h>
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
#include <gtkmm/toolbar.h>
#include <gtkmm/entry.h>
#include <gtkmm/messagedialog.h>


#include <iostream>
#include "AreaDibujo.h"
#include "Dibujos/Dibujo.h"
#include "Dibujos/Constantes.h"
#include "Impresion/VentanaImpresion.h"
#include "../Controlador/controlador.h"

#define PATH_VISTA "Vista/interfaz.glade"
#define NOMBRE_CIRCUITO "Circuito "
#define NOMBRE_PROGRAMA " - Bk201"

#define PATH_AND "Vista/Imagenes/and.png"
#define PATH_OR "Vista/Imagenes/or.png"
#define PATH_NOT "Vista/Imagenes/not.png"
#define PATH_XOR "Vista/Imagenes/xor.png"
#define PATH_BUFFER "Vista/Imagenes/buf.png"
#define PATH_CONEXION "Vista/Imagenes/conexion.png"
#define PATH_IO "Vista/Imagenes/io.png"
#define PATH_CIRCUITO "Vista/Imagenes/circuito.png"

class AreaDibujo;
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
  Gtk::ToolButton *bAnd;
  Gtk::ToolButton *bOr;
  Gtk::ToolButton *bNot;
  Gtk::ToolButton *bXor;
  Gtk::ToolButton *bBuffer;
  Gtk::ToolButton *bConexion;
  Gtk::ToolButton *bIO;
  Gtk::ToolButton *bCircuito;
  Gtk::ToolButton *bSimular;
  Gtk::ToolButton *bImprimir;
  void loadButtonDrag(Gtk::ToolButton *button, std::string tipo, std::string path);
  void loadToolBar();

  /*TARGETS*/
  std::list<Gtk::TargetEntry> listTargets;
		
  Gtk::Window *window;
  bool on_delete_event(GdkEventAny *event);

  Gtk::FileChooserDialog *filechooserdialog_open;
  void on_response_open(int response_id);

  Gtk::FileChooserDialog *filechooserdialog_saveas;
  void on_response_saveas(int response_id);

  Gtk::Dialog *dialog_servidor;
  void on_response_servidor(int response_id);
  Gtk::MessageDialog *dialog_message;
  void ventanaServidor();

  /*AREADIBUJO*/
  AreaDibujo *areaDibujo;

  /*IMPRESION*/
  Gtk::Window *window_print;
  void loadVentanaImpresion();
  void cerrarVentanaImpresion();

protected:
  //Signal handlers
  void on_drag_data_get(
          const Glib::RefPtr<Gdk::DragContext>& context,
          Gtk::SelectionData& selection_data, guint info, guint time, Glib::ustring componente);
  void on_clicked_conexion();
  virtual void imprimir();

public:
  /**
    * Crea una ventana de trabajo nueva.
    *
    * @param controlador Controlador del modelo.
    */
    VentanaTrabajo(Controlador *controlador, unsigned int id);

    virtual ~VentanaTrabajo();
  /**
    * Comienza a correr la interfaz grafica.
    */
    void correr(bool primeraVez= false);

    void recibirListaCircuitos(std::list<std::string> lista);


};

#endif /*VENTANATRABAJO_H_*/
class VentanaTrabajo;
