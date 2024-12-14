#pragma once

#include <raylib.h>
#include "btBulletDynamicsCommon.h"
#include <string>
#include "AnimationManager.h"
#include <memory>
#include "../../Event/CollisionEvent.h"
#include "raymath.h"

class PlayerData
{
protected:
	std::shared_ptr<btDynamicsWorld> m_dynamicsWorld;  // Store the dynamics world
	std::shared_ptr<btRigidBody> m_rigidBody;
	std::shared_ptr<btCollisionShape> m_collisionShape;
	std::shared_ptr<btDefaultMotionState> m_motionState;
	Vector3 m_velocity;
	bool m_isOnGround;
	std::unique_ptr<AnimationManager> m_animationManager; // Composition


	Vector3 playerPos;
	int playerHealth;
	Model playerModel;
	Vector3 playerScale;
	Vector3 playerRotationAxis;
	float playerRotationAngle;
	BoundingBox playerBoundingBox;
	std::string playerModelPath;
	float moveSpeed;




public:
	PlayerData();
	PlayerData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed);
	PlayerData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::string modelPath, const Vector3& position, const int& health, const Vector3& scale
		, const Vector3& rotaionAxis, float rotationAngle, const float& speed, std::shared_ptr<btDynamicsWorld> world);

	Vector3 getPlayerPos() const;
	int getPlayerHealth() const;
	Model getPlayerModel() const;
	BoundingBox getPlayerBoundingBox() const;
	Vector3 getPlayerScale() const;
	Vector3 getPlayerRotationAxis() const;
	float getPlayerRotationAngle() const;
	float getMoveSpeed() const;
	Vector3 getVelocity() const;
	std::shared_ptr<btRigidBody> getRigidBody() const;
	std::shared_ptr<btDynamicsWorld> getWorld() const;


	void setPlayerPos(Vector3 playerPos);
	void setPlayerHealth(int playerHealth);
	void setPlayerModel(Model playerModel);
	void setPlayerBoundingBox(BoundingBox playerBoundingBox);
	void setPlayerScale(Vector3 playerScale);
	void setPlayerRotationAxis(Vector3 playerRotationAxis);
	void setPlayerRotationAngle(float playerRotationAngle);
	void setMoveSpeed(float moveSpeed);


	void setPlayerModelTransform(const Matrix& transform);
	void setRigidBodyTransform(const btTransform& transform);
	void setLinearVelocity(btVector3 newVelocity);
	bool getIsOnGround() const;
	void setIsOnGround(bool isOnGround);
	void applyCentralImpulse(btVector3 impulse);
	void applyCentralForce(btVector3 force);
	void setDamping(float linearDamping, float angularDamping);


	void updateCollisionShape();
	void updateModelTransform();
	bool checkGroundCollision();
	void playAnimation(int animationIndex);

	virtual ~PlayerData();
};