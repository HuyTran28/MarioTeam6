#pragma once
#include "CharacterInterface.h"
#include <string>
#include "Map.h"

using namespace std;

class Player : public CharacterInterface {
private:
    int m_health;
    bool m_isCrouching;
    float m_jumpForce;
    float m_rotationAngle = 0.0f;
    OBB m_bounds; // Add OBB for player's bounding box

public:
    Player(Model model, const Vector3& forwardDir, const Vector3& position, const Vector3& velocity,
        const float& speed, const float& scale, const float& jumpForce, const int& health);

    void move() override;
    void jump() override;
    void applyGravity() override;
    bool checkGroundCollision() override;
    void rotate() override;
};