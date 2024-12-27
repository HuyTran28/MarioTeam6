#include "WinController.h"

WinController::WinController()
{
	model = std::make_shared<WinModel>();
}

WinController::WinController(std::shared_ptr<WinModel> model)
{
	this->model = model;
}

void WinController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void WinController::update(std::shared_ptr<Event> event)
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
			std::string lastState = GameData::getInstance().getLastState();
			std::string nextState = lastState.substr(0, 5) + std::to_string(lastState[5] - '0' + 1);
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>(nextState));
			return;
		}
		else if (model->getQuitButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Level Select"));
			return;
		}
	}
}