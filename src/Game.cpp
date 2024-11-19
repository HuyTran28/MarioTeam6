#include "Game.h"

float Game::screenWidth = 0;
float Game::screenHeight = 0;

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::~Game()
{
	for (Observer* ob : stateObservers)
	{
		delete ob;
	}
    
	while (!stageStack.empty())
	{
		delete stageStack.top();
		stageStack.pop();
	}
}

Game::Game()
{
	InitWindow(2000, 1200, "Mario Game");
	SetTargetFPS(60);
	screenHeight = GetScreenHeight();
	screenWidth = GetScreenWidth();

    curState = LOGIN;
	curStage = StageCreator::createStage(curState);
	isRunning = true;
	stageStack.push(curStage);
}


void Game::run()
{
    while (isRunning && !WindowShouldClose())
    {
        this->update();
        this->draw();
    }

    CloseWindow(); // Close window and OpenGL context
}

void Game::update()
{
    // update game state
	updateStage();
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Example draw functions
    drawStage();

    EndDrawing();
}

void Game::addGameStateObserver(Observer* ob)
{
    stateObservers.push_back(ob);
}

void Game::notifyStateChange()
{
    for (Observer* ob : stateObservers)
    {
        // Notify each observer of the state change
    }
}

void Game::switchStage(GameState state)
{
    curState = state;
    notifyStateChange();
	if (curStage)
	{
		delete curStage;
	}
	curStage = StageCreator::createStage(curState);
}

void Game::drawStage()
{
    if (curStage)
    {
        curStage->draw();
    }
}

void Game::updateStage()
{
	if (curStage)
	{
		curStage->update();
	}
}

void Game::goBack()
{
	if (stageStack.size() > 1)
	{
		delete curStage;
		stageStack.pop();
		curStage = stageStack.top();
	}
}

