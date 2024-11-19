#pragma once

#include "Stage.h"
#include "LogIn.h"
#include "Menu.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Game.h"

enum GameState;

class StageCreator
{
public:
	static Stage* createStage(GameState type) ;
};