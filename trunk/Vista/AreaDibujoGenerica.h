#ifndef AREADIBUJOGENERICA_H_
#define AREADIBUJOGENERICA_H_

#include <gtkmm/drawingarea.h>
#include "Dibujos/Dibujo.h"

class AreaDibujoGenerica: public Gtk::DrawingArea {

public:
  virtual void agregarDibujo(Dibujo* dibujo)= 0;
};

#endif /* AREADIBUJOGENERICA_H_ */
