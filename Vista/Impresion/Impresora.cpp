#include "Impresora.h"
#include <string>
#include <iostream>

Impresora::Impresora(std::list<Dibujo*> dibujos, Tabla* tabla)
{
	this->dibujos = dibujos;
	std::cout << "Tabla: (impresora) " << tabla << std::endl;
	std::cout << "Dibujo (impresora): " << &dibujos << std::endl;
	this->tabla = tabla;
}
	

Glib::RefPtr<Impresora> Impresora::create(std::list<Dibujo*> dibujos, Tabla* tabla)
{
	std::cout << "Tabla (create): " << tabla << std::endl;
	std::cout << "Dibujo (create): " << &dibujos << std::endl;
	return Glib::RefPtr<Impresora>(new Impresora(dibujos, tabla));
}

void Impresora::on_begin_print(
        const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
	//TODO: provisorio, tendria que ser N paginas de acuerdo a la cantidad
	//de lineas a imprimir
//	if(tabla && dibujos.size()) set_n_pages(2);
//	else set_n_pages(1);
	set_n_pages(1);
}

void Impresora::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int numeroPaginas)
{
	const double width = print_context->get_width();
	const double height = print_context->get_height();

	if(!tabla && !dibujos.size()){ 
		std:: cerr << "Error al imprimir!!! " << std::endl;
		//#warning "Ver El Manejo De Errores Si Llega A Ser Posible Este Error En Impresora";
		return;
	}
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
	cairo_ctx->set_line_width(1);
	cairo_ctx->set_source_rgb(1.0, 0, 0);
	Glib::RefPtr<Gtk::PageSetup> pageSetup= get_default_page_setup();
	Glib::RefPtr<Gtk::PrintSettings> printSettings = get_print_settings();//Gtk::PrintSettings::create();
	double widthPaper = pageSetup->get_paper_width(Gtk::UNIT_INCH); //printSettings->get_paper_width(Gtk::UNIT_INCH);
	double heightPaper = pageSetup->get_paper_height(Gtk::UNIT_INCH);//printSettings->get_paper_height(Gtk::UNIT_INCH);
	double scaleW = 0.0;
	double scaleH = 0.0;
	double scale = 0.0;

	if(width > widthPaper) scaleW = (double)( width / widthPaper);
	if(height > heightPaper) scaleH = (double)( height / heightPaper);

	std::cout << "width!!! : " << width << std::endl;
	std::cout << "height!!! : " << height << std::endl;

	std::cout << "widthP!!! : " << widthPaper << std::endl;
	std::cout << "heightP!!! : " << heightPaper << std::endl;

	std::cout << "scaleW!!! : " << scaleW << std::endl;
	std::cout << "scaleH!!! : " << scaleH << std::endl;



//	Glib::RefPtr<Gtk::PrintJob> printjob =	Gtk::PrintJob::create ("LALALA", this, printSettings, pageSetup);
//	Cairo::RefPtr<Cairo::Surface> surface = printjob->get_surface();
	
	Cairo::RefPtr<Cairo::Surface> surface = cairo_ctx->get_target();
	surface->reference();
	
	if(scaleW || scaleH){
	  if (scaleW > scaleH) scale = scaleW;
	  else scale = scaleH;
	  std::cout << "Escalo!!! : " << (double)scale/100.0 << std::endl;
	  std::cout << "SH!!! : " << scaleH << std::endl;
	  std::cout << "SW!!! : " << scaleW << std::endl;
	  printSettings->set_scale(scale);
	  printSettings->set_orientation(Gtk::PAGE_ORIENTATION_LANDSCAPE );
	  set_print_settings(printSettings);
	  cairo_ctx->scale(scaleW/100.0,scaleH/100.0);
	  cairo_ctx->set_source(surface,0.,0.);
	  cairo_ctx->paint();
	  set_default_page_setup(pageSetup);
	}
	
	if(dibujos.size()){
		//En caso de que haya algun elemento seleccionado,
		//antes de imprimir los deselecciono todos.
		std::list<Dibujo*>::iterator it;
    	for(it= dibujos.begin(); it != dibujos.end(); it++) {
			(*it)->deseleccionar();
    	}

		//Dibujo los elementos
		areaDibujo->dibujarComponentes(cairo_ctx,dibujos); 
      	
      	
      	std::cout<< "Dibujando..." << std::endl;
	}
	if(tabla){
//		set_current_page(2);
		tabla->dibujarTabla(cairo_ctx);
	}
}

bool Impresora::on_my_paginate(const Glib::RefPtr<Gtk::PrintContext>& context){

	return true;
}

