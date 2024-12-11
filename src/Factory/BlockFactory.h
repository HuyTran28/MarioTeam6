#pragma once

#include "raylib.h"
#include "../Model/Block/ModelStage.h"
#include "../Model/Block/BlockData.h"
#include "../Model/Block/BrickBlock.h"
#include "../Model/Block/NormalBrickBlock.h"
#include "../Model/Block/PipeBlock.h"
#include "../Model/Block/QuestionBlock.h"
#include "../Model/Block/EmptyBlock.h"
#include "../Model/Block/RouletteBlock.h"
#include "../Model/Block/SupportivePipeBlock.h"
#include "../Model/Block/FlyBlock.h"



enum class BlockType
{
	BrickBlock,
	NormalBrickBlock,
	PipeBlock,
	QuestionBlock,
	EmptyBlock,
	RouletteBlock,
	SupportivePipeBlock,
	FlyBlock,
};

class BlockFactory : public BlockData
{
public:
	static BlockData* createBlock(BlockType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
		const Vector3& startPosition, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle);
};