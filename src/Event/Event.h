#pragma once

#include <string>

class Event
{
private:
	std::string type;
public:
	Event(std::string type);
	std::string getType();
	virtual ~Event() = default; // Enable polymorphism
};