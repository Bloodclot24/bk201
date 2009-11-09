#include "areaDibujo.h"

AreaDibujo::AreaDibujo()
{
}

AreaDibujo::~AreaDibujo()
{
}

bool AreaDibujo::on_expose_event(GdkEventExpose* event) {

  //ventana de dibujo
  Glib::RefPtr<Gdk::Window> window= get_window();
  if(window) {
    Gtk::Allocation allocation= get_allocation();
    const int width= allocation.get_width();
    const int height= allocation.get_height();

    Cairo::RefPtr<Cairo::Context> cr= window->create_cairo_context();
    cr->set_line_width(10.0);

    if(event) {
      cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
      cr->clip();
    }

    //dibujo el fondo blanco
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->paint();

    //relleno con puntitos
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->set_line_width(2.0);
    for(int w= 10; w<width; w+=20) {
      for(int h= 15; h<height; h+=20) {
        cr->move_to(w, h);
        cr->line_to(w, h + 1);
      }
    }
    cr->stroke();
  }

  return true;
}

