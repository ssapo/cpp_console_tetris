#include "Game.h"
#include <algorithm>
#include "Renderer.h"
#include "Updater.h"
#include "GameLogicBase.h"
#include <conio.h>
#include <Windows.h>

Game::Game(GameLogicBase& base_rogic)
	: renderer(std::make_unique<Renderer>(L"cpp_tetris"))
	, updater(std::make_unique<Updater>())
	, game_logic(base_rogic)
	, delta_time(0.0f)
	, fps_timer(0.0f)
	, fps_time(1 / 60.0f)
{
}

Game::~Game()
{
}

bool Game::handle_events() noexcept
{
	// poll for events

	if (_kbhit() != 0)
	{
		auto key_code = _getch();
		return game_logic.handle_event(key_code);
	}

	return true; // true if the user wants to quit the game
}

void Game::update(const float& delta) noexcept
{
	game_logic.update(updater.get(), delta);
}

void Game::render() noexcept
{
	game_logic.render(renderer.get());
}

int Game::main() noexcept
{
	using clock = std::chrono::steady_clock;

	last_update = clock::now();
	bool continue_game = game_logic.start_game(*this);

	while (continue_game)
	{
		continue_game = handle_events();

		auto now = clock::now();
		delta_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_update).count() / 1000000.0f;
		last_update = now;

		delta_time = std::max<float>(0, delta_time);

		update(delta_time);

		fps_timer += delta_time;
		if (fps_timer >= fps_time)
		{
			fps_timer = 0.0f;
			render();
		}
	}

	return 0;
}