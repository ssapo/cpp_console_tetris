#include "Board.h"
#include "Renderer.h"

TETRIS_START

Board::Board(int w, int h, unsigned short color)
	: width(w)
	, height(h)
	, color(color)
{
	boards.reserve(width * height);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			boards.emplace(boards.end(), Renderer::TextCell::empty);
		}
	}

	for (int x = 0; x < width; ++x)
	{
		boards[(width * 0) + x] = Renderer::TextCell::fill;
		boards[width * (height - 1) + x] = Renderer::TextCell::fill;
	}

	for (int y = 0; y < height; ++y)
	{
		boards[width * y + 0] = Renderer::TextCell::fill;
		boards[width * y + (width - 1)] = Renderer::TextCell::fill;
	}
}

Board::~Board()
{
	boards.clear();
}

void Board::render(Renderer* const renderer) noexcept
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			renderer->write(x, y, boards[width * y + x], color);
		}
	}
}

TETRIS_END


