#ifndef __CIRCUITO_H_INCLUDED__
#define __CIRCUITO_H_INCLUDED__

#include "../Componente/Componente.h"
#include <vector>
#include <iostream>
#include <list>

/** 
 * Clase que representa la conexion entre componentes.
 * 
 */
class Conexion{
private:
     Componente *c1;		/**< Componente que recibe las
				 * conexiones */

     /// La lista de componentes que se conectan con c1
     std::vector<Componente*> componentes;
     
     std::vector<unsigned> pinesC1; /**< Los pines destino */
     std::vector<unsigned> pinesC2; /**< Los pines origen */

     Conexion(const Conexion&){}

public:
     /** 
      * Crea una conexion para un componente dado.
      * 
      * @param c1 El componente asociado a la conexion.
      */
     Conexion(Componente* c1){
	  this->c1 = c1;
     };

     /** 
      * Agrega una conexion al conjunto.
      * 
      * @param pinC1 El pin que recibe la conexion.
      * @param c2  El componente que se nos conecta.
      * @param pinC2 El pin de c2 que se conecta a nuestro pin pinC1
      */
     void agregarConexion(unsigned pinC1,			\
			  Componente* c2, unsigned pinC2){
	  componentes.push_back(c2);
	  pinesC1.push_back(pinC1);
	  pinesC2.push_back(pinC2);
     }

     /** 
      * Actualiza el estado de los pines segun las salidas de los
      * componentes que se nos conectan.
      */
     void actualizar(){
	  std::vector<bool> entradas;
	  /* Creo un vector temporal para almacenar los valores
	   * finales de los pines */
	  for(unsigned i=0;i<c1->getCantidadEntradas()+c1->getCantidadSalidas();i++)
	       entradas.push_back(false);
	  
	  /* por cada conexion del conjunto */
	  for(unsigned i=0;i< componentes.size();i++){
	       /* obtengo el valor de la entrada almacenado*/
	       bool v = entradas[pinesC1[i]];
	       /* Y aplico un OR con el valor que nos quiere imponer
		* este componente.*/
	       v |= componentes[i]->getPin(pinesC2[i]);
	       /* Volvemos a almacenar el valor */
	       entradas[pinesC1[i]] = v;
	       /* Asi, si hay dos o mas componentes que se nos
		* conectan a un mismo pin y ambos nos quieren asignar
		* diferentes estados (alto y bajo), nos quedamos con
		* el valor alto.*/
	  }
	  /* Despues de calculado el valor final, lo asignamos a cada
	   * pin.*/
	  for(unsigned i=0;i<componentes.size();i++)
	       c1->setPin(pinesC1[i], entradas[pinesC1[i]]);
     }
     
     /**
      * Devuelve un puntero constante al componente que recibe las conexiones.
      * Se lo utilizara unicamente para la persistencia.
      */
     const Componente* getComponente(){
     	return this->c1;
     }
     
     /**
      * Devuelve el vector de componentes que se conectan al componente en cuestion.
      * Se lo utilizara unicamente para la persistencia.
      */
     const std::vector<Componente*>& getComponentes(){
     	return this->componentes;
     }
     
     /**
      * Devuelve el vector con las salidas del componente C1.
      * Se lo utilizara unicamente para la persistencia.
      */
     const std::vector<unsigned>& getPin1(){
     	return this->pinesC1;
     }
    
     /**
      * Devuelve el vector con las entradas a cada componente C2.
      * Se lo utilizara unicamente para la persistencia.
      */ 
     const std::vector<unsigned>& getPin2(){
     	return this->pinesC2;
     }
};


/** 
 * Clase que representa un circuito formado por componentes. El
 * circuito en si mismo es un componente.
 * 
 */
class Circuito:public Componente{
private:
     std::vector<Componente*> componentes; /**< Componentes que forman
					    * el circuito */
     std::vector<Conexion*> conexiones;	/**< Conexiones del
					 * circuito */
     uint64_t tiempo;		/**< Tiempo transcurrido desde la
				 * ultima vez que se estabilizaron las
				 * salidas. */
     bool extendido;		/**< Indica si se requiere o no de una
				 * simulacion extendida. */
     bool deboActualizar;

     /** 
      * Actualiza los estados de todas las conexiones.
      */
     void actualizarConexiones(){
	  deboActualizar = false;
	  for(unsigned k=0;k<conexiones.size();k++)
	       conexiones[k]->actualizar();
     }

     /** 
      * Simula hasta el proximo evento.
      * 
      */
     void simularProximoEvento(){
	  uint64_t menorT=-1;
	  for(unsigned i=0;i<componentes.size();i++){
	       if(!componentes[i]->esEstable()){
		    if((componentes[i]->getTProximoEvento() < menorT))
			 menorT=componentes[i]->getTProximoEvento();
	       }
	  }
	  if(menorT == (uint64_t)-1){
//	       std::cerr << "simular con -1 en " << this <<  std::endl;
	       menorT=1;
	  }
	  for(unsigned j=0;j<componentes.size();j++){
	       componentes[j]->simular(menorT);
	  }
	  actualizarConexiones();
	  tiempo+=menorT;
	  
     }

     Circuito(const Circuito& ){};


public:
     /** 
      * Crea un nuevo circuito con la cantidad de entradas y salidas especificadas.
      * 
      * @param cantEntradas La cantidad de entradas del circuito.
      * @param cantSalidas La cantidad de salidas del circuito.
      */
     Circuito(unsigned cantEntradas,unsigned cantSalidas){
	  while(cantEntradas-- > 0)
	       entradas.push_back(false);
	  while(cantSalidas-- > 0)
	       salidas.push_back(false);
	  extendido = 0;
	  tiempo=0;
	  deboActualizar=false;
     };

     /** 
      * Agrega un nuevo componente al circuito. El circuito se adueña
      * del componente y no debe ser utilizado nunca externamente. A
      * cada componente se le asigna un numero que lo
      * identifica. Estos numeros son correlativos y empiezan desde el
      * cero.
      * 
      * @param componente El componente a agregar.
      */
     void agregarComponente(Componente* componente){componentes.push_back(componente);}

     /** 
      * Agrega una nueva conexion al circuito. La conexion va de c1 a
      * c2. Si c1 o c2 son -1, indica que el pin a utilizar
      * corresponde al circuito. Es decir que
      * agregarComponente(-1,0,2,1), conecta el pin 0 del circuito
      * (tomandolo como salida) al pin 1 del componente 2 (tomandolo como entrada).
      * 
      * @param c1 El numero de componente desde el cual se origina la conexion.
      * @param pinC1 El pin de c1 que se conecta (se utiliza como salida)
      * @param c2 El numero de componente que recibe la conexion.
      * @param pinC2 Elpin de c2 que recibe la conexion (se utiliza como entrada)
      */
     void agregarConexion(unsigned c1, unsigned pinC1, unsigned c2, unsigned pinC2){
	  while(conexiones.size() < componentes.size()+1)
	       conexiones.push_back(NULL);
	  Componente *C1, *C2;
	  if(c1 == (unsigned)-1){
	       C1=this;
	       c1=0;
	  }
	  else{
	       C1=componentes[c1];
	       c1++;
	  }
	  if(c2 == (unsigned)-1){
	       C2=this;
	       c2=0;
	  }
	  else{
	       C2=componentes[c2];
	       c2++;
	  }
	  if(conexiones[c2] == NULL)
	       conexiones[c2] = new Conexion(C2);
	  conexiones[c2]->agregarConexion(pinC2,	\
					  C1, pinC1);
     }

     /** 
      * Asigna un valor a una de las entradas del circuito.
      * 
      * @param numero Numero de entrada.
      * @param estado Estado a asignar.
      */
     void setEntrada(unsigned numero, bool estado){
	  if(numero < getCantidadEntradas()){
	       if(estado != getEntrada(numero)){
		    deboActualizar=true;
	       }
	       entradas[numero]=estado;
	  }
     }

     /** 
      * Asigna un estado a uno de los pines delcircuito.
      * 
      * @param numero Numero de pin.
      * @param estado Estado a asignar.
      */
     virtual void setPin(unsigned numero, bool estado){
	  if(numero < getCantidadEntradas()){
	       setEntrada(numero, estado);
	  }
	  else{
	       numero -= getCantidadEntradas();
	       salidas[numero] = estado;
	  }
     }

     /** 
      * Pone un nuevo valor al flag 'extendido',que indica si se debe o
      * no realizar una simulacion extendida.
      * 
      * @param valor Nuevo valor.
      */
     void setExtendido(bool valor){
	  extendido = valor;
     }

     virtual void reset(){
	  for(unsigned j=0;j<componentes.size();j++)
	       componentes[j]->reset();
	  Componente::reset();
     }

     /** 
      * Simula el comportamiento del circuito variando las entradas a
      * todas las combinaciones posibles. Si la simulacion es
      * extendida, se simulan todas las entradas posibles a partir de
      * todas las entradas posibles. Esto es, si las entradas posibles
      * son (00,01,10,11), se simula (00,01,10,11) cada uno viniendo
      * del estado (00), luego se simulan las entradas (00,01,10,11)
      * cada una viniendo del estado (01),... etc.
      * 
      * @param tiempo El tiempo maximo a esperar para la
      * estabilizacion de la salida.
      */

     std::list<uint32_t> simularTodo(uint64_t tiempo){
	  std::list<uint32_t> tabla;
	  uint64_t combinaciones = 2;
	  unsigned entradas= getCantidadEntradas();
	  unsigned salidas = getCantidadSalidas(); 

	  /* Calculo la cantidad decombinaciones totales */
	  for(unsigned i=1;i<entradas;i++,combinaciones *= 2);

	  /* Si es extendido, agrego todas las posibilidades */
	  if(extendido)
	       for(unsigned i=0;i<entradas;i++,combinaciones *= 2);
	       
	  /* Creo la cabecerade la tabla */
	  for(unsigned i=0;i<entradas;i++)
	       std::cout << " " << (char)('a'+i) << " |";
	  if(extendido)
	       for(unsigned i=0;i<entradas;i++)
		    std::cout << (char)('a'+i) << "-1|";
	  for(unsigned j=0;j<salidas;j++)
	       std::cout << "| " << (char)('A'+j) << " " ;
	  if(extendido)
	       for(unsigned j=0;j<salidas;j++)
		    std::cout << "|" << (char)('A'+j) << "-1" ;
	  std::cout << std::endl;
	  for(unsigned k=0;k<(entradas+salidas)*4;k++)
	       std::cout << "=";
	  if(extendido)
	       for(unsigned k=0;k<(entradas+salidas)*4;k++)
		    std::cout << "=";
	  std::cout << std::endl;

	  /* Flag para indicar si la salida anterior fue o no
	   * estable */
	  bool inestableAnterior = false;
	  /* Por cada combinacion */
	  for(uint64_t i=0;i<combinaciones;i++){
	       
	       std::vector<bool> salidasAnteriores;

	       if(extendido){
		    /* Si es simulacion extendida */
		    inestableAnterior=false;

		    /* Reseteo todos los componentes */
		    reset();

		    /* Asigno los valores correspondientes */
		    for(unsigned j=0;j<entradas;j++)
			 setEntrada(j, (i&1<<(j+entradas)));
		    actualizarConexiones();
		    this->tiempo=0;
		    /* y simulo hasta que se esatbilizen las salidas */
		    while(!esEstable() && this->tiempo < tiempo){
			 simularProximoEvento();
		    }
		    /*guardo las salidas estabilizadas */
		    for(unsigned l=0;l<salidas;l++)
			 salidasAnteriores.push_back(getSalida(l));
		    if(this->tiempo >= tiempo){
			 inestableAnterior=true;
		    }
	       }
	       
	       /* Asigno los nuevos valores a las entradas */
	       for(unsigned j=0;j<entradas;j++){
		    setEntrada(j, i&1<<j);
	       }
	       actualizarConexiones();
	       
	       /* Simulo hasta que se estabilizen las entradas.*/
	       this->tiempo=0;
	       while(!esEstable() && this->tiempo < tiempo)
		    simularProximoEvento();

	       /* Muestro los resultados */
	       for(unsigned k=0;k<entradas;k++){
		    std::cout << " " << ((i&1<<k)!=0) << " |";
		    tabla.push_back(((i&1<<k)!=0));
	       }
	       if(extendido)
		    for(unsigned k=0;k<entradas;k++)
			 std::cout << " " << ((i&1<<(k+entradas))!=0) << " |";
	  
	       if(this->tiempo < tiempo){
		    for(unsigned l=0;l<salidas;l++){
			 std::cout << "| " << getSalida(l) << " ";
			 tabla.push_back(getSalida(l));
		    }
		    if(extendido) {
			 if(!inestableAnterior)
			      for(unsigned l=0;l<salidas;l++)
				   std::cout << "| " << salidasAnteriores[l] << " ";
			 else
			      for(unsigned l=0;l<salidas;l++)
				   std::cout << "| " << "?" << " ";
		    }
		    std::cout << " Tiempo: " << this->tiempo << " ns";
		    tabla.push_back(this->tiempo);
		    std::cout << std::endl;
		    
	       }
	       else{ // Paso mas del tiempo maximo permitido
		    for(unsigned l=0;l<salidas;l++)
			 std::cout << "| " << "?" << " ";
		    if(extendido) {
			 if(!inestableAnterior)
			      for(unsigned l=0;l<salidas;l++)
				   std::cout << "| " << salidasAnteriores[l] << " ";
			 else
			      for(unsigned l=0;l<salidas;l++)
				   std::cout << "| " << "?" << " ";
		    }
		    std::cout << " Tiempo: ??? (inestable)";
		    std::cout << std::endl;
		    
	       }
	  }
	  return tabla;
     }


     /** 
      * Simula el tiempo especificado.
      * 
      * @param tiempo El tiempo a simular.
      */
     virtual void simular(uint64_t tiempo){
	  uint64_t i,j;
	  actualizarConexiones();
	  i = this->tiempo + tiempo;
	  j = this->tiempo;
	  while(!esEstable() && i > this->tiempo){
	       simularProximoEvento();
	  }
     }

     /** 
      * Indica si las salidas del circuito son o no estables.
      * 
      * @return TRUE si las salidas son estables.
      */
     bool esEstable(){
	  bool returnValue=true;
	  if(deboActualizar){
	       actualizarConexiones();
	  }
	  /* Busco hasta encontrar algun componente inestable o hasta recorrerlos todos. */
	  for(unsigned i=0;i< componentes.size() && returnValue == true;i++){
	       if(!componentes[i]->esEstable())
		    returnValue = false;
	  }
	  return returnValue;
     }

     uint64_t getTProximoEvento(){
	  uint64_t proximo=-1;
	  for(unsigned i=0;i<componentes.size();i++){
	       if(componentes[i]->getTProximoEvento()<proximo)
		    proximo = componentes[i]->getTProximoEvento();
	  }
	  return proximo;
     }

	/**
	 * Obtengo los componentes que conforman el circuito
	 * este metodo va a utilizarse unicamente para serializar
	 * los circuitos
	 */
	const std::vector<Componente*>& getComponenetes(){
		return this->componentes;
	}
	
	/**
	 * Obtengo las conexiones que conforman el circuito
	 * este metodo va a utilizarse unicamente para serializar
	 * los circuitos
	 */
	 const std::vector<Conexion*>& getConexiones(){
	 	return this->conexiones;
	 }

     /** 
      * Destruye el circuito y todos los componentes.
      */
     virtual ~Circuito(){
	  for(unsigned i=0;i<conexiones.size();i++)
	       if(conexiones[i] != NULL)
		    delete conexiones[i];

	  // for(unsigned j=0;j<componentes.size();j++)
	  //      if(componentes[j] != NULL)
	  // 	    delete componentes[j];
     }
};

#endif //__CIRCUITO_H_INCLUDED__
