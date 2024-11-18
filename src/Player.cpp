#include "Player.h"
#include "raylib.h" // Include raylib for IsKeyDown and GetFrameTime
#include "raymath.h"
#include "btBulletDynamicsCommon.h"

using namespace std;

// Constructor: Initialize player attributes and Bullet RigidBody
Player::Player(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, const float& jumpForce, const int& health)
    : CharacterInterface(rigidBody, model, forwardDir, position, speed, scale), m_jumpForce(jumpForce), m_health(health), m_isCrouching(false) {}

Player* Player::createPlayer(btDiscreteDynamicsWorld* world, const std::string& modelPath, const Vector3& startPosition,
    const Vector3& forwardDir, float speed, float scale, float jumpForce, int health) {
    // Player rigid body setup
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z)); // Start position of the player

    btCollisionShape* playerShape = new btCapsuleShape(0.5f, 1.5f); // Capsule shape for the player
    btScalar mass = 70.0f;
    btVector3 localInertia(0, 0, 0);
    playerShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, playerShape, localInertia);

    btRigidBody* playerRigidBody = new btRigidBody(rbInfo);

    // Add player to the world
    world->addRigidBody(playerRigidBody);

    // Create the player object
    Model playerModel = LoadModel(modelPath.c_str()); // Load the player model from the given path

    return new Player(playerRigidBody, playerModel, forwardDir, startPosition, speed, scale, jumpForce, health);
}

void Player::move() {
    btVector3 movement(0, 0, 0);

    if (IsKeyDown(KEY_W)) {
        movement = btVector3(m_forwardDir.x, 0, m_forwardDir.z).normalized() * m_speed;
        m_rigidBody->setLinearVelocity(movement);  
    }
    if (IsKeyDown(KEY_S)) {
        movement = btVector3(-m_forwardDir.x, 0, -m_forwardDir.z).normalized() * m_speed;
        m_rigidBody->setLinearVelocity(movement);  
    }

    // Update m_position based on rigid body position
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    m_position = { pos.x(), pos.y(), pos.z() };
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

    // Update the forward direction based on rotation
    m_rotationAngle += angularVelocity * GetFrameTime();
    Matrix rotationMatrix = MatrixRotateY(m_rotationAngle);
    m_forwardDir = Vector3Normalize(Vector3Transform(Vector3{ 0.0f, 0.0f, 1.0f }, rotationMatrix));
}

void Player::applyGravity() {
    // Bullet handles gravity through its world settings, no need for manual gravity application
}

void Player::render() {
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

    // Draw the model at the correct position and scale
    DrawModel(m_model, Vector3{ 0.0f, 0.0f, 0.0f }, m_scale, RAYWHITE);
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
    return true;
}


void Player::update()
{
    m_isOnGround = checkGroundCollision();
    rotate();
    if (m_isOnGround)
    {
        jump();
        move();
    }
}

Player::~Player() {
	// Free the player model
	UnloadModel(m_model);
}



