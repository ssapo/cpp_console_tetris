#include "Game.h"

Game::Game()
	: renderer(std::make_unique<DoubleBufferedConsole<wchar_t>>(L"", console_width, console_height))
{
	renderer->clear(' ', FOREGROUND_GREEN);
	renderer->write(1, 1, L'A', FOREGROUND_GREEN);
	renderer->write(5, 5, L'A', FOREGROUND_GREEN);
	renderer->write(5, 10, L'A', FOREGROUND_GREEN);
	renderer->flip();
}

Game::~Game()
{

}

int Game::main()
{
	return 0;
}

