#include "GameLogicBase.h"
#include "Game.h"
#include "Renderer.h"
#include "Updater.h"

GameLogicBase::GameLogicBase()
{
}

GameLogicBase::~GameLogicBase()
{

}

bool GameLogicBase::start_game()
{
	return initialize();
}

void GameLogicBase::render(Renderer* const renderer) noexcept
{
	renderer->render();
}

void GameLogicBase::update(Updater* const updater, float delta) noexcept
{
	updater->update(delta);
}

