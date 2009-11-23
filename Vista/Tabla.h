#ifndef TABLA_H_
#define TABLA_H_

class Tabla;

#include <gtkmm/drawingarea.h>
#include "VentanaTrabajo.h"
#include "../Util/Util.h"

#include <iostream>

#define INICIO_TABLA 10
#define TAMANIO 40


class Tabla: public Gtk::DrawingArea {
  friend class VentanaTrabajo;

private:
  VentanaTrabajo                *ventanaTrabajo;
  Cairo::RefPtr<Cairo::Context> context;
  Glib::RefPtr<Gdk::Window>     window;
  std::list<uint32_t>           lista;
  int                           entradas;
  int                           salidas;
  int                           alto;
  int                           ancho;
  void redibujar();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);

public:
  Tabla(VentanaTrabajo *ventanaTrabajo);
  virtual ~Tabla() { };
  void dibujarTabla();
  void setCantEntradas(int entradas);
  void setCantSalidas(int salidas);
  void setLista(std::list<uint32_t> lista);
};

#endif /* TABLA_H_ */
