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
    cr->rectangle(0, 0, width, height);
    cr->fill();
  }

  return true;
}

