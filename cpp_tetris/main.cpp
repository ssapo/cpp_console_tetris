#include "Tetris.h"

int main()
{
	if (auto let = std::make_unique<Tetris>())
	{
		auto game = std::make_unique<Game>(std::move(let));
		if (game)
		{
			return game->main();
		}
	}

	return 0;
}