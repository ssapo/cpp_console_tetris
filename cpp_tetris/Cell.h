#pragma once
#include "Define.h"
#include "IRenderable.h"

TETRIS_START

class Cell : public IRenderable
{
public:
	explicit Cell(int x, int y, bool empty, unsigned short c);
	virtual ~Cell();

	void cleanup() noexcept;
	
	int get_x() const noexcept { return x; }
	void set_x(int x) noexcept { this->x = x; }
	
	int get_y() const noexcept { return y; }
	void set_y(int y) noexcept { this->y = y; }
	
	bool is_fill();

	wchar_t get_cell() const noexcept { return cell; }
	void set_dot_cell();
	void set_fill_cell();
	
	unsigned short get_color() const noexcept { return color; }
	void set_color(unsigned short c) noexcept { this->color = c; }

	virtual void render(Renderer* const renderer) noexcept override;

private:
	int x;
	int y;
	wchar_t cell;
	unsigned short color;
};

TETRIS_END