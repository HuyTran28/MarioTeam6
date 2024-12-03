#pragma once

#include <memory>
#include "../Event/Event.h"
#include <string>

class StateChangeEvent : public Event
{
private:
	std::string newState;
public:
	StateChangeEvent(std::string newState) : Event("State Change Event")
	{
		this->newState = newState;
	}

	std::string getNewState()
	{
		return newState;
	}

	std::string getType()
	{
		return Event::getType();
	}
};
