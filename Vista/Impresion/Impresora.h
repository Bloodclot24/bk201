#ifndef IMPRESORA_H_
#define IMPRESORA_H_

#include <gtkmm.h>
#include <vector>
#include <list>
#include "../Tabla.h"
#include "../Dibujos/Dibujo.h"

class Impresora : public Gtk::PrintOperation
{
private:
	std::list<Dibujo*> dibujos;
	Tabla* tabla;
	bool circuito;	
	
public:
	Impresora(std::list<Dibujos*> dibujos, Tabla* Tabla);
	static Glib::RefPtr<Impresora> create(std::list<Dibujos*> dibujos, Tabla* tabla);

protected:
	virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
	virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int numeroPagina);
};


#endif /*IMPRESORA_H_*/
