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

PlayerData::PlayerData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed)
{
	this->playerPos = playerPos;
	this->playerHealth = playerHealth;
	this->playerModel = playerModel;
	this->playerBoundingBox = playerBoundingBox;
	this->playerModelPath = playerModelPath;
	playerScale = Vector3{ 10.0f, 10.0f, 10.0f };
	playerRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	playerRotationAngle = 0.0f;
	this->moveSpeed = moveSpeed;
}

PlayerData::PlayerData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::string modelPath, const Vector3& position, const int& health, const Vector3& scale, const Vector3& rotaionAxis, float rotationAngle, const float& speed, std::shared_ptr<btDynamicsWorld> world)
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

	btTransform trans;
	m_rigidBody->getMotionState()->getWorldTransform(trans);

	btVector3 physicalPosition = trans.getOrigin();
	playerPos = { physicalPosition.x(), physicalPosition.y(), physicalPosition.z() };
	// Set the rigid body's user pointer to this character
	m_rigidBody->setUserPointer(this);
	m_rigidBody->setGravity(btVector3(0, -9.81 * m_rigidBody->getMass(), 0));
	m_dynamicsWorld->addRigidBody(m_rigidBody.get());
}





void PlayerData::updateCollisionShape()
{
	// Get the rigid body's current transform
	btTransform transform = m_rigidBody->getWorldTransform();

	// Force the rotation to align with the Y-axis (capsule's up-axis)

	transform.setRotation(btQuaternion(0, 0, 0, 1));


	// Update the rigid body's transformation
	m_rigidBody->setWorldTransform(transform);
	m_rigidBody->getMotionState()->setWorldTransform(transform);

	// Ensure the rigid body is active
	m_rigidBody->activate(true);
}

void PlayerData::updateModelTransform()
{
	// Get the rigid body's transform
	btTransform transform = m_rigidBody->getWorldTransform();
	btVector3 origin = transform.getOrigin();

	// Get the bounding box of the model
	BoundingBox modelBounds = GetModelBoundingBox(playerModel);
	float modelHeight = (modelBounds.max.y - modelBounds.min.y) * playerScale.y;

	// Retrieve the collision shape and calculate capsule dimensions
	btCollisionShape* collisionShape = m_rigidBody->getCollisionShape();
	btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(collisionShape);
	float capsuleRadius = capsuleShape->getRadius();
	float capsuleHeight = capsuleShape->getHalfHeight() * 2.0f + capsuleRadius * 2.0f;

	// Calculate the vertical offset to align the model's center with the capsule's center
	float yOffset = (capsuleHeight / 2) - capsuleRadius * 1.7f - (modelHeight / 2);

	// Update the model position
	playerPos = { origin.getX(), origin.getY() + yOffset, origin.getZ() };

	// Apply rotation and scale to the model
	Matrix rotationMatrix = MatrixRotateY(playerRotationAngle);
	Matrix scaleMatrix = MatrixScale(playerScale.x, playerScale.y, playerScale.z);

	// Combine the transformations and apply to the model
	playerModel.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}

bool PlayerData::checkGroundCollision()
{
	if (m_rigidBody) {
		// Get the current motion state of the rigid body
		btTransform transform;
		m_rigidBody->getMotionState()->getWorldTransform(transform);

		// Perform a raycast below the character to check for ground
		btVector3 start = transform.getOrigin();
		btVector3 end = start - btVector3(0, 3.0f, 0);

		btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
		m_dynamicsWorld->rayTest(start, end, rayCallback);

		if (rayCallback.hasHit()) {
			// If the ray hits something, we are on the ground
			return true;
		}
	}

	return false;
}

void PlayerData::playAnimation(int animationIndex)
{
	m_animationManager->playAnimation(animationIndex);
}