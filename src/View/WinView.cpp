#include "WinView.h"

WinView::WinView()
{
	model = std::make_shared<WinModel>();
}

WinView::WinView(std::shared_ptr<WinModel> model)
{
	EnableCursor();
	this->model = model;
}

#include <iostream>

void WinView::render()
{
	ClearBackground(RAYWHITE);
	BeginDrawing();

	DrawTextEx(GetFontDefault(), "Stage Clear!", {650, 100}, 100, 10, BLACK);

	std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;

	std::string score = std::to_string(GameData::getInstance().getPlayerScore());
	int posX = GetScreenWidth() / 2 - MeasureText(score.c_str(), 50) / 2;
	DrawTextEx(GetFontDefault(), score.c_str(), {(float)posX, 300}, 60, 10, BLACK);

	model->getBackButton()->draw();
	model->getRetryButton()->draw();
	model->getResumeButton()->draw();
	model->getQuitButton()->draw();

	EndDrawing();
}

void WinView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void WinView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}