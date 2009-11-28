#ifndef AREADIBUJOGENERICA_H_
#define AREADIBUJOGENERICA_H_

class AreaDibujoGenerica;

#include <gtkmm/drawingarea.h>
#include "Dibujos/Dibujo.h"
#include "Dibujos/Conexion.h"

class AreaDibujoGenerica: public Gtk::DrawingArea {
protected:
     AreaDibujoGenerica(){ selected=false; seleccion=false;}
     bool                          selected;
     std::vector<Dibujo*>          dibujoSeleccionados;
     std::list<Dibujo*>            dibujos;
     bool                          seleccion;
     Glib::RefPtr<Gdk::Window>     window;
     void agregarComponente(Dibujo* dibujo);
     void deseleccionar();
     void redibujar();
public:
     virtual void agregarDibujo(Dibujo* dibujo);
     virtual void agregarDibujo(ConexionDibujo* dibujo);
     virtual Dibujo* buscarDibujo(int x, int y);
     virtual Dibujo* buscarDibujoCercano(Dibujo *origen, int x, int y);
     virtual bool existeDibujo(Dibujo* d);
     void vaciarListaDibujos();

};

#endif /* AREADIBUJOGENERICA_H_ */
