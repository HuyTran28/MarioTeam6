#pragma once
#include "CharacterInterface.h"

class Enemy : public CharacterInterface {
protected:
    Vector3 m_forwardDir;

public:
    Enemy(btRigidBody* rigidBody, Model model, const Vector3& position, const Vector3& forwardDir, const float& speed, const float& scale);

    void move() override = 0;
    void rotate() override = 0;
    void update() override = 0;
    void onCollision(const CollisionEvent& event) override = 0;

    ~Enemy() override = default;
};