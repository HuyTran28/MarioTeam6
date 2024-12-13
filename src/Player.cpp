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
    float height = (modelBounds.max.y - modelBounds.min.y) * scale - 0.5f; // Height of the model

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
    if (newVelocity.length() > velocityThreshold)
        m_rigidBody->setLinearVelocity(newVelocity);
}

void Player::rotate() {
    float angularVelocity = 0.0f;
    if (IsKeyDown(KEY_A)) {
        angularVelocity = 5.0f;  // Positive for counterclockwise rotation
    }
    if (IsKeyDown(KEY_D)) {
        angularVelocity = -5.0f;  // Negative for clockwise rotation
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
    float invGravity = 1.0f / -m_dynamicsWorld->getGravity().getY();

    if (m_isOnGround && IsKeyDown(KEY_SPACE)) {
        m_isJumping = true;      // Start the jump
        m_jumpTimer = 0.0f;      // Reset the jump timer
        m_isOnGround = false;    // Player is now airborne

        // Increase the jump force for a higher jump
        float acceleration = (m_jumpForce * 1.5f) / m_rigidBody->getMass();
        m_maxJumpDuration = sqrt(acceleration / m_rigidBody->getMass() * invGravity); // Simplified physics calculation
    }

    if (m_isJumping) {
        // Increment the jump timer
        m_jumpTimer += GetFrameTime();

        // Calculate the current jump force based on the elapsed time
        float currentJumpForce = m_jumpForce * 2.0f * (1.0f - (m_jumpTimer / m_maxJumpDuration));

        // Apply the current jump force
        m_rigidBody->applyCentralImpulse(btVector3(0, currentJumpForce * GetFrameTime(), 0));

        // End the jump if the max jump duration is reached
        if (m_jumpTimer >= m_maxJumpDuration) {
            m_isJumping = false;
        }
    }

    // Apply additional gravity to make the player fall faster
    if (!m_isOnGround && !m_isJumping) {
        btVector3 additionalGravity(0, -9.8f * 2.0f * GetFrameTime(), 0); // Increase gravity effect
        m_rigidBody->applyCentralImpulse(additionalGravity);

        // Ensure the velocity is negative to trigger fall animation
        btVector3 currentVelocity = m_rigidBody->getLinearVelocity();
        if (currentVelocity.getY() > 0.01) {
            m_rigidBody->setLinearVelocity(btVector3(currentVelocity.getX(), -fabs(currentVelocity.getY()), currentVelocity.getZ()));
        }
    }
}

void Player::updateAnimationState() {
    btVector3 currentVelocity = m_rigidBody->getLinearVelocity();

    if (!m_isOnGround) {
        // Check if the player is moving horizontally while airborne
        if (currentVelocity.length2() > 0.1f && fabs(currentVelocity.getY()) > 0.01f) {
         
            m_animationManager->playAnimation(3); // Play the jump move animation
        }
        else if (currentVelocity.getY() > 0.0f) {
       
            m_animationManager->playAnimation(3); // Play the jump animation
        }
    }
    else {
        
        // Player is grounded
        if (currentVelocity.length() > 0.1f) {
            
            m_animationManager->playAnimation(4); // Play the walking animation
        }
        else {
            
            m_animationManager->playAnimation(2); // Play the idle animation
        }
    }

    // Update the animation frame based on the player's movement
    m_animationManager->updateAnimation(GetFrameTime());
}



void Player::update() {
    m_isOnGround = checkGroundCollision();  // Update grounded state
	
    if (!m_isOnGround) {
        // Apply gravity
        btVector3 velocity = m_rigidBody->getLinearVelocity();
        btVector3 gravity = m_dynamicsWorld->getGravity();
        m_rigidBody->applyCentralForce(gravity);

        // Apply extra gravity for faster falling if needed
        const float extraGravityFactor = 2.0f;
        btVector3 additionalGravity(0, extraGravityFactor * gravity.getY(), 0);

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

	btVector3 playerVelocity = m_rigidBody->getLinearVelocity();
	updateAnimationState();  // Update animation state
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
	m_health -= 10;
    if (m_health <= 0) {
		// Player is dead
	}
}

Player::~Player() {
	// Free the player model
	UnloadModel(m_model);
}
