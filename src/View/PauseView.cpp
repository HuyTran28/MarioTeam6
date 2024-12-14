#include "PauseView.h"

PauseView::PauseView()
{
	model = std::make_shared<Pause>();
}

PauseView::PauseView(std::shared_ptr<Pause> model)
{
	EnableCursor();
	this->model = model;
}

#include <iostream>

void PauseView::render()
{
	ClearBackground(RAYWHITE);
	BeginDrawing();

	DrawText(model->getTitle().c_str(), GetScreenWidth() / 2.0f - (1010.0f - 650.0f) / 2.0f, 200.0f, 120, BLACK);
	model->getBackButton()->draw();
	model->getRetryButton()->draw();
	model->getResumeButton()->draw();
	model->getQuitButton()->draw();

	EndDrawing();
}

void PauseView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void PauseView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}