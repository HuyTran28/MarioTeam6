#include "Game.h"
#include "raylib.h"

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::Game() : curState(STAGE1), isRunning(true), curStage(nullptr)
{
}

void Game::init()
{
    InitWindow(2000, 1200, "Mario Game");
    SetTargetFPS(60);
}

void Game::run()
{
    this->init();

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
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Example draw functions
    drawBackground();
    drawStage();
    drawUI();

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
}

void Game::drawBackground()
{
    // draw the background
    DrawText("Background", 10, 10, 20, DARKGRAY);
}

void Game::drawStage()
{
    if (curStage)
    {
        curStage->draw();
    }
}

void Game::drawUI()
{
    // draw the UI elements
    DrawText("Score: 100", 10, 50, 20, DARKGRAY);
}
