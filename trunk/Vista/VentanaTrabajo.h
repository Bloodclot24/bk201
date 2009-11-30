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
 * Es el encargo del manejo de los dialogos y del menubar.
 */
class VentanaTrabajo: public Gtk::Window {
  friend class AreaDibujo;

private:
  Glib::RefPtr<Gtk::Builder> refXml;
  Controlador *controlador;
  ControladorVentana *controladorVentana;
  unsigned int id;
  Gtk::Window *window;
  bool on_delete_event(GdkEventAny *event);
  Tabla *tabla;

  //Menubar
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_guardar;
  Glib::RefPtr<Gtk::ActionGroup> m_rotar;
  Glib::RefPtr<Gtk::ActionGroup> m_invertir;
  Glib::RefPtr<Gtk::ActionGroup> m_examinar;
  Glib::RefPtr<Gtk::ActionGroup> m_borrar;
  void loadMenuBar(Gtk::Window *main_window);
  void nuevo();
  void abrir();
  void guardar();
  void guardarComo();
  void cerrar();
  void invertirHorizontal();
  void invertirVertical();
  void rotar90D();
  void rotar90I();
  void examinar();
  void borrar();
  void simular();
  void verTablas();
  void about();
  void setSensitiveEditar(bool tipo);
		
  //Toolbar
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
  std::list<Gtk::TargetEntry> listTargets;
  void loadButtonDrag(Gtk::ToolButton *button, std::string tipo, std::string path);
  void loadToolBar();
		
  //Filechooser Dialog
  Gtk::FileChooserDialog *filechooserdialog_open;
  void on_response_open(int response_id);
  Gtk::FileChooserDialog *filechooserdialog_saveas;
  void on_response_saveas(int response_id);

  //Area Dibujo
  AreaDibujo *areaDibujo;
  void on_clicked_conexion();

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

  //Circuito Remoto
  Gtk::Window *window_remoto;
  DibujoCircuitoRemoto *circuitoRemoto;
  void cerrar_circuito_remoto();
  bool on_delete_event_remoto(GdkEventAny *event);
  void obtenerDatosCircuito(std::string &servidor, std::string &puerto, std::string &nombre);
  std::string nombre;
  std::string puerto;
  std::string servidor;

  //Impresion
  VentanaImpresion *window_print;
  void imprimir();

  //Teclado
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

  //Ventana Examinar
  Gtk::Dialog *dialog_examinar;
  sigc::connection id_ventana_remoto;
  std::string nombreTemp, nombreRemoto;
  bool llegoRemoto;

  //Error Examinar
  Gtk::Dialog *dialog_error_examinar;
  void on_error_examinar(int response_id);

  //Ventana Servidor
  Gtk::Dialog *dialog_servidor;
  void on_response_servidor(int response_id);
  Gtk::Dialog *dialog_conectandose;
  void ventanaServidor();
  Gtk::Dialog *dialog_lista_circuitos;
  void on_lista_circuitos(int response_id);
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

public:
  /**
   * Crea una ventana de trabajo nueva.
   *
   * @param controlador El controlador del modelo.
   */
  VentanaTrabajo(Controlador *controlador, ControladorVentana *controladorV, unsigned int id);

  /**
   * Destruye la ventana trabajo.
   */
  virtual ~VentanaTrabajo();

  /**
   * Comienza a correr la interfaz grafica.
   *
   * @param primeraVez Indica si es la primera vez que se crea una ventana.
   */
  void correr(bool primeraVez= false);

  /**
   * La lista de circuitos que se mostrara como respuesta a la conexion
   * con el servidor.
   *
   * @param lista La lista de circuitos.
   */
  void recibirListaCircuitos(std::list<DescripcionCircuito> lista);

  /**
   * Recibe un dibujo y lo agrega a la lista de dibujos que se reflejara
   * en el area dibujo.
   *
   * @param dibujo El dibujo agregar.
   */
  void agregarDibujo(Dibujo *dibujo);

  /**
   * Recibe un dibujo de tipo conexion y lo agrega a la lista de dibujos
   * que se reflejara en el area dibujo.
   *
   * @param dibujo El dibujo de tipo conexion a agregar.
   */
  void agregarDibujo(ConexionDibujo *dibujo);

  /**
   * Dibuja la tabla resultado de la simulacion en la solapa Tabla.
   *
   * @param listaTabla La lista que posee los resultados.
   * @param entradas La cantidad de entradas de la tabla.
   * @param salidas La cantidad de salidas de la tabla.
   * @param mensaje El mensaje a mostrar en caso de que se haya producido un error.
   */
  void recibirTablaSimulacion(std::list<uint32_t> listaTabla, int entradas, int salidas, const std::string& mensaje, const std::string& leyenda);

  /**
   * Dibuja el circuito remoto.
   *
   * @param nombreArchivo El nombre del archivo donde se encuentran los datos del circuito.
   * @param nombreCircuito El nombre del circuito a dibujar.
   */
  void recibirCircuitoRemoto(const std::string& nombreArchivo, const std::string& nombreCircuito);

  /**
   * Habilita la opcion de guardar en el menubar.
   */
  void habilitarGuardar();
};

#endif /*VENTANATRABAJO_H_*/
