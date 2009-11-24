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
}

AreaDibujo::~AreaDibujo() {

  //libero los componentes
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++)
    delete *it;
}

void AreaDibujo::loadMenuPopup() {

  //crea las acciones del menu popup
  m_refActionGroup= Gtk::ActionGroup::create();
  verCircuitoMenu= Gtk::ActionGroup::create();

  //menu editar
  m_refActionGroup->add(Gtk::Action::create("MenuEditar", "Menu Editar"));
  m_refActionGroup->add(Gtk::Action::create("Rotar90D", Gtk::Stock::REDO,"Rotar 90"),
                          sigc::mem_fun(*this, &AreaDibujo::rotarSeleccion90Derecha));
  m_refActionGroup->add(Gtk::Action::create("Rotar90I", Gtk::Stock::UNDO,"Rotar 90"),
                          sigc::mem_fun(*this, &AreaDibujo::rotarSeleccion90Izquierda));
  m_refActionGroup->add(Gtk::Action::create("Borrar", Gtk::Stock::DELETE),
                            sigc::mem_fun(*this, &AreaDibujo::borrarSeleccion));
  verCircuitoMenu->add(Gtk::Action::create("Examinar", Gtk::Stock::FIND, "Examinar..."),
                            sigc::mem_fun(*this, &AreaDibujo::verCircuito));

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);
  m_refUIManager->insert_action_group(verCircuitoMenu);

  //Etiquetas
  Glib::ustring ui_info =
    "<ui>"
    "  <popup name='PopupMenu'>"
    "    <menuitem action='Rotar90D'/>"
    "    <menuitem action='Rotar90I'/>"
    "    <menuitem action='Examinar'/>"
    "    <menuitem action='Borrar'/>"
    "  </popup>"
    "</ui>";
  m_refUIManager->add_ui_from_string(ui_info);

  //Obtenemos el menu
  menuPopup = dynamic_cast<Gtk::Menu*>(m_refUIManager->get_widget("/PopupMenu"));
}

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

    std::list<Dibujo*>::iterator it;
    for(it= dibujos.begin(); it != dibujos.end(); it++) {
      //seteo matriz identidad
      context->set_identity_matrix();
      //roto respecto el centro de la imagen
      Vertice vCentro= (*it)->getVerticeCentro();
      context->translate(vCentro.x, vCentro.y);
      context->rotate_degrees((*it)->getAngulo());
      context->translate(-vCentro.x, -vCentro.y);
      (*it)->cargarNuevosPines(context);
    }

    //Dibujo los elementos
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
  
  return false;
}

void AreaDibujo::redibujar() {

  //fuerzo al redibujado
  if(window) {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                     get_allocation().get_height());
    window->invalidate_rect(r, false);
  }
}

void AreaDibujo::deseleccionar() {

  //libero los componentes
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++)
    (*it)->deseleccionar();
}

void AreaDibujo::agregarComponente(Dibujo* dibujo) {

  deseleccionar();
  dibujo->seleccionar();
  dibujos.push_back(dibujo);
  seleccionado= dibujo;
  seleccion= true;
  redibujar();
}

void AreaDibujo::dibujarCompuerta(std::string tipo, unsigned int xUp, unsigned int yUp) {

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
  redibujar();
}

void AreaDibujo::dibujarIO(unsigned int xUp, unsigned int yUp) {

  EntradaSalida *entradaSalida= new EntradaSalida(xUp, yUp);
  agregarComponente(entradaSalida);
}

void AreaDibujo::dibujarCircuito(int entradas, int salidas) {

  CircuitoDibujo *circuito= new CircuitoDibujo(xCircuito, yCircuito, entradas, salidas);
  agregarComponente(circuito);
}

//TODO: Por ahora trata que no se dibuje fuera del area de dibujo
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

Dibujo* AreaDibujo::buscarDibujo(int x, int y) {

  std::list<Dibujo*>::iterator it;
  bool encontrado= false;

  for(it= dibujos.begin(); it != dibujos.end() && !encontrado; it++) {
    encontrado= (*it)->setSeleccionado(x,y);
    if(encontrado)
      break;
  }
  if(!encontrado)
    return NULL;
  return *it;
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
    if(menuPopup && seleccion) {
      if(!seleccionado->getExaminar())
        verCircuitoMenu->set_sensitive(false);
      else
        verCircuitoMenu->set_sensitive(true);
      menuPopup->popup(event->button, event->time);
    }
    return true;
  } else
  return false;
}

void AreaDibujo::borrarSeleccion() {

  if(seleccion && !motion) {
    ventanaTrabajo->controladorVentana->eliminarComponente(seleccionado);
    dibujos.remove(seleccionado);
    seleccion= false;
    redibujar();
  }
}

void AreaDibujo::rotarSeleccion90Derecha() {

  if(seleccion && !motion) {
    seleccionado->setAngulo(90);
    redibujar();
  }
}

void AreaDibujo::rotarSeleccion90Izquierda() {

  if(seleccion && !motion) {
    seleccionado->setAngulo(-90);
    redibujar();
  }
}

void AreaDibujo::verCircuito() {

  if(seleccion && !motion) {
    Gtk::Dialog *dialog_remoto;
    ventanaTrabajo->refXml->get_widget("dialog_remoto", dialog_remoto);
    //Remoto
    Gtk::VBox* vbox_remoto;
    ventanaTrabajo->refXml->get_widget("vbox_remoto", vbox_remoto);
    vbox_remoto->add(*(ventanaTrabajo->circuitoRemoto));
    if(dialog_remoto) {
      dialog_remoto->run();
      dialog_remoto->hide();
    }
  }
}

bool AreaDibujo::on_motion_notify_event(GdkEventMotion* event) {

  if(can_motion && event->type == GDK_MOTION_NOTIFY) {
    motion= true;
    seleccion= false;
    seleccionado->deseleccionar();
    Vertice vSupIzq;
    vSupIzq.x= event->x;
    vSupIzq.y= event->y;
    buscarPosicion(vSupIzq.x, vSupIzq.y);
    seleccionado->setVerticeSupIzq(vSupIzq);
    redibujar();
    return true;
  } else
    return false;
}

bool AreaDibujo::on_button_release_event(GdkEventButton* event) {

  if(event->button == 1) {
    can_motion= false;

    if(motion) {
      motion= false;
      seleccion= true;
      seleccionado->seleccionar();
      redibujar();
    }
    return true;

  } else
    return false;
}

//Clicks
bool AreaDibujo::eventoClickBtnIzq(int x, int y) {

  if(conexion) {
     //obtengo el dibujo sobre el que se hizo click
    Dibujo *dibujo= buscarDibujo(x, y);

    //obtengo el pin mas cercano
    Vertice v;
    int nroPin;
    if(dibujo) {
      nroPin= dibujo->obtenerPinMasCercano(x,y);
      if(nroPin != -1)
      v= dibujo->obtenerPin(nroPin);
    } else {
      buscarPosicion(x, y);
      v.x= x;
      v.y= y;
    }

    if(nroPin == -1) {
      dibujo= NULL;
      buscarPosicion(x, y);
      v.x= x;
      v.y= y;
    }

    if(!cargoVInicial) {
       cargoVInicial= true;
       vInicial= v;
       dibujoPin1= dibujo;
       nroPin1= nroPin;
    } else {
      conexion= false;
      ConexionDibujo *conexion= new ConexionDibujo(vInicial.x, vInicial.y, dibujoPin1, nroPin1, this);
      ventanaTrabajo->controladorVentana->crearComponente(conexion);
      conexion->setVerticeFinal(v, dibujo, nroPin);
      agregarComponente(conexion);
      can_motion= false;
      cargoVInicial= false;
    }
    return true;

  } else {

    deseleccionar();
    seleccionado= buscarDibujo(x, y);

    if(!seleccionado) {
      can_motion= false;
      seleccion= false;
    } else {
      seleccion= true;
      can_motion= true;
    }

    redibujar();
    return true;
  }
  return false;
}

void AreaDibujo::eventoDobleClickBtnIzq(int x, int y) {

  //busco el elemento sobre el que se hizo doble click
  //y muestro sus propiedades
  seleccionado= buscarDibujo(x, y);
  if(seleccionado) {
    can_motion= false;
    std::string label= seleccionado->getLabel();
    std::string tiempo= seleccionado->getTiempoT();
    Gtk::Entry *entry;
    ventanaTrabajo->refXml->get_widget("entry_label_prop", entry);
    entry->set_text(label);
    ventanaTrabajo->refXml->get_widget("entry_tiempo_prop", entry);
    entry->set_text(tiempo);
    //muestro el dialogo de propiedades
    ventanaTrabajo->dialog_propiedades->show();
  }
}

void AreaDibujo::agregarDibujo(Dibujo *dibujo) {

  agregarComponente(dibujo);
}
