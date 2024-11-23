#include "PatrollingEnemy.h"
#include "Player.h"


PatrollingEnemy::PatrollingEnemy(btRigidBody* rigidBody, Model model, const Vector3& position,
    const float& speed, const float& scale, const Vector3& patrolPointA, const Vector3& patrolPointB)
    : Enemy(rigidBody, model, position, speed, scale), m_patrolPointA(patrolPointA), m_patrolPointB(patrolPointB),
    m_movingToA(true), m_detectionRange(10.0f), m_attackSpeed(2.0f), m_isChasing(false), m_targetPosition(Vector3())
{
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);

    btVector3 physPos = trans.getOrigin();
    m_position = { physPos.x(), physPos.y(), physPos.z() };
}


void PatrollingEnemy::patrol() {
    // Select the target position based on whether the enemy is moving to A or B
    Vector3 targetPosition = m_movingToA ? m_patrolPointA : m_patrolPointB;
    moveTo(targetPosition);

    // Check if the enemy has reached the target position with some tolerance
    float distance = Vector3Distance(m_position, targetPosition);

    if (distance < 1.5f) {
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

void PatrollingEnemy::onCollision(const CollisionEvent& event) {
    if (auto* player = dynamic_cast<Player*>(event.obj1)) {
        for (const auto& point : event.contactPoints) {
            if (point.m_normalWorldOnB.getY() > 0.7f) {
                this->isStamped();
                return;
            }
        }
    }
}

void PatrollingEnemy::isStamped() {
	cout << "Enemy is stamped!" << endl;
    // Define the respawn position (you can adjust this as needed)
    Vector3 respawnPosition = m_patrolPointA; // Example: respawn at patrol point A

    // Reset the enemy's position to the respawn position
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(respawnPosition.x, respawnPosition.y, respawnPosition.z));
    m_rigidBody->setWorldTransform(trans);
    m_rigidBody->getMotionState()->setWorldTransform(trans);

    // Update the internal position
    m_position = respawnPosition;

    // Reset other states if necessary
    m_isChasing = false;
    m_targetPosition = Vector3();
    m_movingToA = true; // Reset to start patrolling from point A
}


void PatrollingEnemy::update() {
    rotate();
	move();
	updateCollisionShape();
	updateModelTransform();
}
