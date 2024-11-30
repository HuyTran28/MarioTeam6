// KoopaShellState.cpp
#include "KoopaShellState.h"
#include "Koopa.h"
#include "KoopaMovingShellState.h"
#include <iostream>

void KoopaShellState::move(Enemy* enemy) {
	// Shell doesn't move on its own
}

void KoopaShellState::update(Enemy* enemy) {
    // Update shell-specific animations or logic
}

void KoopaShellState::onCollision(Enemy* enemy, const CollisionEvent& event) {
    if (event.type == CollisionType::Kicked) {
        std::cout << "Shell kicked! Applying force to the shell.\n";
        Koopa* koopa = dynamic_cast<Koopa*>(enemy);
        if (koopa) {
            btVector3 force = event.kickDirection * koopa->getSpeed();
            koopa->getRigidBody()->applyCentralImpulse(force);
        }
    }

    // Handle other collision types if necessary
}
