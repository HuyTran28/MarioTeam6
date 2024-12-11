#include "LevelSelectView.h"

LevelSelectView::LevelSelectView()
{
	model = std::make_shared<LevelSelectModel>();
}

LevelSelectView::LevelSelectView(std::shared_ptr<LevelSelectModel> model)
{
	EnableCursor();
	this->model = model;
}

LevelSelectView::LevelSelectView(const LevelSelectView& levelSelectView)
{
	this->model = levelSelectView.model;
}

#include <iostream>

void LevelSelectView::render()
{
	BeginDrawing();

	ClearBackground(DARKBLUE);

	std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;
	DrawTextureEx(model->getBackground(), model->getBackgroundPos(), 0.0f, model->getBackgroundScale(), WHITE);
	
	Rectangle level1 = model->getDestRecLevel1();
	DrawRectangleRec(level1, model->getDestRecColorLevel1());
	DrawTexturePro(model->getLevel1Texture(), model->getSrcRecLevel1(), model->getDestRecLevel1(), model->getOriginLevel1(), 0.0f, WHITE);

	DrawTextureEx(model->getBackArrow(), model->getBackArrowPosition(), 0.0f, model->getBackArrowScale(), WHITE);

	EndDrawing();
}

void LevelSelectView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void LevelSelectView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}




