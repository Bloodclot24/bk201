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
  int                           width;
  int                           height;
  void redibujar();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);

public:
  DibujoCircuitoRemoto(VentanaTrabajo *ventanaTrabajo);
  virtual ~DibujoCircuitoRemoto() { };
};

#endif /* CIRCUITOREMOTO_H_ */
