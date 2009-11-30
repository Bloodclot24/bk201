#include "Tabla.h"

Tabla::Tabla() {
  this->entradas= 0;
  this->salidas= 0;
  altoLeyenda=0;
}

bool Tabla::on_expose_event(GdkEventExpose* event) {
  //ventana de dibujo
  window= get_window();
  if(window) {
    Gdk::Region region= window->get_update_area();
    Cairo::RefPtr<Cairo::Context> context= window->create_cairo_context();
    context->begin_new_path();
    context->set_line_width(10.0);

    if(event) {
      context->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
      context->clip();
    }

    //dibujo el fondo blanco
    context->set_source_rgb(1.0, 1.0, 1.0);
    context->paint();

    dibujarTabla(context);
  }

  //seteo el largo y ancho del drawing area
  ancho= anchoColumna+2*INICIO_TABLA;
  alto= altoFila+2*INICIO_TABLA+altoLeyenda;
  if(entradas != 0 && salidas != 0)
    set_size_request(ancho, alto);
  
  return false;
}

void Tabla::redibujar() {
  //fuerzo al redibujado
  if(window) {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                     get_allocation().get_height());
    window->invalidate_rect(r, false);
  }
}

void Tabla::dibujarTabla(const Cairo::RefPtr<Cairo::Context>& context) {

  if(entradas != 0 && salidas != 0) {

    anchoColumna= (entradas+salidas+1)*TAMANIO+15;
    altoFila= ((lista.size()/(entradas+salidas+1))+2)*TAMANIO;

    context->set_source_rgb(0.0, 0.0, 1.0);

    context->set_line_width(1);
    int Y=0;
    //lineas horizontales
    for(int j= INICIO_TABLA; j<=(altoFila+INICIO_TABLA); j+=TAMANIO) {
      context->move_to(INICIO_TABLA, j);
      context->line_to(anchoColumna+INICIO_TABLA, j);
      Y=j;
    }

    //lineas verticales
    int contador= 0;
    for(int i= INICIO_TABLA; i<=(anchoColumna+INICIO_TABLA); i+=TAMANIO) {
      if(contador == (entradas+salidas+1))
        i= i+15;
      context->move_to(i, INICIO_TABLA);
      context->line_to(i, altoFila+INICIO_TABLA);
      contador++;
    }

    context->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
    context->set_font_size(12);
    
    //indicador
    int x= INICIO_TABLA+12;
    context->move_to(x, TAMANIO-5);
    context->show_text("IN");
    x= x + entradas*TAMANIO - 5;
    context->move_to(x, TAMANIO-5);
    context->show_text("OUT");
    x= x + salidas*TAMANIO + 5;
    context->move_to(x, TAMANIO-5);
    context->show_text("Time");

    context->set_source_rgb(1.0, 0.0, 0.0);
    //titulos
    contador= 0;
    int dec= 65;
    std::string str;
    for(int i= INICIO_TABLA+15; i<=anchoColumna; i+=TAMANIO) {
      str= (char)dec;
      if(contador == (entradas+salidas)) {
        i= i-5;
        str= "T [ns]";
      }
      context->move_to(i, 2*TAMANIO-5);
      context->show_text(str);
      contador++;
      dec++;
    }

    context->set_source_rgb(0.0, 0.0, 0.0);
    //datos
    contador= 0;
    std::list<uint32_t>::iterator it= lista.begin();

    for(int j= 3*TAMANIO-5; j<=(altoFila+INICIO_TABLA); j+=TAMANIO) {
      for(int i= INICIO_TABLA+15; i<=anchoColumna; i+=TAMANIO) {
        if(contador == (entradas+salidas)) {
          i= i+4;
          contador= 0;
        } else
          contador++;
        context->move_to(i, j);
	if(*it != (uint32_t)-1)
	  context->show_text(Util::intToString(*it));
	else
	  context->show_text("??");
        it++;
      }
    }
    context->stroke();
    unsigned int i=0,inicio=0, inicioy=getAlto()-altoLeyenda;

    while(i < leyenda.size()){
      while(i<leyenda.size() && leyenda[i] != '\n')
	i++;

      std::string texto = leyenda;
	 
      texto[i]=0;	 
	 
      Cairo::TextExtents extents;
      context->set_font_size(20.0);
      context->get_text_extents(texto.c_str()+inicio, extents);
      inicioy+=-extents.y_bearing+4;
      Y+=-extents.y_bearing+4;
      context->move_to(15, Y);//inicioy);
      context->show_text(texto.c_str()+inicio);
      context->fill();
      inicio=++i;
    }
    context->stroke();
    if(altoLeyenda==0)
      this->altoLeyenda=inicioy-alto+5;
  }
}

int Tabla::getAncho() {
  anchoColumna= (entradas+salidas+1)*TAMANIO+15;
  ancho= anchoColumna+2*INICIO_TABLA;
  return ancho;
}

int Tabla::getAlto() {
  altoFila= ((lista.size()/(entradas+salidas+1))+2)*TAMANIO;
  alto= altoFila+2*INICIO_TABLA+altoLeyenda;
     
  return alto;
}

void Tabla::setCantEntradas(int entradas) {
  this->entradas= entradas;
}

void Tabla::setCantSalidas(int salidas) {
  this->salidas= salidas;
}

void Tabla::setLista(std::list<uint32_t> lista) {
  this->lista= lista;
  this->redibujar();
}

void Tabla::setLeyenda(const std::string& leyenda){
  altoLeyenda=0;
  this->leyenda = leyenda;
  this->redibujar();
}
