#include "LevelSelectController.h"

LevelSelectController::LevelSelectController()
{
	model = std::make_shared<LevelSelectModel>();
}

LevelSelectController::LevelSelectController(std::shared_ptr<LevelSelectModel> model)
{
	this->model = model;
}

void LevelSelectController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void LevelSelectController::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		updateKeyboard();
		updateMouse();
	}
}

void LevelSelectController::updateKeyboard()
{
}

void LevelSelectController::updateMouse()
{
	Vector2 mousePoint = GetMousePosition();

	if (CheckCollisionPointRec(mousePoint, model->getDestRecLevel1()))
	{
		model->setDestRecColorLevel1(LIGHTGRAY);
	}
	else
	{
		model->setDestRecColorLevel1(WHITE);
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		if (CheckCollisionPointRec(mousePoint, model->getDestRecLevel1()))
		{
			//EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Level 1"));
		}
		if (StateController::isIconClicked(model->getBackArrow(), model->getBackArrowPosition(), model->getBackArrowScale()))
		{
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Menu"));
			return;
		}
	}
}





