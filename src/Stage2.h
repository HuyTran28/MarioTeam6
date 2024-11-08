#pragma once

#include "Stage.h"

class Stage2 : public Stage
{
public:
	Stage2();
	~Stage2();
	void update() override;
	void draw() override;
private:
};