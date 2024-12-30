#pragma once

#include "BlockData.h"
#include "btBulletCollisionCommon.h"
class QuestionBlock : public BlockData
{
private:
	bool isOpen = true;
public:
	QuestionBlock(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass,
		btVector3 inertia, const Model& model, const Vector3& position, const Vector3& scale,
		const Vector3& rotationAxis, const float& rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		: BlockData(rigidBody, shape, motionState, mass, inertia, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld) {
		objectType = "Block-Question";
	}
	void save(std::ofstream& file) override
	{
		BlockData::save(file);
	}
	void load(std::ifstream& file) override
	{
		BlockData::load(file);
	}
	//~QuestionBlock(){}
};