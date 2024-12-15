#pragma once
#include "Enemy.h"

class Koopa : public Enemy
{
public:
	Koopa(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::string modelPath, const Vector3& position, const Vector3& forwardDir, const Vector3& pointA, const Vector3& pointB, const float& speed, const Vector3& scale,
		const Vector3& rotaionAxis, const float& rotationAngle, std::shared_ptr< btDynamicsWorld> world, std::string name)
		: Enemy(rigidBody, shape, motionState, modelPath, position, forwardDir, pointA, pointB, speed, scale, rotaionAxis, rotationAngle, world, name) {}


};