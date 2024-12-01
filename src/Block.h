#pragma once

#include "raylib.h"
#include "btBulletDynamicsCommon.h"
#include "ModelStage.h"
#include "string"

const float TILE_DURATION = 0.3f;
const float VELOCCITY = 0.9f;
class Block
{
protected:
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    btRigidBody* m_rigidBodyOfBlock;
    std::string m_name;
    bool m_isBouncing = false;
    float m_bounceTime = 0.0f;
    float m_gravity;
    float m_velocity;
    Model m_model;
    Vector3 m_position;
    Vector3 m_scale;


public:
    Block(btRigidBody* rigidBody, const std::string& name, Model model, Vector3 position, Vector3 scale, btDiscreteDynamicsWorld* dynamicsWorld)
        : m_rigidBodyOfBlock(rigidBody), m_name(name), m_model(model), m_position(position), m_scale(scale), m_dynamicsWorld(dynamicsWorld) {}

    bool isPlayerCollidingWithBlock(btRigidBody* player);
    bool checkCollisionWithPlayer(btRigidBody* player);
    void updateBounce();
    Vector3 getPosition() const;
    Vector3 getScale() const;
    bool getIsBouncing();
    btDiscreteDynamicsWorld* getDynamicsWorld();
    virtual ~Block();

    void render();

};