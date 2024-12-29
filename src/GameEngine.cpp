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
	SetTargetFPS(30);

	this->registerSelf();

	//curState = "Menu";
	std::shared_ptr<StateChangeEvent> stateChangeEvent = std::make_shared<StateChangeEvent>("Stage3");
	EventManager::getInstance().notify(stateChangeEvent);

	GameData& gameData = GameData::getInstance();
	CollisionManager::getInstance();
	SoundManager::getInstance();


	while (isRunning == true && !WindowShouldClose())
	{
		DrawFPS(10, 10);
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
		GameData::getInstance().setLastState(curState);

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
	else if (event->getType() == "Tick Event")
	{
		GameData::getInstance().setCurState(curState);


		if (isGameOver == true)
		{
			timer += GetFrameTime();

			if (timer > 3.0f)
			{
				isGameOver = false;
				timer = 0.0f;
				EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Game Over"));
			}
		}
		else if (isWin == true)
		{
			timer += GetFrameTime();

			if (timer > 6.0f)
			{
				isWin = false;
				timer = 0.0f;
				EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Win"));
			}
		}

		if (curState.substr(0, 5) == "Stage")
		{
			while (stateModelStack.size() > 0)
			{
				stateModelStack.pop();
				stateViewStack.pop();
				stateControllerStack.pop();
				stateStack.pop();
			}
		}
	}
	else if (event->getType() == "Die Event")
	{
		isGameOver = true;
	}
	else if (event->getType() == "Win Event")
	{
		isWin = true;
	}

}

void GameEngine::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
	isInit = true;
}