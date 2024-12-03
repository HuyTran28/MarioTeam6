#include "GameEngine.h"

GameEngine::GameEngine()
{
	isRunning = false;
	inputHandler = std::make_shared<InputHandler>();
	inputHandler->registerSelf();
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

void GameEngine::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Quit Event")
	{
		isRunning = false;
	}
	else if (event->getType() == "State Change Event")
	{
		auto specificEvent = std::dynamic_pointer_cast<StateChangeEvent>(event);
		std::string curState = specificEvent->getNewState();
		StateFactory::createMVC(curState, stateModel, stateView, stateController);

		std::shared_ptr<InitializeEvent> initEvent = std::make_shared<InitializeEvent>();
		EventManager::getInstance().notify(initEvent);
	}
}

void GameEngine::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
	isInit = true;
}
