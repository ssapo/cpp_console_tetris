#pragma once
#include <memory>

class Game;
class Renderer;
class Updater;
class GameLogicBase
{
public:
	explicit GameLogicBase();
	virtual ~GameLogicBase();

	virtual bool handle_event(char keycode) noexcept abstract;
	void render(Renderer* const renderer) noexcept;
	void update(Updater* const updater, float delta) noexcept;

	bool start_game();
	virtual bool initialize() noexcept abstract;
};

