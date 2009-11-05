#ifndef AREADIBUJO_H_
#define AREADIBUJO_H_

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

#include <iostream>

class AreaDibujo: public Gtk::DrawingArea {

public:
  AreaDibujo();
  virtual ~AreaDibujo();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);

};

#endif /* AREADIBUJO_H_ */
