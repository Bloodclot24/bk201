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
	set_n_pages(2);
}

void Impresora::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int numeroPagina)
{
	double width = print_context->get_width();
	double height = print_context->get_height();

	if(!tabla && !dibujos.size()){ 
		std:: cerr << "Error al imprimir!!! " << std::endl;
		//#warning "Ver El Manejo De Errores Si Llega A Ser Posible Este Error En Impresora";
		return;
	}
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
	cairo_ctx->set_line_width(1);
	cairo_ctx->set_source_rgb(1.0, 0, 0);
	Glib::RefPtr<Gtk::PageSetup> pageSetup= get_default_page_setup();
	double widthPaper = pageSetup->get_paper_width(Gtk::UNIT_INCH); //printSettings->get_paper_width(Gtk::UNIT_INCH);
	double heightPaper = pageSetup->get_paper_height(Gtk::UNIT_INCH);//printSettings->get_paper_height(Gtk::UNIT_INCH);
	double scaleW = 1.0;
	double scaleH = 1.0;
	double scale = 0.0;
	//Paso a INCH el ancho y el alto del print_context
	std::cout << "width en pixels: " << width << std::endl;
	std::cout << "height en pixels: " << height << std::endl;

	width = (double) (width / print_context->get_dpi_x());
	height = (double) (height / print_context->get_dpi_y());

	std::cout << "puntos por pulgada en x: " << print_context->get_dpi_x() << std::endl;

	std::cout << "puntos por pulgada en y: " << print_context->get_dpi_y() << std::endl;

	if(width > widthPaper) scaleW = (double)( widthPaper / (width * 100.0)/*width / widthPaper*/);
	if(height > heightPaper) scaleH = (double)( heightPaper / (height * 100.0)/*height / heightPaper*/);
	
	std::cout << "width!!! : " << width << std::endl;
	std::cout << "height!!! : " << height << std::endl;

	std::cout << "widthP!!! : " << widthPaper << std::endl;
	std::cout << "heightP!!! : " << heightPaper << std::endl;

	std::cout << "scaleW!!! : " << scaleW << std::endl;
	std::cout << "scaleH!!! : " << scaleH << std::endl;

	if(scaleW || scaleH){
	  if (scaleW > scaleH) scale = scaleW;
	  else scale = scaleH;
	  std::cout << "Escalo!!! : " << (double)scale/100.0 << std::endl;
	  std::cout << "SH!!! : " << scaleH/100.0 << std::endl;
	  std::cout << "SW!!! : " << scaleW/100.0 << std::endl;
	}
	if(numeroPagina == 0){
		if(dibujos.size()){
			//En caso de que haya algun elemento seleccionado,
			//antes de imprimir los deselecciono todos.
			std::list<Dibujo*>::iterator it;
			for(it= dibujos.begin(); it != dibujos.end(); it++) {
				(*it)->deseleccionar();
				cairo_ctx->scale(scaleW,scaleH);//0.5,0.5);
				//roto respecto el centro de la imagen
				Vertice vCentro= (*it)->getVerticeCentro();
				cairo_ctx->translate(vCentro.x, vCentro.y);
				cairo_ctx->rotate_degrees((*it)->getAngulo());
				cairo_ctx->translate(-vCentro.x, -vCentro.y);
				(*it)->dibujarImpresion(cairo_ctx);
				cairo_ctx->set_identity_matrix();
			}
		}
	}else{
		if(tabla){

		cairo_ctx->scale(scaleW,scaleH);
		tabla->dibujarTabla(cairo_ctx);
		}
	}
	
}

bool Impresora::on_my_paginate(const Glib::RefPtr<Gtk::PrintContext>& context){

	return true;
}

