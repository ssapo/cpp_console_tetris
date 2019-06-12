#include "Board.h"
#include "Renderer.h"

Board::Board(const int width, const int height)
	: width(width)
	, height(height)
	, color(Renderer::TextColor::blue)
{
}

Board::~Board()
{

}

void Board::render(Renderer* const renderer) noexcept
{
	renderer->write(3, 5, L'бс', color);
}

void Board::update(float delta) noexcept
{

}
