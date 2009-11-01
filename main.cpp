#include <glibmm/thread.h>
#include "Controlador/controlador.h"

int main(int argc, char *argv[]) {
        
	Glib::thread_init();
  Gtk::Main kit(argc, argv);
  Controlador controlador;
  controlador.correr();
  
  return 0;
}
