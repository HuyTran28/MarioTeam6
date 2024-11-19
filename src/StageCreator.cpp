#include "StageCreator.h"

Stage* StageCreator::createStage(GameState stageType)
{
	switch (stageType)
	{
	case LOGIN:
		return new LogIn();
	case MENU:
		return new Menu();
	case STAGE1:
		return new Stage1();
	case STAGE2:
		return new Stage2();
	default:
		return nullptr;
	}
}