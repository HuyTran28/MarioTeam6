#pragma once
#include "../CharacterData.h"
//#include "EnemyState.h"
#include <memory>
#include <string>


class Enemy : public CharacterData {
protected:

    Vector3 m_pointA;
    Vector3 m_pointB;
    Vector3 m_targetPosition;
    bool m_movingToA;
    std::string m_name;

   // std::unique_ptr<EnemyState> m_currentState;

public:
    Enemy(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::string modelPath, const Vector3& position, const Vector3& forwardDir, const Vector3& pointA, const Vector3& pointB, const float& speed, const Vector3& scale,
        const Vector3& rotaionAxis, const float& rotationAngle, std::shared_ptr< btDynamicsWorld> world, std::string name);


    void setForwardDir(const Vector3& dir);
    Vector3 getForwardDir() const;
    Vector3 getPointA() const;
    Vector3 getPointB() const;
    Vector3 getTargetPosition() const;
    bool getMovingToA() const;
    std::string getName() const;
    void setMovingToA(bool movingToA);
    void setTargetPosistion(Vector3 targetPos);
         


    void setPosition(const Vector3& pos);
    float getSpeed() const;
    



    ~Enemy() override;
};