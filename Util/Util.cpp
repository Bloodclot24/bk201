#include "Util.h"

/****************************************************************************/
std::string Util::intToString(int numero) {
	
	std::string snumero;
	std::stringstream cvz;
	cvz.width();
	cvz << numero;
	snumero= cvz.str();
	
	return snumero;
}

/****************************************************************************/
