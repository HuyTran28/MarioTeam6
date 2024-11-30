#include "PatrollingEnemy.h"
#include "Player.h"


PatrollingEnemy::PatrollingEnemy(btRigidBody* rigidBody, Model model, const Vector3& position, const Vector3& forwardDir, const float& speed, const float& scale, const Vector3& patrolPointA, const Vector3& patrolPointB, btDynamicsWorld* world)
    :Enemy(rigidBody, model, position, forwardDir, speed, scale, world), m_patrolPointA(patrolPointA), m_patrolPointB(patrolPointB),
    m_movingToA(true), m_detectionRange(10.0f), m_attackSpeed(2.0f), m_isChasing(false), m_targetPosition(Vector3())
{}


void PatrollingEnemy::patrol() {
    // Select the target position based on whether the enemy is moving to A or B
    m_targetPosition = m_movingToA ? m_patrolPointA : m_patrolPointB;
    moveTo();

    // Check if the enemy has reached the target position with some tolerance
    float distance = Vector3Distance(m_position, m_targetPosition);

    if (distance < 2.0f) {
        m_movingToA = !m_movingToA; // Switch target point after reaching current point
        m_targetPosition = m_movingToA ? m_patrolPointA : m_patrolPointB;
        rotate();
    }
}


void PatrollingEnemy::detectPlayer(const Vector3& playerPosition) {
    // Check if the player is within detection range
    float distance = Vector3Distance(playerPosition, m_position);
    if (distance < m_detectionRange) {
        m_isChasing = true;
        m_targetPosition = playerPosition;
    } else {
        m_isChasing = false;
    }
}

void PatrollingEnemy::chasePlayer() {
    if (m_isChasing) {
        moveTo();
    }
}

void PatrollingEnemy::moveTo() {

    Vector3 direction = Vector3Normalize(m_targetPosition - m_position);
    btVector3 movement(direction.x, 0, direction.z);
    m_rigidBody->setLinearVelocity(movement * m_speed);

    // Update position
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    m_position = { pos.x(), pos.y(), pos.z() };
}

void PatrollingEnemy::move() {
    // Handle either patrolling or chasing
    patrol();
   /* if (m_isChasing) {
        chasePlayer();
    } else {
        patrol();
    }*/
}

void PatrollingEnemy::rotate() {
    // Step 1: Calculate the desired direction
    Vector3 desiredDirection = Vector3Subtract(m_targetPosition, m_position);
    if (Vector3Length(desiredDirection) < 0.001f) return; // Avoid division by zero
    desiredDirection = Vector3Normalize(desiredDirection);

    // Step 2: Get the current forward direction
    Vector3 normalizedForwardDir = Vector3Normalize(m_forwardDir);
    btTransform transform;
    m_rigidBody->getMotionState()->getWorldTransform(transform);
    btQuaternion currentRotation = transform.getRotation();
    btVector3 worldForward = quatRotate(currentRotation, btVector3(normalizedForwardDir.x, normalizedForwardDir.y, normalizedForwardDir.z));
    Vector3 currentForwardDir = Vector3Normalize({ worldForward.getX(), worldForward.getY(), worldForward.getZ() });

    // Step 3: Calculate the rotation axis
    Vector3 rotationAxis = Vector3CrossProduct(currentForwardDir, desiredDirection);
    if (Vector3Length(rotationAxis) < 0.001f) {
        if (Vector3DotProduct(currentForwardDir, desiredDirection) < -0.999f) {
            rotationAxis = { 0.0f, -1.0f, 0.0f }; // Arbitrary perpendicular axis
        }
        else {
            return; // Already aligned, no rotation needed
        }
    }
    rotationAxis = Vector3Normalize(rotationAxis);

    // Step 4: Calculate the rotation angle
    float dot = Vector3DotProduct(currentForwardDir, desiredDirection);
    float angle = acosf(Clamp(dot, -1.0f, 1.0f)); // Clamp for safety



    // Step 5: Create and apply the rotation
    if (angle > 0.01f) { // Skip tiny rotations
        btQuaternion rotation(btVector3(rotationAxis.x, rotationAxis.y, rotationAxis.z), angle);
        btQuaternion newRotation = rotation * currentRotation;

        // Smoothly interpolate the rotation
        btQuaternion interpolatedRotation = slerp(currentRotation, newRotation, 0.1f);
        interpolatedRotation.normalize(); // Normalize to avoid numerical errors

        // Update transform (preserve position)
        btVector3 currentPosition = transform.getOrigin();
        transform.setRotation(interpolatedRotation);
        transform.setOrigin(currentPosition);

        // Apply to rigid body
        m_rigidBody->setWorldTransform(transform);
    }
	m_rotationAngle = angle;
}

void PatrollingEnemy::onCollision(const CollisionEvent& event) {
    if (event.type == CollisionType::Stomped) {
        this->isStamped();
    }
}

void PatrollingEnemy::isStamped() {
	"Enemy stamped!";
}

void PatrollingEnemy::update() {
    move();
	updateCollisionShape();
	updateModelTransform();
}
