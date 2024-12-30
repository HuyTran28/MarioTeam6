#include "PlayerData.h"



PlayerData::PlayerData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState,
	std::string modelPath, const Vector3& forwardDir, const Vector3& position, const float& speed, const Vector3& scale, const Vector3& rotaionAxis,
	const float& rotationAngle, const float& jumpForce, const int& health, std::shared_ptr<btDynamicsWorld> world, bool isSpecial,
	float specialDuration, float specialTimer, float invicibilityTimer, bool isInvincible, float invincibilityDuration, float throwTimer, float throwDuration, bool m_isThrowing)
	: CharacterData(rigidBody, shape, motionState, modelPath, position, health, scale, rotaionAxis, rotationAngle, speed, world)
{
	m_jumpForce = jumpForce;
	m_maxJumpDuration = 0.5f;
	m_isCrouching = false;
	m_forwardDir = forwardDir;
	objectType = "Player-Normal";
	m_isSpecial = isSpecial;
	m_specialDuartion = specialDuration;
	m_specialTimer = specialTimer;
	m_invincibilityTimer = invicibilityTimer;
	m_isInvincible = isInvincible;
	m_invincibilityDuration = invincibilityDuration;
	m_throwTimer = throwTimer;
	m_throwDuration = throwDuration;
	m_isThrowing = m_isThrowing;
}

void PlayerData::save(std::ofstream& file)
{
	CharacterData::save(file);

	file << m_isJumping << " ";
	file << m_isCrouching << " ";
	file << m_jumpForce << " ";
	file << m_jumpTimer << " ";
	file << m_maxJumpDuration << " ";
	file << bigDuration << " ";
	file << isBig << " ";
	file << m_invincibilityTimer << " ";
	file << m_isInvincible << " ";
	file << m_invincibilityDuration << " ";
	file << m_throwTimer << " ";
	file << m_throwDuration << " ";
	file << m_isThrowing << " ";
	file << m_isSpecial << " ";
	file << m_specialDuartion << " ";
	file << m_specialTimer;
}

void PlayerData::load(std::ifstream& file)
{
	CharacterData::load(file);

	file >> m_isJumping;
	file >> m_isCrouching;
	file >> m_jumpForce;
	file >> m_jumpTimer;
	file >> m_maxJumpDuration;
	file >> bigDuration;
	file >> isBig;
	file >> m_invincibilityTimer;
	file >> m_isInvincible;
	file >> m_invincibilityDuration;
	file >> m_throwTimer;
	file >> m_throwDuration;
	file >> m_isThrowing;
	file >> m_isSpecial;
	file >> m_specialDuartion;
	file >> m_specialTimer;
}


//Vector3 PlayerData::getForwarDir() const
//{
//	return m_forwardDir;
//}

bool PlayerData::getIsBig() const
{
	return isBig;
}

float PlayerData::getInvincibilityTimer() const
{
	return m_invincibilityTimer;
}

float PlayerData::getThrowTimer() const
{
	return m_throwTimer;
}

bool PlayerData::getIsSpecial() const
{
	return m_isSpecial;
}

float PlayerData::getSpecialDuration() const
{
	return m_specialDuartion;
}

float PlayerData::getSpecialTimer() const
{
	return m_specialTimer;
}

float PlayerData::getThrowDuration() const
{
	return m_throwDuration;
}

bool PlayerData::getIsThrowing() const
{
	return m_isThrowing;
}

bool PlayerData::getIsvincible() const
{
	return m_isInvincible;
}

float PlayerData::getInvincibilityDuration() const
{
	return m_invincibilityDuration;
}

void PlayerData::setInvincibilityTimer(float timer)
{
	m_invincibilityTimer = timer;
}

void PlayerData::setThrowTimer(float timer)
{
	m_throwTimer = timer;
}

void PlayerData::setIsThrowing(bool isThrowing)
{
	m_isThrowing = isThrowing;
}

void PlayerData::setIsSpecial(bool isSpecial)
{
	m_isSpecial = isSpecial;
}

void PlayerData::setSpecialTimer(float timer)
{
	m_specialTimer = timer;
}

void PlayerData::setIsvincible(bool isVincible)
{
	m_isInvincible = isVincible;
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



void PlayerData::setSpecialDuration(float duration)
{
	m_specialDuartion = duration;
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
