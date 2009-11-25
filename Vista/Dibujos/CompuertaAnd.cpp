#include "CompuertaAnd.h"

CompuertaAnd::CompuertaAnd(int xUp, int yUp): Compuerta::Compuerta(xUp, yUp) {

  //cargarNuevosPines(vSupIzq);
}

//void CompuertaAnd::cargarNuevosPines(Vertice vSupIzq) {
void CompuertaAnd::cargarNuevosPines(const Cairo::RefPtr<Cairo::Context>& context) {

  pines.clear();
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y+10, context));
  pines.push_back(rotarPin(vSupIzq.x, vSupIzq.y+30, context));
  pines.push_back(rotarPin(vSupIzq.x+40, vSupIzq.y+20, context));
}

void CompuertaAnd::dibujar(const Cairo::RefPtr<Cairo::Context>& context) {

  //puerta
  context->set_source_rgb(0.0, 0.0, 1.0);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->line_to(vSupIzq.x+10, vSupIzq.y+40);
  context->move_to(vSupIzq.x+10, vSupIzq.y);
  context->curve_to(vSupIzq.x+38, vSupIzq.y+5, vSupIzq.x+38, vSupIzq.y+35, vSupIzq.x+10, vSupIzq.y+40);
  context->stroke();
  //entradas
  context->set_source_rgb(0.0, 0.0, 0.0);
  context->move_to(vSupIzq.x, vSupIzq.y+10);
  context->line_to(vSupIzq.x+10, vSupIzq.y+10);
  context->move_to(vSupIzq.x, vSupIzq.y+30);
  context->line_to(vSupIzq.x+10, vSupIzq.y+30);
  //salida
  context->move_to(vSupIzq.x+32, vSupIzq.y+20);
  context->line_to(vSupIzq.x+40, vSupIzq.y+20);
  context->stroke();

  if(seleccionado)
    dibujarSeleccion(context);
  
  //Muestro la etiqueta
  mostrarEtiqueta(context,vSupIzq.y,alto);

  context->set_identity_matrix();

  for(int i=0;i<pines.size();i++){
       context->move_to(pines[i].x, pines[i].y);
       context->line_to(pines[i].x, pines[i].y+5);
       context->stroke();
  }

}
