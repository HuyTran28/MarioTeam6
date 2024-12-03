#include "ControlEngine.h"

ControlEngine::ControlEngine()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void ControlEngine::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Initialize Event")
	{
	}
	else if (event->getType() == "State Change Event")
	{
		//changeState();
	}
}
