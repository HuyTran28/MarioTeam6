#include "AnimationManager.h"
#include <iostream>



AnimationManager& AnimationManager::getInstance()
{
    static AnimationManager animationManager;
    return animationManager;
}



void AnimationManager::playAnimation(int animationIndex, std::shared_ptr<CharacterData> characterData)
{
    if (animationIndex >= 0 && animationIndex < characterData->getAnimationCount()) {
        if (characterData->getCurrentAnimation() != animationIndex) {
            characterData->setCurrentAnimation(animationIndex);
            characterData->setAnimationFrame(0.0f); // Reset frame only when switching animations
        }
    }

}




void AnimationManager::updateAnimation(float deltaTime, std::shared_ptr<CharacterData> characterData) {
    if (characterData->getAnimationCount() > 0) {
        UpdateModelAnimation(characterData->getPlayerModel(), characterData->getModelAnimation().get()[characterData->getCurrentAnimation()], characterData->getAnimationFrame());
       

        characterData->setAnimationFrame(characterData->getAnimationFrame() + (deltaTime * 30));
     

        if (characterData->getAnimationFrame() >= characterData->getModelAnimation().get()[characterData->getCurrentAnimation()].frameCount) {
            characterData->setAnimationFrame(0.0f); // Loop the animation
        }
    }
}

