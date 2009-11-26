#ifndef IMPRESORA_H_
#define IMPRESORA_H_

#include <gtkmm.h>
#include <vector>
#include <list>
#include "../Tabla.h"
#include "../Dibujos/Dibujo.h"

class Impresora : public Gtk::PrintOperation
{
	friend class Tabla;
private:
	std::list<Dibujo*> dibujos;
	Tabla* tabla;
	
public:
	Impresora(std::list<Dibujo*> dibujos, Tabla* tabla);
	static Glib::RefPtr<Impresora> create(std::list<Dibujo*> dibujos, Tabla* tabla);

protected:
	virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
	virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int numeroPagina);
	//friend Tabla::dibujarTabla(void dibujarTabla(const Cairo::RefPtr<Cairo::Context>& context);
};


#endif /*IMPRESORA_H_*/
