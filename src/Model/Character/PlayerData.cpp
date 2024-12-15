#include "PlayerData.h"

PlayerData::PlayerData()
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


PlayerData::~PlayerData()
{

	UnloadModel(playerModel);
}

Vector3 PlayerData::getPlayerPos() const
{
	return playerPos;
}

int PlayerData::getPlayerHealth() const
{
	return playerHealth;
}

Model PlayerData::getPlayerModel() const
{
	return playerModel;
}

BoundingBox PlayerData::getPlayerBoundingBox() const
{
	return playerBoundingBox;
}

Vector3 PlayerData::getPlayerScale() const
{
	return playerScale;
}

Vector3 PlayerData::getPlayerRotationAxis() const
{
	return playerRotationAxis;
}

float PlayerData::getPlayerRotationAngle() const
{
	return playerRotationAngle;
}

float PlayerData::getMoveSpeed() const
{
	return moveSpeed;
}

Vector3 PlayerData::getVelocity() const
{
	return m_velocity;
}

std::shared_ptr<btRigidBody> PlayerData::getRigidBody() const
{
	if(m_rigidBody)
		return m_rigidBody;
}

std::shared_ptr<btDynamicsWorld> PlayerData::getWorld() const
{
	return m_dynamicsWorld;
}


std::shared_ptr<ModelAnimation> PlayerData::getModelAnimation() const
{
	return m_animations;
}

int PlayerData::getAnimationCount() const
{
	return m_animationCount;
}

int PlayerData::getCurrentAnimation() const
{
	return m_currentAnimation;
}

float PlayerData::getAnimationFrame() const
{
	return m_animationFrame;
}

void PlayerData::setModelAnimation(std::shared_ptr<ModelAnimation> modelAnimation)
{
	m_animations = modelAnimation;
}

void PlayerData::setAnimationCount(int animationCount)
{
	m_animationCount = animationCount;
}

void PlayerData::setCurrentAnimation(int currentAnimation)
{
	m_currentAnimation = currentAnimation;
}

void PlayerData::setAnimationFrame(float animationFrame)
{
	m_animationFrame = animationFrame;
}

void PlayerData::setPlayerScale(Vector3 playerScale)
{
	this->playerScale = playerScale;
}

void PlayerData::setPlayerRotationAxis(Vector3 playerRotationAxis)
{
	this->playerRotationAxis = playerRotationAxis;
}

void PlayerData::setPlayerRotationAngle(float playerRotationAngle)
{
	this->playerRotationAngle = playerRotationAngle;
}

void PlayerData::setPlayerPos(Vector3 playerPos)
{
	this->playerPos = playerPos;
}

void PlayerData::setPlayerHealth(int playerHealth)
{
	this->playerHealth = playerHealth;
}

void PlayerData::setPlayerModel(Model playerModel)
{
	this->playerModel = playerModel;
}

void PlayerData::setPlayerBoundingBox(BoundingBox playerBoundingBox)
{
	this->playerBoundingBox = playerBoundingBox;
}

void PlayerData::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void PlayerData::setPlayerModelTransform(const Matrix& transform)
{
	playerModel.transform = transform;
}

void PlayerData::setRigidBodyTransform(const btTransform& transform)
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

void PlayerData::setLinearVelocity(btVector3 newVelocity)
{
	if (m_rigidBody)
		m_rigidBody->setLinearVelocity(newVelocity);
}

bool PlayerData::getIsOnGround() const
{
	return m_isOnGround;
}

void PlayerData::setIsOnGround(bool isOnGround)
{
	m_isOnGround = isOnGround;
}

void PlayerData::applyCentralImpulse(btVector3 impulse)
{
	if(m_rigidBody)
		m_rigidBody->applyCentralImpulse(impulse);
}

void PlayerData::applyCentralForce(btVector3 force)
{
	if (m_rigidBody)
		m_rigidBody->applyCentralForce(force);
}

void PlayerData::setDamping(float linearDamping, float angularDamping)
{
	if(m_rigidBody)
		m_rigidBody->setDamping(linearDamping, angularDamping);
}

void PlayerData::setWorldTransform(const btTransform& transform)
{
	if (m_rigidBody)
		m_rigidBody->setWorldTransform(transform);
}

//PlayerData::PlayerData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed)
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
void PlayerData::setPlayerAnimationState(PlayerAnimationState animationState)
{
	m_animationState = animationState;
}

PlayerAnimationState PlayerData::getPlayerAnimationState() const
{
	return m_animationState;
}

PlayerData::PlayerData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState,
	std::string modelPath, const Vector3& position, const int& health, const Vector3& scale, const Vector3& rotaionAxis, float rotationAngle, 
	const float& speed, std::shared_ptr<btDynamicsWorld> world)
{
	m_rigidBody = rigidBody;
	m_collisionShape = shape;
	m_motionState = motionState;
	m_dynamicsWorld = world;
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

	//m_animationManager = std::make_unique<AnimationManager>(playerModel, modelPath.c_str());

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





