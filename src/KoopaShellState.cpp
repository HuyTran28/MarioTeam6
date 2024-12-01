// KoopaShellState.cpp
#include "KoopaShellState.h"
#include "Koopa.h"
#include <iostream>

void KoopaShellState::move(Enemy* enemy) {
	// Shell doesn't move on its own
 }

void KoopaShellState::update(Enemy* enemy) {
    // Update shell-specific animations or logic
}

void KoopaShellState::onCollision(Enemy* enemy, const CollisionEvent& event) {
    if (event.type == CollisionType::Kicked) {
        std::cout << "Shell kicked with enhanced force!\n";
        Koopa* koopa = dynamic_cast<Koopa*>(enemy);
        if (koopa) {
            // Enhance kick force by increasing the speed multiplier
            const float FORCE_MULTIPLIER = 100.0f; // Adjust for desired kick strength
            btVector3 enhancedForce = event.kickDirection * koopa->getSpeed() * FORCE_MULTIPLIER;
			std::cout << "Applying enhanced force: " << enhancedForce.getX() << ", " << enhancedForce.getY() << ", " << enhancedForce.getZ() << "\n";
            koopa->getRigidBody()->applyCentralImpulse(enhancedForce);
        }
    }

    // Handle other collision types if necessary
}

