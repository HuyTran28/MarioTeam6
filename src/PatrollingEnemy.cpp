#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, const Vector3& patrolPointA, const Vector3& patrolPointB)
    : Enemy(rigidBody, model, forwardDir, position, speed, scale), m_patrolPointA(patrolPointA), m_patrolPointB(patrolPointB),
      m_movingToA(true), m_detectionRange(10.0f), m_attackSpeed(2.0f), m_isChasing(false), m_targetPosition(Vector3()) {}

PatrollingEnemy::~PatrollingEnemy() {
    Enemy::~Enemy();
}

void PatrollingEnemy::patrol() {
    // Select the target position based on whether the enemy is moving to A or B
    Vector3 targetPosition = m_movingToA ? m_patrolPointA : m_patrolPointB;
    moveTo(targetPosition);

    // Check if the enemy has reached the target position with some tolerance
    if (Vector3Distance(m_position, targetPosition) < 1.0f) {
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
}

void PatrollingEnemy::render() {
    // Use the base class's render implementation
    Enemy::render();
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
    // Automatically adjust direction towards the target or patrol
    // Implement rotation logic if needed
}

bool PatrollingEnemy::checkGroundCollision() {
    // Use the base class's checkGroundCollision implementation
    return Enemy::checkGroundCollision();
}
