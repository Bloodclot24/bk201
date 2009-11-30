#ifndef VERTICE_H_
#define VERTICE_H_

/**
 * Clase que representa un vertice.
 *
 */
class Vertice {

public:
  int x;
  int y;

  Vertice() {x= 0; y= 0; };
  Vertice(int x, int y) {x= x; y= y;};
     bool operator==(const Vertice& v2){
	  return (x==v2.x && y==v2.y);
     }
};

#endif /* VERTICE_H_ */
