#pragma once

#include "../Event/Event.h"
#include <string>
#include <raylib.h>

class MouseClickedEvent : public Event
{
private:
	Vector2 pos;
public:
	MouseClickedEvent(Vector2 pos) : Event("Mouse Clicked Event")
	{
		this->pos = pos;
	}

	Vector2 getMousePos() { return pos; }

	std::string getType() { return Event::getType(); }
};