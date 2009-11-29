#include "VentanaImpresion.h"
#include <iostream>

VentanaImpresion::VentanaImpresion():btnQuit(Gtk::Stock::QUIT),
									btnPageSetup("Setup"),
									btnPrintPreview("Preview"),
									btnPrint(Gtk::Stock::PRINT){
  std::cout << "SE CREO LA VENTANA!!!!!!" << std::endl;
  m_refPageSetup = Gtk::PageSetup::create();
  m_refSettings = Gtk::PrintSettings::create();

  set_title("BK201 Imprimir");
  set_default_size(400, 300);

  build_main_menu();
  vBox.pack_start(hBox, Gtk::PACK_SHRINK);
  add(vBox);
  show_all_children();
  
}


void VentanaImpresion::build_main_menu()
{
	btnPageSetup.signal_clicked().connect(sigc::mem_fun(*this, &VentanaImpresion::on_menu_file_page_setup));
	btnPrintPreview.signal_clicked().connect(sigc::mem_fun(*this, &VentanaImpresion::on_menu_file_print_preview));
	btnPrint.signal_clicked().connect(sigc::mem_fun(*this, &VentanaImpresion::on_menu_file_print));
	btnQuit.signal_clicked().connect(sigc::mem_fun(*this, &VentanaImpresion::on_menu_file_quit));
	
	hBox.pack_start(btnPageSetup, Gtk::PACK_EXPAND_WIDGET, 20);
	hBox.pack_start(btnPrintPreview, Gtk::PACK_EXPAND_WIDGET, 20);
	hBox.pack_start(btnPrint, Gtk::PACK_EXPAND_WIDGET, 20);
	hBox.pack_start(btnQuit, Gtk::PACK_EXPAND_WIDGET, 20);
}

void VentanaImpresion::on_printoperation_status_changed(const Glib::RefPtr<Impresora>& operation)
{
	if (operation->is_finished())
	{
		Gtk::MessageDialog err_dialog(*this, "Finalizo la impresion", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
		err_dialog.run();
	}
}

void VentanaImpresion::on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<Impresora>& operation)
{
  if (result == Gtk::PRINT_OPERATION_RESULT_ERROR)
  {
    Gtk::MessageDialog err_dialog(*this, "Error al imprimir desde ", false,
            Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    err_dialog.run();
  }
  else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY)
  {
    m_refSettings = operation->get_print_settings();
  }

  if (! operation->is_finished())
  {
    operation->signal_status_changed().connect(sigc::bind(sigc::mem_fun(*this,
                    &VentanaImpresion::on_printoperation_status_changed),
                operation));
  }
}

void VentanaImpresion::print_or_preview(Gtk::PrintOperationAction print_action)
{
	std::cout << "Tabla (preview) " << tabla << std::endl;
  Glib::RefPtr<Impresora> print = Impresora::create(dibujos,tabla);

  print->set_track_print_status();
//  m_refSettings->set_orientation(Gtk::PAGE_ORIENTATION_LANDSCAPE );
  print->set_default_page_setup(m_refPageSetup);
  print->set_print_settings(m_refSettings);

  print->signal_done().connect(sigc::bind(sigc::mem_fun(*this,
                  &VentanaImpresion::on_printoperation_done), print));
  try
  {
    print->run(print_action /* print or preview */, *this);
  }
  catch (const Gtk::PrintError& ex)
  {
    std::cerr << "Ocurrio un error al tratar de ejecutar la operacion de impresion:"
        << ex.what() << std::endl;
  }

}

void VentanaImpresion::on_menu_file_page_setup()
{
  Glib::RefPtr<Gtk::PageSetup> new_page_setup = Gtk::run_page_setup_dialog(*this, m_refPageSetup, m_refSettings);
  m_refPageSetup = new_page_setup;
}

void VentanaImpresion::on_menu_file_print_preview()
{
  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PREVIEW);
}

void VentanaImpresion::on_menu_file_print()
{
  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG);
}

void VentanaImpresion::on_menu_file_quit()
{
  hide();
}

void VentanaImpresion::setDibujosAImprimir(std::list<Dibujo*> dibujos)
{
	this->dibujos = dibujos;
}

void VentanaImpresion::setTablasAImprimir(Tabla* tabla)
{
	this->tabla = tabla;
	
}

  
