#include "Impresora.h"
#include <string>

Impresora::Impresora(std::list<Dibujos*> dibujos, Tabla* Tabla)
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
	

Glib::RefPtr<Impresora> Impresora::create(std::list<Dibujos*> dibujos, Tabla* tabla)
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
	if(!tabla || !dibujos.size()){ 
		std:: cerr << "Error al imprimir!!! " << std::endl;
		#warning "Ver El Manejo De Errores Si Llega A Ser Posible Este Error En Impresora";
		return;
	}
	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
	cairo_ctx->set_line_width(1);
	cairo_ctx->set_source_rgb(1.0, 0, 0);

	if(circuito){
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
    	}
	}else{
		//TODO: 
		//Ver si hago Impresora clase friend de tabla o hacemos publico el metodo
		//AMIGAAAAA:P
		//tabla->dibujarTabla();
	}		
//	double x = 0;
//	double y = 0;
//	double x_to = x_step;
//	double y_to = height;
//	for(int i = 0; i < 100 ; ++i)
//	{
//		cairo_ctx->move_to(x, y);
//		cairo_ctx->line_to(x_to, y_to);
//		y += y_step;
//		x_to += x_step;
//	}
//	cairo_ctx->stroke();
//
//	cairo_ctx->set_source_rgb(0, 1.0, 0);
//	x = 0;
//	y = 0;
//	x_to = width;
//	y_to = y_step;
//	for(int i = 0; i < 100 ; ++i)
//	{
//		cairo_ctx->move_to(x, y);
//		cairo_ctx->line_to(x_to, y_to);
//		x += x_step;
//		y_to += y_step;
//	}
//
//	cairo_ctx->stroke();
//
//	cairo_ctx->set_source_rgb(0, 0, 0);
//	cairo_ctx->set_font_size(28.0);
//	std::string text("Taller de Programación - FIUBA");
//	Cairo::TextExtents extents;
//	cairo_ctx->get_text_extents(text, extents);
//	cairo_ctx->move_to (width/2.0 + - extents.x_bearing - extents.width/2, height/2.0);
//	cairo_ctx->show_text(text);
//	cairo_ctx->fill();
}
