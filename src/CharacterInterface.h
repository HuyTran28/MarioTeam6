#pragma once
#include "btBulletDynamicsCommon.h"
#include "raylib.h"
#include "raymath.h"
#include "CollisionEvent.h"
#include <iostream>

class CharacterInterface {
protected:
    btRigidBody* m_rigidBody;
	Model m_model;
    Vector3 m_position;
    Vector3 m_velocity;
    float m_scale;
    float m_speed;
	float m_rotationAngle;
    bool m_isOnGround;
    btDynamicsWorld* m_dynamicsWorld;  // Store the dynamics world

public:
    static const float GRAVITY;

    CharacterInterface(btRigidBody* rigidBody, Model model, const Vector3& position,
        const float& speed, const float& scale, btDynamicsWorld* world);
    
    virtual void move() = 0;
    virtual void rotate() = 0;
    virtual void update() = 0;
    virtual void onCollision(const CollisionEvent& event) = 0;
     virtual void determineCollisionType(CollisionEvent& event) = 0;

    virtual ~CharacterInterface();

	Vector3 getPosition() const { return m_position; }
	Vector3 getVelocity() const { return m_velocity; }
    btRigidBody* getRigidBody() { return m_rigidBody; }
    void updateCollisionShape();
    void updateModelTransform();
    bool checkGroundCollision();
    void render();
};


