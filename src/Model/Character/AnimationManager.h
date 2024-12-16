#pragma once
#include "raylib.h"
#include "CharacterData.h"
#include <memory>

class AnimationManager {
private:
    AnimationManager(){}

public:
    static AnimationManager& getInstance();
  
    AnimationManager(const AnimationManager& animation) = delete;
    AnimationManager& operator= (const AnimationManager& animation) = delete;



    void playAnimation(int animationIndex, std::shared_ptr<CharacterData> characterData);
    void updateAnimation(float deltaTime, std::shared_ptr<CharacterData> characterData);
};