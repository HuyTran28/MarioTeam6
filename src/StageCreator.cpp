#include "StageCreator.h"

Stage* StageCreator::createStage(StageType stageType) const
{
	switch (stageType)
	{
	case STAGE1:
		return new Stage1();
	case STAGE2:
		return new Stage2();
	default:
		return nullptr;
	}
}