#include "AreaDibujo.h"

AreaDibujo::AreaDibujo(VentanaTrabajo *ventanaTrabajo): menuPopup() {

  listTargets.push_back(Gtk::TargetEntry("STRING"));
  listTargets.push_back(Gtk::TargetEntry("text/plain"));
  this->ventanaTrabajo = ventanaTrabajo;
  //Zona drop, conecto señal - Toolbar & Drawing area
  drag_dest_set(listTargets);
  signal_drag_data_received().connect(sigc::mem_fun(*this, &AreaDibujo::on_drop_drag_data_received));

  //agrego evento button press mask del mouse y conecto señal
  add_events(Gdk::ALL_EVENTS_MASK);
  signal_button_press_event().connect(sigc::mem_fun(*this, &AreaDibujo::on_button_press_event));
  signal_motion_notify_event().connect(sigc::mem_fun(*this, &AreaDibujo::on_motion_notify_event));
  signal_button_release_event().connect(sigc::mem_fun(*this, &AreaDibujo::on_button_release_event));
  seleccion= false;
  can_motion= false;
  motion= false;

  loadMenuPopup();

  //Conexion
  conexion= false;
  cargoVInicial= false;

  //seleccion multiple
  can_selected= false;
  selected= false;
  dibujarSelected= false;
}

AreaDibujo::~AreaDibujo() {

  //libero los componentes
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++)
    delete *it;
}

/***************************/
/*** MENUPOPUP ***/
/***************************/
void AreaDibujo::loadMenuPopup() {

  //crea las acciones del menu popup
  verRotar= Gtk::ActionGroup::create();
  verBorrar= Gtk::ActionGroup::create();
  verExaminar= Gtk::ActionGroup::create();
  verInvertir= Gtk::ActionGroup::create();

  //menu editar
  verRotar->add(Gtk::Action::create("MenuEditar", "Menu Editar"));
  verRotar->add(Gtk::Action::create("Rotar90D", Gtk::Stock::REDO,"Rotar 90"),
                          sigc::mem_fun(*this, &AreaDibujo::rotarSeleccion90Derecha));
  verRotar->add(Gtk::Action::create("Rotar90I", Gtk::Stock::UNDO,"Rotar 90"),
                          sigc::mem_fun(*this, &AreaDibujo::rotarSeleccion90Izquierda));
  verInvertir->add(Gtk::Action::create("InvertirV", Gtk::Stock::GO_UP,"Invertir Vertical"),
                   sigc::mem_fun(*this, &AreaDibujo::invertirVertical));
  verInvertir->add(Gtk::Action::create("InvertirH", Gtk::Stock::GO_DOWN,"Invertir Horizontal"),
                   sigc::mem_fun(*this, &AreaDibujo::invertirHorizontal));
  verBorrar->add(Gtk::Action::create("Borrar", Gtk::Stock::DELETE),
                            sigc::mem_fun(*this, &AreaDibujo::borrarSeleccion));
  verExaminar->add(Gtk::Action::create("Examinar", Gtk::Stock::FIND, "Examinar..."),
                            sigc::mem_fun(*this, &AreaDibujo::verCircuito));

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(verRotar);
  m_refUIManager->insert_action_group(verInvertir);
  m_refUIManager->insert_action_group(verExaminar);
  m_refUIManager->insert_action_group(verBorrar);

  //Etiquetas
  Glib::ustring ui_info =
    "<ui>"
    "  <popup name='PopupMenu'>"
    "    <menuitem action='Rotar90D'/>"
    "    <menuitem action='Rotar90I'/>"
    "    <menuitem action='InvertirV'/>"
    "    <menuitem action='InvertirH'/>"
    "    <menuitem action='Examinar'/>"
    "    <menuitem action='Borrar'/>"
    "  </popup>"
    "</ui>";
  m_refUIManager->add_ui_from_string(ui_info);

  //Obtenemos el menu
  menuPopup = dynamic_cast<Gtk::Menu*>(m_refUIManager->get_widget("/PopupMenu"));
}

void AreaDibujo::activarMenuBar() {
  if(dibujoSeleccionados.size() == 1) {
    ventanaTrabajo->setSensitiveEditar(true);
    if(dibujoSeleccionados[0]->getTipo().compare(CIRCUITO) != 0)
      ventanaTrabajo->m_examinar->set_sensitive(false);
  } else {
    ventanaTrabajo->setSensitiveEditar(false);
    ventanaTrabajo->m_borrar->set_sensitive(true);
  }
}

/***************************/
/*** REDEFINICIONES ***/
/***************************/
bool AreaDibujo::on_expose_event(GdkEventExpose* event) {
  //ventana de dibujo
  window= get_window();
  if(window) {
    Gdk::Region region= window->get_update_area();
    Gtk::Allocation allocation= get_allocation();
    width= allocation.get_width();
    height= allocation.get_height();

    context= window->create_cairo_context();
    context->begin_new_path();
    context->set_line_width(10.0);

    if(event) {
      context->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
      context->clip();
    }

    //dibujo el fondo blanco
    context->set_source_rgb(1.0, 1.0, 1.0);
    context->paint();

    //relleno con puntitos
    context->set_source_rgb(0.0, 0.0, 0.0);
    context->set_line_width(2.0);
    for(int w= PASO; w<width; w+=PASO) {
      for(int h= PASO; h<height; h+=PASO) {
        context->move_to(w, h);
        context->line_to(w, h + 0.5);
      }
    }
    context->stroke();

    dibujarSeleccionMultiple(context);

    std::list<Dibujo*>::iterator it;
    for(it= dibujos.begin(); it != dibujos.end(); it++) {
      //seteo matriz identidad
      context->set_identity_matrix();
      //roto respecto el centro de la imagen
      Vertice vCentro= (*it)->getVerticeCentro();
      context->translate(vCentro.x, vCentro.y);
      context->rotate_degrees((*it)->getAngulo());
      context->translate(-vCentro.x, -vCentro.y);
      (*it)->cargarNuevosPines();
    }

    //Dibujo los elementos
    dibujarComponentes(context, dibujos);
  }
  return false;
}

bool AreaDibujo::on_button_press_event(GdkEventButton* event) {
  //Evento click boton izquierdo
  if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    return eventoClickBtnIzq(event->x, event->y);

  //Evento doble click boton izquierdo
  else if(event->type == GDK_2BUTTON_PRESS && event->button == 1) {
    eventoDobleClickBtnIzq(event->x, event->y);
    return false;

  //Evento boton derecho
  } else if(event->type == GDK_BUTTON_PRESS && event->button == 3) {
    Dibujo *seleccionado= NULL;
    if(!dibujoSeleccionados.empty())
      seleccionado= dibujoSeleccionados[0];
    if(menuPopup && !dibujoSeleccionados.empty()) {
      verRotar->set_sensitive(true);
      verInvertir->set_sensitive(true);
      if(!seleccionado->getExaminar() || dibujoSeleccionados.size() != 1)
        verExaminar->set_sensitive(false);
      else
        verExaminar->set_sensitive(true);
      if(dibujoSeleccionados.size() != 1) {
        verRotar->set_sensitive(false);
        verInvertir->set_sensitive(false);
      }
      menuPopup->popup(event->button, event->time);
    }
    return true;

  } else
  return false;
}

bool AreaDibujo::on_motion_notify_event(GdkEventMotion* event) {

  if(can_motion && event->type == GDK_MOTION_NOTIFY) {
    motion= true;
    seleccion= false;
    selected= false;
    deseleccionar();
    int deltax, deltay;
    for(unsigned int i=0; i<dibujoSeleccionados.size(); i++) {
      Vertice vSupIzq= dibujoSeleccionados[i]->getVerticeSupIzq();
      deltax= event->x - vAnteriorMotion.x;
      deltay= event->y - vAnteriorMotion.y;
      dibujoSeleccionados[i]->setVerticesMotion(deltax, deltay);
    }
    vAnteriorMotion.x= event->x;
    vAnteriorMotion.y= event->y;
    redibujar();
    return true;

  } else if(can_selected && event->type == GDK_MOTION_NOTIFY) {
    anchoSelected= event->x - vInicialSelected.x;
    altoSelected= event->y - vInicialSelected.y;
    selected= true;
    dibujarSelected= true;
    redibujar();
    return true;
  } else
    return false;
}

bool AreaDibujo::on_button_release_event(GdkEventButton* event) {

  if(event->button == 1 && can_motion) {
    can_motion= false;

    if(motion) {
      motion= false;
      seleccion= true;
      Vertice v;
      for(unsigned int i=0; i<dibujoSeleccionados.size(); i++) {
        dibujoSeleccionados[i]->seleccionar();
        v= dibujoSeleccionados[i]->getVerticeSupIzq();
        buscarPosicion(v.x, v.y);
        dibujoSeleccionados[i]->setVerticeSupIzq(v);
        dibujarSelected= false;
        selected= true;
      }
      redibujar();
    }
    return true;

  } else if(event->button == 1 && can_selected) {
    can_selected= false;
    selected= true;
    dibujarSelected= false;
    vFinalSelected.x= event->x;
    vFinalSelected.y= event->y;
    cargarSeleccionMultiple();
    if(!dibujoSeleccionados.empty())
      activarMenuBar();
    redibujar();
    return true;

  } else
    return false;
}

/*** Clicks ***/
bool AreaDibujo::eventoClickBtnIzq(int x, int y) {
  if(conexion) {
    //obtengo el primer vertice de la conexion
    if(!cargoVInicial) {
      vInicial.x= x;
      vInicial.y= y;
      cargoVInicial= true;
    } else {
      conexion= false;
      //obtengo el segundo vertice de la conexion y creo la conexion
      Vertice vFinal;
      vFinal.x= x;
      vFinal.y= y;
      ConexionDibujo *conexion= new ConexionDibujo(vInicial.x, vInicial.y, vFinal, this);
      ventanaTrabajo->controladorVentana->crearComponente(conexion);
      agregarComponente(conexion);
      can_motion= false;
    }
    return true;

  } else {
    deseleccionar();
    if(!selected)
      dibujoSeleccionados.clear();
    Dibujo *dibujo=buscarDibujo(x, y);
    if(dibujo && dibujoSeleccionados.empty())
      dibujoSeleccionados.push_back(dibujo);
    if(!dibujo)
      dibujoSeleccionados.clear();

    if(dibujoSeleccionados.empty()) {
      ventanaTrabajo->setSensitiveEditar(false);
      //Preparo la seleccion
      vInicialSelected.x= x;
      vInicialSelected.y= y;
      anchoSelected= 0;
      altoSelected= 0;
      can_selected= true;
      selected= false;
      can_motion= false;
      seleccion= false;
    } else {
      if(dibujoSeleccionados.size() == 1) {
        can_selected= false;
        selected= false;
      }
      seleccion= true;
      can_motion= true;
      vAnteriorMotion.x= x;
      vAnteriorMotion.y= y;
      activarMenuBar();
    }

    redibujar();
    return true;
  }
  return false;
}

void AreaDibujo::eventoDobleClickBtnIzq(int x, int y) {
  //busco el elemento sobre el que se hizo doble click y
  //muestro sus propiedades segun el tipo de componente
  Dibujo *seleccionado= NULL;
  if(!dibujoSeleccionados.empty())
    seleccionado= dibujoSeleccionados[0];
  if(seleccionado) {
    std::string tipo= seleccionado->getTipo();
    can_motion= false;

    if((tipo.compare(COMPUERTA)) == 0)
      ventanaTrabajo->prepararVentanaCompuerta(seleccionado);
    else if((tipo.compare(IO)) == 0)
      ventanaTrabajo->prepararVentanaIO(seleccionado);
    else if((tipo.compare(CIRCUITO)) == 0)
      ventanaTrabajo->prepararVentanaCircuito(seleccionado);
  }
}

/***************************/
/*** DIBUJOS ***/
/***************************/
void AreaDibujo::dibujarComponentes(const Cairo::RefPtr<Cairo::Context>& context, std::list<Dibujo*> dibujos) {
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++) {
    //seteo matriz identidad
    context->set_identity_matrix();
    //roto respecto el centro de la imagen
    Vertice vCentro= (*it)->getVerticeCentro();
    context->translate(vCentro.x, vCentro.y);
    context->rotate_degrees((*it)->getAngulo());
    context->translate(-vCentro.x, -vCentro.y);
    (*it)->dibujar(context);
  }
}

void AreaDibujo::dibujarCompuerta(std::string tipo, int xUp, int yUp) {
  Compuerta *compuerta;
  if((tipo.compare(AND)) == 0)
    compuerta= new CompuertaAnd(xUp, yUp);
  else if((tipo.compare(OR)) == 0)
    compuerta= new CompuertaOr(xUp, yUp);
  else if((tipo.compare(NOT)) == 0)
    compuerta= new CompuertaNot(xUp, yUp);
  else if((tipo.compare(XOR)) == 0)
    compuerta= new CompuertaXor(xUp, yUp);
  else if((tipo.compare(BUFFER)) == 0)
    compuerta= new CompuertaBuffer(xUp, yUp);
  ventanaTrabajo->controladorVentana->crearComponente(compuerta, tipo);
  agregarComponente(compuerta);
}

void AreaDibujo::dibujarConexion() {
  deseleccionar();
  conexion= true;
  cargoVInicial= false;
  redibujar();
}

void AreaDibujo::dibujarIO(int xUp, int yUp) {
  EntradaSalida *entradaSalida= new EntradaSalida(xUp, yUp);
  ventanaTrabajo->controladorVentana->crearComponente(entradaSalida);
  agregarComponente(entradaSalida);
}

void AreaDibujo::dibujarCircuito(int entradas, int salidas) {
  CircuitoDibujo *circuito= new CircuitoDibujo(xCircuito, yCircuito, entradas, salidas);
  std::string servidor, puerto, nombre;
  ventanaTrabajo->obtenerDatosCircuito(servidor, puerto, nombre);
  circuito->agregarDatos(servidor, puerto, nombre);
  ventanaTrabajo->controladorVentana->crearComponente(circuito);
  agregarComponente(circuito);
}

void calcularPosicion(int &x, int max, int min) {
  int mod= x % 10;
  if(mod != 0)
    x= x-mod;
  if(x < min)
    x= min;
  else if(x+41 > max)
    x= max - 40 - (max%10);
}

void AreaDibujo::buscarPosicion(int &x, int &y) {
  //Modifico el punto para caiga justo en un punto de la grilla
  calcularPosicion(x, width, PASO);
  calcularPosicion(y, height, PASO);
}

void AreaDibujo::on_drop_drag_data_received(
        const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
        const Gtk::SelectionData& selection_data, guint info, guint time) {
  //Recibe la senial de drop y le pide a la zona de drag los datos
  //del componente a dibujar.
  ventanaTrabajo->setSensitiveEditar(true);

  const int length = selection_data.get_length();
  if((length >= 0) && (selection_data.get_format() == 8)) {

    std::string componente= selection_data.get_data_as_string();
    buscarPosicion(x,y);

    if((componente.compare(IO)) == 0)
      dibujarIO(x,y);
    else if((componente.compare(CIRCUITO)) == 0) {
      xCircuito= x;
      yCircuito= y;
    } else
      dibujarCompuerta(componente,x,y);
  }

  context->drag_finish(false, false, time);
}

void AreaDibujo::borrarSeleccion() {
  if(!dibujoSeleccionados.empty() && !motion) {
    seleccion= false;
    for(unsigned int i=0; i<dibujoSeleccionados.size(); i++) {
      ventanaTrabajo->controladorVentana->eliminarComponente(dibujoSeleccionados[i]);
      dibujos.remove(dibujoSeleccionados[i]);
    }
    if(dibujos.empty())
      ventanaTrabajo->setSensitiveEditar(false);
    selected= false;
    redibujar();
  }
}

void AreaDibujo::rotarSeleccion90Derecha() {
  Dibujo *seleccionado= dibujoSeleccionados[0];
  if(seleccion && !motion) {
    seleccionado->setAngulo(90);
    redibujar();
  }
}

void AreaDibujo::rotarSeleccion90Izquierda() {
  Dibujo *seleccionado= dibujoSeleccionados[0];
  if(seleccion && !motion) {
    seleccionado->setAngulo(-90);
    redibujar();
  }
}

int tipoInversion(int angulo) {
  if((angulo/90)%2 ==0)
    return 0;
  else
    return 90;
}

void AreaDibujo::invertirVertical() {
  Dibujo *seleccionado= dibujoSeleccionados[0];
  if(seleccion && !motion) {
    if(tipoInversion(seleccionado->getAngulo()) == 90) {
      seleccionado->setAngulo(180);
      redibujar();
    }
  }
}

void AreaDibujo::invertirHorizontal() {
  Dibujo *seleccionado= dibujoSeleccionados[0];
  if(seleccion && !motion) {
    if(tipoInversion(seleccionado->getAngulo()) == 0) {
      seleccionado->setAngulo(180);
      redibujar();
    }
  }
}

void AreaDibujo::verCircuito() {
  if(seleccion && !motion) {
    CircuitoDibujo* dibujoCircuitoRemoto = dynamic_cast<CircuitoDibujo*> (this->dibujoSeleccionados[0]);
    ventanaTrabajo->controladorVentana->obtenerCircuitoServidor(dibujoCircuitoRemoto->getNombre(),dibujoCircuitoRemoto->getServidor(),atoi(dibujoCircuitoRemoto->getPuerto().c_str()));
  }
}

void AreaDibujo::dibujarSeleccionMultiple(const Cairo::RefPtr<Cairo::Context>& context) {
  if(dibujarSelected) {
    context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
    context->rectangle(vInicialSelected.x, vInicialSelected.y, anchoSelected, altoSelected);
    context->set_source_rgba(0, 0, 1, 0.2);
    context->fill_preserve();
    context->set_source_rgba (0, 0, 0, 0.5);
    context->stroke();
  }
}

void AreaDibujo::buscarInclusion(Dibujo *dibujo, Vertice vertice, Vertice vMenor, bool &marcado) {
  if((vertice.x >= vMenor.x && vertice.x <= vMenor.x+abs(anchoSelected)) && (vertice.y >= vMenor.y && vertice.y <= vMenor.y+abs(altoSelected)) && !marcado) {
    dibujoSeleccionados.push_back(dibujo);
    dibujo->seleccionar();
    marcado= true;
  }
}

void AreaDibujo::cargarSeleccionMultiple() {
  //Recorre la lista de dibujos y carga aquellos dibujos que caen
  //dentro de la seleccion realizada
  Vertice vMenor;
  if(vInicialSelected.x <= vFinalSelected.x)
    vMenor.x= vInicialSelected.x;
  else
    vMenor.x= vFinalSelected.x;
  if(vInicialSelected.y <= vFinalSelected.y)
    vMenor.y= vInicialSelected.y;
  else
    vMenor.y= vFinalSelected.y;

  bool marcado= false;
  dibujoSeleccionados.clear();
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++) {
    Vertice vertice= (*it)->getVerticeSupIzq();
    buscarInclusion(*it, vertice, vMenor, marcado);
    vertice.x= vertice.x + (*it)->getAncho();
    buscarInclusion(*it, vertice, vMenor, marcado);
    vertice.y= vertice.y + (*it)->getAlto();
    buscarInclusion(*it, vertice, vMenor, marcado);
    vertice.x= vertice.x + (*it)->getAncho();
    buscarInclusion(*it, vertice, vMenor, marcado);
    marcado= false;
  }
}
