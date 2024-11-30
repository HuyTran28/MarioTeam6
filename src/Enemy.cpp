#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(btRigidBody* rigidBody, Model model, const Vector3& position, const Vector3& forwardDir, const float& speed, const float& scale, btDynamicsWorld* world)
    : CharacterInterface(rigidBody, model, position, speed, scale, world), m_forwardDir(forwardDir), m_currentState(nullptr)
{}

void Enemy::kill() {
    // Disable the physics by deactivating the rigid body
    m_rigidBody->setActivationState(DISABLE_SIMULATION);

    m_model.meshCount = 0;
}

void Enemy::setState(std::unique_ptr<EnemyState> newState) {
    m_currentState = std::move(newState);
}

EnemyState* Enemy::getState() const {
    return m_currentState.get();
}

void Enemy::move() {
    if (m_currentState) {
        m_currentState->move(this);
    }
}

void Enemy::update() {
    this->updateCollisionShape();
    this->updateModelTransform();
    if (m_currentState) {
        m_currentState->update(this);
    }
}

void Enemy::determineCollisionType(CollisionEvent& event) {
    // Check if the collision involves the player
    if (event.obj1 == this || event.obj2 == this) {
        CharacterInterface* other = (event.obj1 == this) ? event.obj2 : event.obj1;

        // Check if the other object is the player
        if (dynamic_cast<Player*>(other)) {
            btRigidBody* enemy = this->getRigidBody(); // Enemy's collision object
            btCollisionShape* shape = enemy->getCollisionShape(); // Enemy's collision shape

            // Retrieve the bounding box of the enemy using the collision shape
            btVector3 enemyMin, enemyMax;
            shape->getAabb(enemy->getWorldTransform(), enemyMin, enemyMax);

            const float epsilon = 0.01f;
            // Check if any contact point is at the top of the bounding box
            bool isHighestPoint = false;
            for (const auto& contactPoint : event.contactPoints) {
                btVector3 normal = contactPoint.m_normalWorldOnB;
                if (normal.getY() > 0.9f && contactPoint.getPositionWorldOnB().getY() >= enemyMax.getY() - epsilon) {
                    isHighestPoint = true;
                    break;
                }
            }

            // If the enemy is the highest point, it is stomped
            event.type = isHighestPoint ? CollisionType::Stomped : CollisionType::HitByEnemy;
        }
    }
}

// Getter and Setter for Forward Direction
void Enemy::setForwardDir(const Vector3& dir) {
    m_forwardDir = dir;
}

Vector3 Enemy::getForwardDir() const {
    return m_forwardDir;
}

// Getter and Setter for Position
void Enemy::setPosition(const Vector3& pos) {
    m_position = pos;
}

// Getter for Speed
float Enemy::getSpeed() const {
    return m_speed;
}


Enemy::~Enemy() 
{
    CharacterInterface::~CharacterInterface();
}