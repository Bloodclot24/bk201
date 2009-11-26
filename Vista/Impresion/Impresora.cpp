#include "Impresora.h"
#include <string>
#include <iostream>

Impresora::Impresora(std::list<Dibujo*> dibujos, Tabla* Tabla)
{
	this->dibujos = dibujos;
	this->tabla = tabla;
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
		//tabla->dibujarTabla(cairo_ctx);
//		if(tabla->entradas != 0 && tabla->salidas != 0) {
//
//		    tabla->ancho= (tabla->entradas+tabla->salidas+1)*TAMANIO+15;
//		    tabla->alto= ((tabla->lista.size()/(tabla->entradas+tabla->salidas+1))+2)*TAMANIO;
//		
//		    cairo_ctx->set_source_rgb(0.0, 0.0, 1.0);
//		    cairo_ctx->set_line_width(1);
//		    //lineas horizontales
//		    for(int j= INICIO_TABLA; j<=(tabla->alto+INICIO_TABLA); j+=TAMANIO) {
//		          cairo_ctx->move_to(INICIO_TABLA, j);
//		          cairo_ctx->line_to(tabla->ancho+INICIO_TABLA, j);
//		    }
//		
//		    //lineas verticales
//		    int contador= 0;
//		    for(int i= INICIO_TABLA; i<=(tabla->ancho+INICIO_TABLA); i+=TAMANIO) {
//		      if(contador == (tabla->entradas+tabla->salidas+1))
//		        i= i+15;
//		      cairo_ctx->move_to(i, INICIO_TABLA);
//		      cairo_ctx->line_to(i, tabla->alto+INICIO_TABLA);
//		      contador++;
//		     }
//		
//		    cairo_ctx->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
//		    cairo_ctx->set_font_size(12);
//		
//		    //indicador
//		    int x= INICIO_TABLA+12;
//		    cairo_ctx->move_to(x, TAMANIO-5);
//		    cairo_ctx->show_text("IN");
//		    x= x + tabla->entradas*TAMANIO - 5;
//		    cairo_ctx->move_to(x, TAMANIO-5);
//		    cairo_ctx->show_text("OUT");
//		    x= x + tabla->salidas*TAMANIO + 5;
//		    cairo_ctx->move_to(x, TAMANIO-5);
//		    cairo_ctx->show_text("Time");
//		
//		    cairo_ctx->set_source_rgb(1.0, 0.0, 0.0);
//		    //titulos
//		    contador= 0;
//		    int dec= 65;
//		    std::string str;
//		    for(int i= INICIO_TABLA+15; i<=tabla->ancho; i+=TAMANIO) {
//		      str= (char)dec;
//		      if(contador == (tabla->entradas+tabla->salidas)) {
//		        i= i-5;
//		        str= "T [ns]";
//		      }
//		      cairo_ctx->move_to(i, 2*TAMANIO-5);
//		      cairo_ctx->show_text(str);
//		      contador++;
//		      dec++;
//		    }
//		
//		    cairo_ctx->set_source_rgb(0.0, 0.0, 0.0);
//		    //datos
//		    contador= 0;
//		    std::list<uint32_t>::iterator it= tabla->lista.begin();
//		    for(int j= 3*TAMANIO-5; j<=(tabla->alto+INICIO_TABLA); j+=TAMANIO) {
//		      for(int i= INICIO_TABLA+15; i<=tabla->ancho; i+=TAMANIO) {
//		        if(contador == (tabla->entradas+tabla->salidas)) {
//		          i= i+8;
//		          contador= 0;
//		        } else
//		          contador++;
//		        cairo_ctx->move_to(i, j);
//		        cairo_ctx->show_text(Util::intToString(*it));
//		        it++;
//		      }
//		    }
//		
//		    cairo_ctx->stroke();
//		  
//		//	}	
//		}	
	}
}