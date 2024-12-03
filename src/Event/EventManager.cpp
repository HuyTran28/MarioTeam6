#include "EventManager.h"

EventManager& EventManager::getInstance()
{
	static EventManager instance;
	return instance;
}

void EventManager::addObserver(std::shared_ptr<IObserver> ob)
{
	observers.push_back(ob);
}

void EventManager::removeObserver(std::shared_ptr<IObserver> ob)
{
	observers.erase(std::remove(observers.begin(), observers.end(), ob), observers.end());
}

void EventManager::notify(std::shared_ptr<Event> event)
{
	for (auto ob : observers)
	{
		ob->update(event);
	}
}