#include "Impresora.h"
#include <string>

Glib::RefPtr<CustomPrintOperation> CustomPrintOperation::create()
{
	return Glib::RefPtr<CustomPrintOperation>(new CustomPrintOperation());
}

void CustomPrintOperation::on_begin_print(
        const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
	set_n_pages(1);
}


void CustomPrintOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int numeroPaginas)
{
	const double width = print_context->get_width();
	const double height = print_context->get_height();
	const double x_step = width/100.0;
	const double y_step = height/100.0;

	Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
	cairo_ctx->set_line_width(1);
	cairo_ctx->set_source_rgb(1.0, 0, 0);
	
	double x = 0;
	double y = 0;
	double x_to = x_step;
	double y_to = height;
	for(int i = 0; i < 100 ; ++i)
	{
		cairo_ctx->move_to(x, y);
		cairo_ctx->line_to(x_to, y_to);
		y += y_step;
		x_to += x_step;
	}
	cairo_ctx->stroke();

	cairo_ctx->set_source_rgb(0, 1.0, 0);
	x = 0;
	y = 0;
	x_to = width;
	y_to = y_step;
	for(int i = 0; i < 100 ; ++i)
	{
		cairo_ctx->move_to(x, y);
		cairo_ctx->line_to(x_to, y_to);
		x += x_step;
		y_to += y_step;
	}

	cairo_ctx->stroke();

	cairo_ctx->set_source_rgb(0, 0, 0);
	cairo_ctx->set_font_size(28.0);
	std::string text("Taller de Programación - FIUBA");
	Cairo::TextExtents extents;
	cairo_ctx->get_text_extents(text, extents);
	cairo_ctx->move_to (width/2.0 + - extents.x_bearing - extents.width/2, height/2.0);
	cairo_ctx->show_text(text);
	cairo_ctx->fill();
}
