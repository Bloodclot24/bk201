#ifndef CIRCUITOREMOTO_H_
#define CIRCUITOREMOTO_H_

class DibujoCircuitoRemoto;

#include "AreaDibujoGenerica.h"
#include <cairomm/context.h>
#include <list>
#include "VentanaTrabajo.h"

class DibujoCircuitoRemoto: public AreaDibujoGenerica {

private:
  VentanaTrabajo*               ventanaTrabajo;
  Glib::RefPtr<Gdk::Window>     window;
  std::list<Dibujo*>            dibujos;
  int                           width;
  int                           height;
  void redibujar();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);

public:
  DibujoCircuitoRemoto(VentanaTrabajo *ventanaTrabajo);
  virtual ~DibujoCircuitoRemoto() { };
  void agregarDibujos(std::list<Dibujo*> dibujos);
  virtual void agregarDibujo(Dibujo* dibujo) { };
};

#endif /* CIRCUITOREMOTO_H_ */
