#ifndef IMPRESORA_H_
#define IMPRESORA_H_

#include <gtkmm.h>
#include <vector>

class Impresora : public Gtk::PrintOperation
{
public:
	static Glib::RefPtr<Impresora> create();

protected:
	virtual void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
	virtual void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int numeroPagina);
};


#endif /*IMPRESORA_H_*/
