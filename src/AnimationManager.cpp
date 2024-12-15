#include "AnimationManager.h"
#include <iostream>

AnimationManager::AnimationManager(Model& model, const char* modelPath)
    : m_model(model), m_animationFrame(0.0f), m_currentAnimation(0)
{
    m_animations = LoadModelAnimations(modelPath, &m_animationCount);
    std::cout << "Loaded " << m_animationCount << " animations\n";
    if (m_animationCount == 0) {
        m_animations = nullptr;
    }
}

AnimationManager::~AnimationManager() {
    if (m_animations) {
        UnloadModelAnimations(m_animations, m_animationCount);
    }
}

void AnimationManager::playAnimation(int animationIndex) {
    if (animationIndex >= 0 && animationIndex < m_animationCount) {
        if (m_currentAnimation != animationIndex) {
            m_currentAnimation = animationIndex;
            m_animationFrame = 0.0f; // Reset frame only when switching animations
        }
    }
}

void AnimationManager::updateAnimation(float deltaTime) {
    if (m_animationCount > 0) {
        UpdateModelAnimation(m_model, m_animations[m_currentAnimation], m_animationFrame);

        m_animationFrame += deltaTime * 60.0f; // Ensure a reasonable frame rate multiplier (30 FPS)

        if (m_animationFrame >= m_animations[m_currentAnimation].frameCount) {
            m_animationFrame = 0.0f; // Loop the animation
        }
    }
}

int AnimationManager::getCurrentFrame() const {
    if (m_animationCount > 0) {
        return static_cast<int>(m_animationFrame);
    }
    return 0; // Default to frame 0 if no animations loaded
}

bool AnimationManager::isAnimationFinished() const {
    if (m_animationCount > 0) {
        return m_animationFrame >= m_animations[m_currentAnimation].frameCount;
    }
    return true; // Return true if no animations are loaded
}
