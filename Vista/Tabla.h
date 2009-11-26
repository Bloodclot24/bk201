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
  friend class Impresora;
private:
  VentanaTrabajo                *ventanaTrabajo;
  Glib::RefPtr<Gdk::Window>     window;
  std::list<uint32_t>           lista;
  int                           entradas;
  int                           salidas;
  int                           alto;
  int                           ancho;
  void redibujar();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);
  void dibujarTabla(const Cairo::RefPtr<Cairo::Context>& context);

public:
  Tabla(VentanaTrabajo *ventanaTrabajo);
  Tabla(const Tabla& Tabla){ };
  virtual ~Tabla() { };
  void setCantEntradas(int entradas);
  void setCantSalidas(int salidas);
  void setLista(std::list<uint32_t> lista);
};

#endif /* TABLA_H_ */
