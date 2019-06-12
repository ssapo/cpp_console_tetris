#include "Board.h"
#include "Define.h"

Board::Board(const int width, const int height)
	: width(width)
	, height(height)
	, color(FOREGROUND_BLUE)
{
}

Board::~Board()
{

}

void Board::render(const Renderer* renderer) noexcept
{
	renderer->write()
}

void Board::update(const float& delta) noexcept
{

}
