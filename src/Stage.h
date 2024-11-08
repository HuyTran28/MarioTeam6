#pragma once

#include <raylib.h>

class Stage
{
public: 
	virtual void update() = 0;
	virtual void draw() = 0;
};