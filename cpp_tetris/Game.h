#pragma once
#include <memory>

class GameLogicBase;
class Renderer;
class Updater;

class Game
{
public:
	explicit Game(std::unique_ptr<GameLogicBase> raw);
	virtual ~Game();

	int main() noexcept;

	bool handle_events() noexcept;
	void update(const float& delta) noexcept;
	void render() noexcept;

	Renderer* get_renderer() const { return renderer.get(); }
	Updater* get_updater() const { return updater.get(); }

public:
	static constexpr int console_width = 30;
	static constexpr int console_height = 20;

private:

	std::unique_ptr<GameLogicBase> game_logic;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Updater> updater;
};

