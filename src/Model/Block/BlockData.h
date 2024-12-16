#pragma once

#include "raylib.h"
#include "btBulletDynamicsCommon.h"
#include <string>
#include "../ModelStage.h"
#include <memory>


class BlockData
{
protected:
    std::shared_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
    std::shared_ptr<btRigidBody> m_rigidBodyOfBlock;
	std::shared_ptr<btCollisionShape> m_collisionShape;
	std::shared_ptr<btDefaultMotionState> m_motionState;
	btScalar m_mass;
	btVector3 m_inertia;

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
    BlockData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass, btVector3 inertia, const std::string& name, Model model, Vector3 position, Vector3 scale,
        Vector3 rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		: m_rigidBodyOfBlock(rigidBody), m_collisionShape(shape), m_motionState(motionState), m_mass(mass), m_inertia(inertia), m_name(name), m_model(model),
          m_position(position), m_scale(scale), m_rotationAxis(rotationAxis), m_rotationAngle(rotationAngle), m_dynamicsWorld(dynamicsWorld) { }

    // Destructor
    virtual ~BlockData();


    std::shared_ptr<btDiscreteDynamicsWorld> getDynamicsWorld() const;
    std::shared_ptr<btRigidBody> getRigidBody() const;
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
