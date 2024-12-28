#pragma once

#include <raylib.h>
#include "btBulletDynamicsCommon.h"
#include <string>
#include <memory>
#include "../../Event/CollisionEvent.h"
#include "raymath.h"
#include "../CollidableObject.h"

enum class PlayerAnimationState {
	IDLE,
	WALKING,
	JUMPING,
	FALLING,
	HIT,
	DIE,
	WIN,
	THROW
};


class CharacterData : public CollidableObject
{
protected:

	bool m_isUsed = false;
	const float m_duarationOfBoomerang = 30.0f;
	float m_timeBoomerang = 0.0f;


	Vector3 m_velocity;
	bool m_isOnGround;
	Vector3 m_forwardDir;
	Vector3 playerPos;
	int playerHealth;
	Model playerModel;
	Vector3 playerScale;
	Vector3 playerRotationAxis;
	float playerRotationAngle;
	BoundingBox playerBoundingBox;
	std::string playerModelPath;
	float moveSpeed;

	std::shared_ptr<ModelAnimation> m_animations;
	int m_animationCount;
	int m_currentAnimation;
	float m_animationFrame;
	PlayerAnimationState m_animationState = PlayerAnimationState::IDLE;




public:
	CharacterData();
	CharacterData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed);
	CharacterData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, 
		std::string modelPath, const Vector3& position, const int& health, const Vector3& scale
		,const Vector3& rotaionAxis, float rotationAngle, const float& speed, std::shared_ptr<btDynamicsWorld> world);

	Vector3 getPlayerPos() const;
	int getPlayerHealth() const;
	Model getPlayerModel() const;
	BoundingBox getPlayerBoundingBox() const;
	Vector3 getPlayerScale() const;
	Vector3 getPlayerRotationAxis() const;
	Vector3 getForwardDir() const;
	float getPlayerRotationAngle() const;
	float getMoveSpeed() const;
	Vector3 getVelocity() const;
	std::shared_ptr<btRigidBody> getRigidBody() const;
	std::shared_ptr<btDynamicsWorld> getWorld() const;
	PlayerAnimationState getPlayerAnimationState() const;

	std::shared_ptr<ModelAnimation> getModelAnimation() const;
	int getAnimationCount() const;
	int getCurrentAnimation() const;
	float getAnimationFrame() const;


	void setModelAnimation(std::shared_ptr<ModelAnimation> modelAnimation);
	void setAnimationCount(int animationCount);
	void setCurrentAnimation(int currentAnimation);
	void setAnimationFrame(float animationFrame);
	void setPlayerAnimationState(PlayerAnimationState animationState);

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
	void setWorldTransform(const btTransform& transform);



	bool getIsUsed() const;
	void setIsUsed(bool isUsed);
	float getDurationBoomerang() const;
	float getTimeOfBoomerang() const;
	void setTimeOfBoomerang(float time);

	virtual ~CharacterData();
};