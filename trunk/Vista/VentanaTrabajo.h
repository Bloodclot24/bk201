#ifndef VENTANATRABAJO_H_
#define VENTANATRABAJO_H_

class VentanaTrabajo;

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
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/viewport.h>

#include <iostream>
#include "AreaDibujo.h"
#include "Dibujos/Dibujo.h"
#include "Dibujos/Constantes.h"
#include "Impresion/VentanaImpresion.h"
#include "../Controlador/controlador.h"
#include "../Controlador/ControladorVentana.h"
#include "Tabla.h"
#include "CircuitoRemoto.h"

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
class VentanaImpresion;
/**
 * Ventana de principal de trabajo para el usuario.
 */
class VentanaTrabajo: public Gtk::Window {
  friend class AreaDibujo;

private:
  Glib::RefPtr<Gtk::Builder> refXml;
  Controlador        *controlador;
  ControladorVentana *controladorVentana;
  unsigned int id;
		
  /*MENUBAR*/
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_guardar;
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


  /*AREADIBUJO*/
  AreaDibujo *areaDibujo;

  /*SERVIDOR*/
  Gtk::Dialog *dialog_servidor;
  void on_response_servidor(int response_id);
  Gtk::MessageDialog *dialog_message;
  void ventanaServidor();
  Gtk::Dialog *dialog_lista_circuitos;
  void on_lista_circuitos(int response_id);

  /*TREEVIEW CIRCUITO*/
  Glib::RefPtr<Gtk::TreeView> treeView_circuitos;

  class ModelColumns_circuitos: public Gtk::TreeModel::ColumnRecord {

  public:
    ModelColumns_circuitos() {
      add(col_circuito);
      add(col_entradas);
      add(col_salidas);
    }

    Gtk::TreeModelColumn<Glib::ustring> col_circuito;
    Gtk::TreeModelColumn<int> col_entradas;
    Gtk::TreeModelColumn<int> col_salidas;
  };

  Glib::RefPtr<Gtk::ListStore> treeModel_circuitos;
  ModelColumns_circuitos columns_circuito;
  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
  void agregarCircuito(std::string circuito, int i, int o);

  /*TABLA*/
  Tabla *tabla;

  /*CIRCUITO REMOTO*/
  Gtk::Window *window_remoto;
  DibujoCircuitoRemoto *circuitoRemoto;
  void cerrar_circuito_remoto();
  bool on_delete_event_remoto(GdkEventAny *event);
  void obtenerDatosCircuito(std::string &servidor, std::string &puerto, std::string &nombre);
  std::string nombre;
  std::string puerto;
  std::string servidor;

  /*IMPRESION*/
  VentanaImpresion *window_print;

  /*TECLADO*/
  bool on_key_press_event(GdkEventKey* event);

  //Ventana Propiedades
  Gtk::Dialog *dialog_prop_compuerta;
  void on_propiedades_compuerta(int response_id);
  void prepararVentanaCompuerta(Dibujo *seleccionado);
  Gtk::Dialog *dialog_prop_io;
  void on_propiedades_io(int response_id);
  void prepararVentanaIO(Dibujo *seleccionado);
  Gtk::Dialog *dialog_prop_circuito;
  void on_propiedades_circuito(int response_id);
  void prepararVentanaCircuito(Dibujo *seleccionado);

  //Ventana Servidor
  sigc::connection id_ventana_servidor;
  bool llegoRta;
  std::list<DescripcionCircuito> lista_circuito;
  bool esperandoRtaServidor();

  //Error Servidor
  Gtk::Dialog *dialog_error_servidor;
  void on_error_servidor(int response_id);

  //Ventana Simulando
  Gtk::Dialog *dialog_simulando;
  sigc::connection id_ventana_simulando;
  bool llegoTabla;
  std::string mensajeTabla;
  bool esperandoRtaSimulacion();

  //Error Simulando
  Gtk::Dialog *dialog_error_simulando;
  Gtk::Label *label_error_simulando;
  void mostrarMsjErrorSimulando(const std::string mensaje);
  void on_error_simulando(int response_id);

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
    VentanaTrabajo(Controlador *controlador, ControladorVentana *controladorV, unsigned int id);

    virtual ~VentanaTrabajo();
  /**
    * Comienza a correr la interfaz grafica.
    */
    void correr(bool primeraVez= false);

    void recibirListaCircuitos(std::list<DescripcionCircuito> lista);
    void agregarDibujo(Dibujo *dibujo);
    void agregarDibujo(ConexionDibujo *dibujo);
    void recibirTablaSimulacion(std::list<uint32_t> listaTabla, int entradas, int salidas, const std::string& mensaje);
    void recibirCircuitoRemoto(const std::string& nombreArchivo, const std::string& nombreCircuito);
    void habilitarGuardar();
};

#endif /*VENTANATRABAJO_H_*/
