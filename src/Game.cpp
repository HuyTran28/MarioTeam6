#include "Game.h"

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::~Game()
{
	if (curStage)
	{
		delete curStage;
	}
}

Game::Game()
{
    curState = MENU;
	curStage = StageCreator::createStage(curState);
	isRunning = true;
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

