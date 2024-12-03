#pragma once

#include "../Event/Event.h"
#include <string>

class KeyBoardEvent : public Event
{
private:
	int c;
public:
	KeyBoardEvent(int c) : Event("Keyboard Event")
	{
		this->c = c;
	}

	int getKey()
	{
		return c;
	}

	std::string getType()
	{
		return Event::getType();
	}
};