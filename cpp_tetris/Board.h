#pragma once
#include "IRenderable.h"
#include "IUpdatable.h"
#include <vector>


class Board : public IRenderable, public IUpdatable
{
public:
	explicit Board(const int width, const int height);
	virtual ~Board();

	virtual void render(Renderer* const renderer) noexcept override;
	virtual void update(float delta) noexcept override;

private:
	int width = 0;
	int height = 0;
	unsigned short color = 0;

	std::vector<wchar_t> boards;
};

