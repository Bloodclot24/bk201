#include "AreaDibujo.h"

AreaDibujo::AreaDibujo() {

  //Zona drop, conecto señal - Toolbar
  listTargets.push_back(Gtk::TargetEntry("STRING"));
  listTargets.push_back(Gtk::TargetEntry("text/plain"));
  drag_dest_set(listTargets);
  signal_drag_data_received().connect(sigc::mem_fun(*this, &AreaDibujo::on_drop_drag_data_received));

  //agrego evento button press mask del mouse y conecto señal
  add_events(Gdk::BUTTON_PRESS_MASK);
  signal_button_press_event().connect(sigc::mem_fun(*this, &AreaDibujo::on_button_press_event));
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
    for(int w= PASO; w<(width-PASO); w+=PASO) {
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
  redibujar();
}

void AreaDibujo::dibujarOr(unsigned int xUp, unsigned int yUp) {

  CompuertaOr *compuertaOr= new CompuertaOr(xUp, yUp);
  dibujos.push_back(compuertaOr);
  redibujar();
}

void AreaDibujo::dibujarNot(unsigned int xUp, unsigned int yUp) {

  CompuertaNot *compuertaNot= new CompuertaNot(xUp, yUp);
  dibujos.push_back(compuertaNot);
  redibujar();
}

void AreaDibujo::dibujarXor(unsigned int xUp, unsigned int yUp) {

  CompuertaXor *compuertaXor= new CompuertaXor(xUp, yUp);
  dibujos.push_back(compuertaXor);
  redibujar();
}

void AreaDibujo::dibujarBuffer(unsigned int xUp, unsigned int yUp) {

  CompuertaBuffer *compuertaBuffer= new CompuertaBuffer(xUp, yUp);
  dibujos.push_back(compuertaBuffer);
  redibujar();
}

//TODO: Por ahora trata que no se dibuje fuera del area de dibujo
void AreaDibujo::buscarPosicion(int &x, int &y) {

  //Modifico el punto para caiga justo en un punto de la grilla
  int mod= x % 10;
  if(mod != 0)
    x= x-mod;
  if(x < PASO)
    x= PASO;
  else if(x+60 > width)
    x= width - 60;

  mod= y % 10;
  if(mod != 0)
    y= y-mod;
  if(y < PASO)
    y= PASO;
  else if(y+50 > height)
    y= height - 50;
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

bool AreaDibujo::on_button_press_event(GdkEventButton* event) {

  std::cout << "tocaron boton del mouse" << std::endl;
  std::cout << "x: " << event->x << std::endl;
  std::cout << "y: " << event->y << std::endl;

  if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    std::cout << "tocaron boton izquierdo del mouse" << std::endl;
  else if(event->type == GDK_BUTTON_PRESS && event->button == 3)
    std::cout << "tocaron boton derecho del mouse" << std::endl;
  return true;
}
