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

  //La aplicacion siempre imprime en 2 hojas diferentes,
  //si tiene tanto la tabla como el circuito para imprimir
  //en caso contrario, imprime en una sola pagina lo que posea.
  //Para poder imprimir en 2 paginas, tanto la tabla como el
  //circuito son escalados para que entren dentro de la pagina.
	if(tabla->entradas && dibujos.size()) set_n_pages(2);
  else set_n_pages(1);
}

void Impresora::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int numeroPagina)
{
  double width = print_context->get_width();
  double height = print_context->get_height();

  if(!tabla && !dibujos.size()){ 
    std:: cerr << "Error al imprimir!!! " << std::endl;
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

  //Obtengo el ancho y el alto de los dibujos
  //que van a imprimirse.
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
  //Paso a INCH
  anchoCtx /= print_context->get_dpi_x();
  altoCtx /= print_context->get_dpi_y();

  //Calculo el factor de escala.
  scaleW = (double)( widthPaper / (anchoCtx * 100.0));
  scaleH = (double)( heightPaper / (altoCtx * 100.0));
  //Siempre me quedo con el menor.
  if(scaleW>scaleH)
    scaleW=scaleH;
  else
    scaleH=scaleW;

  if(scaleH==0 || scaleW==0){
    scaleW=1.0;
    scaleH=1.0;
  }

  //En la primera pagina, imprimo el circuito
  if(numeroPagina == 0){
    if(dibujos.size()){
      //Obtengo la matriz, para poder recuperarla
      //luego de escalar, por si se habia modificado
      //la orientacion de la pagina.
      Cairo::Matrix matrix;
      cairo_ctx->get_matrix(matrix);
						
      std::list<Dibujo*>::iterator it;
      for(it= dibujos.begin(); it != dibujos.end(); it++) {
    	  //En caso de que haya algun elemento seleccionado,
    	  //antes de imprimir los deselecciono todos.

    	  (*it)->deseleccionar();
    	  //Aplico el escalado
	cairo_ctx->scale(scaleW,scaleH);
			

	//roto respecto el centro de la imagen
	Vertice vCentro= (*it)->getVerticeCentro();
	cairo_ctx->translate(vCentro.x-xMin, vCentro.y-yMin);
	cairo_ctx->rotate_degrees((*it)->getAngulo());
	cairo_ctx->translate(-vCentro.x, -vCentro.y);
	(*it)->dibujarImpresion(cairo_ctx);
	cairo_ctx->set_identity_matrix();
	//Seteo la matriz que antes habia obtenido.
	cairo_ctx->set_matrix(matrix);
      }
    }
  }else{
    if(tabla){
      //Paso a INCH
    	double ancho = tabla->getAncho()/print_context->get_dpi_x();
      double alto = tabla->getAlto()/print_context->get_dpi_y();
      //Calculo el factor de escala.
      scaleW = (double)(widthPaper / (ancho * 100.0));
      scaleH = (double)(heightPaper/ (alto * 100.0));
      //Siempre me quedo con el menor.
      if(scaleW>scaleH)
	scaleW=scaleH;
      else
	scaleH=scaleW;


      if(scaleH!=0&&scaleW!=0)
    	  //escalo
    	  cairo_ctx->scale(scaleW,scaleH);
      tabla->dibujarTabla(cairo_ctx);
		
    }
 	
  }

}
