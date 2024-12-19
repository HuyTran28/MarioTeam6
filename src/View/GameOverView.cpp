#include "GameOverView.h"

GameOverView::GameOverView(std::shared_ptr<GameOverModel> gameOverModel)
{
	model = gameOverModel;
}
#include <iostream>

void GameOverView::render()
{
	ClearBackground(RAYWHITE);
	BeginDrawing();

	DrawText("Game Over", GetScreenWidth() / 2 - (1270.0f - 630.0f) / 2.0f, 150.0f, 120, BLACK);

	model->getRetryButton()->draw();
	model->getQuitButton()->draw();

	EndDrawing();
}

void GameOverView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void GameOverView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}