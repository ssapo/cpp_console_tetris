#include "Cell.h"
#include "Renderer.h"

Cell::Cell(int x, int y, bool is_cell, unsigned short color)
	: x(x)
	, y(y)
	, cell(is_cell ? Renderer::TextCell::cell : Renderer::TextCell::fill)
	, color(color)
{

}

Cell::~Cell()
{

}

void Cell::set_empty_cell()
{
	this->cell = Renderer::TextCell::empty;
}

void Cell::set_fill_cell()
{
	this->cell = Renderer::TextCell::fill;
}

void Cell::render(Renderer* const renderer) noexcept
{
	renderer->write(x, y, cell, color);
}
