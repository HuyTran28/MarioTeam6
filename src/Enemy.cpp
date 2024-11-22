#include "Enemy.h"

Enemy::Enemy(btRigidBody* rigidBody, Model model, const Vector3& position, const float& speed, const float& scale)
    : CharacterInterface(rigidBody, model, position, speed, scale, nullptr)
{}