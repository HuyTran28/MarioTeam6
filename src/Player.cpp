#include "Player.h"
#include "raylib.h"
#include "raymath.h"

#include "CollisionUtils.h"

using namespace std;

// Constructor: Initialize player attributes and Bullet RigidBody
Player::Player(btRigidBody* rigidBody, string modelPath, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, const float& jumpForce, const int& health, btDynamicsWorld* world)
    : CharacterInterface(rigidBody, modelPath, position, speed, scale, world), m_jumpForce(jumpForce), m_health(health), m_isCrouching(false), m_forwardDir(forwardDir) 
{}

Player* Player::createPlayer(btDiscreteDynamicsWorld* world, const std::string& modelPath, const Vector3& startPosition,
    const Vector3& forwardDir, float speed, float scale, float jumpForce, int health) {
    
    Model playerModel = LoadModel(modelPath.c_str());
    BoundingBox modelBounds = GetModelBoundingBox(playerModel);

    // Calculate the arm span (distance along the X-axis)
    float armSpan = (modelBounds.max.x - modelBounds.min.x) * scale;

    // Set the capsule radius to half the arm span
    float radius = armSpan * 0.5f - 0.2f;

    // Calculate height of the capsule based on the model's bounding box
    float height = (modelBounds.max.y - modelBounds.min.y) * scale; // Height of the model

    // Adjust height to exclude spherical parts of the capsule
    float capsuleHeight = height - radius;
    if (capsuleHeight < 0) {
        capsuleHeight = 0; // Prevent negative height
    }

    // Define initial transformation for the player
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z));

    // Create capsule shape
    btCollisionShape* playerShape = new btCapsuleShape(radius, capsuleHeight);

    // Physics body setup remains the same
    btScalar mass = 75.0f;
    btVector3 localInertia(0, 0, 0);
    playerShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, playerShape, localInertia);

    btRigidBody* playerRigidBody = new btRigidBody(rbInfo);

    // Add the player to the physics world
    world->addRigidBody(playerRigidBody);

    return new Player(playerRigidBody, modelPath, forwardDir, startPosition, speed, scale, jumpForce, health, world);
}

void Player::move() {
    btVector3 desiredVelocity(0, 0, 0);

    // Calculate the desired movement direction based on input
    if (IsKeyDown(KEY_W)) {
        desiredVelocity = btVector3(m_forwardDir.x, 0, m_forwardDir.z).normalized() * m_speed;
    }
    // Smooth acceleration towards the desired velocity
    const float accelerationFactor = 100.0f; // Higher values mean faster acceleration
    btVector3 currentVelocity = m_rigidBody->getLinearVelocity();
    btVector3 acceleration = (desiredVelocity - currentVelocity) * accelerationFactor * GetFrameTime();

    // Update the player's velocity with acceleration
    btVector3 newVelocity = currentVelocity + acceleration;

    // Clamp the new velocity to the max speed
    if (newVelocity.length() > m_speed) {
        newVelocity = newVelocity.normalized() * m_speed;
    }

    // Apply the new velocity if significant
    const float velocityThreshold = 0.01f;
    if (newVelocity.length() > velocityThreshold) {
        m_rigidBody->setLinearVelocity(newVelocity);
    }

    // Update the player's position from the rigid body's transform
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    // Increase the threshold to ignore very small position changes
    const float positionThreshold = 1.0f; // Increased from 0.001f
    if (btVector3(m_position.x, m_position.y, m_position.z).distance(pos) > positionThreshold) {
        m_position = { pos.x(), pos.y(), pos.z() };
    }

	m_animationManager->playAnimation(1);  // Play the player's idle animation (index 0
}

void Player::rotate() {
    float angularVelocity = 0.0f;
    if (IsKeyDown(KEY_A)) {
        angularVelocity = 1.0f;  // Positive for counterclockwise rotation
    }
    if (IsKeyDown(KEY_D)) {
        angularVelocity = -1.0f;  // Negative for clockwise rotation
    }
    
	if (angularVelocity == 0) {
        return;
    }
	
    // Update the forward direction based on rotation
    m_rotationAngle += angularVelocity * GetFrameTime();
    Matrix rotationMatrix = MatrixRotateY(m_rotationAngle);
    m_forwardDir = Vector3Normalize(Vector3Transform(Vector3{ 0.0f, 0.0f, 1.0f }, rotationMatrix));
}


void Player::jump() {
    if (m_isOnGround && IsKeyDown(KEY_SPACE)) {
        m_isJumping = true;      // Start the jump
        m_jumpTimer = 0.0f;      // Reset the jump timer
        m_isOnGround = false;    // Player is now airborne

        // Calculate max jump duration based on jump force
        float acceleration = m_jumpForce / m_rigidBody->getMass();  // a = F / m
        float initialVelocity = acceleration * GetFrameTime(); // Initial velocity based on force and frame time

        // Max jump duration based on velocity and gravity (ignoring air resistance)
        float gravity = 9.81f;  // Gravity acceleration
        m_maxJumpDuration = initialVelocity / gravity / 10.0f;
    }

    // Apply continuous jump force while the timer is below max duration
    if (m_isJumping && m_jumpTimer < m_maxJumpDuration) 
    {
        // Apply upward force during the jump duration
        m_rigidBody->applyCentralForce(btVector3(0, m_jumpForce, 0));
        m_jumpTimer += GetFrameTime();  // Increment the jump timer
    }
    else 
    {
        m_isJumping = false;  // Stop applying force once the timer expires
    }
}



void Player::update() {
    m_isOnGround = checkGroundCollision();  // Update grounded state
	
    if (!m_isOnGround) {
        // Apply extra gravity for faster falling if needed
        btVector3 velocity = m_rigidBody->getLinearVelocity();
        const float extraGravityFactor = 2.0f;
        btVector3 additionalGravity(0, extraGravityFactor * m_dynamicsWorld->getGravity().getY(), 0);

        if (velocity.getY() < 0.0f) {  // Only apply extra gravity when falling
            m_rigidBody->applyCentralForce(additionalGravity);
        }

        // Reduce damping for smooth motion in the air
        m_rigidBody->setDamping(0.1f, m_rigidBody->getAngularDamping());
    }
    else {
        // Restore damping when on the ground
        m_rigidBody->setDamping(0.5f, m_rigidBody->getAngularDamping());
    }

    move();    // Update movement
    rotate();  // Update rotation
    jump();  // Handle jumping

    updateCollisionShape();  // Update collision shape
    updateModelTransform();  // Synchronize model with physics body

	m_animationManager->updateAnimation(GetFrameTime());  // Update the player's animation
}



void Player::determineCollisionType(CollisionEvent& event) {
    if (dynamic_cast<Enemy*>(event.obj2)) {
        CollisionUtils::determineCollisionType(event);
    }
}


void Player::onCollision(const CollisionEvent& event) {
    if (event.type == CollisionType::Stomped) {
        this->handleJumpOnEnemy();
    }
    else if (event.type == CollisionType::HitByEnemy) {
        this->handleTouchEnemy();
    }
}

void Player::handleJumpOnEnemy() {
    //std::cout << "Handling jump on enemy." << std::endl;
}

void Player::handleTouchEnemy() {
    //std::cout << "Handling touch with enemy." << std::endl;
    
}

Player::~Player() {
	// Free the player model
	UnloadModel(m_model);
}
