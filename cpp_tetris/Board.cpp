#include "Board.h"
#include "Renderer.h"

Board::Board(const int w, const int h)
	: width(w / 2)
	, height(h)
	, color(Renderer::TextColor::blue)
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
		boards[(width * 0) + x] = L'бс';
		boards[width * (height - 1) + x] = L'бс';
	}

	for (int y = 0; y < height; ++y)
	{
		boards[width * y + 0] = L'бс';
		boards[width * y + (width - 1)] = L'бс';
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
			renderer->write(x * 2, y, boards[width * y + x], color);
			renderer->write(x * 2 + 1, y, L' ', color);
		}
	}
}


void Board::update(float delta) noexcept
{
	
}
