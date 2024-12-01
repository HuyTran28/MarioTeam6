#pragma once

#include "Block.h"
class PipeBlock : public Block
{

public:
	PipeBlock(btRigidBody* rigidBody, const std::string& name, Model model, const Vector3& position, const Vector3& scale, btDiscreteDynamicsWorld* dynamicsWorld)
		: Block(rigidBody, name, model, position, scale, dynamicsWorld) {}
	//~PipeBlock() override = default;
};