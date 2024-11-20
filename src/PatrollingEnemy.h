#pragma once
#include "Enemy.h"

class PatrollingEnemy : public Enemy {
private:
    Vector3 m_patrolPointA;  // First patrol point
    Vector3 m_patrolPointB;  // Second patrol point
    bool m_movingToA;        // Flag to indicate current target point
    float m_detectionRange;  // Range for detecting the player
    float m_attackSpeed;     // Speed multiplier during attack
    bool m_isChasing;        // Flag for chase behavior
    Vector3 m_targetPosition; // Player's position to chase

public:
    PatrollingEnemy(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
        const float& speed, const float& scale, const Vector3& patrolPointA, const Vector3& patrolPointB);
    
    ~PatrollingEnemy();

    void patrol();
    void detectPlayer(const Vector3& playerPosition);
    void chasePlayer();
    void moveTo(const Vector3& targetPosition);
    void render() override;
    void move() override;
    void rotate() override;
    bool checkGroundCollision() override;
};