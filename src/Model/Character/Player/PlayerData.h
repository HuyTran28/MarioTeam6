#pragma once
#include "../CharacterData.h"
#include <string>
#include <fstream>


class PlayerData : public CharacterData
{
private:
    bool m_isCrouching;
    bool m_isJumping = false;
    float m_jumpForce;
    float m_jumpTimer = 0.0f;  // Timer to control jump force duration
    float m_maxJumpDuration;  // Maximum time to apply jump force (in seconds)

    float bigDuration = 0.0f;
	bool isBig = false;

    bool m_isSpecial = false;
    float m_specialDuartion = 3.0f;
    float m_specialTimer = 0.0f;

    float m_invincibilityTimer = 0.0f;   // Timer to track invincibility duration
    bool m_isInvincible = false;         // Flag to indicate if the player is invincible
    float m_invincibilityDuration = 1.2f; // Duration of invincibility in seconds


	float m_throwTimer = 0.0f;
	float m_throwDuration = 0.7f;
	bool m_isThrowing = false;

public:
    PlayerData() {}

    PlayerData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::string modelPath, const Vector3& forwardDir, const Vector3& position,
        const float& speed, const Vector3& scale, const Vector3& rotaionAxis, const float& rotationAngle, const float& jumpForce, const int& health, std::shared_ptr<btDynamicsWorld> world, bool isSpecial = false,
        float specialDuration = 3.0f, float specialTimer = 0.0f, float invicibilityTimer = 0.0f, bool isInvincible = false, float invincibilityDuration = 1.2f, float throwTimer = 0.0f, float throwDuration = 0.7f, bool m_isThrowing = false);

    void save(std::ofstream& file);
	void load(std::ifstream& file);

    //Vector3 getForwarDir() const;
    bool getIsJumping() const;
    bool getIsCrouching() const;
    float getJumpForce() const;
    float getJumpTimer() const;
    float getMaxJumpDuration() const;
	float getBigDuration() const;
	bool getIsBig() const;
    float getInvincibilityTimer() const;
    bool getIsvincible() const;
    float getInvincibilityDuration() const;
	bool getIsThrowing() const;
	float getThrowTimer() const;
    bool getIsSpecial() const;
    float getSpecialDuration() const;
    float getSpecialTimer() const;
	float getThrowDuration() const;
	

    void setInvincibilityTimer(float timer);
    void setIsvincible(bool isVincible);
	void setThrowTimer(float timer);
	void setIsThrowing(bool isThrowing);
    void setIsSpecial(bool isSpecial);
    void setSpecialTimer(float timer);
	void setJumpForce(float jumpForce) { m_jumpForce = jumpForce; }
	void setInvincibilityDuration(float duration) { m_invincibilityDuration = duration; }
	void setThrowDuration(float duration) { m_throwDuration = duration; }
	void setSpecialDuration(float duration);
    void setForwarDir(const Vector3& forwardDir);
    void setIsJumping(bool isJumping);
    void setJumpTimer(float jumTimer);
    void setMaxJumpDuaration(float maxJumpDuaration);
	void setIsCrouching(bool isCrouching);
	void setBigDuration(float bigDuration);
	void setIsBig(bool isBig);

    virtual ~PlayerData();
};