#ifndef CIRCUITOREMOTO_H_
#define CIRCUITOREMOTO_H_

class DibujoCircuitoRemoto;

#include "AreaDibujoGenerica.h"
#include <cairomm/context.h>
#include <list>
#include "VentanaTrabajo.h"

/**
 * Es la clase que dibuja el circuito remoto.
 */
class DibujoCircuitoRemoto: public AreaDibujoGenerica {

private:
  int                           width;
  int                           height;
  void redibujar();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);

public:
  virtual ~DibujoCircuitoRemoto() { };
};

#endif /* CIRCUITOREMOTO_H_ */
