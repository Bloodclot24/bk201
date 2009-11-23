#ifndef CIRCUITOREMOTO_H_
#define CIRCUITOREMOTO_H_

class DibujoCircuitoRemoto;

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <list>
#include "VentanaTrabajo.h"
#include "Dibujos/Vertice.h"


class DibujoCircuitoRemoto: public Gtk::DrawingArea {
	private:
		VentanaTrabajo* ventanaTrabajo;
		Cairo::RefPtr<Cairo::Context> context;
 		Glib::RefPtr<Gdk::Window>     window;
 		std::list<Dibujo*>            dibujos;
 		int                           width;
 		int                           height;


	protected:
  		virtual bool on_expose_event(GdkEventExpose* event);
		void redibujar();
	public:
  		DibujoCircuitoRemoto(VentanaTrabajo *ventanaTrabajo);
		void agregarDibujos(std::list<Dibujo*> dibujos);
};

#endif /* CIRCUITOREMOTO_H_ */
