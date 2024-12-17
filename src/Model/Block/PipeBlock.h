#pragma once
#include "BlockData.h"


class PipeBlock : public BlockData
{
private:
	btVector3 newPosition;

public:
	PipeBlock(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass,
		btVector3 inertia, const Model& model, const Vector3& position, const Vector3& scale,
		const Vector3& rotationAxis, const float& rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		: BlockData(rigidBody, shape, motionState, mass, inertia, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld) {
		objectType = "Block-Pipe";
		
	}
	void setNewPosition(btVector3 position)
	{
		newPosition = position;
	}

	btVector3 getNewPosition() const
	{
		return newPosition;
	}
	//~PipeBlock(){}
};