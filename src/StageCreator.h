#pragma once

#include "Stage.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Game.h"

class StageCreator
{
public:
	enum StageType
	{
		STAGE1,
		STAGE2
	};
	Stage* createStage(StageType type) const;
};