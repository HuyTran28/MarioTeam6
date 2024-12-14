#include "PlayerAnimationStates.h"
#include "Player.h"

// Define the Idle state
void Idle::onEnter(Player& player) {
    player.m_animationManager->playAnimation(3);  // Play idle animation
}

// Define the Walk state (added)
void Walk::onEnter(Player& player) {
    player.m_animationManager->playAnimation(6);  // Play walking animation
}

// Define the Jump state
void Jump::onEnter(Player& player) {
    player.m_animationManager->playAnimation(4);  // Play jumping animation
}

// Define the Fall state
void Fall::onEnter(Player& player) {
    player.m_animationManager->playAnimation(1);  // Play falling animation
}

// Define the Run state
void Run::onEnter(Player& player) {
    player.m_animationManager->playAnimation(5);  // Play running animation
}

// Define the Hit state
void Hit::onEnter(Player& player) {
    player.m_animationManager->playAnimation(2);  // Play hit animation
}

// Optionally, define the Hit state's exit logic
void Hit::onExit(Player& player) {
    if (player.isInvincible()) {
        player.m_animationFsm.transition<Idle>();  // Transition back to Idle after hit animation ends
    }
}
