#include "Board.h"
#include "Renderer.h"

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
			boards.emplace(boards.end(), L' ');
		}
	}

	for (int x = 0; x < width; ++x)
	{
		boards[(width * 0) + x] = L'��';
		boards[width * (height - 1) + x] = L'��';
	}

	for (int y = 0; y < height; ++y)
	{
		boards[width * y + 0] = L'��';
		boards[width * y + (width - 1)] = L'��';
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