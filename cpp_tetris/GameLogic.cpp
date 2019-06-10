#include "GameLogic.h"
#include "Game.h"

GameLogicBase::GameLogicBase(std::shared_ptr<Game> ptr)
	: game(ptr)
{
	if (auto let = game.lock())
	{
		let->get_renderer()->add(this);
		let->get_updater()->add(this);
	}
}

GameLogicBase::~GameLogicBase()
{

}

void GameLogicBase::render()
{
}

void GameLogicBase::update(const float& delta)
{
}
