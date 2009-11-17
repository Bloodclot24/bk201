#include "AreaDibujo.h"

AreaDibujo::AreaDibujo(): menuPopup() {

  listTargets.push_back(Gtk::TargetEntry("STRING"));
  listTargets.push_back(Gtk::TargetEntry("text/plain"));

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

  /*Menu popup*/
  //crea las acciones del menu popup
  m_refActionGroup = Gtk::ActionGroup::create();

  //menu editar
  m_refActionGroup->add(Gtk::Action::create("MenuEditar", "Menu Editar"));
  m_refActionGroup->add(Gtk::Action::create("Rotar90D", Gtk::Stock::REDO,"Rotar 90"),
                          sigc::mem_fun(*this, &AreaDibujo::rotarSeleccion90Derecha));
  m_refActionGroup->add(Gtk::Action::create("Rotar90I", Gtk::Stock::UNDO,"Rotar 90"),
                          sigc::mem_fun(*this, &AreaDibujo::rotarSeleccion90Izquierda));
  m_refActionGroup->add(Gtk::Action::create("Borrar", Gtk::Stock::DELETE),
                          sigc::mem_fun(*this, &AreaDibujo::borrarSeleccion));

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  //Etiquetas
  Glib::ustring ui_info =
    "<ui>"
    "  <popup name='PopupMenu'>"
    "    <menuitem action='Rotar90D'/>"
    "    <menuitem action='Rotar90I'/>"
    "    <menuitem action='Borrar'/>"
    "  </popup>"
    "</ui>";
  m_refUIManager->add_ui_from_string(ui_info);

  //Obtenemos el menu
  menuPopup = dynamic_cast<Gtk::Menu*>(m_refUIManager->get_widget("/PopupMenu"));
}

AreaDibujo::~AreaDibujo() {

  //libero los componentes
  std::list<Dibujo*>::iterator it;
  for(it= dibujos.begin(); it != dibujos.end(); it++)
    delete *it;
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
        context->line_to(w, h + 1);
      }
    }
    context->stroke();

    //Dibujo los elementos
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

    //Si hay algun elemento seleccionado
    if(seleccion)
      dibujarSeleccion(context);
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

void AreaDibujo::dibujarAnd(unsigned int xUp, unsigned int yUp) {

  CompuertaAnd *compuertaAnd= new CompuertaAnd(xUp, yUp);
  dibujos.push_back(compuertaAnd);
  seleccionado= compuertaAnd;
  seleccion= true;
  redibujar();
}

void AreaDibujo::dibujarOr(unsigned int xUp, unsigned int yUp) {

  CompuertaOr *compuertaOr= new CompuertaOr(xUp, yUp);
  dibujos.push_back(compuertaOr);
  seleccionado= compuertaOr;
  seleccion= true;
  redibujar();
}

void AreaDibujo::dibujarNot(unsigned int xUp, unsigned int yUp) {

  CompuertaNot *compuertaNot= new CompuertaNot(xUp, yUp);
  dibujos.push_back(compuertaNot);
  seleccionado= compuertaNot;
  seleccion= true;
  redibujar();
}

void AreaDibujo::dibujarXor(unsigned int xUp, unsigned int yUp) {

  CompuertaXor *compuertaXor= new CompuertaXor(xUp, yUp);
  dibujos.push_back(compuertaXor);
  seleccionado= compuertaXor;
  seleccion= true;
  redibujar();
}

void AreaDibujo::dibujarBuffer(unsigned int xUp, unsigned int yUp) {

  CompuertaBuffer *compuertaBuffer= new CompuertaBuffer(xUp, yUp);
  dibujos.push_back(compuertaBuffer);
  seleccionado= compuertaBuffer;
  seleccion= true;
  redibujar();
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

    if((componente.compare(AND)) == 0)
      dibujarAnd(x,y);
    else if((componente.compare(OR)) == 0)
      dibujarOr(x,y);
    else if((componente.compare(NOT)) == 0)
      dibujarNot(x,y);
    else if((componente.compare(XOR)) == 0)
      dibujarXor(x,y);
    else if((componente.compare(BUFFER)) == 0)
      dibujarBuffer(x,y);
  }

  context->drag_finish(false, false, time);
}

Dibujo* AreaDibujo::buscarDibujo(int x, int y) {

  std::list<Dibujo*>::iterator it;
  bool encontrado= false;
  for(it= dibujos.begin(); it != dibujos.end() && !encontrado; it++) {
    Vertice vSupIzq= (*it)->getVerticeSupIzq();
    if((x >= vSupIzq.x) && ((x <= vSupIzq.x+40)) && (y >= vSupIzq.y) && (y <= (vSupIzq.y+40))) {
      encontrado= true;
      break;
    }
  }

  if(!encontrado)
    return NULL;

  return *it;
}

bool AreaDibujo::on_button_press_event(GdkEventButton* event) {

  if(event->type == GDK_BUTTON_PRESS && event->button == 1) {
    seleccionado= buscarDibujo(event->x, event->y);
    if(!seleccionado) {
      can_motion= false;
      seleccion= false;
    } else {
      seleccion= true;
      can_motion= true;
    }

    redibujar();
    return true;

  } else if(event->type == GDK_BUTTON_PRESS && event->button == 3) {
    if(menuPopup && seleccion)
      menuPopup->popup(event->button, event->time);
    return true;
  }

  return false;
}

void AreaDibujo::dibujarSeleccion(Cairo::RefPtr<Cairo::Context> context) {

  if(seleccionado) {
    //seteo matriz identidad
    context->set_identity_matrix();
    //roto respecto el centro de la imagen
    Vertice vCentro= seleccionado->getVerticeCentro();
    context->translate(vCentro.x, vCentro.y);
    context->rotate_degrees(seleccionado->getAngulo());
    context->translate(-vCentro.x, -vCentro.y);
    Vertice vSupIzq= seleccionado->getVerticeSupIzq();
    context->set_source_rgba(0.0, 0.0, 1.0, 0.3);
    context->rectangle(vSupIzq.x-2, vSupIzq.y-2, 44, 44);
    context->fill();
    context->stroke();
  }
}

void AreaDibujo::borrarSeleccion() {

  if(seleccion && !motion) {
    dibujos.remove(seleccionado);
    delete seleccionado;
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

bool AreaDibujo::on_motion_notify_event(GdkEventMotion* event) {

  if(can_motion && event->type == GDK_MOTION_NOTIFY) {
    motion= true;
    seleccion= false;
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
      redibujar();
    }
    return true;

  } else
    return false;
}
