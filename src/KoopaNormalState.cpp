#include "KoopaNormalState.h"
#include "Koopa.h" 
#include "KoopaShellState.h"

#include <iostream>

void KoopaNormalState::move(Enemy* enemy) {
    // Implement normal walking behavior
    // For example, move forward in the current direction
    auto* koopa = dynamic_cast<Koopa*>(enemy);
    if (koopa) {
        koopa->patrol();

    }
}

void KoopaNormalState::update(Enemy* enemy) {
    
}

void KoopaNormalState::onCollision(Enemy* enemy, const CollisionEvent& event) {
    // Handle collisions in normal state
    if (event.type == CollisionType::Stomped) {
		// Transition to ShellState
		auto* koopa = dynamic_cast<Koopa*>(enemy);
        if (koopa) {
			koopa->changeToShellModel();
            koopa->recalculatePhysicsForShell();
            koopa->setState(std::make_unique<KoopaShellState>());
        }
    }
    // Handle other collision types as needed
}

