#include "PlayerData.h"



PlayerData::PlayerData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState,
	std::string modelPath, const Vector3& forwardDir, const Vector3& position, const float& speed, const Vector3& scale, const Vector3& rotaionAxis,
	const float& rotationAngle, const float& jumpForce, const int& health, std::shared_ptr<btDynamicsWorld> world)
	: CharacterData(rigidBody, shape, motionState, modelPath, position, health, scale, rotaionAxis, rotationAngle, speed, world)
{
	m_jumpForce = jumpForce;
	m_isCrouching = false;
	m_forwardDir = forwardDir;
	objectType = "Player-Normal";
}


Vector3 PlayerData::getForwarDir() const
{
	return m_forwardDir;
}

bool PlayerData::getIsBig() const
{
	return isBig;
}

float PlayerData::getBigDuration() const
{
	return bigDuration;
}

void PlayerData::setIsBig(bool isBig)
{
	this->isBig = isBig;
}

void PlayerData::setBigDuration(float bigDuration)
{
	this->bigDuration = bigDuration;
}

void PlayerData::setIsCrouching(bool isCrouching)
{
	m_isCrouching = isCrouching;
}

bool PlayerData::getIsJumping() const
{
	return m_isJumping;
}

bool PlayerData::getIsCrouching() const
{
	return m_isCrouching;
}

float PlayerData::getJumpForce() const
{
	return m_jumpForce;
}

float PlayerData::getJumpTimer() const
{
	return m_jumpTimer;
}

float PlayerData::getMaxJumpDuration() const
{
	return m_maxJumpDuration;
}



void PlayerData::setForwarDir(const Vector3& forwardDir)
{
	m_forwardDir = forwardDir;
}

void PlayerData::setIsJumping(bool isJumping)
{
	m_isJumping = isJumping;
}

void PlayerData::setJumpTimer(float jumTimer)
{
	m_jumpTimer = jumTimer;
}

void PlayerData::setMaxJumpDuaration(float maxJumpDuaration)
{
	m_maxJumpDuration = maxJumpDuaration;
}



PlayerData::~PlayerData()
{
}
