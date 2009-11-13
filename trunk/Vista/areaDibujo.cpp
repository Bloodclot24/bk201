#include "areaDibujo.h"

AreaDibujo::AreaDibujo() {

  listTargets.push_back(Gtk::TargetEntry("STRING"));
  listTargets.push_back(Gtk::TargetEntry("text/plain"));

  //Zona drop, conecto señal
  drag_dest_set(listTargets);
  signal_drag_data_received().connect(sigc::mem_fun(*this, &AreaDibujo::on_drop_drag_data_received));

  //agrego evento button press mask del mouse y conecto señal
  add_events(Gdk::BUTTON_PRESS_MASK);
  signal_button_press_event().connect(sigc::mem_fun(*this, &AreaDibujo::on_button_press_event));

  mostrarAnd= false;

}

AreaDibujo::~AreaDibujo()
{
}

bool AreaDibujo::on_expose_event(GdkEventExpose* event) {

  //ventana de dibujo
  window= get_window();
  if(window) {
    region= window->get_update_area();
    Gtk::Allocation allocation= get_allocation();
    const int width= allocation.get_width();
    const int height= allocation.get_height();

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
    for(int w= 10; w<width; w+=10) {
      for(int h= 10; h<height; h+=10) {
        context->move_to(w, h);
        context->line_to(w, h + 1);
      }
    }
    context->stroke();



    //+++++++++++++++compuertasb
//    dibujarAnd(50, 30);
    if(mostrarAnd) {
      And();
    }

    dibujarOr(150, 30);
    dibujarBuffer(250, 30);
    dibujarNot(350, 30);
    dibujarXor(450, 30);
  }

  return false;
}

bool AreaDibujo::on_my_button_press_event(GdkEventButton* event) {

  std::cout << "clicked" << std::endl;

  return true;
}

void AreaDibujo::dibujarAnd(unsigned int xUp, unsigned int yUp) {

  this->xUp= xUp;
  this->yUp= yUp;
  mostrarAnd= true;

  // force our program to redraw the entire clock.
  Glib::RefPtr<Gdk::Window> win = get_window();
  if(window) {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),
              get_allocation().get_height());
      win->invalidate_rect(r, false);
  }
}

void AreaDibujo::And() {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp, yUp);
  context->line_to(xUp, yUp+40);
  context->move_to(xUp, yUp);
  context->curve_to(xUp+40, yUp+5, xUp+40, yUp+35, xUp, yUp+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp, yUp+10);
  context->line_to(xUp-10, yUp+10);
  context->move_to(xUp, yUp+30);
  context->line_to(xUp-10, yUp+30);
  //salida
  context->move_to(xUp+30, yUp+20);
  context->line_to(xUp+40, yUp+20);
  context->stroke();

  mostrarAnd= false;
}

void AreaDibujo::dibujarOr(unsigned int xUp, unsigned int yUp) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp, yUp);
  context->curve_to(xUp+10, yUp+5, xUp+10, yUp+35, xUp, yUp+40);
  context->move_to(xUp, yUp);
  context->curve_to(xUp+40, yUp+5, xUp+40, yUp+35, xUp, yUp+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp+5, yUp+10);
  context->line_to(xUp-10, yUp+10);
  context->move_to(xUp+5, yUp+30);
  context->line_to(xUp-10, yUp+30);
  //salida
  context->move_to(xUp+30, yUp+20);
  context->line_to(xUp+40, yUp+20);

  context->stroke();
}

void AreaDibujo::dibujarNot(unsigned int xUp, unsigned int yUp) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp, yUp);
  context->line_to(xUp, yUp+40);
  context->move_to(xUp, yUp);
  context->line_to(xUp+22, yUp+20);
  context->move_to(xUp+22, yUp+20);
  context->line_to(xUp, yUp+40);
  context->move_to(xUp+26, yUp+20);
  context->begin_new_sub_path();
  context->arc(xUp+26, yUp+20, 3.0, 0.0, 2*M_PI);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp, yUp+10);
  context->line_to(xUp-10, yUp+10);
  context->move_to(xUp, yUp+30);
  context->line_to(xUp-10, yUp+30);
  //salida
  context->move_to(xUp+30, yUp+20);
  context->line_to(xUp+40, yUp+20);

  context->stroke();
}

void AreaDibujo::dibujarXor(unsigned int xUp, unsigned int yUp) {
  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp, yUp);
  context->curve_to(xUp+10, yUp+5, xUp+10, yUp+35, xUp, yUp+40);
  context->move_to(xUp, yUp);
  context->curve_to(xUp+20, yUp+5, xUp+20, yUp+35, xUp, yUp+40);
  context->move_to(xUp, yUp);
  context->curve_to(xUp+40, yUp+5, xUp+40, yUp+35, xUp, yUp+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp+5, yUp+10);
  context->line_to(xUp-10, yUp+10);
  context->move_to(xUp+5, yUp+30);
  context->line_to(xUp-10, yUp+30);
  //salida
  context->move_to(xUp+30, yUp+20);
  context->line_to(xUp+40, yUp+20);

  context->stroke();
}

void AreaDibujo::dibujarBuffer(unsigned int xUp, unsigned int yUp) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(xUp, yUp);
  context->line_to(xUp, yUp+40);
  context->move_to(xUp, yUp);
  context->line_to(xUp+30, yUp+20);
  context->move_to(xUp+30, yUp+20);
  context->line_to(xUp, yUp+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(xUp, yUp+10);
  context->line_to(xUp-10, yUp+10);
  context->move_to(xUp, yUp+30);
  context->line_to(xUp-10, yUp+30);
  //salida
  context->move_to(xUp+30, yUp+20);
  context->line_to(xUp+40, yUp+20);
  context->stroke();
}

//void buscarPosicion(int &x, int &y) {
//
//  int mod= x mod 10;
//  if(mod != 0)
//    x= x-mod;
//  mod= y MOD 10;
//  if(mod != 0)
//    y= y-mod;
//}

void AreaDibujo::on_drop_drag_data_received(
        const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
        const Gtk::SelectionData& selection_data, guint info, guint time) {

  std::cout << "DROP!" << std::endl;

  const int length = selection_data.get_length();
  if((length >= 0) && (selection_data.get_format() == 8)) {
    std::cout << "Received \"" << selection_data.get_data_as_string() << "\" in label " << std::endl;

    dibujarAnd(x, y);
    std::cout << "x: " << x << " - y: " << y << std::endl;
  }

  context->drag_finish(false, false, time);
}

bool AreaDibujo::on_button_press_event(GdkEventButton* event) {

  std::cout << "tocaron boton del mouse" << std::endl;

  if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    std::cout << "tocaron boton izquierdo del mouse" << std::endl;

  return true;
}
