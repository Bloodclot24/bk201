#ifndef AREADIBUJOGENERICA_H_
#define AREADIBUJOGENERICA_H_

class AreaDibujoGenerica;

#include <gtkmm/drawingarea.h>
#include "Dibujos/Dibujo.h"
#include "Dibujos/Conexion.h"
#include <stdint.h>
/**
 * El area de dibujo generica es una clase madre de todas las areas de dibujo
 * de la aplicacion que debe dibujar componentes.
 */
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

     /**
       * Recibe un dibujo y lo agrega a la lista de dibujos que se reflejara
       * en el area dibujo.
       *
       * @param dibujo El dibujo de tipo conexion a agregar.
       */
     virtual void agregarDibujo(Dibujo* dibujo);

     /**
       * Recibe un dibujo de tipo conexion y lo agrega a la lista de dibujos
       * que se reflejara en el area dibujo.
       *
       * @param dibujo El dibujo de tipo conexion a agregar.
       */
     virtual void agregarDibujo(ConexionDibujo* dibujo);

     /**
       * Devuelve el dibujo que se encuentra en la posicion pasada
       * por parametro. En caso de no hallar ningun dibujo, devuelve NULL.
       *
       * @param x La componente x de la posicion.
       * @param y La componente y de la posicion.
       */
     virtual Dibujo* buscarDibujo(int x, int y);

     /**
       * Devuelve el dibujo que se encuentra mas cercano al dibujo pasado por
       * parametro. En caso de no hallar ningun dibujo, devuelve NULL.
       *
       * @param origen El dibujo sobre el cual se esta buscando.
       * @param x La componente x de la posicion.
       * @param y La componente y de la posicion.
       */
     virtual Dibujo* buscarDibujoCercano(Dibujo *origen, int x, int y);

     /**
       * Devuelve si existe el dibujo pasado por parametro en la lista
       * de componentes del area de dibujo.
       *
       * @param origen El dibujo sobre el cual se esta preguntando.
       */
     virtual bool existeDibujo(Dibujo* d);

     /**
       * Vacia la lista de dibujos
       */
     void vaciarListaDibujos();

     /**
       * Devuelve el ancho del contexto del area de dibujo.
       */
     uint32_t getAncho();

     /**
       * Devuelve el alto del contexto del area de dibujo.
       */
     uint32_t getAlto();
};

#endif /* AREADIBUJOGENERICA_H_ */
