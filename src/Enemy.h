#pragma once
#include "CharacterInterface.h"

class Enemy : public CharacterInterface {
public:
    Enemy(btRigidBody* rigidBody, Model model, const Vector3& position,
        const float& speed, const float& scale);

    void move() override = 0;
    void rotate() override = 0;
	void update() override = 0;
	void onCollision(const CollisionEvent& event) override = 0;

    ~Enemy() override = default;
};
