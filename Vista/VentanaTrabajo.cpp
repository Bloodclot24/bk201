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
  tabla= new Tabla();
  circuitoRemoto= new DibujoCircuitoRemoto();
  this->controlador= controlador;
  this->controladorVentana= controladorV;
  controladorV->setAreaDibujo(areaDibujo);
  this->id= id;
  window_print= new VentanaImpresion(this);
}

VentanaTrabajo::~VentanaTrabajo() {
  delete areaDibujo;
  delete tabla;
  delete circuitoRemoto;
  delete window_print;
  delete controladorVentana;
};

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

  //Tabla
  Gtk::Viewport* viewport_tabla;
  refXml->get_widget("viewport_tabla", viewport_tabla);
  viewport_tabla->add(*tabla);

  //Circuito Remoto
  refXml->get_widget("window_remoto", window_remoto);
  Gtk::ScrolledWindow *scrolledwindow_remoto;
  refXml->get_widget("scrolledwindow_remoto", scrolledwindow_remoto);
  scrolledwindow_remoto->add(*circuitoRemoto);
  Gtk::Button *button_cerrar_remoto;
  refXml->get_widget("button_cerrar_remoto", button_cerrar_remoto);
  button_cerrar_remoto->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::cerrar_circuito_remoto));
  window_remoto->signal_delete_event().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_delete_event_remoto));

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
  refXml->get_widget("dialog_conectandose", dialog_conectandose);
  refXml->get_widget("dialog_lista_circuitos", dialog_lista_circuitos);
  dialog_lista_circuitos->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_lista_circuitos));

  //Treeview Circuitos
  Glib::RefPtr<Glib::Object> obj_treeView_circuitos= refXml->get_object("treeview_circuitos");
  treeView_circuitos= Glib::RefPtr<Gtk::TreeView>::cast_static(obj_treeView_circuitos);
  Glib::RefPtr<Glib::Object> obj_treeModel_circuitos= refXml->get_object("liststore_circuitos");
  treeModel_circuitos= Glib::RefPtr<Gtk::ListStore>::cast_static(obj_treeModel_circuitos);
  refTreeSelection= treeView_circuitos->get_selection();

  //Propiedades
  refXml->get_widget("dialog_prop_compuerta", dialog_prop_compuerta);
  dialog_prop_compuerta->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_propiedades_compuerta));
  refXml->get_widget("dialog_prop_io", dialog_prop_io);
  dialog_prop_io->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_propiedades_io));
  refXml->get_widget("dialog_prop_circuito", dialog_prop_circuito);
  dialog_prop_circuito->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_propiedades_circuito));

  //Teclado
  window->signal_key_press_event().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_key_press_event));

  //Ventana Examinar
  refXml->get_widget("dialog_examinar", dialog_examinar);
  refXml->get_widget("dialog_error_examinar", dialog_error_examinar);
  dialog_error_examinar->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_error_examinar));


  //Dialog de error servidor
  refXml->get_widget("dialog_error_servidor", dialog_error_servidor);
  dialog_error_servidor->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_error_servidor));

  //Ventana simulando
  refXml->get_widget("dialog_simulando", dialog_simulando);

  //Dialog de error simulando
  refXml->get_widget("dialog_error_simulando", dialog_error_simulando);
  dialog_error_simulando->signal_response().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_error_simulando));
  refXml->get_widget("label_error_simulando", label_error_simulando);

  window->show_all();

  if(primeraVez)
    Gtk::Main::run(*window);
}

bool VentanaTrabajo::on_delete_event(GdkEventAny *event) {
  cerrar();
  return(false);
}

/***************************/
/*** MENUBAR ***/
/***************************/
void VentanaTrabajo::loadMenuBar(Gtk::Window *window) {
  //crea las acciones del menu bar
  m_refActionGroup= Gtk::ActionGroup::create();
  m_guardar= Gtk::ActionGroup::create();

  //menu archivo
  m_refActionGroup->add(Gtk::Action::create("ArchivoMenu", "Archivo"));
  m_refActionGroup->add(Gtk::Action::create("Nuevo", Gtk::Stock::NEW),
                        sigc::mem_fun(*this, &VentanaTrabajo::nuevo));
  m_refActionGroup->add(Gtk::Action::create("Abrir", Gtk::Stock::OPEN),
                        sigc::mem_fun(*this, &VentanaTrabajo::abrir));
  m_guardar->add(Gtk::Action::create("Guardar", Gtk::Stock::SAVE),
		 sigc::mem_fun(*this, &VentanaTrabajo::guardar));
  m_refActionGroup->add(Gtk::Action::create("Guardar como...", Gtk::Stock::SAVE_AS, "Guardar como..."),
                        sigc::mem_fun(*this, &VentanaTrabajo::guardarComo));
  m_refActionGroup->add(Gtk::Action::create("Imprimir", Gtk::Stock::PRINT),
                        sigc::mem_fun(*this, &VentanaTrabajo::imprimir));
  m_refActionGroup->add(Gtk::Action::create("Salir", Gtk::Stock::QUIT),
                        sigc::mem_fun(*this, &VentanaTrabajo::cerrar));

  //menu editar
  m_rotar= Gtk::ActionGroup::create();
  m_invertir= Gtk::ActionGroup::create();
  m_examinar= Gtk::ActionGroup::create();
  m_borrar= Gtk::ActionGroup::create();
  m_refActionGroup->add(Gtk::Action::create("EditarMenu", "Editar"));
  m_rotar->add(Gtk::Action::create("RotarD 90", Gtk::Stock::REDO,"Rotar 90"),
	       sigc::mem_fun(*this, &VentanaTrabajo::rotar90D));
  m_rotar->add(Gtk::Action::create("RotarI 90", Gtk::Stock::UNDO,"Rotar 90"),
	       sigc::mem_fun(*this, &VentanaTrabajo::rotar90I));
  m_invertir->add(Gtk::Action::create("InvertirV", Gtk::Stock::GO_UP,"Invertir Vertical"),
		  sigc::mem_fun(*this, &VentanaTrabajo::invertirVertical));
  m_invertir->add(Gtk::Action::create("InvertirH", Gtk::Stock::GO_DOWN,"Invertir Horizontal"),
		  sigc::mem_fun(*this, &VentanaTrabajo::invertirHorizontal));
  m_examinar->add(Gtk::Action::create("Examinar", Gtk::Stock::FIND, "Examinar..."),
		  sigc::mem_fun(*this, &VentanaTrabajo::examinar));
  m_borrar->add(Gtk::Action::create("Borrar", Gtk::Stock::DELETE),
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
  m_refUIManager->insert_action_group(m_guardar);
  m_refUIManager->insert_action_group(m_rotar);
  m_refUIManager->insert_action_group(m_invertir);
  m_refUIManager->insert_action_group(m_examinar);
  m_refUIManager->insert_action_group(m_borrar);

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
    "    <menuitem action='InvertirV'/>"
    "    <menuitem action='InvertirH'/>"
    "    <menuitem action='Examinar'/>"
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
  m_guardar->set_sensitive(false);
  setSensitiveEditar(false);
}

void VentanaTrabajo::setSensitiveEditar(bool tipo) {
  m_rotar->set_sensitive(tipo);
  m_invertir->set_sensitive(tipo);
  m_examinar->set_sensitive(tipo);
  m_borrar->set_sensitive(tipo);
}

void VentanaTrabajo::nuevo() {
  controlador->crearNuevaVentana();
}

void VentanaTrabajo::abrir() {
  filechooserdialog_open->run();
}

void VentanaTrabajo::guardar() {
  controladorVentana->guardar();
}

void VentanaTrabajo::habilitarGuardar() {
  m_guardar->set_sensitive(true);
}

void VentanaTrabajo::guardarComo() {
  filechooserdialog_saveas->run();
}

void VentanaTrabajo::cerrar() {
  controlador->cerrarVentana(id);
  window->hide();
}

void VentanaTrabajo::invertirHorizontal() {
  areaDibujo->invertirHorizontal();
}

void VentanaTrabajo::invertirVertical() {
  areaDibujo->invertirVertical();
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

void VentanaTrabajo::about() {
  Gtk::AboutDialog* about;
  refXml->get_widget("aboutdialog", about);
  if(about) {
    about->run();
    about->hide();
  }
}

/***************************/
/*** TOOLBAR ***/
/***************************/
void VentanaTrabajo::loadButtonDrag(Gtk::ToolButton *button, std::string tipo, std::string path) {

  if(button) {
    //le seteo un drag window
    button->set_use_drag_window(true);
    button->drag_source_set(listTargets);
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
  loadButtonDrag(bAnd, TIPO_COMPUERTA_AND, PATH_AND);

  refXml->get_widget("or", bOr);
  loadButtonDrag(bOr, TIPO_COMPUERTA_OR, PATH_OR);

  refXml->get_widget("not", bNot);
  loadButtonDrag(bNot, TIPO_COMPUERTA_NOT, PATH_NOT);

  refXml->get_widget("xor", bXor);
  loadButtonDrag(bXor, TIPO_COMPUERTA_XOR, PATH_XOR);

  refXml->get_widget("buffer", bBuffer);
  loadButtonDrag(bBuffer, TIPO_COMPUERTA_BUFFER, PATH_BUFFER);

  refXml->get_widget("conexion", bConexion);
  if(bConexion) {
    bConexion->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::on_clicked_conexion));
  }

  refXml->get_widget("i/o", bIO);
  loadButtonDrag(bIO, TIPO_PIN, PATH_IO);

  refXml->get_widget("circuito", bCircuito);
  loadButtonDrag(bCircuito, TIPO_CIRCUITO, PATH_CIRCUITO);

  refXml->get_widget("imprimir", bImprimir);
  if(bImprimir)
    bImprimir->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::imprimir));

  refXml->get_widget("simular", bSimular);
  if(bSimular)
    bSimular->signal_clicked().connect(sigc::mem_fun(*this, &VentanaTrabajo::simular));
}

void VentanaTrabajo::on_drag_data_get(
				      const Glib::RefPtr<Gdk::DragContext>& context,
				      Gtk::SelectionData& selection_data, guint info, guint time, Glib::ustring componente) {

  const std::string str= componente;

  if(componente.compare(TIPO_CIRCUITO) == 0)
    ventanaServidor();
  selection_data.set(selection_data.get_target(), 8, (const guchar*)str.c_str(), str.length());
}

/***************************/
/*** FILECHOOSERDIALOG ***/
/***************************/
void VentanaTrabajo::on_response_open(int response_id) {

  switch(response_id) {
  case Gtk::RESPONSE_ACCEPT: {
    Glib::ustring file= filechooserdialog_open->get_filename();
    std::cout << "Cargando File: " << file << std::endl;
    areaDibujo->vaciarListaDibujos();
    controladorVentana->cargar(file);
    filechooserdialog_open->hide();
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
    controladorVentana->guardarComo(file);
    filechooserdialog_saveas->hide();
  }
    break;
  default:
    filechooserdialog_saveas->hide();
    break;
  }
}

/***************************/
/*** AREA DIBUJO ***/
/***************************/
void VentanaTrabajo::on_clicked_conexion() {

  areaDibujo->dibujarConexion();
}

void VentanaTrabajo::agregarCircuito(std::string circuito, int i, int o) {

  Gtk::TreeModel::Row row= *(treeModel_circuitos->append());
  row[columns_circuito.col_circuito]= circuito;
  row[columns_circuito.col_entradas]= i;
  row[columns_circuito.col_salidas]= o;
}

void VentanaTrabajo::agregarDibujo(Dibujo *dibujo){
  areaDibujo->agregarDibujo(dibujo);
} 

void VentanaTrabajo::agregarDibujo(ConexionDibujo *dibujo){
  areaDibujo->agregarDibujo(dibujo);
}

/***************************/
/*** CIRCUITO REMOTO ***/
/***************************/
void VentanaTrabajo::cerrar_circuito_remoto() {
  window_remoto->hide();
  window->set_sensitive(true);
}

bool VentanaTrabajo::on_delete_event_remoto(GdkEventAny *event) {
  cerrar_circuito_remoto();
  return true;
}

void VentanaTrabajo::obtenerDatosCircuito(std::string &servidor, std::string &puerto, std::string &nombre) {
  nombre= this->nombre;
  servidor= this->servidor;
  puerto= this->puerto;
}

/***************************/
/*** IMPRESION ***/
/***************************/
void VentanaTrabajo::imprimir() {
  if(window_print){
  	window->set_sensitive(false);
    window_print->setDibujosAImprimir(areaDibujo->dibujos);
    window_print->setTablasAImprimir(tabla);
    window_print->show();
  }
}

/***************************/
/*** TECLADO ***/
/***************************/
bool VentanaTrabajo::on_key_press_event(GdkEventKey* event) {
  if(event->keyval == 65535)
    areaDibujo->borrarSeleccion();
  return true;
}

/***************************/
/*** VENTANA PROPIEDADES ***/
/***************************/
void VentanaTrabajo::prepararVentanaCompuerta(Dibujo *seleccionado) {
  //tomo todos los atributos de la compuerta
  //y los muestro en la ventana de propiedades
  Compuerta *compuerta= dynamic_cast<Compuerta*>(seleccionado);
  std::string label= compuerta->getLabel();
  std::string tiempo= compuerta->getTiempoT();
  Gtk::Entry *entry;
  refXml->get_widget("entry_label_prop_compuertas", entry);
  entry->set_text(label);
  refXml->get_widget("entry_tiempo_prop_compuertas", entry);
  entry->set_text(tiempo);
  //deshabilito la ventana
  window->set_sensitive(false);
  //muestro el dialogo de propiedades
  dialog_prop_compuerta->show();
}

void VentanaTrabajo::on_propiedades_compuerta(int response_id) {
  switch(response_id) {
  case Gtk::RESPONSE_ACCEPT: {
    //tomo todos los atributos de la compuerta y los almaceno
    Compuerta *compuerta= dynamic_cast<Compuerta*>(areaDibujo->dibujoSeleccionados[0]);
    Gtk::Entry *entry;
    refXml->get_widget("entry_label_prop_compuertas", entry);
    Glib::ustring label= entry->get_text();
    compuerta->setLabel(label);
    refXml->get_widget("entry_tiempo_prop_compuertas", entry);
    Glib::ustring tiempo= entry->get_text();
    compuerta->setTiempoT(tiempo);
    areaDibujo->redibujar();
  }
    break;
  default:
    break;
  }
  dialog_prop_compuerta->hide();
  //habilito la ventana
  window->set_sensitive(true);
}

void VentanaTrabajo::prepararVentanaIO(Dibujo *seleccionado) {
  //tomo todos los atributos de la io
  //y los muestro en la ventana de propiedades
  EntradaSalida *io= dynamic_cast<EntradaSalida*>(seleccionado);
  std::string label= io->getLabel();
  std::string tipoPin= io->getTipoPin();
  Gtk::Entry *entry;
  refXml->get_widget("entry_label_prop_io", entry);
  entry->set_text(label);
  Gtk::RadioButton *entrada;
  refXml->get_widget("radiobutton_entrada_io", entrada);
  Gtk::RadioButton *salida;
  refXml->get_widget("radiobutton_salida_io", salida);
  if(tipoPin.compare(TIPO_ENTRADA) == 0)
    entrada->set_active(true);
  else
    entrada->set_active(false);
  //deshabilito la ventana
  window->set_sensitive(false);
  //muestro el dialogo de propiedades
  dialog_prop_io->show();
}

void VentanaTrabajo::on_propiedades_io(int response_id) {

  switch(response_id) {
  case Gtk::RESPONSE_ACCEPT: {
    //tomo todos los atributos de la io y los almaceno
    EntradaSalida *io= dynamic_cast<EntradaSalida*>(areaDibujo->dibujoSeleccionados[0]);
    Gtk::Entry *entry;
    refXml->get_widget("entry_label_prop_io", entry);
    Glib::ustring label= entry->get_text();
    io->setLabel(label);
    Gtk::RadioButton *entrada;
    refXml->get_widget("radiobutton_entrada_io", entrada);
    Gtk::RadioButton *salida;
    refXml->get_widget("radiobutton_salida_io", salida);
    if(entrada->get_active())
      io->setTipoPin(TIPO_ENTRADA);
    else
      io->setTipoPin(TIPO_SALIDA);
    areaDibujo->redibujar();
  }
    break;
  default:
    break;
  }
  dialog_prop_io->hide();
  //habilito la ventana
  window->set_sensitive(true);
}

void VentanaTrabajo::prepararVentanaCircuito(Dibujo *seleccionado) {
  //tomo todos los atributos de la circuito
  //y los muestro en la ventana de propiedades
  CircuitoDibujo *circuito= dynamic_cast<CircuitoDibujo*>(seleccionado);
  std::string label_nombre= circuito->getLabel();
  std::string servidor= circuito->getServidor();
  std::string puerto= circuito->getPuerto();
  Gtk::Entry *entry;
  refXml->get_widget("entry_label_prop_circuito", entry);
  entry->set_text(label_nombre);
  Gtk::Label *label;
  refXml->get_widget("entry_servidor_prop_circuito", label);
  label->set_text(servidor);
  refXml->get_widget("entry_puerto_prop_circuito", label);
  label->set_text(puerto);
  //deshabilito la ventana
  window->set_sensitive(false);
  //muestro el dialogo de propiedades
  dialog_prop_circuito->show();
}

void VentanaTrabajo::on_propiedades_circuito(int response_id) {

  switch(response_id) {
  case Gtk::RESPONSE_ACCEPT: {
    //tomo todos los atributos del circuito y los almaceno
    CircuitoDibujo *circuito= dynamic_cast<CircuitoDibujo*>(areaDibujo->dibujoSeleccionados[0]);
    Gtk::Entry *entry;
    refXml->get_widget("entry_label_prop_circuito", entry);
    Glib::ustring label= entry->get_text();
    circuito->setLabel(label);
    areaDibujo->redibujar();
  }
    break;
  default:
    break;
  }
  dialog_prop_circuito->hide();
  //habilito la ventana
  window->set_sensitive(true);
}

/***************************/
/*** VENTANA EXAMINAR ***/
/***************************/
void VentanaTrabajo::examinar() {
  areaDibujo->verCircuito();
}

void VentanaTrabajo::recibirCircuitoRemoto(const std::string& nombreArchivo, const std::string& nombreCircuito) {
  this->nombreTemp= nombreArchivo;
  this->nombreRemoto= nombreCircuito;
  llegoRemoto= true;
}

void VentanaTrabajo::on_error_examinar(int response_id) {
  window->set_sensitive(true);
  dialog_error_examinar->hide();
}

/***************************/
/*** VENTANA SERVIDOR ***/
/***************************/
void VentanaTrabajo::on_response_servidor(int response_id) {

  switch(response_id) {
  case Gtk::RESPONSE_ACCEPT: {
    Gtk::Entry *entry;
    refXml->get_widget("entry_servidor", entry);
    this->servidor= entry->get_text();
    std::cout << "Servidor: " << servidor << std::endl;
    refXml->get_widget("entry_puerto", entry);
    this->puerto= entry->get_text();
    std::cout << "Puerto: " << puerto << std::endl;
    dialog_servidor->set_sensitive(false);
    dialog_conectandose->show();
    llegoRta= false;
    id_ventana_servidor= Glib::signal_timeout().connect(sigc::mem_fun(*this,&VentanaTrabajo::esperandoRtaServidor), 1000);
    controladorVentana->obtenerListaServidor(servidor, atoi(puerto.c_str()));
  }
    break;
  default:
    dialog_servidor->hide();
    //habilito la ventana
    window->set_sensitive(true);
    break;
  }
}

void VentanaTrabajo::ventanaServidor() {
  if(dialog_servidor) {
    dialog_servidor->set_sensitive(true);
    dialog_servidor->show();
    //deshabilito la ventana
    window->set_sensitive(false);
  }
}

bool VentanaTrabajo::esperandoRtaServidor() {
  if(llegoRta) {
    id_ventana_servidor.disconnect();
    if(!lista_circuito.empty()) {
      treeModel_circuitos->clear();
      std::list<DescripcionCircuito>::const_iterator it;
      for(it=lista_circuito.begin(); it != lista_circuito.end(); it++){
	agregarCircuito((*it).nombre, (*it).cantidadEntradas, (*it).cantidadSalidas);
	std::cout << "Agrego Circuito: " << (*it).nombre << std::endl;
      }
      dialog_conectandose->hide();
      dialog_servidor->hide();
      dialog_lista_circuitos->show();
      //habilito la ventana
      window->set_sensitive(true);
    } else {
      std::cout << "Lista vacía\n";
      dialog_conectandose->hide();
      dialog_servidor->set_sensitive(false);
      if(dialog_error_servidor)
        dialog_error_servidor->show();
    }
  }
  return true;
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
      this->nombre= circuito;
      areaDibujo->dibujarCircuito(entradas, salidas);
    }
  }
    break;
  default:
    dialog_lista_circuitos->hide();
    break;
  }
}

void VentanaTrabajo::recibirListaCircuitos(std::list<DescripcionCircuito> lista) {
  this->lista_circuito= lista;
  this->llegoRta= true;
}

/***************************/
/*** ERROR SERVIDOR ***/
/***************************/
void VentanaTrabajo::on_error_servidor(int response_id) {
  //habilito el dialogo del servidor
  dialog_servidor->set_sensitive(true);
  //cierro el dialogo
  dialog_error_servidor->hide();
}

/***************************/
/*** VENTANA SIMULANDO ***/
/***************************/
void VentanaTrabajo::simular() {
  dialog_simulando->show();
  window->set_sensitive(false);
  llegoTabla= false;
  id_ventana_simulando= Glib::signal_timeout().connect(sigc::mem_fun(*this,&VentanaTrabajo::esperandoRtaSimulacion), 1000);
  controladorVentana->simular();
}

bool VentanaTrabajo::esperandoRtaSimulacion() {
  if(llegoTabla) {
    id_ventana_simulando.disconnect();
    dialog_simulando->hide();
    if(mensajeTabla.size() != 0)
      //Muestro mensaje de error enviado
      mostrarMsjErrorSimulando(mensajeTabla);
    else
      //habilito la ventana
      window->set_sensitive(true);
  }
  return true;
}

void VentanaTrabajo::recibirTablaSimulacion(std::list<uint32_t> listaTabla, int entradas, int salidas, const std::string& mensaje, const std::string& leyenda){
  this->mensajeTabla= mensaje;
  tabla->setCantEntradas(entradas);
  tabla->setCantSalidas(salidas);
  tabla->setLista(listaTabla);
  tabla->setLeyenda(leyenda);
  llegoTabla= true;
}

/***************************/
/*** ERROR SIMULANDO ***/
/***************************/
void VentanaTrabajo::mostrarMsjErrorSimulando(const std::string mensaje) {
  //cargo el mensaje y muestro el dialogo
  label_error_simulando->set_text(mensaje);
  dialog_error_simulando->show();
}

void VentanaTrabajo::on_error_simulando(int response_id) {
  //habilito la ventana
  window->set_sensitive(true);
  //cierro el dialogo
  dialog_error_simulando->hide();
}
