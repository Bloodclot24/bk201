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

void VentanaTrabajo::correr(bool primeraVez) {
	
	refXml->get_widget("window", main_window);
  main_window->maximize();

	/*MENUBAR*/
	loadMenuBar(main_window);

 	/*TOOLBAR*/
//	loadToolBar();

	main_window->show();
	
	if(primeraVez)
		Gtk::Main::run();
}

/**MENUBAR**/
void VentanaTrabajo::loadMenuBar(Gtk::Window *main_window) {

	//Create actions for menus and toolbars
  m_refActionGroup = Gtk::ActionGroup::create();

	//File menu:
  m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));

  m_refActionGroup->add(Gtk::Action::create("New", Gtk::Stock::NEW),
                        sigc::mem_fun(*this, &VentanaTrabajo::lala));

  //Help menu:
  m_refActionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
	m_refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT), sigc::mem_fun(*this, &VentanaTrabajo::lala));

	m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  main_window->add_accel_group(m_refUIManager->get_accel_group());

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menuitem action='New'/>"
        "    </menu>"
        "    <menu action='HelpMenu'>"
        "      <menuitem action='HelpAbout'/>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

	m_refUIManager->add_ui_from_string(ui_info);

  Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");

  Gtk::VBox* boxMenuBar;
  refXml->get_widget("vbox_menubar", boxMenuBar);
  boxMenuBar->add(*pMenubar);
}

/**TOOLBAR**/
void VentanaTrabajo::loadToolBar() {

}

void VentanaTrabajo::lala() {
	
	controlador->crearNuevaVentana();
}


void VentanaTrabajo::lala2() {
	
	controlador->cerrarVentana(id);
	main_window->hide();
}
