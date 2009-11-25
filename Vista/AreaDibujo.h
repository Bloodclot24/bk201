#ifndef AREADIBUJO_H_
#define AREADIBUJO_H_

class AreaDibujo;

#include <gtkmm/drawingarea.h>
#include <gtkmm/menu.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/stock.h>
#include <cairomm/context.h>
#include <list>
#include "VentanaTrabajo.h"
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

#include <iostream>

#define PASO 10

class VentanaTrabajo;
class AreaDibujo: public Gtk::DrawingArea {
  friend class VentanaTrabajo;
  friend class ConexionDibujo;

private:
  VentanaTrabajo                *ventanaTrabajo;
  Cairo::RefPtr<Cairo::Context> context;
  Glib::RefPtr<Gdk::Window>     window;
  std::list<Dibujo*>            dibujos;
  int                           width;
  int                           height;
  bool                          motion;
  bool                          can_motion;
  bool                          seleccion;
  Dibujo*                       seleccionado;

  void deseleccionar();

  //Conexion
  bool                          conexion;
  bool                          cargoVInicial;
  Dibujo*                       dibujoPin1;
  int                           nroPin1;
  Vertice                       vInicial;

  /*MenuPopup*/
  Gtk::Menu     *menuPopup;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> verCircuitoMenu;
  void loadMenuPopup();

  /*TARGETS*/
  std::list<Gtk::TargetEntry> listTargets;

  void buscarPosicion(int &x, int &y);
  void redibujar();

  //Circuito
  int xCircuito;
  int yCircuito;

  //Clicks
  bool eventoClickBtnIzq(int x, int y);
  void eventoDobleClickBtnIzq(int x, int y);

protected:
  virtual bool on_expose_event(GdkEventExpose* event);
  virtual void on_drop_drag_data_received(
          const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
          const Gtk::SelectionData& selection_data, guint info, guint time);
  virtual bool on_button_press_event(GdkEventButton* event);
  virtual bool on_motion_notify_event(GdkEventMotion* event);
  virtual bool on_button_release_event(GdkEventButton* event);

  void agregarComponente(Dibujo* dibujo);
  void dibujarCompuerta(std::string tipo, unsigned int xUp, unsigned int yUp);
  void dibujarIO(unsigned int xUp, unsigned int yUp);

  Dibujo* buscarDibujo(int x, int y);
     Dibujo* buscarDibujoCercano(Dibujo *origen, int x, int y);

public:
  AreaDibujo(VentanaTrabajo *ventanaTrabajo);
  virtual ~AreaDibujo();

  void dibujarConexion();
  void dibujarCircuito(int entradas, int salidas);

  void borrarSeleccion();
  void rotarSeleccion90Derecha();
  void rotarSeleccion90Izquierda();
  void verCircuito();
     
  void agregarDibujo(Dibujo *dibujo);
};

#endif /* AREADIBUJO_H_ */
