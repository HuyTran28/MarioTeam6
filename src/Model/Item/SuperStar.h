#pragma once
#include "ItemData.h"
#include "btBulletDynamicsCommon.h"
#include <memory>


class SuperStar : public ItemData
{
public:
	SuperStar(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState
		, const std::string& modelPath, const Model& model, const Vector3& position, const Vector3& scale,
		const Vector3& rotationAxis, const float& rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		:ItemData(rigidBody, shape, motionState, model, position, scale, rotationAxis, rotationAngle, modelPath, dynamicsWorld) {
		objectType = "Item-SuperStar";
	}
};