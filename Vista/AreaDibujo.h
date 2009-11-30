#ifndef AREADIBUJO_H_
#define AREADIBUJO_H_

class AreaDibujo;

#include <gtkmm/menu.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/stock.h>
#include <cairomm/context.h>
#include <list>
#include <vector>
#include "VentanaTrabajo.h"
#include "AreaDibujoGenerica.h"
#include "Dibujos/Dibujo.h"
#include "Dibujos/Constantes.h"
#include "Dibujos/Compuerta.h"
#include "Dibujos/CompuertaAnd.h"
#include "Dibujos/CompuertaOr.h"
#include "Dibujos/CompuertaNot.h"
#include "Dibujos/CompuertaXor.h"
#include "Dibujos/CompuertaBuffer.h"
#include "Dibujos/Conexion.h"
#include "Dibujos/EntradaSalida.h"
#include "Dibujos/Circuito.h"
#include "Impresion/Impresora.h"

#include <iostream>

#define PASO 10
/**
 * El area de dibujo es la grilla de la ventana donde se dibujan distintos componentes,
 * que permiten formar circuitos logicos.
 */
class AreaDibujo: public AreaDibujoGenerica {
  friend class VentanaTrabajo;
  friend class ConexionDibujo;
  friend class Impresora;

private:
  VentanaTrabajo                *ventanaTrabajo;
  Cairo::RefPtr<Cairo::Context> context;
  int                           width;
  int                           height;
  Vertice                       vAnteriorMotion;
  bool                          motion;
  bool                          can_motion;

  //Target
  std::list<Gtk::TargetEntry> listTargets;

  //Conexion
  bool                          conexion;
  bool                          cargoVInicial;
  Vertice                       vInicial;

  //MenuPopup
  Gtk::Menu                             *menuPopup;
  Glib::RefPtr<Gtk::UIManager>          m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup>        verRotar;
  Glib::RefPtr<Gtk::ActionGroup>        verInvertir;
  Glib::RefPtr<Gtk::ActionGroup>        verBorrar;
  Glib::RefPtr<Gtk::ActionGroup>        verExaminar;
  void loadMenuPopup();
  void activarMenuBar();

  //Circuito
  int xCircuito;
  int yCircuito;

  //Ventana Remoto
  bool esperandoCircuitoRemoto();

  //Clicks
  bool eventoClickBtnIzq(int x, int y);
  void eventoDobleClickBtnIzq(int x, int y);

  //Seleccion Multiple
  bool                          can_selected;
  bool                          dibujarSelected;
  Vertice                       vInicialSelected;
  Vertice                       vFinalSelected;
  int                           anchoSelected;
  int                           altoSelected;
  void dibujarSeleccionMultiple(const Cairo::RefPtr<Cairo::Context>& context);
  void buscarInclusion(Dibujo *dibujo, Vertice vertice, Vertice vMenor, bool &marcado);
  void cargarSeleccionMultiple();

  //Funciones para el dibujos de los distintos componentes
  void dibujarConexion();
  void dibujarCircuito(int entradas, int salidas);
  void dibujarCompuerta(std::string tipo, int xUp, int yUp);
  void dibujarIO(int xUp, int yUp);
  void dibujarComponentes(const Cairo::RefPtr<Cairo::Context>& context, std::list<Dibujo*> dibujos);

  //Acciones que se le pueden aplicar a los componentes
  void rotarSeleccion90Derecha();
  void rotarSeleccion90Izquierda();
  void invertirVertical();
  void invertirHorizontal();
  void borrarSeleccion();
  void verCircuito();

  void buscarPosicion(int &x, int &y);

protected:
  virtual bool on_expose_event(GdkEventExpose* event);
  virtual void on_drop_drag_data_received(
          const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
          const Gtk::SelectionData& selection_data, guint info, guint time);
  virtual bool on_button_press_event(GdkEventButton* event);
  virtual bool on_motion_notify_event(GdkEventMotion* event);
  virtual bool on_button_release_event(GdkEventButton* event);

public:
  /**
    * Crea un area de dibujo nueva.
    *
    * @param ventanaTrabajo La ventana trabajo a la que pertenece.
    */
    AreaDibujo(VentanaTrabajo *ventanaTrabajo);

  /**
    * Destruye el area de dibujo.
    */
    virtual ~AreaDibujo();
};

#endif /* AREADIBUJO_H_ */
