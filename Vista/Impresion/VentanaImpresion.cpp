#include "VentanaImpresion.h"

//  btnPageSetup.signal_clicked().connect(sigc::mem_fun(*this, &VentanaImpresion::on_menu_file_page_setup));
//  btnPrintPreview.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print_preview));
//  btnPrint.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print));
//  btnQuit.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));


//void ExampleWindow::on_printoperation_status_changed(const Glib::RefPtr<CustomPrintOperation>& operation)
//{
//        if (operation->is_finished())
//        {
//                Gtk::MessageDialog err_dialog(*this, "Print Finished.", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
//                err_dialog.run();
//        }
//}
//
//void ExampleWindow::on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<CustomPrintOperation>& operation)
//{
//  if (result == Gtk::PRINT_OPERATION_RESULT_ERROR)
//  {
//    Gtk::MessageDialog err_dialog(*this, "Error printing form", false,
//            Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
//    err_dialog.run();
//  }
//  else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY)
//  {
//    m_refSettings = operation->get_print_settings();
//  }
//
//  if (! operation->is_finished())
//  {
//    operation->signal_status_changed().connect(sigc::bind(sigc::mem_fun(*this,
//                    &ExampleWindow::on_printoperation_status_changed),
//                operation));
//  }
//}

void VentanaImpresion::print_or_preview(Gtk::PrintOperationAction print_action) {

//  Glib::RefPtr<CustomPrintOperation> print = CustomPrintOperation::create();
//
//  print->set_track_print_status();
//  print->set_default_page_setup(m_refPageSetup);
//  print->set_print_settings(m_refSettings);
//
//  print->signal_done().connect(sigc::bind(sigc::mem_fun(*this,
//                  &ExampleWindow::on_printoperation_done), print));
//  try
//    print->run(print_action /* print or preview */, *this);
//
//  catch (const Gtk::PrintError& ex)
//    std::cerr << "An error occurred while trying to run a print operation:" << ex.what() << std::endl;

}

void VentanaImpresion::on_menu_file_page_setup() {

  Glib::RefPtr<Gtk::PageSetup> new_page_setup = Gtk::run_page_setup_dialog(*this, m_refPageSetup, m_refSettings);
  m_refPageSetup = new_page_setup;
}

void VentanaImpresion::on_menu_file_print_preview() {

  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PREVIEW);
}

void VentanaImpresion::on_menu_file_print() {

  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG);
}
