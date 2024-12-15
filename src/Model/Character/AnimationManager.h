#pragma once
#include "raylib.h"
#include "PlayerData.h"
#include <memory>

class AnimationManager {
private:
    //ModelAnimation* m_animations;
    //int m_animationCount;
    //int m_currentAnimation;
    //float m_animationFrame;
   // Model& m_model;

    AnimationManager(){}

public:
    static AnimationManager& getInstance();
  
    AnimationManager(const AnimationManager& animation) = delete;
    AnimationManager& operator= (const AnimationManager& animation) = delete;



    void playAnimation(int animationIndex, std::shared_ptr<PlayerData> playerData);
    void updateAnimation(float deltaTime, std::shared_ptr<PlayerData> playerData);
    //int getCurrentFrame() const;          // Get the current frame of the animation
    //bool isAnimationFinished() const;    // Check if the animation has finished
    //bool hasAnimations() const { return m_animationCount > 0; }
};