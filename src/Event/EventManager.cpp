#include "EventManager.h"
#include <iostream>

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
	std::vector<std::shared_ptr<IObserver>> tmp = observers;
	for (auto &ob : tmp)
	{
		if (ob)
		{
			ob->update(event);
		}
	}
}

void EventManager::pop_back()
{
	observers.pop_back();
}