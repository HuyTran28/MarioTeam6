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
	btDynamicsWorld* m_dynamicsWorld;  // Store the dynamics world
	btRigidBody* m_rigidBody;
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
	PlayerData(btRigidBody* rigidBody, std::string modelPath, const Vector3& position, const int& health, const Vector3& scale
		, const Vector3& rotaionAxis, float rotationAngle, const float& speed, btDynamicsWorld* world);

	Vector3 getPlayerPos() const;
	int getPlayerHealth() const;
	Model getPlayerModel() const;
	BoundingBox getPlayerBoundingBox() const;
	Vector3 getPlayerScale() const;
	Vector3 getPlayerRotationAxis() const;
	float getPlayerRotationAngle() const;
	float getMoveSpeed() const;
	Vector3 getVelocity() const;
	btRigidBody* getRigidBody() const;
	btDynamicsWorld* getWorld() const;


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