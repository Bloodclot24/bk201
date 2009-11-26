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
	set_n_pages(1);
}


void Impresora::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int numeroPaginas)
{
	const double width = print_context->get_width();
	const double height = print_context->get_height();
//	const double x_step = width/100.0;
//	const double y_step = height/100.0;
	if(!tabla && !dibujos.size()){ 
		std:: cerr << "Error al imprimir!!! " << std::endl;
		//#warning "Ver El Manejo De Errores Si Llega A Ser Posible Este Error En Impresora";
		return;
	}
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
	cairo_ctx->set_line_width(1);
	cairo_ctx->set_source_rgb(1.0, 0, 0);
	Glib::RefPtr<Gtk::PrintSettings> printSettings = get_print_settings();//Gtk::PrintSettings::create();
	double widthPaper = printSettings->get_paper_width(Gtk::UNIT_POINTS);
	double heightPaper = printSettings->get_paper_height(Gtk::UNIT_POINTS);
	double scaleW = 0.0;
	double scaleH = 0.0;
	double scale = 0.0;

	if(width > widthPaper) scaleW = width / widthPaper;
	if(height > heightPaper) scaleH = height / heightPaper;

	std::cout << "width!!! : " << width << std::endl;
	std::cout << "height!!! : " << height << std::endl;

	std::cout << "widthP!!! : " << widthPaper << std::endl;
	std::cout << "heightP!!! : " << heightPaper << std::endl;



	if(scaleW || scaleH){
	  if (scaleW > scaleH) scale = scaleW;
	  else scale = scaleH;
	  std::cout << "Escalo!!! : " << (double)100.0/scale << std::endl;
	  std::cout << "SH!!! : " << scaleH << std::endl;
	  std::cout << "SW!!! : " << scaleW << std::endl;
	  printSettings->set_scale(100.0/scale);
	  set_print_settings(printSettings);
	}

	if(dibujos.size()){
	//TODO Ver Manejo Del Flag, si lo pongo funciona solo a veces
	//if(circuito){
		//Dibujo los elementos
    	std::list<Dibujo*>::iterator it;
    	for(it= dibujos.begin(); it != dibujos.end(); it++) {
      		//seteo matriz identidad
      		cairo_ctx->set_identity_matrix();
      		//roto respecto el centro de la imagen
      		Vertice vCentro= (*it)->getVerticeCentro();
      		cairo_ctx->translate(vCentro.x, vCentro.y);
      		cairo_ctx->rotate_degrees((*it)->getAngulo());
      		cairo_ctx->translate(-vCentro.x, -vCentro.y);
      		(*it)->dibujar(cairo_ctx);
      		std::cout<< "Dibujando..." << std::endl;
    	}
	}
	if(tabla){
	//}else{
		//TODO: 
		//Ver si hago Impresora clase friend de tabla o hacemos publico el metodo
		//AMIGAAAAA:P
		tabla->dibujarTabla(cairo_ctx);

	}
}
