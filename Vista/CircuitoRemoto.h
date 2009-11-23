#ifndef CIRCUITOREMOTO_H_
#define CIRCUITOREMOTO_H_

class DibujoCircuitoRemoto;

#include <gtkmm/drawingarea.h>
#include "VentanaTrabajo.h"

class DibujoCircuitoRemoto: public Gtk::DrawingArea {

public:
  DibujoCircuitoRemoto(VentanaTrabajo *ventanaTrabajo) { };
};

#endif /* CIRCUITOREMOTO_H_ */
