#include "Enemy.h"

Enemy::Enemy(btRigidBody* rigidBody, Model model, const Vector3& position, const Vector3& forwardDir, const float& speed, const float& scale)
    : CharacterInterface(rigidBody, model, position, speed, scale, nullptr), m_forwardDir(forwardDir)
{}