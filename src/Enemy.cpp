#include "Enemy.h"

Enemy::Enemy(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position, const float& speed, const float& scale)
    : CharacterInterface(rigidBody, model, forwardDir, position, speed, scale, nullptr)
{
}

void Enemy::render() {
     CharacterInterface::render();
}

bool Enemy::checkGroundCollision() {
    return CharacterInterface::checkGroundCollision();
}
