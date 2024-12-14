#include "Mario.h"



Mario::Mario(btRigidBody* rigidBody, std::string modelPath, const Vector3& forwardDir, const Vector3& position, const float& speed, const Vector3& scale, const Vector3& rotaionAxis, const float& rotationAngle, const float& jumpForce, const int& health, btDynamicsWorld* world)
	: PlayerData(rigidBody, modelPath, position, health, scale, rotaionAxis, rotationAngle, speed, world)
{
	m_jumpForce = jumpForce;
	m_isCrouching = false;
	m_forwardDir = forwardDir;
}

//Mario::Mario(btRigidBody* rigidBody, std::string modelPath, Vector3 forwardDir, Vector3 position, float speed, Vector3 scale, Vector3 rotationAxis, float rotationAngle, float jumpForce, int health, btDynamicsWorld* world)
//	: PlayerData(rigidBody, modelPath, position, health, scale, rotationAxis, rotationAngle, speed, world)
//{
//	m_jumpForce = jumpForce;
//	m_isCrouching = false;
//	m_forwardDir = forwardDir;
//}

Vector3 Mario::getForwarDir() const
{
	return m_forwardDir;
}

bool Mario::getIsJumping() const
{
	return m_isJumping;
}

bool Mario::getIsCrouching() const
{
	return m_isCrouching;
}

float Mario::getJumpForce() const
{
	return m_jumpForce;
}

float Mario::getJumpTimer() const
{
	return m_jumpTimer;
}

float Mario::getMaxJumpDuration() const
{
	return m_maxJumpDuration;
}

void Mario::setForwarDir(const Vector3& forwardDir)
{
	m_forwardDir = forwardDir;
}

void Mario::setIsJumping(bool isJumping)
{
	m_isJumping = isJumping;
}

void Mario::setJumpTimer(float jumTimer)
{
	m_jumpTimer = jumTimer;
}

void Mario::setMaxJumpDuaration(float maxJumpDuaration)
{
	m_maxJumpDuration = maxJumpDuaration;
}

Mario::~Mario()
{
}
