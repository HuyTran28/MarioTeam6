#include "GameEngine.h"
#include <iostream>
GameEngine::GameEngine()
{
	isRunning = false;
}


void GameEngine::run()
{
	isRunning = true;

	InitWindow(1900, 1000, "Game Engine");
	SetTargetFPS(90);

	this->registerSelf();

	std::shared_ptr<StateChangeEvent> stateChangeEvent = std::make_shared<StateChangeEvent>("Menu");
	EventManager::getInstance().notify(stateChangeEvent);

	GameData& gameData = GameData::getInstance();

	std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = gameData.getDynamicsWorld();


	while (isRunning == true && !WindowShouldClose())
	{
		dynamicsWorld->stepSimulation(GetFrameTime());

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
		EventManager::getInstance().removeObserver(stateView);
		EventManager::getInstance().removeObserver(stateController);

		stateModelStack.push(stateModel);
		stateViewStack.push(stateView);
		stateControllerStack.push(stateController);

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
