#include "LogInController.h"

LogInController::LogInController()
{
}

LogInController::LogInController(std::shared_ptr<LogInModel> model)
{
	this->model = model;
}

void LogInController::update(std::shared_ptr<Event> event)
{

}

void LogInController::updateGameState()
{
}

void LogInController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}



