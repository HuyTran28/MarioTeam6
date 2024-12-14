#include "GameEngine.h"
#include <iostream>
GameEngine::GameEngine()
{
	isRunning = false;
	isInit = false;
	stateModel = nullptr;
	stateView = nullptr;
	stateController = nullptr;
	curState = "";
}


void GameEngine::run()
{
	isRunning = true;

	InitWindow(1900, 1000, "Game Engine");
	SetTargetFPS(60);

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
		GameData::getInstance().setLastState(curState);

		if (stateView != nullptr)
			EventManager::getInstance().removeObserver(stateView);
		if (stateController != nullptr)
			EventManager::getInstance().removeObserver(stateController);

		if (stateModel != nullptr)
			stateModelStack.push(stateModel);
		if (stateView != nullptr)
			stateViewStack.push(stateView);
		if (stateController != nullptr)
		{
			stateControllerStack.push(stateController);
			stateStack.push(curState);
		}

		auto specificEvent = std::dynamic_pointer_cast<StateChangeEvent>(event);
		curState = specificEvent->getNewState();

		StateFactory::createMVC(curState, stateModel, stateView, stateController);
	}
	else if (event->getType() == "Back Event")
	{
		EventManager::getInstance().removeObserver(stateView);
		EventManager::getInstance().removeObserver(stateController);
		stateModel = stateModelStack.top();
		stateView = stateViewStack.top();
		stateController = stateControllerStack.top();
		curState = stateStack.top();

		stateModelStack.pop();
		stateViewStack.pop();
		stateControllerStack.pop();
		stateStack.pop();

		if (curState == "Menu")
		{
			DisableCursor();
		}

		EventManager::getInstance().addObserver(stateView);
		EventManager::getInstance().addObserver(stateController);
	}
}

void GameEngine::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
	isInit = true;
}