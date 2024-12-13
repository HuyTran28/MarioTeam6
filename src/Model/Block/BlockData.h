#pragma once

#include "raylib.h"
#include "btBulletDynamicsCommon.h"
#include <string>
#include "ModelStage.h"


class BlockData
{
protected:
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    btRigidBody* m_rigidBodyOfBlock;

    std::string m_name;
    Model m_model;
    Vector3 m_position;
    Vector3 m_scale;
    Vector3 m_rotationAxis;
    float m_rotationAngle;

    bool m_isBouncing = false;
    float m_bounceTime = 0.0f;
    float m_gravity;
    float m_velocity;

public:
    // Constructor
    BlockData(btRigidBody* rigidBody, const std::string& name, Model model, Vector3 position, Vector3 scale,
        Vector3 rotationAxis, float rotationAngle, btDiscreteDynamicsWorld* dynamicsWorld)
        : m_rigidBodyOfBlock(rigidBody), m_name(name), m_model(model), m_position(position), m_scale(scale), 
        m_rotationAxis(rotationAxis), m_rotationAngle(rotationAngle), m_dynamicsWorld(dynamicsWorld) {}

    // Destructor
    virtual ~BlockData();


    btDiscreteDynamicsWorld* getDynamicsWorld() const;
    btRigidBody* getRigidBody() const;
    std::string getName() const;
    Model getModel() const;
    Vector3 getPosition() const;
    Vector3 getScale() const;
    Vector3 getRotationAxis() const;
    float getRotationAngle() const;
    bool getIsBouncing() const;

    //void setPosition(const Vector3& position);
    //void setScale(const Vector3& scale);
    //void setBouncing(bool isBouncing);

};
