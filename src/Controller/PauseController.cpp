#include "PauseController.h"

PauseController::PauseController()
{
	model = std::make_shared<Pause>();
}

PauseController::PauseController(std::shared_ptr<Pause> model)
{
	this->model = model;
}

void PauseController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void PauseController::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		if (model->getBackButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Menu"));
			return;
		}
		else if (model->getRetryButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>(GameData::getInstance().getLastState()));
			return;
		}
		else if (model->getResumeButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<BackEvent>());
			return;
		}
		else if (model->getQuitButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Level Select"));
			return;
		}
	}
}