#ifndef VENTANAIMPRESION_H_
#define VENTANAIMPRESION_H_

#include <gtkmm/window.h>
#include <gtkmm/printoperation.h>


class VentanaImpresion: public Gtk::Window {

private:
  void build_main_menu();
  void print_or_preview(Gtk::PrintOperationAction print_action);
 //void on_printoperation_status_changed(const Glib::RefPtr<CustomPrintOperation>& operation);
 //void on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<CustomPrintOperation>& operation);


  //Printing-related objects:
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
  Glib::RefPtr<Gtk::PrintSettings> m_refSettings;

public:
  ~VentanaImpresion() { };

  //Action signal handlers:
  void on_menu_file_page_setup();
  void on_menu_file_print_preview();
  void on_menu_file_print();
};

#endif /* VENTANAIMPRESION_H_ */
