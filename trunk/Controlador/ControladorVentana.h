#ifndef __CONTROLADORVENTANA_H_INCLUDED__
#define __CONTROLADORVENTANA_H_INCLUDED__

class ControladorVentana;

struct DescripcionCircuito;

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
     CircuitoDibujo *c;
     std::string nombre;
     std::string servidor;
     int puerto;
     std::string label;
     int cantidadEntradas, cantidadSalidas;
};

struct DatosCompuerta{
     Gate* g;
     Compuerta *c;
     uint64_t tr;
     std::string label;
     std::string tipo;
};

struct DatosPista{
     
};

struct DatosPin{
     bool esEntrada;
};

struct DescripcionCircuito{
     std::string nombre;
     int cantidadEntradas, cantidadSalidas;
};

class ControladorVentana{
private:
     ControladorVentana(const ControladorVentana& c);
     ControladorVentana& operator=(const ControladorVentana& c);

protected:
     VentanaTrabajo* ventana;
     DatosCircuito circuito;
     std::map<Dibujo*, DatosCompuerta*> compuertas;
     std::map<Dibujo*, DatosCircuitoRemoto*> circuitos;
     std::map<Dibujo*, DatosPista*> pistas;
     std::map<Dibujo*, DatosPin*> pines;
     friend class Persistidor;

public:
     ControladorVentana(){ ventana=NULL; circuito.cantidadEntradas = circuito.cantidadSalidas=0;};
     void setVentana(VentanaTrabajo* v){ ventana = v; }

     void crearComponente(Compuerta* d, const std::string& tipo);
     void crearComponente(CircuitoDibujo* d);
     void eliminarComponente(Dibujo* d);
     void simular();
     void obtenerListaServidor(const std::string& servidor, int puerto);
     std::list<uint64_t> obtenerTabla();
     void guardar(const std::string& nombreArchivo);
     void cargar(const std::string& nombreArchivo);
     DatosCircuitoRemoto* cargarCircuito();
     DatosCompuerta* cargarCompuerta(const std::string& tipo);
     void notificarLista(std::list<DescripcionCircuito> lista);
};

#endif //__CONTROLADORVENTANA_H_INCLUDED__
