#include "StageController.h"
#include <iostream>
void StageController::registerSelf()
{
}

void StageController::updateMovementOfMario(std::shared_ptr<Mario> marioData)
{
   // std::shared_ptr<Mario> marioData = std::dynamic_pointer_cast<Mario>(marioData);

    if (marioData->getRigidBody())
    {
        marioData->setIsOnGround(checkGroundCollision(marioData));
        if (!(marioData->getIsOnGround())) {
            // Apply gravity
            btVector3 velocity = marioData->getRigidBody()->getLinearVelocity();
            btVector3 gravity = marioData->getWorld()->getGravity();
            marioData->applyCentralForce(gravity);
            // Apply extra gravity for faster falling if needed
            const float extraGravityFactor = 2.0f;
            btVector3 additionalGravity(0, extraGravityFactor * gravity.getY(), 0);

            if (velocity.getY() < 0.0f) {  
                marioData->applyCentralForce(additionalGravity);
            }

            // Reduce damping for smooth motion in the air
            marioData->setDamping(0.1f, marioData->getRigidBody()->getAngularDamping());
        }
        else {
            // Restore damping when on the ground
            marioData->setDamping(0.5f, marioData->getRigidBody()->getAngularDamping());
        }

        moveMario(marioData);    // Update movement
        rotateMario(marioData);  // Update rotation
        jumpMario(marioData);  // Handle jumping

        updateCollisionShape(marioData);  // Update collision shape
        updateModelTransform(marioData);  // Synchronize marioData with physics body

        // btVector3 playerVelocity = m_rigidBody->getLinearVelocity();
        // updateAnimationState();  // Update animation state
    }
}

void StageController::moveMario(std::shared_ptr<Mario> marioData)
{


    btVector3 desiredVelocity(0, 0, 0);

    // Calculate the desired movement direction based on input
    if (IsKeyDown(KEY_W)) {
        desiredVelocity = btVector3(marioData->getForwarDir().x, 0, marioData->getForwarDir().z).normalized() * marioData->getMoveSpeed();
    }
    // Smooth acceleration towards the desired velocity
    const float accelerationFactor = 100.0f; // Higher values mean faster acceleration
    btVector3 currentVelocity = marioData->getRigidBody()->getLinearVelocity();
    btVector3 acceleration = (desiredVelocity - currentVelocity) * accelerationFactor * GetFrameTime();

    // Update the player's velocity with acceleration
    btVector3 newVelocity = currentVelocity + acceleration;

    // Clamp the new velocity to the max speed
    if (newVelocity.length() > marioData->getMoveSpeed()) {
        newVelocity = newVelocity.normalized() * marioData->getMoveSpeed();
    }

    // Apply the new velocity if significant
    const float velocityThreshold = 0.01f;
    if (newVelocity.length() > velocityThreshold)
        marioData->setLinearVelocity(newVelocity);

   // marioData->setPlayerPos()
}

void StageController::rotateMario(std::shared_ptr<Mario> marioData)
{
    

    float angularVelocity = 0.0f;
    if (IsKeyDown(KEY_A)) {
        angularVelocity = 5.0f;  // Positive for counterclockwise rotation
    }
    if (IsKeyDown(KEY_D)) {
        angularVelocity = -5.0f;  // Negative for clockwise rotation
    }

    if (angularVelocity == 0) {
        return;
    }

    // Update the forward direction based on rotation
    float rotationAngle = marioData->getPlayerRotationAngle();
    rotationAngle += angularVelocity * GetFrameTime();
    marioData->setPlayerRotationAngle(rotationAngle);

    Matrix rotationMatrix = MatrixRotateY(rotationAngle);
    marioData->setForwarDir(Vector3Normalize(Vector3Transform(Vector3{ 0.0f, 0.0f, 1.0f }, rotationMatrix)));
}

void StageController::jumpMario(std::shared_ptr<Mario> marioData)
{
   
    float invGravity = 1.0f / -(marioData->getWorld())->getGravity().getY();

    if (marioData->getIsOnGround() && IsKeyDown(KEY_SPACE)) {
        marioData->setIsJumping(true);      // Start the jump
        marioData->setJumpTimer(0.0f);      // Reset the jump timer
        marioData->setIsOnGround(false);   // Player is now airborne

        // Increase the jump force for a higher jump
        float acceleration = (marioData->getJumpForce() * 1.5f) / marioData->getRigidBody()->getMass();
        marioData->setMaxJumpDuaration(sqrt(acceleration / marioData->getRigidBody()->getMass() * invGravity)); // Simplified physics calculation
    }

    if (marioData->getIsJumping())
    {
        // Increment the jump timer
        float jumpTimer = marioData->getJumpTimer();
        marioData->setJumpTimer(jumpTimer += GetFrameTime());
        // Calculate the current jump force based on the elapsed time
        float currentJumpForce = marioData->getJumpForce() * 2.0f * (1.0f - (marioData->getJumpTimer() / marioData->getMaxJumpDuration()));

        // Apply the current jump force

        marioData->applyCentralImpulse(btVector3(0, currentJumpForce * GetFrameTime(), 0));
        // End the jump if the max jump duration is reached
        if (marioData->getJumpTimer() >= marioData->getMaxJumpDuration()) {
            marioData->setIsJumping(false);
        }
    }

    // Apply additional gravity to make the player fall faster
    if (!(marioData->getIsOnGround()) && !(marioData->getIsJumping())) 
    {
        btVector3 additionalGravity(0, -9.8f * 2.0f * GetFrameTime(), 0); // Increase gravity effect
        marioData->applyCentralImpulse(additionalGravity);
        // Ensure the velocity is negative to trigger fall animation
        btVector3 currentVelocity = marioData->getRigidBody()->getLinearVelocity();
        if (currentVelocity.getY() > 0.01) {
            marioData->setLinearVelocity(btVector3(currentVelocity.getX(), -fabs(currentVelocity.getY()), currentVelocity.getZ()));
        }
    }
}


void StageController::updateCollisionShape(std::shared_ptr<Mario> marioData)
{
    
    // Get the rigid body's current transform
    btTransform transform = marioData->getRigidBody()->getWorldTransform();

    // Force the rotation to align with the Y-axis (capsule's up-axis)

    transform.setRotation(btQuaternion(0, 0, 0, 1));
    marioData->setRigidBodyTransform(transform);
}

void StageController::updateModelTransform(std::shared_ptr<Mario> marioData)
{
   

    // Get the rigid body's transform
    btTransform transform = marioData->getRigidBody()->getWorldTransform();
    btVector3 origin = transform.getOrigin();

    // Get the bounding box of the marioData
    BoundingBox marioDataBounds = GetModelBoundingBox(marioData->getPlayerModel());
    float marioDataHeight = (marioDataBounds.max.y - marioDataBounds.min.y) * marioData->getPlayerScale().y;

    // Retrieve the collision shape and calculate capsule dimensions
    btCollisionShape* collisionShape = marioData->getRigidBody()->getCollisionShape();
    btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(collisionShape);
    float capsuleRadius = capsuleShape->getRadius();
    float capsuleHeight = capsuleShape->getHalfHeight() * 2.0f + capsuleRadius * 2.0f;

    // Calculate the vertical offset to align the marioData's center with the capsule's center
    float yOffset = (capsuleHeight / 2) - capsuleRadius * 1.7f - (marioDataHeight / 2);

    // Update the marioData position
    marioData->setPlayerPos({ origin.getX(), origin.getY() + yOffset, origin.getZ() });

    // Apply rotation and scale to the marioData
    Matrix rotationMatrix = MatrixRotateY(marioData->getPlayerRotationAngle());
    Matrix scaleMatrix = MatrixScale(marioData->getPlayerScale().x, marioData->getPlayerScale().y, marioData->getPlayerScale().z);

    // Combine the transformations and apply to the marioData

    marioData->setPlayerModelTransform(MatrixMultiply(scaleMatrix, rotationMatrix));
}

bool StageController::checkGroundCollision(std::shared_ptr<Mario> marioData)
{
    
    if (marioData->getRigidBody()) {
        // Get the current motion state of the rigid body
        btTransform transform;
        marioData->getRigidBody()->getMotionState()->getWorldTransform(transform);

        // Perform a raycast below the character to check for ground
        btVector3 start = transform.getOrigin();
        btVector3 end = start - btVector3(0, 3.0f, 0);

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        marioData->getWorld()->rayTest(start, end, rayCallback);

        if (rayCallback.hasHit()) {
            // If the ray hits something, we are on the ground
            return true;
        }
    }

    return false;
}

void StageController::playAnimation(int animationIndex)
{
}