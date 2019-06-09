#pragma once
#include <memory>
#include "DoubleBufferedConsole.h"



class Game
{
public:
	explicit Game();
	virtual ~Game();

	int main();


private:
	static constexpr int console_width = 400;
	static constexpr int console_height = 800;

	std::unique_ptr<DoubleBufferedConsole<wchar_t>> renderer;
};

