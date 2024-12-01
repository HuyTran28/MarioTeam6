#pragma once

#include "raylib.h"
#include "Block.h"
#include "ModelStage.h"
#include "BrickBlock.h"
#include "CastleBlock.h"
#include "NormalBrickBlock.h"
#include "PipeBlock.h"
#include "QuestionBlock.h"
#include "EmptyBlock.h"
#include "RouletteBlock.h"
#include "SupportivePipeBlock.h"
#include "FlyBlock.h"
#include "WaterBlock.h"





enum class BlockType
{
	BrickBlock,
	CastleBlock,
	ManmaBlock,
	NormalBrickBlock,
	PipeBlock,
	QuestionBlock,
	EmptyBlock,
	RouletteBlock,
	SupportivePipeBlock,
	FlyBlock,
};

class BlockFactory : public Block
{
public:
	static Block* createBlock(BlockType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
		const Vector3& startPosition, const Vector3& scale);
};