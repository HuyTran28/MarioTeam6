#pragma once
#include "ItemData.h"
#include "raylib.h"

class Boomerang : public ItemData
{
private:
    Vector3 m_forwardDir;
    Vector3 m_startPos;
    const float   m_distance = 15.0f;
    float   m_traveledDistance;
    bool    m_isReturning;
    bool    m_isVisible;
    float   m_speed;

public:
    Boomerang(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState
        , const std::string& modelPath, const Model& model, const Vector3& position, const Vector3& scale,
        const Vector3& rotationAxis, const float& rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, float speed)
        :ItemData(rigidBody, shape, motionState, model, position, scale, rotationAxis, rotationAngle, modelPath, dynamicsWorld)
    {
        objectType = "Item-Boomerang";
        m_isVisible = false;
        m_speed = speed;
        m_isReturning = false;
        m_forwardDir = { 0.0f, 0.0f, 0.0f };
        m_traveledDistance = 0.0f;
        m_startPos = { 0.0f, 0.0f, 0.0f };
    }

    Vector3 getForwarDir() const {
        return m_forwardDir;
    }

    void setForwarDir(Vector3 forwardDir)
    {
        m_forwardDir = forwardDir;
    }

    float getTravelDistance() const
    {
        return m_traveledDistance;
    }

    void setTravelDis(float travelDis)
    {
        m_traveledDistance = travelDis;
    }


    bool getIsreturning() const
    {
        return m_isReturning;
    }

    void setIsreturning(const bool& isReturning)
    {
        m_isReturning = isReturning;
    }


    bool getIsvisble() const
    {
        return m_isVisible;
    }

    void setIsVisble(bool isVisble) 
    {
        m_isVisible = isVisble;
    }

    float getSpeed() const
    {
        return m_speed;
    }

    float getDistance() const
    {
        return m_distance;
    }

    Vector3 getStartPos() const
    {
        return m_startPos;
    }
   
    void setStartPos(Vector3 pos)
    {
        m_startPos = pos;
    }
};