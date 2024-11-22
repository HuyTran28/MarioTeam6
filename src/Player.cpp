#include "Player.h"
#include "raylib.h"
#include "raymath.h"

using namespace std;

// Constructor: Initialize player attributes and Bullet RigidBody
Player::Player(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, const float& jumpForce, const int& health, btDynamicsWorld* world)
    : CharacterInterface(rigidBody, model, position, speed, scale, world), m_jumpForce(jumpForce), m_health(health), m_isCrouching(false), m_forwardDir(forwardDir) {}

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
   
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y + 1.0f, startPosition.z));
    
    // Create box shape based on model dimensions
    btCollisionShape* playerShape = new btBoxShape(btVector3(
        dimensions.x * 0.3f,  // Half-extents
        dimensions.y * 0.4f,
        dimensions.z * 0.3f
    ));

    btScalar mass = 70.0f;
    btVector3 localInertia(0, 0, 0);
    playerShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, playerShape, localInertia);

    btRigidBody* playerRigidBody = new btRigidBody(rbInfo);
    
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

void Player::jump() {
    if (m_isOnGround && IsKeyPressed(KEY_SPACE)) {
        // Apply an upward force for jumping
        btVector3 jumpForce(0, m_jumpForce, 0);
        m_rigidBody->setLinearVelocity(jumpForce);

        // Set the flag to prevent double-jumping
        m_isOnGround = false;
    }
}

void Player::update()
{
    m_isOnGround = checkGroundCollision();
    move();
    rotate();
    jump();

	updateCollisionShape();
	updateModelTransform();
}

Player::~Player() {
	// Free the player model
	UnloadModel(m_model);
}
