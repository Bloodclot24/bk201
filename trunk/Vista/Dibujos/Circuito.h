#ifndef CIRCUITO_H_
#define CIRCUITO_H_

#include "Dibujo.h"

#include <iostream>

#define SEPARACION 10

  /**
    * Clase encargada del dibujo del circuito remoto.
    * Se la utiliza para dibujar cualquier circuito
    * remoto de N de entradas y M salidas alojado en algun
    * servidor remoto.
    *
    */
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

  /**
      * Agrega los datos al circuito.
      *
      * @param servidor El host(ip) del servidor al que pertenece el circuito.
      * @param puerto El puerto mediante el cual se establece la conexion con el servidor.
      * @param nombre El nombre en el servidor(nombre del archivo) del circuito en cuestion.
      */
   void agregarDatos(const std::string &servidor, const std::string &puerto, const std::string &nombre);

   /**
     * Setea el valor del vertice superior izquierdo del circuito, el mismo
     * se utilizara luego para poder dibujarlo, entre otras cosas.
     *
     * @param vSupIzq El nuevo vertice superior izquierdo del circuito.
     *
     */
   virtual void setVerticeSupIzq(Vertice vSupIzq);
   /**
     * Setea la cantidad de entradas y salidas del circuito.
     *
     * @param entradas La cantidad de entradas del circuito.
     * @param salidas La cantidad de salidas del circuito.
     *
     */
   void setEntradasSalidas(int entradas, int salidas);

  /**
    * Se dibuja el circuito en el contexto dado por parametro.
    *
    * @param context El contexto del area de dibujo.
    */
  virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& context);

  /**
    * Obtiene el servidor al cual pertenece el circuito en cuestion.
    *
    */
  std::string getServidor();

  /**
    * Setea el servidor al que pertenece el circuito.
    *
    * @param servidor El host(ip) del servidor que posee el circuito.
    *
    */
  void setServidor(std::string servidor);

  /**
    * Obtiene el puerto mediante el cual debe conectarse al servidor.
    *
    */
  std::string getPuerto();

  /**
    * Setea el puerto mediante el cual debe conectarse al servidor.
    *
    * @param puerto El puerto de conexion con el servidor.
    *
    */
  void setPuerto(std::string puerto);

  /**
    * Obtiene el nombre del circuito en el servidor (es el nombre del archivo).
    *
	*/
  std::string getNombre();

  /**
    * Setea el nombre del circuito en el servidor(nombre del archivo).
    *
    * @param nombre Es el nuevo nombre del circuito en el servidor.
    *
    */
  void setNombre(const std::string& nombre){this->nombre=nombre;}

  /**
    * Obtiene la cantidad de entradas.
    *
    */
  int getCantidadEntradas();

  /**
     * Obtiene la cantidad de salidas.
     *
     */
  int getCantidadSalidas();

  /**
     * Dibuja el circuito en el contexto que recibe por parametro, este metodo se
     * utiliza para imprimir el circuito.
     *
     * @param context El contexto sobre el cual se va a dibujar el circuito.
     *
     */
  virtual void dibujarImpresion(const Cairo::RefPtr<Cairo::Context>& context);

     void setAngulo(int angulo);

};

#endif /* CIRCUITO_H_ */
