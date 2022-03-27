#pragma once
#include <memory>
#include <chrono>

class GameLogicBase;
class Renderer;
class Updater;

class Game
{
public:
	explicit Game(GameLogicBase& base_rogic);
	virtual ~Game();

	int main() noexcept;

	bool handle_events() noexcept;
	void update(const float& delta) noexcept;
	void render() noexcept;

	Renderer* get_renderer() const { return renderer.get(); }
	Updater* get_updater() const { return updater.get(); }

private:
	std::chrono::steady_clock::time_point last_update;

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Updater> updater;
	
	GameLogicBase& game_logic;

	float delta_time;
	float fps_timer;
	float fps_time;
};

