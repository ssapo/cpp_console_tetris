#include "Cell.h"
#include "Renderer.h"

TETRIS_START

Cell::Cell(int x, int y, bool is_cell, unsigned short color)
	: x(x)
	, y(y)
	, cell(is_cell ? Renderer::TextCell::dot : Renderer::TextCell::fill)
	, color(color)
{

}

Cell::~Cell()
{

}

void Cell::cleanup() noexcept
{
	this->cell = Renderer::TextCell::dot;
	color = Color::gray;
}

bool Cell::is_fill()
{
	return this->cell == Renderer::TextCell::fill;
}

void Cell::set_dot_cell()
{
	this->cell = Renderer::TextCell::dot;
}

void Cell::set_fill_cell()
{
	this->cell = Renderer::TextCell::fill;
}

void Cell::render(Renderer* const renderer) noexcept
{
	renderer->write(x, y, cell, color);
}

TETRIS_END

