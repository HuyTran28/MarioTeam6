#pragma once
#include "raylib.h"
#include "OBB.h"
#include <string>

class CharacterInterface {
protected:
    Model m_model;
    Vector3 m_position;
    Vector3 m_velocity;
    Vector3 m_forwardDir;
    float m_scale;
    float m_speed;
    OBB m_bounds;

    bool m_isOnGround;

public:
    static const float GRAVITY;

    CharacterInterface(Model model, const Vector3& forwardDir, const Vector3& position, const Vector3& velocity, 
                        const float& speed, const float& scale);
    void render();
    OBB getBoundingBox() const;
    void setOnGround(bool isOnGround);
    void updateTransform();
    void updateBoundingBox();
    void update();

    virtual ~CharacterInterface();    
    
    virtual void move() = 0;
    virtual void jump() = 0;
    virtual void rotate() = 0;
    virtual void applyGravity() = 0;
    virtual bool checkGroundCollision() = 0;
};
