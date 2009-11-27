#ifndef CIRCUITO_H_
#define CIRCUITO_H_

#include "Dibujo.h"

#include <iostream>

#define SEPARACION 10

class CircuitoDibujo: public Dibujo {

private:
   int entradas;
   int pasoEntrada;
   int salidas;
   int pasoSalida;
   std::string nombre;
   std::string servidor;
   std::string puerto;

protected:
   virtual void mostrarAtributos(const Cairo::RefPtr<Cairo::Context>& context, int yTexto);
   void cargarNuevosPines(Vertice vSupIzq);
   int pasoPinesMenor(int mayor, int menor);
public:
  /**
    * Crea un circuito.
    *
    * @param supIzqX La componente x del vertice superior izquierdo del circuito.
    * @param supIzqY La componente y del vertice superior izquierdo del circuito.
    */
  CircuitoDibujo(int supIzqX, int supIzqY, int entradas, int salidas);

  virtual ~CircuitoDibujo() { };

  void agregarDatos(const std::string &servidor, const std::string &puerto, const std::string &nombre);

  virtual void setVerticeSupIzq(Vertice vSupIzq);
     void setEntradasSalidas(int entradas, int salidas);

  /**
    * Se dibuja el circuito en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  std::string getServidor();
  void setServidor(std::string servidor);
  std::string getPuerto();
  void setPuerto(std::string puerto);
  int getCantidadEntradas();
  int getCantidadSalidas();
  void setVerticesMotion(Vertice vertice);
};

#endif /* CIRCUITO_H_ */
