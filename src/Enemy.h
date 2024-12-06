#pragma once
#include "CharacterInterface.h"
#include "EnemyState.h"
#include <memory>

class Enemy : public CharacterInterface {
protected:
    Vector3 m_forwardDir;
    std::unique_ptr<EnemyState> m_currentState;

public:
    Enemy(btRigidBody* rigidBody, std::string modelPath, const Vector3& position, const Vector3& forwardDir, const float& speed, const float& scale, btDynamicsWorld* world);

    virtual void move() override;
    virtual void rotate() override {};
    virtual void update() override;
	virtual void determineCollisionType(CollisionEvent& event) override;
    void setForwardDir(const Vector3& dir);
    Vector3 getForwardDir() const;
    void setPosition(const Vector3& pos);
    float getSpeed() const;
	virtual void kill();

    void setState(std::unique_ptr<EnemyState> newState);
    EnemyState* getState() const;

    ~Enemy() override;
};