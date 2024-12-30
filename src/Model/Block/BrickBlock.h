#pragma once

#include "BlockData.h"
class BrickBlock : public BlockData
{

public:
	BrickBlock(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass,
		btVector3 inertia, const Model& model, const Vector3& position, const Vector3& scale,
		const Vector3& rotationAxis, const float& rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, bool isbouncing = false, float bounceTime = 0.0f, float gravity = 9.81, float velocity = 0.0f)
		: BlockData(rigidBody, shape, motionState, mass, inertia, model, position, scale, rotationAxis, rotationAngle, dynamicsWorld, isbouncing, bounceTime, gravity, velocity) {
		objectType = "Block-Normal-Brick";
	}
	void save(std::ofstream& file) override
	{
		BlockData::save(file);
	}
	void load(std::ifstream& file) override
	{
		BlockData::load(file);
	}
	//~BrickBlock(){}
};