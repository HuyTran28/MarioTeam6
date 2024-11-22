#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(btRigidBody* rigidBody, Model model, const Vector3& position,
    const float& speed, const float& scale, const Vector3& patrolPointA, const Vector3& patrolPointB)
    : Enemy(rigidBody, model, position, speed, scale), m_patrolPointA(patrolPointA), m_patrolPointB(patrolPointB),
    m_movingToA(true), m_detectionRange(10.0f), m_attackSpeed(2.0f), m_isChasing(false), m_targetPosition(Vector3())
{
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);

    btVector3 physPos = trans.getOrigin();
    m_position = { physPos.x(), physPos.y(), physPos.z() };

    // Debug prints to verify patrol points
    std::cout << "Patrol Point A: (" << m_patrolPointA.x << ", " << m_patrolPointA.y << ", " << m_patrolPointA.z << ")" << std::endl;
    std::cout << "Patrol Point B: (" << m_patrolPointB.x << ", " << m_patrolPointB.y << ", " << m_patrolPointB.z << ")" << std::endl;
}


void PatrollingEnemy::patrol() {
    // Select the target position based on whether the enemy is moving to A or B
    Vector3 targetPosition = m_movingToA ? m_patrolPointA : m_patrolPointB;
    moveTo(targetPosition);

    // Check if the enemy has reached the target position with some tolerance
    float distance = Vector3Distance(m_position, targetPosition);
    std::cout << "Current position: (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")" << std::endl;
    std::cout << "Target position: (" << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << ")" << std::endl;
    std::cout << "Distance to target: " << distance << std::endl;

    if (distance < 1.5f) {
        std::cout << "Reached patrol point: " << (m_movingToA ? "A" : "B") << std::endl;
        m_movingToA = !m_movingToA; // Switch target point after reaching current point
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
        moveTo(m_targetPosition);
    }
}

void PatrollingEnemy::moveTo(const Vector3& targetPosition) {

    Vector3 direction = Vector3Normalize(targetPosition - m_position);
    btVector3 movement(direction.x, 0, direction.z);
    m_rigidBody->setLinearVelocity(movement * m_speed);

    // Update position
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    m_position = { pos.x(), pos.y(), pos.z() };
    std::cout << "Updated position: (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")" << std::endl;
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
    // Calculate the direction vector towards the target position
    Vector3 direction = Vector3Subtract(m_targetPosition, m_position);

    // Normalize the direction vector to get the forward direction
    direction = Vector3Normalize(direction);

    // Calculate the angle to rotate the enemy to face the target
    float angle = atan2(direction.x, direction.z); // Assuming forward in +Z

    // Convert the angle to a quaternion rotation (Raylib or Bullet can help here)
    Quaternion rotation = QuaternionFromAxisAngle(Vector3{ 0.0f, 1.0f, 0.0f }, angle);

    // Update the model's transform to apply the rotation
    m_model.transform = MatrixRotate(Vector3{ 0.0f, 1.0f, 0.0f }, angle);

    
}


void PatrollingEnemy::update() {
    rotate();
	move();
	updateCollisionShape();
	updateModelTransform();
}
