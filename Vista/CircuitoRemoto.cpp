#include "CircuitoRemoto.h"

bool DibujoCircuitoRemoto::on_expose_event(GdkEventExpose* event) {
  //ventana de dibujo
  window= get_window();
  if(window) {
    Gdk::Region region= window->get_update_area();
    Gtk::Allocation allocation= get_allocation();
    width= allocation.get_width();
    height= allocation.get_height();

    Cairo::RefPtr<Cairo::Context> context= window->create_cairo_context();
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
      //deselecciono los objetos antes de dibujarlos
      (*it)->deseleccionar();
      (*it)->mostrarEtiqueta(context);
      (*it)->dibujar(context);
    }
  }
  set_size_request(getAncho(), getAlto());
  return false;
}
