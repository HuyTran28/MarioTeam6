#pragma once

#include <memory>
#include "../Event/Event.h"
#include <string>

class StateChangeEvent : public Event
{
private:
	std::string newState;
	int continu = 0;
public:
	StateChangeEvent(std::string newState) : Event("State Change Event")
	{
		this->newState = newState;
	}

	StateChangeEvent(std::string newState, int continu) : Event("State Change Event")
	{
		this->newState = newState;
		this->continu = continu;
	}

	int getContinu()
	{
		return continu;
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
