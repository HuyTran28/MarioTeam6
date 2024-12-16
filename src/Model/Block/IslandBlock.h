#pragma once

#include "BlockData.h"
class IslandBlock : public BlockData
{

public:
	IslandBlock(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass,
		btVector3 inertia, const std::string& name, Model model, const Vector3& position, const Vector3& scale,
		Vector3 rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		: BlockData(rigidBody, shape, motionState, mass, inertia, name, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld) {
		objectType = "Block-Normal";
	}
	//~IslandBlock(){}
};