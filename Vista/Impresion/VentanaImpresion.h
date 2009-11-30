#ifndef VENTANAIMPRESION_H_
#define VENTANAIMPRESION_H_

#include "Impresora.h"
#include <memory>
#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/printoperation.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/pagesetup.h>
#include <gtkmm/printsettings.h>
#include <gtkmm/scrolledwindow.h>
#include <iostream>

#define PATH_LOGO "Vista/Imagenes/logo.png"

class Impresora;
class PrintFormOperation;


/**
 * Clase que dibuja la ventana de impresion y a su vez
 * permite interactuar con las systemcall para setear
 * las propiedades de impresion.
 *
 */
class VentanaImpresion: public Gtk::Window {

private:
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup2;
  Glib::RefPtr<Gtk::PrintSettings> m_refSettings;

  //Atributos para la vista de la ventana de impresion
  Gtk::HBox hBox;
  Gtk::VBox vBox;
  Gtk::Button btnQuit;
  Gtk::Button btnPageSetup;
  Gtk::Button btnPrintPreview;
  Gtk::Button btnPrint;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

  //Señales.
  void build_main_menu();
  void print_or_preview(Gtk::PrintOperationAction print_action);
  void on_printoperation_status_changed(const Glib::RefPtr<Impresora>& operation);
  void on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<Impresora>& operation);

  void on_menu_file_page_setup();
  void on_menu_file_print_preview();
  void on_menu_file_print();
  void on_menu_file_quit();

  std::list<Dibujo*> dibujos;
  Tabla* tabla;
  
public:
  VentanaImpresion();

  /**
   * Setea la lista de dibujos a imprimir.
   *
   * @param dibujos La lista de dibujos que van a imprimirse.
   *
   */
  void setDibujosAImprimir(std::list<Dibujo*> dibujos);

  /**
   * Setea la tabla a imprimir.
   *
   * @param tabla La tabla que va a imprimirse.
   */
  void setTablasAImprimir(Tabla* tabla);

  ~VentanaImpresion() { };
};

#endif /* VENTANAIMPRESION_H_ */
