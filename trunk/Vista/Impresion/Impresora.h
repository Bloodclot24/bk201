#ifndef IMPRESORA_H_
#define IMPRESORA_H_

#include <gtkmm/printoperation.h>
#include <gtkmm/printcontext.h>
#include <gtkmm/printsettings.h>
#include <gtkmm/printjob.h>
#include <vector>
#include <list>
#include "../Tabla.h"
#include "../Dibujos/Dibujo.h"
#include "../AreaDibujo.h"

class Impresora : public Gtk::PrintOperation
{
	friend class Tabla;
	friend class AreaDibujo;
private:
	std::list<Dibujo*> dibujos;
	Tabla* tabla;
	AreaDibujo* areaDibujo;
	
public:
	Impresora(std::list<Dibujo*> dibujos, Tabla* tabla);
	static Glib::RefPtr<Impresora> create(std::list<Dibujo*> dibujos, Tabla* tabla);

protected:
	virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
	virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int numeroPagina);
//	bool on_my_paginate(const Glib::RefPtr<Gtk::PrintContext>& context);
	//friend Tabla::dibujarTabla(void dibujarTabla(const Cairo::RefPtr<Cairo::Context>& context);
};


#endif /*IMPRESORA_H_*/
