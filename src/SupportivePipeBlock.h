#pragma once

#include "Block.h"
class SupportivePipeBLock : public Block
{

public:
	SupportivePipeBLock(btRigidBody* rigidBody, const std::string& name, Model model, const Vector3& position, const Vector3& scale, btDiscreteDynamicsWorld* dynamicsWorld)
		: Block(rigidBody, name, model, position, scale, dynamicsWorld) {}

};