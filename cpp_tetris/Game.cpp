#include "Game.h"
#include <chrono>
#include "Renderer.h"
#include "Updater.h"
#include "GameLogicBase.h"

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

Game::Game(std::unique_ptr<GameLogicBase> raw)
	: renderer(std::make_unique<Renderer>(L"cpp_tetris", console_width, console_height))
	, updater(std::make_unique<Updater>())
	, game_logic(std::move(raw))
{
}

Game::~Game()
{
}

bool Game::handle_events() noexcept
{
	// poll for events

	return false; // true if the user wants to quit the game
}

void Game::update(const float& delta) noexcept
{
	game_logic->update(updater.get(), delta);
}

void Game::render() noexcept
{
	game_logic->render(renderer.get());
}

int Game::main() noexcept
{
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = false;

	while (!quit_game)
	{
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		quit_game = handle_events();

		// update game logic as lag permits
		while (lag >= timestep) 
		{
			auto delta = lag - timestep;
			lag -= delta;

			auto time = std::chrono::duration<float>(delta).count();
			update(time); // update at a fixed rate each time
		}

		render();
	}

	return 0;
}