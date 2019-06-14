#pragma once
#include "IRenderable.h"
#include "IUpdatable.h"
#include <vector>
#include <tuple>

class Board : public IRenderable
{
public:
	explicit Board(const int width, const int height);
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

