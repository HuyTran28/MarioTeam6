#pragma once

#include "Block.h"
#include "btBulletCollisionCommon.h"
#include "Player.h"
class QuestionBlock : public Block
{
private:
	bool isOpen = true;
public:
	QuestionBlock(btRigidBody* rigidBody, const std::string& name, Model model, const Vector3& position, const Vector3& scale, btDiscreteDynamicsWorld* dynamicsWorld)
		: Block(rigidBody, name, model, position, scale, dynamicsWorld) {}

	//~QuestionBlock() override = default;
};