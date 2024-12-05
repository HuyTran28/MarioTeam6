#include "GameEngine.h"

GameEngine::GameEngine()
{
	isRunning = false;
}

void GameEngine::run()
{
	isRunning = true;

	InitWindow(2000, 1200, "Game Engine");
	SetTargetFPS(90);

	this->registerSelf();

	std::shared_ptr<StateChangeEvent> stateChangeEvent = std::make_shared<StateChangeEvent>("Menu");
	EventManager::getInstance().notify(stateChangeEvent);

	while (isRunning == true && !WindowShouldClose())
	{
		std::shared_ptr<Event> newEvent = std::make_shared<TickEvent>();
		EventManager::getInstance().notify(newEvent);
		newEvent.reset();
	}
}

#include <iostream>

void GameEngine::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Quit Event")
	{
		isRunning = false;
	}
	else if (event->getType() == "State Change Event")
	{
		EventManager::getInstance().removeObserver(stateView);
		EventManager::getInstance().removeObserver(stateController);

		auto specificEvent = std::dynamic_pointer_cast<StateChangeEvent>(event);
		std::string curState = specificEvent->getNewState();
		StateFactory::createMVC(curState, stateModel, stateView, stateController);
	}
}

void GameEngine::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
	isInit = true;
}
