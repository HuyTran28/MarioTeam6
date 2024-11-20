#pragma once
#include "btBulletDynamicsCommon.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

class CharacterInterface {
protected:
    btRigidBody* m_rigidBody;
	Model m_model;
    Vector3 m_position;
    Vector3 m_velocity;
    Vector3 m_forwardDir;
    float m_scale;
    float m_speed;
    bool m_isOnGround;
    btDynamicsWorld* m_dynamicsWorld;  // Store the dynamics world

public:
    static const float GRAVITY;

    CharacterInterface(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
        const float& speed, const float& scale, btDynamicsWorld* world);
    virtual void render() = 0;
    virtual void move() = 0;
    virtual void rotate() = 0;
    virtual bool checkGroundCollision() = 0;

    virtual ~CharacterInterface() = default;
};


