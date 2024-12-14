#pragma once
#include "../PlayerData.h"
#include <string>


class Mario : public PlayerData
{
private:
    Vector3 m_forwardDir;
    bool m_isCrouching;
    bool m_isJumping = false;
    float m_jumpForce;
    float m_jumpTimer = 0.0f;  // Timer to control jump force duration
    float m_maxJumpDuration;  // Maximum time to apply jump force (in seconds)


public:

    //Mario(btRigidBody* rigidBody, std::string modelPath, Vector3 forwardDir, Vector3 position,
    //    float speed, Vector3 scale, Vector3 rotationAxis, float rotationAngle,
    //    float jumpForce, int health, btDynamicsWorld* world);

    Mario(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::string modelPath, const Vector3& forwardDir, const Vector3& position,
            const float& speed, const Vector3& scale, const Vector3& rotaionAxis, const float& rotationAngle, const float& jumpForce, const int& health, std::shared_ptr<btDynamicsWorld> world);

    Vector3 getForwarDir() const;
    bool getIsJumping() const;
    bool getIsCrouching() const;
    float getJumpForce() const;
    float getJumpTimer() const;
    float getMaxJumpDuration() const;

    void setForwarDir(const Vector3& forwardDir);
    void setIsJumping(bool isJumping);
    void setJumpTimer(float jumTimer);
    void setMaxJumpDuaration(float maxJumpDuaration);

    ~Mario();
};