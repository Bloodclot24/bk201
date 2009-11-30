#ifndef TABLA_H_
#define TABLA_H_

class Tabla;

#include <gtkmm/drawingarea.h>
#include "VentanaTrabajo.h"
#include "../Util/Util.h"

#include <iostream>

#define INICIO_TABLA 10
#define TAMANIO 40

/**
 * Es la clase que dibuja la tabla con los resultados de la simulacion.
 */
class Tabla: public Gtk::DrawingArea {
  friend class Impresora;

private:
  Glib::RefPtr<Gdk::Window>     window;
  std::list<uint32_t>           lista;
  int                           entradas;
  int                           salidas;
  int                           anchoColumna;
  int                           altoFila;
  int                           ancho;
  int                           alto;
  int                           altoLeyenda;
  std::string                   leyenda;
  void redibujar();

protected:
  virtual bool on_expose_event(GdkEventExpose* event);
  void dibujarTabla(const Cairo::RefPtr<Cairo::Context>& context);

public:
  /**
   * Crea una nueva tabla.
   */
  Tabla();

  /**
   * Destruye la tabla.
   */
  virtual ~Tabla() { };

  /**
   * Devuelve el ancho de la tabla.
   */
  int getAncho();

  /**
   * Devuelve el alto de la tabla.
   */
  int getAlto();

  /**
   * Cambia la cantidad de entradas de la tabla.
   *
   * @param entradas La nueva cantidad de entradas.
   */
  void setCantEntradas(int entradas);

  /**
   * Cambia la cantidad de salidas de la tabla.
   *
   * @param salidas La nueva cantidad de salidas.
   */
  void setCantSalidas(int salidas);

  /**
   * Cambia la lista de resultados a mostrar.
   *
   * @param lista La lista de resultados.
   */
  void setLista(std::list<uint32_t> lista);

  void setLeyenda(const std::string& leyenda);
};

#endif /* TABLA_H_ */
