#include "VentanaTrabajo.h"

VentanaTrabajo::VentanaTrabajo(Controlador *controlador, ControladorVentana *controladorV, unsigned int id) {

  try {
    this->refXml= Gtk::Builder::create_from_file(PATH_VISTA);
  } catch(const Gtk::BuilderError &be) {
    std::cerr << "Gtk::BuilderError code:" << be.code() << std::endl;
  } catch(const Glib::FileError &fe) {
    std::cerr << "Glib::FileError code:" << fe.code() << std::endl;
  } catch(const Glib::MarkupError &me) {
    std::cerr << "Glib::MarkupError code:" << me.code() << std::endl;
  }

  areaDibujo= new AreaDibujo(this);
  this->controlador= controlador;
  this->controladorVentana= controladorV;
  this->id= id;
}

VentanaTrabajo::~VentanaTrabajo() {

  delete areaDibujo;
};

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
  name+= NOMBRE_CIRCUITO;
  name+= Util::intToString(id);
  name+= NOMBRE_PROGRAMA;
  window-> set_title(name);

  //Area de Dibujo
  Gtk::VBox* vbox_drawing_area;
  refXml->get_widget("vbox_drawing_area", vbox_drawing_area);
  vbox_drawing_area->add(*areaDibujo);

  //Menu Bar
  loadMenuBar(window);

  //Tool Bar
  loadToolBar();

  //FilechooserDialog Open
  refXml->get_widget("filechooserdialog_open", filechooserdialog_open);
  filechooserdialog_open->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_response_open));

  //FilechooserDialog Save as
  refXml->get_widget("filechooserdialog_saveas", filechooserdialog_saveas);
  filechooserdialog_saveas->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_response_saveas));

  //Dialog Servidor
  refXml->get_widget("dialog_servidor", dialog_servidor);
  dialog_servidor->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_response_servidor));
  refXml->get_widget("messagedialog_servidor", dialog_message);
  refXml->get_widget("messagedialog_error_servidor", messagedialog_error_servidor);
  messagedialog_error_servidor->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_error_servidor));
  refXml->get_widget("dialog_lista_circuitos", dialog_lista_circuitos);
  dialog_lista_circuitos->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_lista_circuitos));

  //Treeview Circuitos
  Glib::RefPtr<Glib::Object> obj_treeView_circuitos= refXml->get_object("treeview_circuitos");
  treeView_circuitos= Glib::RefPtr<Gtk::TreeView>::cast_static(obj_treeView_circuitos);
  Glib::RefPtr<Glib::Object> obj_treeModel_circuitos= refXml->get_object("liststore_circuitos");
  treeModel_circuitos= Glib::RefPtr<Gtk::ListStore>::cast_static(obj_treeModel_circuitos);
  refTreeSelection= treeView_circuitos->get_selection();

  //Propiedades
  refXml->get_widget("dialog_propiedades", dialog_propiedades);
  dialog_propiedades->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_propiedades));

  //Ventana Impresion
  loadVentanaImpresion();

  window->show_all();

  if(primeraVez)
    Gtk::Main::run(*window);
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
  m_refActionGroup->add(Gtk::Action::create("Imprimir", Gtk::Stock::PRINT),
                        sigc::mem_fun(*this, &VentanaTrabajo::imprimir));
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
    "      <menuitem action='Imprimir'/>"
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
    "    </menu>"
    "    <menu action='AyudaMenu'>"
    "      <menuitem action='About'/>"
    "    </menu>"
    "  </menubar>"
    "</ui>";
  m_refUIManager->add_ui_from_string(ui_info);

  //Obtenemos el menu
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

  areaDibujo->rotarSeleccion90Derecha();
}

void VentanaTrabajo::rotar90I() {

  areaDibujo->rotarSeleccion90Izquierda();
}

void VentanaTrabajo::borrar() {

  areaDibujo->borrarSeleccion();
}

void VentanaTrabajo::simular() {

  std::cout << "Se apreto boton simular" << std::endl;
}

void VentanaTrabajo::about() {

  Gtk::AboutDialog* about;
  refXml->get_widget("aboutdialog", about);
  if(about) {
    about->run();
    about->hide();
  }
}

/**TOOLBAR**/
void VentanaTrabajo::loadButtonDrag(Gtk::ToolButton *button, std::string tipo, std::string path) {

  if(button) {
    //le seteo un drag window
    button->set_use_drag_window(true);
    button->drag_source_set(listTargets);
    button->drag_unhighlight();
    //le conecto la señal de drag
    button->signal_drag_data_get().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &VentanaTrabajo::on_drag_data_get), tipo));
    //creo icono para el drag
    Glib::RefPtr<Gdk::Pixbuf> pixbuf= Gdk::Pixbuf::create_from_file(path);
    if(pixbuf)
      button->drag_source_set_icon(pixbuf);
  }
}

void VentanaTrabajo::loadToolBar() {

  listTargets.push_back(Gtk::TargetEntry("STRING"));
  listTargets.push_back(Gtk::TargetEntry("text/plain"));

  //la barra de herramientas es una zona drag
  refXml->get_widget("and", bAnd);
  loadButtonDrag(bAnd, AND, PATH_AND);

  refXml->get_widget("or", bOr);
  loadButtonDrag(bOr, OR, PATH_OR);

  refXml->get_widget("not", bNot);
  loadButtonDrag(bNot, NOT, PATH_NOT);

  refXml->get_widget("xor", bXor);
  loadButtonDrag(bXor, XOR, PATH_XOR);

  refXml->get_widget("buffer", bBuffer);
  loadButtonDrag(bBuffer, BUFFER, PATH_BUFFER);

  refXml->get_widget("conexion", bConexion);
  if(bConexion) {
    bConexion->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_clicked_conexion));
  }

  refXml->get_widget("i/o", bIO);
  loadButtonDrag(bIO, IO, PATH_IO);

  refXml->get_widget("circuito", bCircuito);
  loadButtonDrag(bCircuito, CIRCUITO, PATH_CIRCUITO);

  refXml->get_widget("imprimir", bImprimir);
  if(bImprimir)
    bImprimir->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::imprimir));
}

void VentanaTrabajo::on_drag_data_get(
        const Glib::RefPtr<Gdk::DragContext>& context,
        Gtk::SelectionData& selection_data, guint info, guint time, Glib::ustring componente) {

  const std::string str= componente;

  if(componente.compare(CIRCUITO) == 0)
    ventanaServidor();
  selection_data.set(selection_data.get_target(), 8, (const guchar*)str.c_str(), str.length());
}

/**FILECHOOSERDIALOG**/
void VentanaTrabajo::on_response_open(int response_id) {

  switch(response_id) {
    case Gtk::RESPONSE_ACCEPT: {
      std::cout << "checkear open" << std::endl;
      Glib::ustring file= filechooserdialog_open->get_filename();
      std::cout << "File: " << file << std::endl;
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
      Glib::ustring file= filechooserdialog_saveas->get_filename();
      controladorVentana->guardar(file);
      filechooserdialog_saveas->hide();
    }
      break;
    default:
        filechooserdialog_saveas->hide();
      break;
  }
}


/**IMPRESION**/
void VentanaTrabajo::loadVentanaImpresion() {

  //ventana impresion
 // Glib::RefPtr<Glib::Object> obj_window_print= refXml->get_object("window_print");
  //window_print= dynamic_cast<VentanaImpresion>(obj_window_print);

  refXml->get_widget("window_print", window_print);

  //cargo las señales de cada boton
  Gtk::Button *button_print_cancel;
  refXml->get_widget("button_print_cancel", button_print_cancel);
  button_print_cancel->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::cerrarVentanaImpresion));

}

void VentanaTrabajo::on_clicked_conexion() {

  areaDibujo->dibujarConexion();
}

void VentanaTrabajo::ventanaServidor() {

  if(dialog_servidor) {
    dialog_servidor->set_sensitive(true);
    dialog_servidor->run();
  }
}


void VentanaTrabajo::on_response_servidor(int response_id) {

  switch(response_id) {
    case Gtk::RESPONSE_ACCEPT: {
      Gtk::Entry *entry;
      refXml->get_widget("entry_servidor", entry);
      Glib::ustring servidor= entry->get_text();
      std::cout << "Servidor: " << servidor << std::endl;
      refXml->get_widget("entry_puerto", entry);
      Glib::ustring puerto= entry->get_text();
      std::cout << "Puerto: " << puerto << std::endl;
      dialog_servidor->set_sensitive(false);

      dialog_message->show();
      dialog_message->set_message("Conectandose al servidor...");

      std::list<std::string> lista;
      lista.push_back("Hola");
      recibirListaCircuitos(lista);
    }
      break;
    default:
      dialog_servidor->hide();
      break;
  }
}

void VentanaTrabajo::imprimir() {

  if(window_print)
    window_print->show();
}

void VentanaTrabajo::cerrarVentanaImpresion() {

  if(window_print)
    window_print->hide();
}

void VentanaTrabajo::recibirListaCircuitos(std::list<std::string> lista) {

  if(!lista.empty()) {
    treeModel_circuitos->clear();
    agregarCircuito("Master", 4, 5);
    agregarCircuito("Slave", 10, 7);
    dialog_message->hide();
    dialog_servidor->hide();
    dialog_lista_circuitos->show();


  } else {
    dialog_message->hide();
    dialog_servidor->set_sensitive(true);
    if(messagedialog_error_servidor) {
      messagedialog_error_servidor->set_message("Error al conectar el servidor");
      messagedialog_error_servidor->show();
    }
  }
}

void VentanaTrabajo::on_error_servidor(int response_id) {

  messagedialog_error_servidor->hide();
}

void VentanaTrabajo::on_lista_circuitos(int response_id) {

  switch(response_id) {
    case Gtk::RESPONSE_ACCEPT: {
      Gtk::TreeModel::iterator iter= refTreeSelection->get_selected();
      if(iter) {
        Gtk::TreeModel::Row row= *iter;
        Glib::ustring circuito= row[columns_circuito.col_circuito];
        int entradas= row[columns_circuito.col_entradas];
        int salidas= row[columns_circuito.col_salidas];
        dialog_lista_circuitos->hide();
        areaDibujo->dibujarCircuito(entradas, salidas);
      }
    }
      break;
    default:
      dialog_lista_circuitos->hide();
      break;
  }
}


void VentanaTrabajo::agregarCircuito(std::string circuito, int i, int o) {

  Gtk::TreeModel::Row row= *(treeModel_circuitos->append());
  row[columns_circuito.col_circuito]= circuito;
  row[columns_circuito.col_entradas]= i;
  row[columns_circuito.col_salidas]= o;
}

/**PROPIEDADES**/
void VentanaTrabajo::on_propiedades(int response_id) {

  switch(response_id) {
    case Gtk::RESPONSE_ACCEPT: {
      Gtk::Entry *entry;
      refXml->get_widget("entry_nombre_prop", entry);
      Glib::ustring nombre= entry->get_text();
      areaDibujo->seleccionado->setNombre(nombre);
      refXml->get_widget("entry_tiempo_prop", entry);
      Glib::ustring tiempo= entry->get_text();
      areaDibujo->seleccionado->setTiempoT(tiempo);
      dialog_propiedades->hide();
      areaDibujo->redibujar();
    }
      break;
    default:
      dialog_propiedades->hide();
      break;
  }
}
