#include "AnimationManager.h"
#include <iostream>



AnimationManager& AnimationManager::getInstance()
{
    static AnimationManager animationManager;
    return animationManager;
}



void AnimationManager::playAnimation(int animationIndex, std::shared_ptr<CharacterData> playerData)
{
    if (animationIndex >= 0 && animationIndex < playerData->getAnimationCount()) {
        if (playerData->getCurrentAnimation() != animationIndex) {
            playerData->setCurrentAnimation(animationIndex);
            playerData->setAnimationFrame(0.0f); // Reset frame only when switching animations
        }
    }

}




void AnimationManager::updateAnimation(float deltaTime, std::shared_ptr<CharacterData> playerData) {
    if (playerData->getAnimationCount() > 0) {
        UpdateModelAnimation(playerData->getPlayerModel(), playerData->getModelAnimation().get()[playerData->getCurrentAnimation()], playerData->getAnimationFrame());
       

        playerData->setAnimationFrame(playerData->getAnimationFrame() + (deltaTime * 30));
     

        if (playerData->getAnimationFrame() >= playerData->getModelAnimation().get()[playerData->getCurrentAnimation()].frameCount) {
            playerData->setAnimationFrame(0.0f); // Loop the animation
        }
    }
}

//int AnimationManager::getCurrentFrame() const {
//    if (m_animationCount > 0) {
//        return static_cast<int>(m_animationFrame);
//    }
//    return 0; // Default to frame 0 if no animations loaded
//}
//
//bool AnimationManager::isAnimationFinished() const {
//    if (m_animationCount > 0) {
//        return m_animationFrame >= m_animations[m_currentAnimation].frameCount;
//    }
//    return true; // Return true if no animations are loaded
//}
