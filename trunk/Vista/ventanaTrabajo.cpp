#include "ventanaTrabajo.h"

VentanaTrabajo::VentanaTrabajo(Controlador *controlador, unsigned int id) {

  try {
    this->refXml= Gtk::Builder::create_from_file(PATH_VISTA);
  } catch(const Gtk::BuilderError &be) {
    std::cerr << "Gtk::BuilderError code:" << be.code() << std::endl;
  } catch(const Glib::FileError &fe) {
    std::cerr << "Glib::FileError code:" << fe.code() << std::endl;
  } catch(const Glib::MarkupError &me) {
    std::cerr << "Glib::MarkupError code:" << me.code() << std::endl;
  }

  this->controlador= controlador;
  this->id= id;
}

bool VentanaTrabajo::on_delete_event(GdkEventAny *event) {

  cerrar();

  return(false);
}

void VentanaTrabajo::correr(bool primeraVez) {
	
  refXml->get_widget("window", window);
  window->maximize();
  window->signal_delete_event().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_delete_event));

  //nombre ventana
  std::string name;
  name+= CIRCUITO;
  name+= Util::intToString(id);
  name+= NOMBRE_PROGRAMA;
  window-> set_title(name);

  //Area de Dibujo
  Gtk::Table *table;
  refXml->get_widget("table", table);
  table->attach(areaDibujo, 0, 10, 0, 10);

  //Menu Bar
  loadMenuBar(window);

  /*TOOLBAR*/
//	loadToolBar();

  //FilechooserDialog Open
  refXml->get_widget("filechooserdialog_open", filechooserdialog_open);
  filechooserdialog_open->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_response_open));

  //FilechooserDialog Save as
  refXml->get_widget("filechooserdialog_saveas", filechooserdialog_saveas);
  filechooserdialog_saveas->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_response_saveas));

  window->show_all();
	
  if(primeraVez)
    Gtk::Main::run();
}

/**MENUBAR**/
void VentanaTrabajo::loadMenuBar(Gtk::Window *window) {

  //crea las acciones del menu bar
  m_refActionGroup = Gtk::ActionGroup::create();

  //menu archivo
  m_refActionGroup->add(Gtk::Action::create("ArchivoMenu", "Archivo"));
  m_refActionGroup->add(Gtk::Action::create("Nuevo", Gtk::Stock::NEW),
                        sigc::mem_fun(*this, &VentanaTrabajo::nuevo));
  m_refActionGroup->add(Gtk::Action::create("Abrir", Gtk::Stock::OPEN),
                        sigc::mem_fun(*this, &VentanaTrabajo::abrir));
  m_refActionGroup->add(Gtk::Action::create("Guardar", Gtk::Stock::SAVE),
                        sigc::mem_fun(*this, &VentanaTrabajo::guardar));
  m_refActionGroup->add(Gtk::Action::create("Guardar como...", Gtk::Stock::SAVE_AS, "Guardar como..."),
                        sigc::mem_fun(*this, &VentanaTrabajo::guardarComo));
  m_refActionGroup->add(Gtk::Action::create("Salir", Gtk::Stock::QUIT),
                        sigc::mem_fun(*this, &VentanaTrabajo::cerrar));

  //menu editar
  m_refActionGroup->add(Gtk::Action::create("EditarMenu", "Editar"));
  m_refActionGroup->add(Gtk::Action::create("RotarD 90", Gtk::Stock::REDO,"Rotar 90"),
                        sigc::mem_fun(*this, &VentanaTrabajo::rotar90D));
  m_refActionGroup->add(Gtk::Action::create("RotarI 90", Gtk::Stock::UNDO,"Rotar 90"),
                        sigc::mem_fun(*this, &VentanaTrabajo::rotar90I));
  m_refActionGroup->add(Gtk::Action::create("Borrar", Gtk::Stock::DELETE),
                        sigc::mem_fun(*this, &VentanaTrabajo::borrar));

  //menu simular
  m_refActionGroup->add(Gtk::Action::create("SimularMenu", "Simular"));
  m_refActionGroup->add(Gtk::Action::create("Simular", Gtk::Stock::MEDIA_PLAY, "Simular"),
                        sigc::mem_fun(*this, &VentanaTrabajo::simular));
  m_refActionGroup->add(Gtk::Action::create("Tablas", "Ver tablas"),
                        sigc::mem_fun(*this, &VentanaTrabajo::verTablas));

  //menu ayuda
  m_refActionGroup->add(Gtk::Action::create("AyudaMenu", "Ayuda"));
  m_refActionGroup->add(Gtk::Action::create("About", Gtk::Stock::ABOUT), sigc::mem_fun(*this, &VentanaTrabajo::about));

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  window->add_accel_group(m_refUIManager->get_accel_group());

  //etiquetas menu
  Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='ArchivoMenu'>"
        "      <menuitem action='Nuevo'/>"
	"      <menuitem action='Abrir'/>"
        "      <separator/>"
        "      <menuitem action='Guardar'/>"
        "      <menuitem action='Guardar como...'/>"
        "      <separator/>"
        "      <menuitem action='Salir'/>"
	"    </menu>"
        "    <menu action='EditarMenu'>"
        "      <menuitem action='RotarD 90'/>"
        "      <menuitem action='RotarI 90'/>"
        "      <menuitem action='Borrar'/>"
        "    </menu>"
        "    <menu action='SimularMenu'>"
        "      <menuitem action='Simular'/>"
        "      <menuitem action='Tablas'/>"
        "    </menu>"
        "    <menu action='AyudaMenu'>"
        "      <menuitem action='About'/>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

  m_refUIManager->add_ui_from_string(ui_info);

  Gtk::Widget* pMenubar= m_refUIManager->get_widget("/MenuBar");

  Gtk::HBox* boxMenuBar;
  refXml->get_widget("hbox_menubar", boxMenuBar);
  boxMenuBar->add(*pMenubar);
}

void VentanaTrabajo::nuevo() {

  controlador->crearNuevaVentana();
}

void VentanaTrabajo::abrir() {

  filechooserdialog_open->run();
}

void VentanaTrabajo::guardar() {

  std::cout << "Se apreto boton guardar" << std::endl;
}

void VentanaTrabajo::guardarComo() {

  filechooserdialog_saveas->run();
}


void VentanaTrabajo::cerrar() {

  controlador->cerrarVentana(id);
  window->hide();
}

void VentanaTrabajo::rotar90D() {

  std::cout << "Se apreto boton rotar 90 derecha" << std::endl;
}

void VentanaTrabajo::rotar90I() {

  std::cout << "Se apreto boton rotar 90 izquierda" << std::endl;
}

void VentanaTrabajo::borrar() {

  std::cout << "Se apreto boton borrar" << std::endl;
}

void VentanaTrabajo::simular() {

  std::cout << "Se apreto boton simular" << std::endl;
}

void VentanaTrabajo::verTablas() {

  std::cout << "Se apreto boton ver tablas" << std::endl;
}

void VentanaTrabajo::about() {

  Gtk::AboutDialog* about;
  refXml->get_widget("aboutdialog", about);
  about->run();
  about->hide();
}

/**TOOLBAR**/
void VentanaTrabajo::loadToolBar() {

}

/**FILECHOOSERDIALOG**/
void VentanaTrabajo::on_response_open(int response_id) {

  switch(response_id) {
    case Gtk::RESPONSE_ACCEPT: {
      std::cout << "checkear open" << std::endl;
    }
      break;
    default:
        filechooserdialog_open->hide();
      break;
  }
}

void VentanaTrabajo::on_response_saveas(int response_id) {

  switch(response_id) {
    case Gtk::RESPONSE_ACCEPT: {
      std::cout << "checkear save as" << std::endl;
    }
      break;
    default:
        filechooserdialog_saveas->hide();
      break;
  }
}
