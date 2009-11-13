#ifndef AREADIBUJO_H_
#define AREADIBUJO_H_

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include <iostream>
#include <math.h>

class AreaDibujo: public Gtk::DrawingArea {

private:
  Cairo::RefPtr<Cairo::Context> context;
  Glib::RefPtr<Gdk::Window>     window;
  Gdk::Region                   region;

  unsigned int                  xUp;
  unsigned int                  yUp;
  bool                          mostrarAnd;

  /*TARGETS*/
  std::list<Gtk::TargetEntry> listTargets;

  void And();


protected:
  virtual bool on_expose_event(GdkEventExpose* event);
  virtual bool on_my_button_press_event(GdkEventButton* event);
  virtual void on_drop_drag_data_received(
          const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
          const Gtk::SelectionData& selection_data, guint info, guint time);
  virtual bool on_button_press_event(GdkEventButton* event);

public:
  AreaDibujo();
  virtual ~AreaDibujo();

  void dibujarAnd(unsigned int xUp, unsigned int yUp);
  void dibujarOr(unsigned int xUp, unsigned int yUp);
  void dibujarNot(unsigned int xUp, unsigned int yUp);
  void dibujarXor(unsigned int xUp, unsigned int yUp);
  void dibujarBuffer(unsigned int xUp, unsigned int yUp);
};

#endif /* AREADIBUJO_H_ */
