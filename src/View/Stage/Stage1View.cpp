#include "Stage1View.h"

Stage1View::Stage1View(std::shared_ptr<Stage1Model> model) : m_model(model){}

void Stage1View::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawText("Stage 1", 10, 10, 20, BLACK);

	EndDrawing();
}

void Stage1View::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void Stage1View::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());	
}
