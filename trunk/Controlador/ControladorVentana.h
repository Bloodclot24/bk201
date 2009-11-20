#ifndef __CONTROLADORVENTANA_H_INCLUDED__
#define __CONTROLADORVENTANA_H_INCLUDED__

class ControladorVentana;

#include <map>

#include "../Circuito/Circuito.h"
#include "../Componente/Componente.h"
#include "../Vista/VentanaTrabajo.h"
#include "../Vista/Dibujos/Dibujo.h"
#include "../Vista/Dibujos/Compuerta.h"
#include "../Vista/Dibujos/Circuito.h"
#include "../Gates/Gate.h"
#include "../Circuito/CircuitoRemoto.h"

struct DatosCircuito{
     Circuito* c;
     int cantidadEntradas, cantidadSalidas;
     std::string label;
     std::string nombre;
};

struct DatosCircuitoRemoto{
     CircuitoRemoto *cr;
     Dibujo *c;
     std::string nombre;
     std::string servidor;
     int puerto;
     std::string label;
     int cantidadEntradas, cantidadSalidas;
};

struct DatosCompuerta{
     Gate* g;
     Dibujo *c;
     uint64_t tr;
     std::string label;
     std::string tipo;
};

struct DatosPista{
     
};

struct DatosPin{
     bool esEntrada;
};

class ControladorVentana{
private:
     VentanaTrabajo* ventana;
     ControladorVentana(const ControladorVentana& c);
     ControladorVentana& operator=(const ControladorVentana& c);

protected:
     DatosCircuito circuito;
     std::map<Dibujo*, DatosCompuerta*> compuertas;
     std::map<Dibujo*, DatosCircuitoRemoto*> circuitos;
     std::map<Dibujo*, DatosPista*> pistas;
     std::map<Dibujo*, DatosPin*> pines;

public:
     ControladorVentana(){ ventana=NULL;};
     void setVentana(VentanaTrabajo* v){ ventana = v; }

     void crearComponente(Dibujo* d, const std::string& tipo);
     void eliminarComponente(Dibujo* d);
     void simular();
     std::list<std::string> obtenerListaServidor(const std::string& servidor, int puerto);
     std::list<uint64_t> obtenerTabla();
     void setAtributo(Dibujo* d, const std::string& nombre, const std::string& valor);
     std::string getAtributo(Dibujo* d, const std::string& nombre);
     void guardar(const std::string& nombreArchivo);
};

#endif //__CONTROLADORVENTANA_H_INCLUDED__
