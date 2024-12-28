#pragma once

#include "raylib.h"
#include "btBulletDynamicsCommon.h"
#include "../ModelStage.h"
#include <memory>
#include "../CollidableObject.h"

class BlockData : public CollidableObject

{
protected:
	btScalar m_mass;
	btVector3 m_inertia;

    Model m_model;
    Vector3 m_position;
    Vector3 m_scale;
    Vector3 m_rotationAxis;
    float m_rotationAngle;

    bool m_isBouncing ;
    float m_bounceTime;
    float m_gravity;
    float m_velocity;

public:
    // Constructor
    BlockData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, btScalar mass, btVector3 inertia, Model model, Vector3 position, Vector3 scale,
        Vector3 rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
		: CollidableObject(rigidBody, shape, motionState, dynamicsWorld), m_mass(mass), m_inertia(inertia), m_model(model),
          m_position(position), m_scale(scale), m_rotationAxis(rotationAxis), m_rotationAngle(rotationAngle)
    {
        
        m_isBouncing = false;
        m_bounceTime = 0.0f;
    }

    // Destructor
    virtual ~BlockData();


    Model getModel() const;
    Vector3 getPosition() const;
    Vector3 getScale() const;
    Vector3 getRotationAxis() const;
    float getRotationAngle() const;
    bool getIsBouncing() const;
    float getBounceTime() const;

    void setIsBounce(bool isBounce);
    void setBouncetime(float bounceTime);
    void setWorldTransform(const btTransform& transform);
    //void setPosition(const Vector3& position);
    //void setScale(const Vector3& scale);
    //void setBouncing(bool isBouncing);

};
