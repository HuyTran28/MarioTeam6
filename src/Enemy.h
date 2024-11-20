#pragma once
#include "CharacterInterface.h"

class Enemy : public CharacterInterface {
public:
    Enemy(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
        const float& speed, const float& scale);

    void move() override = 0;
    void rotate() override = 0;
    void render() override;
    bool checkGroundCollision() override;

    ~Enemy() override = default;
};
