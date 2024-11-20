#include "Player.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

// Constructor: Initialize player attributes and Bullet RigidBody
Player::Player(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, const float& jumpForce, const int& health, btDynamicsWorld* world)
    : CharacterInterface(rigidBody, model, forwardDir, position, speed, scale, world), m_jumpForce(jumpForce), m_health(health), m_isCrouching(false) {}

// Method:Player::createPlayer
Player* Player::createPlayer(btDiscreteDynamicsWorld* world, const std::string& modelPath, const Vector3& startPosition,
    const Vector3& forwardDir, float speed, float scale, float jumpForce, int health) {
    // Load the player model first to get dimensions
    Model playerModel = LoadModel(modelPath.c_str());
    BoundingBox modelBounds = GetModelBoundingBox(playerModel);
    
    // Calculate dimensions for collision shape
    Vector3 dimensions = {
        (modelBounds.max.x - modelBounds.min.x) * scale,
        (modelBounds.max.y - modelBounds.min.y) * scale,
        (modelBounds.max.z - modelBounds.min.z) * scale
    };

    // Calculate the offset to position the collision shape below the model
    float offsetY = (modelBounds.max.y - modelBounds.min.y) * scale * 0.5f;

    // Player rigid body setup
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y - offsetY, startPosition.z));
    
    // Create box shape based on model dimensions
    btCollisionShape* playerShape = new btBoxShape(btVector3(
        dimensions.x * 0.5f,  // Half-extents
        dimensions.y * 0.5f,
        dimensions.z * 0.5f
    ));

    btScalar mass = 70.0f;
    btVector3 localInertia(0, 0, 0);
    playerShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, playerShape, localInertia);

    btRigidBody* playerRigidBody = new btRigidBody(rbInfo);
    playerRigidBody->setActivationState(DISABLE_DEACTIVATION);
    
    // Add player to the world
    world->addRigidBody(playerRigidBody);

    return new Player(playerRigidBody, playerModel, forwardDir, startPosition, speed, scale, jumpForce, health, world);
}

void Player::move() {
    btVector3 movement(0, 0, 0);

    if (IsKeyDown(KEY_W)) {
        movement = btVector3(m_forwardDir.x, 0, m_forwardDir.z).normalized() * m_speed;
    }
    if (IsKeyDown(KEY_S)) {
        movement = btVector3(-m_forwardDir.x, 0, -m_forwardDir.z).normalized() * m_speed;
    }

    // Only apply the movement if it is non-zero
    if (movement.length() > 0) {
        m_rigidBody->setLinearVelocity(movement);
    }

    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    // Add a threshold to ignore very small position changes
    const float positionThreshold = 0.001f;
    if (btVector3(m_position.x, m_position.y, m_position.z).distance(pos) > positionThreshold) {
        m_position = { pos.x(), pos.y(), pos.z() };
    }
}

void Player::rotate() {
    float angularVelocity = 0.0f;
    if (IsKeyDown(KEY_A)) {
        angularVelocity = 1.0f;  // Positive for counterclockwise rotation
    }
    if (IsKeyDown(KEY_D)) {
        angularVelocity = -1.0f;  // Negative for clockwise rotation
    }

    // Apply angular velocity around the Y-axis for rotation
    m_rigidBody->setAngularVelocity(btVector3(0, angularVelocity, 0));
    
	if (angularVelocity == 0) {
        return;
    }

    // Update the forward direction based on rotation
    m_rotationAngle += angularVelocity * GetFrameTime();
    Matrix rotationMatrix = MatrixRotateY(m_rotationAngle);
    m_forwardDir = Vector3Normalize(Vector3Transform(Vector3{ 0.0f, 0.0f, 1.0f }, rotationMatrix));
}

void Player::updateCollisionShape() {
    // Update the collision shape's scale based on the model's scale
    btVector3 bulletScale(m_scale, m_scale, m_scale);
    m_rigidBody->getCollisionShape()->setLocalScaling(bulletScale);

    // Update the collision shape's transformation to match the model's position and rotation
    btTransform transform;
    m_rigidBody->getMotionState()->getWorldTransform(transform);
    transform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

    // Convert the model's rotation matrix into a Bullet quaternion
    Matrix rotationMatrix = MatrixRotateY(m_rotationAngle); // Assumes Y-axis rotation
    Quaternion modelQuaternion = QuaternionFromMatrix(rotationMatrix);
    transform.setRotation(btQuaternion(modelQuaternion.x, modelQuaternion.y, modelQuaternion.z, modelQuaternion.w));

    // Update the rigid body's transformation
    m_rigidBody->setWorldTransform(transform);
    m_rigidBody->getMotionState()->setWorldTransform(transform);

    // Activate the rigid body to ensure changes take effect
    m_rigidBody->activate(true);
}

void Player::updateModelTransform() {
    // Translation matrix for position
    Matrix translationMatrix = MatrixTranslate(m_position.x, m_position.y, m_position.z);

    // Calculate the right vector as the cross product of the world up and forward direction
    Vector3 right = Vector3CrossProduct(Vector3{ 0.0f, 1.0f, 0.0f }, m_forwardDir);
    right = Vector3Normalize(right);

    // Calculate the up vector as the cross product of forward direction and right vector
    Vector3 up = Vector3CrossProduct(m_forwardDir, right);
    up = Vector3Normalize(up);

    // Create rotation matrix with right, up, and forward vectors as columns
    Matrix rotationMatrix = {
        right.x, up.x, m_forwardDir.x, 0.0f,
        right.y, up.y, m_forwardDir.y, 0.0f,
        right.z, up.z, m_forwardDir.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // Combine rotation and translation matrices (rotation first, then translation)
    m_model.transform = MatrixMultiply(rotationMatrix, translationMatrix);
}

void Player::render() {
	CharacterInterface::render();
}

void Player::jump() {
    if (m_isOnGround && IsKeyPressed(KEY_SPACE)) {
        // Apply an upward force for jumping
        btVector3 jumpForce(0, m_jumpForce, 0);
        m_rigidBody->setLinearVelocity(jumpForce);

        // Set the flag to prevent double-jumping
        m_isOnGround = false;
    }
}

bool Player::checkGroundCollision() {
	return CharacterInterface::checkGroundCollision();
}

void Player::update()
{
    m_isOnGround = checkGroundCollision();
    rotate();
    jump();
    move();
    updateModelTransform();
    updateCollisionShape();
}

Player::~Player() {
	// Free the player model
	UnloadModel(m_model);
}
