#include "Enemy.h"
#include "Player.h"
#include "CollisionUtils.h"

Enemy::Enemy(btRigidBody* rigidBody, std::string modelPath, const Vector3& position, const Vector3& forwardDir, const float& speed, const float& scale, btDynamicsWorld* world)
    : CharacterInterface(rigidBody, modelPath, position, speed, scale, world), m_forwardDir(forwardDir), m_currentState(nullptr)
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
    if (m_currentState) {
        m_currentState->update(this);
    }
    this->updateCollisionShape();
    this->updateModelTransform();
}

void Enemy::determineCollisionType(CollisionEvent& event) {
    if (dynamic_cast<Player*>(event.obj1) || dynamic_cast<Player*>(event.obj2)) {
        CollisionUtils::determineCollisionType(event);
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