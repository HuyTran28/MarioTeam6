#include "GameOverController.h"

GameOverController::GameOverController(std::shared_ptr<GameOverModel> gameOverModel)
{
	model = gameOverModel;
}

void GameOverController::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		if (model->getRetryButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>(GameData::getInstance().getLastState()));
		}
		else if (model->getQuitButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Menu"));
		}
	}
}

void GameOverController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

