#include "Impresora.h"
#include <string>
#include <iostream>

Impresora::Impresora(std::list<Dibujo*> dibujos, Tabla* Tabla)
{
	if(dibujos.size()){
		this->dibujos = dibujos;
		this->circuito = true;
	}
	if (tabla){
		 this->tabla = tabla;
		 this->circuito = false;
	}
}
	

Glib::RefPtr<Impresora> Impresora::create(std::list<Dibujo*> dibujos, Tabla* tabla)
{
	return Glib::RefPtr<Impresora>(new Impresora(dibujos, tabla));
}

void Impresora::on_begin_print(
        const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
	set_n_pages(1);
}


void Impresora::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int numeroPaginas)
{
//	const double width = print_context->get_width();
//	const double height = print_context->get_height();
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
	//}else{
		//TODO: 
		//Ver si hago Impresora clase friend de tabla o hacemos publico el metodo
		//AMIGAAAAA:P
		//tabla->dibujarTabla(cairo_ctx);
//	}		
}