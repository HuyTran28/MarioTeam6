#include "Enemy.h"



Enemy::Enemy(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState,
	std::string modelPath, const Vector3& position, const Vector3& forwardDir, const Vector3& pointA, const Vector3& pointB, const float& speed, const Vector3& scale, const Vector3& rotaionAxis, const float& rotationAngle, std::shared_ptr<btDynamicsWorld> world, std::string name)
	: CharacterData(rigidBody, shape, motionState, modelPath, position, 0, scale, rotaionAxis, rotationAngle, speed, world)
{
	m_forwardDir = forwardDir;
	m_pointA = pointA;
	m_pointB = pointB;
	m_movingToA = true;
}

void Enemy::setForwardDir(const Vector3& dir)
{
	m_forwardDir = dir;
}

Vector3 Enemy::getForwardDir() const
{
	return m_forwardDir;
}

Vector3 Enemy::getPointA() const
{
	return m_pointA;
}

Vector3 Enemy::getPointB() const
{
	return m_pointB;
}

Vector3 Enemy::getTargetPosition() const
{
	return m_targetPosition;
}

bool Enemy::getMovingToA() const
{
	return m_movingToA;
}

void Enemy::setMovingToA(bool movingToA)
{
	m_movingToA = movingToA;
}

void Enemy::setTargetPosistion(Vector3 targetPos)
{
	m_targetPosition = targetPos;
}

void Enemy::setPosition(const Vector3& pos)
{
	playerPos = pos;
}

float Enemy::getSpeed() const
{
	return moveSpeed;
}

void Enemy::setIsDie(bool isDie)
{
	m_isDie = isDie;
}

bool Enemy::getIsDie() const
{
	return m_isDie;
}

bool Enemy::getIsThrowing() const
{
	return m_isThrowing;
}

float Enemy::getThrowTimer() const
{
	return m_throwTimer;
}

void Enemy::setThrowTimer(float timer)
{
	m_throwTimer = timer;
}

void Enemy::setIsThrowing(bool isThrowing)
{
	m_isThrowing = isThrowing;
}

void Enemy::save(std::ofstream& file)
{
	CharacterData::save(file);
	file << m_pointA.x << " " << m_pointA.y << " " << m_pointA.z << " ";
	file << m_pointB.x << " " << m_pointB.y << " " << m_pointB.z << " ";
	file << m_movingToA << " ";
	file << m_isDie << " ";
}

void Enemy::load(std::ifstream& file)
{
	CharacterData::load(file);
	file >> m_pointA.x >> m_pointA.y >> m_pointA.z;
	file >> m_pointB.x >> m_pointB.y >> m_pointB.z;
	file >> m_movingToA;
	file >> m_isDie;
}

Enemy::~Enemy()
{

}
