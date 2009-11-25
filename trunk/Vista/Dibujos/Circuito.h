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
   std::string servidor;
   std::string puerto;

protected:
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

  virtual void setVerticeSupIzq(Vertice vSupIzq);

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
};

#endif /* CIRCUITO_H_ */
