#include "InputHandler.h"
#include <iostream>
InputHandler::InputHandler()
{
}

void InputHandler::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Initialize Event")
	{
	}
	else if (event->getType() == "Tick Event")
	{
		for (int i = 0; i < 256; i++)
		{
			if (IsKeyPressed(i))
			{
				std::shared_ptr<KeyBoardEvent> keyEvent = std::make_shared<KeyBoardEvent>(i);
				EventManager::getInstance().notify(keyEvent);
			}
		}

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			std::shared_ptr<MouseClickedEvent> mouseEvent = std::make_shared<MouseClickedEvent>(GetMousePosition());
			EventManager::getInstance().notify(mouseEvent);
		}
	}
}

void InputHandler::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}