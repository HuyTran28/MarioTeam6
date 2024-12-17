#include "CharacterData.h"

CharacterData::CharacterData()
{
	playerModelPath = "../../Assets\\Models\\joystick2.glb";
	playerModel = LoadModel(playerModelPath.c_str());
	playerPos = Vector3{ 0.0f, 0.0f, 0.0f };
	playerHealth = 100;
	playerScale = Vector3{ 10.0f, 10.0f, 10.0f };
	playerRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	playerRotationAngle = 0.0f;
	playerBoundingBox = GetModelBoundingBox(playerModel);
	moveSpeed = 1.0f;
}


CharacterData::~CharacterData()
{

	UnloadModel(playerModel);
}

Vector3 CharacterData::getPlayerPos() const
{
	return playerPos;
}

int CharacterData::getPlayerHealth() const
{
	return playerHealth;
}

Model CharacterData::getPlayerModel() const
{
	return playerModel;
}

BoundingBox CharacterData::getPlayerBoundingBox() const
{
	return playerBoundingBox;
}

Vector3 CharacterData::getPlayerScale() const
{
	return playerScale;
}

Vector3 CharacterData::getPlayerRotationAxis() const
{
	return playerRotationAxis;
}

float CharacterData::getPlayerRotationAngle() const
{
	return playerRotationAngle;
}

float CharacterData::getMoveSpeed() const
{
	return moveSpeed;
}

Vector3 CharacterData::getVelocity() const
{
	return m_velocity;
}

std::shared_ptr<btRigidBody> CharacterData::getRigidBody() const
{
	if (m_rigidBody)
		return m_rigidBody;
}

std::shared_ptr<btDynamicsWorld> CharacterData::getWorld() const
{
	return m_dynamicsWorld;
}


std::shared_ptr<ModelAnimation> CharacterData::getModelAnimation() const
{
	return m_animations;
}

int CharacterData::getAnimationCount() const
{
	return m_animationCount;
}

int CharacterData::getCurrentAnimation() const
{
	return m_currentAnimation;
}

float CharacterData::getAnimationFrame() const
{
	return m_animationFrame;
}

void CharacterData::setModelAnimation(std::shared_ptr<ModelAnimation> modelAnimation)
{
	m_animations = modelAnimation;
}

void CharacterData::setAnimationCount(int animationCount)
{
	m_animationCount = animationCount;
}

void CharacterData::setCurrentAnimation(int currentAnimation)
{
	m_currentAnimation = currentAnimation;
}

void CharacterData::setAnimationFrame(float animationFrame)
{
	m_animationFrame = animationFrame;
}

void CharacterData::setPlayerScale(Vector3 playerScale)
{
	this->playerScale = playerScale;
}

void CharacterData::setPlayerRotationAxis(Vector3 playerRotationAxis)
{
	this->playerRotationAxis = playerRotationAxis;
}

void CharacterData::setPlayerRotationAngle(float playerRotationAngle)
{
	this->playerRotationAngle = playerRotationAngle;
}

void CharacterData::setPlayerPos(Vector3 playerPos)
{
	this->playerPos = playerPos;
}

void CharacterData::setPlayerHealth(int playerHealth)
{
	this->playerHealth = playerHealth;
}

void CharacterData::setPlayerModel(Model playerModel)
{
	this->playerModel = playerModel;
}

void CharacterData::setPlayerBoundingBox(BoundingBox playerBoundingBox)
{
	this->playerBoundingBox = playerBoundingBox;
}

void CharacterData::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void CharacterData::setPlayerModelTransform(const Matrix& transform)
{
	playerModel.transform = transform;
}

void CharacterData::setRigidBodyTransform(const btTransform& transform)
{
	if (m_rigidBody)
	{
		m_rigidBody->setWorldTransform(transform);

		if (m_rigidBody->getMotionState() != nullptr) {
			m_rigidBody->getMotionState()->setWorldTransform(transform);
		}

		m_rigidBody->activate(true);
	}

}

void CharacterData::setLinearVelocity(btVector3 newVelocity)
{
	if (m_rigidBody)
		m_rigidBody->setLinearVelocity(newVelocity);
}

bool CharacterData::getIsOnGround() const
{
	return m_isOnGround;
}

void CharacterData::setIsOnGround(bool isOnGround)
{
	m_isOnGround = isOnGround;
}

void CharacterData::applyCentralImpulse(btVector3 impulse)
{
	if (m_rigidBody)
		m_rigidBody->applyCentralImpulse(impulse);
}

void CharacterData::applyCentralForce(btVector3 force)
{
	if (m_rigidBody)
		m_rigidBody->applyCentralForce(force);
}

void CharacterData::setDamping(float linearDamping, float angularDamping)
{
	if (m_rigidBody)
		m_rigidBody->setDamping(linearDamping, angularDamping);
}

void CharacterData::setWorldTransform(const btTransform& transform)
{
	if (m_rigidBody)
		m_rigidBody->setWorldTransform(transform);
}

//CharacterData::CharacterData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed)
//{
//	this->playerPos = playerPos;
//	this->playerHealth = playerHealth;
//	this->playerModel = playerModel;
//	this->playerBoundingBox = playerBoundingBox;
//	this->playerModelPath = playerModelPath;
//	playerScale = Vector3{ 10.0f, 10.0f, 10.0f };
//	playerRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
//	playerRotationAngle = 0.0f;
//	this->moveSpeed = moveSpeed;
//}
void CharacterData::setPlayerAnimationState(PlayerAnimationState animationState)
{
	m_animationState = animationState;
}

PlayerAnimationState CharacterData::getPlayerAnimationState() const
{
	return m_animationState;
}

CharacterData::CharacterData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState,
	std::string modelPath, const Vector3& position, const int& health, const Vector3& scale, const Vector3& rotaionAxis, float rotationAngle,
	const float& speed, std::shared_ptr<btDynamicsWorld> world) : CollidableObject(rigidBody, shape, motionState, world)
{
	playerModelPath = modelPath;
	playerPos = position;
	playerHealth = health;
	playerModel = LoadModel(playerModelPath.c_str());
	playerScale = scale;
	playerRotationAxis = rotaionAxis;
	playerRotationAngle = rotationAngle;
	this->moveSpeed = speed;

	m_isOnGround = true;
	m_velocity = { 0.0f, 0.0f, 0.0f };


	playerModel.transform = MatrixScale(scale.x, scale.y, scale.z);


	ModelAnimation* tmp = LoadModelAnimations(playerModelPath.c_str(), &m_animationCount);
	std::shared_ptr<ModelAnimation> modelAnimation(tmp);
	m_currentAnimation = 0;
	m_animationFrame = 0.0f;
	this->m_animations = modelAnimation;

	if (m_animationCount == 0) {
		m_animations = nullptr;
	}

	btTransform trans;
	m_rigidBody->getMotionState()->getWorldTransform(trans);

	btVector3 physicalPosition = trans.getOrigin();
	playerPos = { physicalPosition.x(), physicalPosition.y(), physicalPosition.z() };
	// Set the rigid body's user pointer to this character
	m_rigidBody->setUserPointer(this);
	m_rigidBody->setGravity(btVector3(0, -9.81 * m_rigidBody->getMass(), 0));
	m_dynamicsWorld->addRigidBody(m_rigidBody.get());
}





