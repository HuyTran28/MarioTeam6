#pragma once

#include "BlockData.h"
#include "btBulletCollisionCommon.h"
class QuestionBlock : public BlockData
{
private:
	bool isOpen = true;
public:
	QuestionBlock(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass,
		btVector3 inertia, const std::string& name, Model model, const Vector3& position, const Vector3& scale,
		Vector3 rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		: BlockData(rigidBody, shape, motionState, mass, inertia, name, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld) {}
	//~QuestionBlock(){}
};