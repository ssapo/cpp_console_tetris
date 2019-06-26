#pragma once
#include "Define.h"
#include "IRenderable.h"
#include "IUpdatable.h"
#include <vector>
#include <tuple>
#include "Point.h"

TETRIS_START

class Board : public IRenderable
{
public:
	explicit Board(int w, int h, unsigned short color);
	virtual ~Board();

	virtual void render(Renderer* const renderer) noexcept override;

	int get_width() const noexcept { return width; }
	int get_height() const noexcept { return height; }
	int get_size() const noexcept { return width * height; }

private:
	int width = 0;
	int height = 0;
	unsigned short color = 0;

	std::vector<wchar_t> boards;
};

TETRIS_END