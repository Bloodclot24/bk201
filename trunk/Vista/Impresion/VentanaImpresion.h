#ifndef VENTANAIMPRESION_H_
#define VENTANAIMPRESION_H_

#include "Impresora.h"
#include <memory>
#include <vector>
#include <pangomm.h>
#include <gtkmm/window.h>
#include <gtkmm/printoperation.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>

class PrintFormOperation;


class VentanaImpresion: public Gtk::Window {

private:
co //Printing-related objects:
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
  Glib::RefPtr<Gtk::PrintSettings> m_refSettings;

  //Child widgets:
  Gtk::HBox hBox;
  Gtk::VBox vBox;
  Gtk::Button btnQuit;
  Gtk::Button btnPageSetup;
  Gtk::Button btnPrintPreview;
  Gtk::Button btnPrint;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

  void build_main_menu();
  void print_or_preview(Gtk::PrintOperationAction print_action);
  void on_printoperation_status_changed(const Glib::RefPtr<CustomPrintOperation>& operation);
  void on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<CustomPrintOperation>& operation);

  //Action signal handlers:
  void on_menu_file_page_setup();
  void on_menu_file_print_preview();
  void on_menu_file_print();
  void on_menu_file_quit();


public:
  VentanaImpresion();
  ~VentanaImpresion() { };
};

#endif /* VENTANAIMPRESION_H_ */
