#include "Player.h"
#include "raylib.h"
#include "raymath.h"

#include "CollisionUtils.h"

using namespace std;

// Constructor: Initialize player attributes and Bullet RigidBody
Player::Player(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, const float& jumpForce, const int& health, btDynamicsWorld* world)
    : CharacterInterface(rigidBody, model, position, speed, scale, world), m_jumpForce(jumpForce), m_health(health), m_isCrouching(false), m_forwardDir(forwardDir) 
{}

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

    btScalar mass = 75.0f;
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
    btVector3 desiredVelocity(0, 0, 0);

    // Calculate the desired movement direction based on input
    if (IsKeyDown(KEY_W)) {
        desiredVelocity = btVector3(m_forwardDir.x, 0, m_forwardDir.z).normalized() * m_speed;
    }
    // Smooth acceleration towards the desired velocity
    const float accelerationFactor = 5.0f; // Higher values mean faster acceleration
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
    if (m_isOnGround) {
        // Predefined jump velocity magnitude (tweak for gameplay feel)
        const float jumpVelocityMagnitude = 50.0f;

        // Apply the impulse for the jump
        float mass = (m_rigidBody->getInvMass() > 0) ? 1.0f / m_rigidBody->getInvMass() : 1.0f;
        btVector3 jumpImpulse(0, jumpVelocityMagnitude * mass, 0);

        m_rigidBody->applyCentralImpulse(jumpImpulse);

        // Set ground flag
        m_isOnGround = false;
    }
}


void Player::update() {
    m_isOnGround = checkGroundCollision();
    if (!m_isOnGround) {
        btVector3 velocity = m_rigidBody->getLinearVelocity();
        float gravityFactor = 2.0f; // Increase fall acceleration (tweak this value)
        btVector3 additionalGravity(0, gravityFactor * m_dynamicsWorld->getGravity().getY(), 0);

        if (velocity.getY() < 0.0f) { // Apply additional force only when falling
            m_rigidBody->applyCentralForce(additionalGravity);
        }

        // Reduce damping for smooth movement while airborne
        m_rigidBody->setDamping(0.1f, m_rigidBody->getAngularDamping());
    }
    else {
        // Restore damping when on the ground
        m_rigidBody->setDamping(0.5f, m_rigidBody->getAngularDamping());
    }
    move();
    rotate();
    if (IsKeyDown(KEY_SPACE))
        jump();

    updateModelTransform();
	updateCollisionShape();
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

void Player::setLastCollisionEvent(const CollisionEvent& event) {
	m_lastCollisionEvent = event;
}



Player::~Player() {
	// Free the player model
	UnloadModel(m_model);
}
