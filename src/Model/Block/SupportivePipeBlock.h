#pragma once

#include "BlockData.h"
class SupportivePipeBLock : public BlockData
{

public:
	SupportivePipeBLock(btRigidBody* rigidBody, const std::string& name, Model model, const Vector3& position, const Vector3& scale,
		Vector3 rotationAxis, float rotationAngle, btDiscreteDynamicsWorld* dynamicsWorld)
		: BlockData(rigidBody, name, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld) {}
	~SupportivePipeBLock(){}
};