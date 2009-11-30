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
#include "../Vista/Dibujos/Conexion.h"
#include "../Vista/Dibujos/EntradaSalida.h"
#include "../Vista/AreaDibujoGenerica.h"
#include "../Threads/ThreadLimpieza.h"

struct DatosCircuito{
  Circuito* c;
  int cantidadEntradas, cantidadSalidas;
  std::string label;
  std::string nombre;
};

struct DatosCircuitoRemoto{
  CircuitoRemoto *cr;
  CircuitoDibujo *c;
};

struct DatosCompuerta{
  Gate* g;
  Compuerta *c;
  std::string tipo;
};


struct DescripcionCircuito{
  std::string nombre;
  int cantidadEntradas, cantidadSalidas;
};

/** 
 * Controlador de la ventana.
 */
class ControladorVentana{
private:
  ControladorVentana(const ControladorVentana& c);
  ControladorVentana& operator=(const ControladorVentana& c);
  std::string filename;

  void crearConexiones(uint32_t componente, uint32_t pin, bool esSalida, const std::list<Vertice> &lista);
  
  void buscarExtremos(ConexionDibujo* pista, Vertice v, std::list<Vertice> &lista, std::map<ConexionDibujo*, ConexionDibujo*> *listaRecorridos);

protected:
  /* Estan declarados protegidos, para que la clase Persistidor
   * pueda cargar/grabar el estado */
  VentanaTrabajo* ventana;
  AreaDibujoGenerica *area;
  DatosCircuito circuito;
  std::map<Dibujo*, DatosCompuerta*> compuertas;
  std::map<Dibujo*, DatosCircuitoRemoto*> circuitos;
  std::map<Dibujo*, ConexionDibujo*> pistas;
  std::map<Dibujo*, EntradaSalida*> pines;
  ThreadLimpieza* limpieza;
  /** 
   * Avisa que se crea un nuevo circuito remoto y devuelve la
   * estructura asociada.
   * 
   * @return La estructura que contiene los datos del circuito.
   */
  DatosCircuitoRemoto* cargarCircuito();

  /** 
   * Avisa que se crea una nueva compuerta del tipo dado.
   * 
   * @param tipo Tipo de compuerta a crear.
   * 
   * @return La estructura que define la compuerta.
   */
  DatosCompuerta* cargarCompuerta(const std::string& tipo);

  ConexionDibujo* cargarConexion();

  EntradaSalida* cargarEntradaSalida();

  friend class Persistidor;

public:
  /** 
   * Crea un nuevo controlador. Antes de ser utilizado se debe
   * llamar a setVentana() para asociarlo a una ventana.
   * 
   */
  ControladorVentana();

  /** 
   * Inicializa el thread que hace la limpieza de threads.
   * IMPORTANTE: debe ser llamado antes de utilizar cualquier otro
   * metodo de la clase.
   */
  void iniciar();

  /** 
   * Asocia una ventana al controlador.
   * 
   * @param v Ventana a asociar al controlador.
   */
  void setVentana(VentanaTrabajo* v){ ventana = v; }

  /** 
   * Asigna un area de dibujo al controlador.
   * 
   * @param a El area de dibujo.
   */
  void setAreaDibujo(AreaDibujoGenerica *a){ area = a; }

  /** 
   * Metodo que indica al controlador que se acaba de agregar una
   * compuerta al circuito.
   * 
   * @param d El dibujo que idintifica a la compuerta.
   * @param tipo El tipo de compuerta que se agrega (and, or, xor, etc)
   */
  void crearComponente(Compuerta* d, const std::string& tipo);
     
  /** 
   * Metodo que indica al controlador que se acaba de agregar un
   * circuito remoto al circuito.
   * 
   * @param d El dibujo asociado al circuito a agregar.
   */
  void crearComponente(CircuitoDibujo* d);

  /** 
   * Indica al controlador que se acaba de agregar una conexion al
   * circuito.
   * 
   * @param d La conexion a agregar.
   */
  void crearComponente(ConexionDibujo* d);

  /** 
   * Indica al controlador que se acaba de agregar una entrada/salida
   * al ciruito.
   * 
   * @param d La entrada/salida a agregar.
   */
  void crearComponente(EntradaSalida* d);

  /** 
   * Metodo que indica que se elimino un componente del circuito.
   * 
   * @param d El dibujo asociado al componente a eliminar.
   */
  void eliminarComponente(Dibujo* d);

  /** 
   * Crea un circuito con los componentes agregados y simula.
   */
  void simular();

  /** 
   * Obtiene la leyenda de la tabla de resultados de la simulacion.
   * Cada linea del string cotiene el nombre de la entrada/salida
   * mostrado en la tabla y su nombre real (el mostrado en el
   * circuito)
   * 
   * @return La leyenda.
   */
  std::string getLeyenda();

  /** 
   * Crea un circuito con los elementos que tenemos.
   * 
   * @param errores Un string donde se pondran los errores detectados
   * en el proceso de armado del circuito.
   * 
   * @return El circuito creado o NULL.
   */
  Circuito* getCircuito(std::string* errores);

  /** 
   * Callback para que los threads que lanzo puedan ser eliminados.
   * 
   * @param thread 
   */
  void eliminarThread(Thread* thread);
     
  /** 
   * Devuelve una lista con los resultados de la simulacion. Cada
   * elemento de la lista es una posicion de la tabla.
   * 
   * 
   * @return Devuelve la lista de valores obtenidos en la simulacion.
   */
  std::list<uint64_t> obtenerTabla();

  /** 
   * Hace un pedido al servidor para que mande una lista de
   * circuitos disponibles. El pedido es asincronico.
   * 
   * @param servidor El servidor al que me conecto.
   * @param puerto El puerto al cual me conecto.
   */
  void obtenerListaServidor(const std::string& servidor, int puerto);

  /** 
   * Avisa al controlador que ya se recibio la lista de circuitos pedida.
   * 
   * @param lista La lista recibida.
   */
  void notificarLista(std::list<DescripcionCircuito> lista);

  /** 
   * Hace un pedido al servidor para que le envie un circuito
   * dado. El pedido es asincronico.
   * 
   * @param nombre El nombre del circuito a pedir.
   * @param servidor El servidor al cual le pido el circuito.
   * @param puerto El puerto al cual me conecto.
   */
  void obtenerCircuitoServidor(const std::string& nombre, const std::string& servidor, int puerto);

  /** 
   * Callback para el thread que obtiene el circuito del servidor.
   * 
   * @param nombreArchivo Nombre del archivo obtenido.
   * @param nombre Nombre del circuito.
   */
  void notificarCircuito(const std::string& nombreArchivo, const std::string& nombre);

  /** 
   * Guarda en un archivo el estado del modelo.
   * 
   * @param nombreArchivo Nombre del archivo donde guardar.
   */
  void guardarComo(const std::string& nombreArchivo);

  /**
   * Guarda en un archivo el estado del modelo con el ultimo filename.
   */
  void guardar();
     
  /** 
   * Carga el estado del modelo desde un archivo.
   * 
   * @param nombreArchivo El nombre del archivo.
   */
  bool cargar(const std::string& nombreArchivo);

  /** 
   * Callback para el thread que corre la simulacion.
   * 
   * @param tabla Tabla con los resultados de la simulacion.
   * @param errores Mensajes de error, si los hubo.
   */
  void recibirTablaSimulacion(std::list<uint32_t> tabla, std::string errores);

  /** 
   * Elimina todos los elementos que tenemos registrados (vacia el
   * objeto).
   * 
   */
  void eliminarTodo();

  ~ControladorVentana();
};

#endif //__CONTROLADORVENTANA_H_INCLUDED__
