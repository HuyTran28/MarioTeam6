#include "Player.h"
#include "raylib.h" // Include raylib for IsKeyDown and GetFrameTime
#include <raymath.h>

using namespace std;

// Constructor now takes model path as a parameter
Player::Player(Model model, const Vector3& forwardDir, const Vector3& position, const Vector3& velocity,
    const float& speed, const float& scale, const float& jumpForce, const int& health):
    CharacterInterface(model, forwardDir, position, velocity, speed, scale),
    m_jumpForce(jumpForce), 
    m_health(health), 
    m_isCrouching(false),
    m_bounds(position, Vector3{scale, scale, scale}) // Initialize OBB
{}

void Player::move() {
    if (IsKeyDown(KEY_W)) m_position = Vector3Add(m_position, Vector3Scale(m_forwardDir, m_speed));
    if (IsKeyDown(KEY_S)) m_position = Vector3Subtract(m_position, Vector3Scale(m_forwardDir, m_speed));

    updateTransform();
}

void Player::rotate() {
    // Accumulate rotation angle based on input
    if (IsKeyDown(KEY_A)) m_rotationAngle += 1.0f * GetFrameTime();
    if (IsKeyDown(KEY_D)) m_rotationAngle -= 1.0f * GetFrameTime();

    // Update forward direction based on cumulative rotation
    Matrix rotationMatrix = MatrixRotateY(m_rotationAngle);
    m_forwardDir = Vector3Normalize(Vector3Transform(Vector3{ 0.0f, 0.0f, 1.0f }, rotationMatrix));

    // Update the player transform (position and rotation)
    updateTransform();
}

// Implementing jump
void Player::jump() {
    if (m_isOnGround && IsKeyPressed(KEY_SPACE)) {
        m_velocity.y = m_jumpForce;
        m_isOnGround = false;
    }

    // Apply gravity to ensure smooth transition
    applyGravity();

    updateTransform();
}

bool Player::checkGroundCollision() {
    OBB playerBox = m_bounds;
    BoundingBox groundBox = Map::getInstance().getGroundLevel(playerBox);
    BoundingBox mapBound = Map::getInstance().calculateMapBounds();
    
    // Check if the player's position is within the map bounds
    bool isWithinMapBounds = (m_position.x >= mapBound.min.x && m_position.x <= mapBound.max.x) &&
                              (m_position.z >= mapBound.min.z && m_position.z <= mapBound.max.z);

    return isWithinMapBounds && (m_position.y <= groundBox.max.y);
}

void Player::applyGravity() {
    // Get the ground's bounding box beneath the player
    BoundingBox groundBox = Map::getInstance().getGroundLevel(m_bounds);
    BoundingBox playerBox = m_bounds;
	
    // Calculate the height of the player's bounding box
    float playerHeight = m_position.y - playerBox.min.y;

    // Calculate ground level
    float groundLevel = groundBox.max.y + playerHeight - 10.0f; // Lower the ground level

    // Constants for gravity, drag, and bounce
    const float terminalVelocity = -25.0f;  // Faster terminal velocity
    const float drag = 0.98f;               // Slight drag for falling
    const float bounceFactor = 0.5f;        // Moderate bounce height
    const float maxBounceVelocity = 5.0f;   // Limit max upward bounce velocity
    const float minBounceVelocity = 1.5f;   // Stop bouncing below this velocity
    const float interpolationSpeed = 5.0f;  // Smoother ground snapping

    if (checkGroundCollision()) {
        if (!m_isOnGround && m_velocity.y < 0) {
            // Ensure snapping to ground level before starting bounce
            if (std::abs(m_position.y - groundLevel) > 0.05f) {
                m_position.y = Lerp(m_position.y, groundLevel, interpolationSpeed * GetFrameTime());
            }

            // Apply bounce effect
            m_velocity.y *= -bounceFactor;
            if (std::abs(m_velocity.y) < minBounceVelocity) {
                m_velocity.y = 0;
                m_isOnGround = true;
            }
            else if (m_velocity.y > maxBounceVelocity) {
                m_velocity.y = maxBounceVelocity;
            }
        }
    }
    else {
        // Apply gravity if not grounded
        m_velocity.y -= CharacterInterface::GRAVITY * GetFrameTime(); // Corrected to subtract gravity
        if (m_velocity.y < terminalVelocity) {
            m_velocity.y = terminalVelocity;
        }
        m_isOnGround = false;
    }

    // Apply drag to the Y velocity (to slow down fall)
    m_velocity.y *= drag;

    // Update position based on velocity
    m_position.y += m_velocity.y * GetFrameTime();

    // Update player transform for rendering
    updateTransform();
}


