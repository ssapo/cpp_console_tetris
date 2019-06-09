#include "Game.h"

int main()
{
	auto game = std::make_unique<Game>();
	return game->main();
}