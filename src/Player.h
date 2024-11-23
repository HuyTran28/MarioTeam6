#pragma once
#include "CharacterInterface.h"

#include "Enemy.h"
#include "CollisionEvent.h"

using namespace std;

class Player : public CharacterInterface {
private:
	Vector3 m_forwardDir;
    int m_health;
    bool m_isCrouching;
    float m_jumpForce;
    CollisionEvent m_lastCollisionEvent; // Store the latest collision event for this player


public:
    Player(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
        const float& speed, const float& scale, const float& jumpForce, const int& health, btDynamicsWorld* world);

    ~Player();

    static Player* createPlayer(btDiscreteDynamicsWorld* world, const std::string& modelPath, const Vector3& startPosition,
        const Vector3& forwardDir, float speed, float scale, float jumpForce, int health);

    void move() override;
    void rotate() override;
    void onCollision(const CollisionEvent& event) override;
    void handleJumpOnEnemy();
    void handleTouchEnemy();
	void update() override;

    void jump();
    void setLastCollisionEvent(const CollisionEvent& event);

};