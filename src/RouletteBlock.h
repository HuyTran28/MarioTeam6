#pragma once

#include "Block.h"
class RouletteBlock : public Block
{

public:
	RouletteBlock(btRigidBody* rigidBody, const std::string& name, Model model, const Vector3& position, const Vector3& scale, btDiscreteDynamicsWorld* dynamicsWorld)
		: Block(rigidBody, name, model, position, scale, dynamicsWorld) {}

};