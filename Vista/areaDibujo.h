#ifndef AREADIBUJO_H_
#define AREADIBUJO_H_

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include <iostream>

class AreaDibujo: public Gtk::DrawingArea {

private:
  Cairo::RefPtr<Cairo::Context> context;

  /*TARGETS*/
  std::list<Gtk::TargetEntry> listTargets;

protected:
  virtual bool on_expose_event(GdkEventExpose* event);
  virtual bool on_my_button_press_event(GdkEventButton* event);
  void on_drop_drag_data_received(
          const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
          const Gtk::SelectionData& selection_data, guint info, guint time);

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
