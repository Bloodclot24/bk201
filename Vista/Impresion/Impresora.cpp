#include "Impresora.h"
#include <string>
#include <iostream>

Impresora::Impresora(std::list<Dibujo*> dibujos, Tabla* tabla)
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

     if(tabla->entradas && dibujos.size()) set_n_pages(2);
     else set_n_pages(1);
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
     double widthPaper = width;
     double heightPaper = height;
     double scaleW = 1.0;
     double scaleH = 1.0;
     //Paso a INCH el ancho y el alto del print_context

     width = (double) (width / print_context->get_dpi_x());
     height = (double) (height / print_context->get_dpi_y());

     std::list<Dibujo*>::iterator it;
     uint32_t yMax=0,xMax=0;
     uint32_t yMin=(uint32_t)-1,xMin=(uint32_t)-1;

     for(it = dibujos.begin(); it!=dibujos.end();it++){
	  if(yMax < (uint32_t)(*it)->getVerticeSupIzq().y)
	       yMax= (*it)->getVerticeSupIzq().y;
	  if(xMax < (uint32_t)(*it)->getVerticeSupIzq().x)
	       xMax= (*it)->getVerticeSupIzq().x;
	     
	  if(yMin > (uint32_t)(*it)->getVerticeSupIzq().y)
	       yMin = (*it)->getVerticeSupIzq().y;
	  if(xMin > (uint32_t)(*it)->getVerticeSupIzq().x)
	       xMin = (*it)->getVerticeSupIzq().x;

     }
     yMin-=50;
     xMax+=100;
     yMax+=100;


     int anchoCtx = xMax-xMin;
     int altoCtx = yMax-yMin;

     anchoCtx /= print_context->get_dpi_x();
     altoCtx /= print_context->get_dpi_y();


     if(xMax > widthPaper) ;
     scaleW = (double)( widthPaper / (anchoCtx * 100.0));
     if(yMax > heightPaper) ;
     scaleH = (double)( heightPaper / (altoCtx * 100.0));

     if(scaleW>scaleH)
	  scaleW=scaleH;
     else
	  scaleH=scaleW;



     if(numeroPagina == 0){
	  if(dibujos.size()){
	       //En caso de que haya algun elemento seleccionado,
	       //antes de imprimir los deselecciono todos.
	       Cairo::Matrix matrix;
	       cairo_ctx->get_matrix(matrix);
						
	       std::list<Dibujo*>::iterator it;
	       for(it= dibujos.begin(); it != dibujos.end(); it++) {
		    (*it)->deseleccionar();

		    cairo_ctx->scale(scaleW,scaleH);
			

		    //roto respecto el centro de la imagen
		    Vertice vCentro= (*it)->getVerticeCentro();
		    cairo_ctx->translate(vCentro.x-xMin, vCentro.y-yMin);
		    cairo_ctx->rotate_degrees((*it)->getAngulo());
		    cairo_ctx->translate(-vCentro.x, -vCentro.y);
		    (*it)->dibujarImpresion(cairo_ctx);
		    cairo_ctx->set_identity_matrix();
		    cairo_ctx->set_matrix(matrix);
	       }
	  }
     }else{
	  if(tabla){
	       double ancho = tabla->getAncho();
	       double alto = tabla->getAlto();

	       if (ancho > width* print_context->get_dpi_x()){
		    scaleW = (double)(width * print_context->get_dpi_x() / (ancho * 100.0));
	       }
	       if (alto > height* print_context->get_dpi_y()){
		    scaleH = (double)(height * print_context->get_dpi_y() / (alto * 100.0));
	       }


	       cairo_ctx->scale(scaleW,scaleH);
	       tabla->dibujarTabla(cairo_ctx);
		
	  }
 	
     }

}
