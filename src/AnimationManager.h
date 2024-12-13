#pragma once
#include "raylib.h"

class AnimationManager {
private:
    ModelAnimation* m_animations;
    int m_animationCount;
    int m_currentAnimation;
    float m_animationFrame;
    Model& m_model;

public:
    AnimationManager(Model& model, const char* modelPath);
    ~AnimationManager();

    void playAnimation(int animationIndex);
    int getCurrentFrame() const;          // Get the current frame of the animation
    bool isAnimationFinished() const;    // Check if the animation has finished
    void updateAnimation(float deltaTime);
    bool hasAnimations() const { return m_animationCount > 0; }
};