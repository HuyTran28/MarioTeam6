#pragma once
#include "CharacterInterface.h"

#include "Enemy.h"
#include "CollisionEvent.h"

using namespace std;

enum class PlayerAnimationState {
    IDLE,
    WALKING,
    JUMPING,
    FALLING,
    HIT,
    DIE
};

class Player : public CharacterInterface {
private:
	Vector3 m_forwardDir;
    int m_health;
    bool m_isCrouching;

	bool m_isJumping = false;
    float m_jumpForce;
    float m_jumpTimer = 0.0f;  // Timer to control jump force duration
    float m_maxJumpDuration;  // Maximum time to apply jump force (in seconds)

    float m_invincibilityTimer = 0.0f;   // Timer to track invincibility duration
    bool m_isInvincible = false;         // Flag to indicate if the player is invincible
    const float m_invincibilityDuration = 1.2f; // Duration of invincibility in seconds

	PlayerAnimationState m_animationState = PlayerAnimationState::IDLE;

public:
    Player(btRigidBody* rigidBody, string modelPath, const Vector3& forwardDir, const Vector3& position,
        const float& speed, const float& scale, const float& jumpForce, const int& health, btDynamicsWorld* world);

    ~Player();

    static Player* createPlayer(btDiscreteDynamicsWorld* world, const std::string& modelPath, const Vector3& startPosition,
        const Vector3& forwardDir, float speed, float scale, float jumpForce, int health);

    void move() override;
    void rotate() override;
    void determineCollisionType(CollisionEvent& event) override;
    void onCollision(const CollisionEvent& event) override;

    void handleJumpOnEnemy();
    void handleTouchEnemy();
	void update() override;

    void jump();

	void startInvincibility();
	bool isInvincible() const;
	void updateInvincibilityTimer();

    void updateAnimationState();
    void updatePlayerAnimationState();
};