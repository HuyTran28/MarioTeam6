#include "Event.h"

Event::Event(std::string type) : type(type) 
{
}

std::string Event::getType() 
{ 
	return type; 
}