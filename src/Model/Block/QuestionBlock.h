#pragma once

#include "BlockData.h"
#include "btBulletCollisionCommon.h"
class QuestionBlock : public BlockData
{
private:
	bool isOpen = true;
public:
	QuestionBlock(btRigidBody* rigidBody, const std::string& name, Model model, const Vector3& position, const Vector3& scale,
		Vector3 rotationAxis, float rotationAngle, btDiscreteDynamicsWorld* dynamicsWorld)
		: BlockData(rigidBody, name, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld) {}
	~QuestionBlock(){}
};