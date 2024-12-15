#include "StageController.h"
#include <iostream>

void StageController::moveEnemy(std::shared_ptr<Enemy> enemyData)
{
    Vector3 targetPos = enemyData->getMovingToA() ? enemyData->getPointA() : enemyData->getPointB();
    enemyData->setTargetPosistion(targetPos);

    moveToEnemy(enemyData);
    // Check if the enemy has reached the target position with some tolerance
    float distance = Vector3Distance(enemyData->getPlayerPos(), targetPos);

    if (distance < 2.0f) {
        enemyData->setMovingToA(!(enemyData->getMovingToA()));
        Vector3 newtargetPos = enemyData->getMovingToA() ? enemyData->getPointA() : enemyData->getPointB();
        enemyData->setTargetPosistion(newtargetPos);

        rotateEnemy(enemyData);
    }
}

void StageController::moveToEnemy(std::shared_ptr<Enemy> enemyData)
{
    Vector3 direction = Vector3Normalize(enemyData->getTargetPosition() - enemyData->getPlayerPos());
    btVector3 movement(direction.x, 0, direction.z);

    enemyData->setLinearVelocity(movement * enemyData->getMoveSpeed());
    // Update position
    btTransform trans;
    enemyData->getRigidBody()->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    Vector3 newPos = { pos.x(), pos.y(), pos.z() };
    enemyData->setPlayerPos(newPos);
}

void StageController::rotateEnemy(std::shared_ptr<Enemy> enemyData)
{
    // Step 1: Calculate the desired horizontal direction
    btTransform transform = enemyData->getRigidBody()->getWorldTransform();
    btQuaternion currentRotation = transform.getRotation();

    Vector3 desiredDirection = Vector3Subtract(enemyData->getTargetPosition(), enemyData->getPlayerPos());
    desiredDirection.y = 0; // Ignore vertical component
    if (Vector3Length(desiredDirection) < 0.001f) return; // Avoid division by zero
    desiredDirection = Vector3Normalize(desiredDirection);

    // Step 2: Get the current forward direction (projected on the horizontal plane)
    Vector3 normalizedForwardDir = Vector3Normalize(enemyData->getForwardDir());
    Vector3 currentForwardDir = { normalizedForwardDir.x, 0.0f, normalizedForwardDir.z };
    currentForwardDir = Vector3Normalize(currentForwardDir);

    // Step 3: Calculate the rotation axis
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f }; // Constrain rotation to the Y-axis

    // Step 4: Calculate the rotation angle
    float dot = Vector3DotProduct(currentForwardDir, desiredDirection);
    float angle = acosf(Clamp(dot, -1.0f, 1.0f)); // Clamp for safety

    // Determine the sign of the angle using the cross product
    Vector3 cross = Vector3CrossProduct(currentForwardDir, desiredDirection);
    if (cross.y < 0) angle = -angle; // Clockwise rotation

    // Step 5: Apply the rotation
    if (fabs(angle) > 0.01f) { // Skip tiny rotations
        // Calculate smooth interpolation factor based on the angle
        float rotationSpeedFactor = fminf(fabs(angle) / 3.14159f, 1.0f); // Cap at 1.0 for maximum speed
        float slerpFactor = 0.1f + (rotationSpeedFactor * 0.4f); // Smooth factor (adjust as needed)

        btQuaternion rotation(btVector3(rotationAxis.x, rotationAxis.y, rotationAxis.z), angle);
        btQuaternion newRotation = rotation * currentRotation;

        // Smoothly interpolate the rotation
        btQuaternion interpolatedRotation = slerp(currentRotation, newRotation, slerpFactor); // Adjust factor as needed
        interpolatedRotation.normalize(); // Normalize to avoid numerical errors

        // Update transform (preserve position)
        btVector3 currentPosition = transform.getOrigin();
        transform.setRotation(interpolatedRotation);
        transform.setOrigin(currentPosition);

        // Apply to rigid body
        enemyData->setWorldTransform(transform);
    }
    enemyData->setPlayerRotationAngle(angle);
}   
    
void StageController::updateMovemenOfEnemy(std::vector<std::shared_ptr<Enemy>> enemies)
{
    for (auto &enemy : enemies)
    {
        
        moveEnemy(enemy);
        updateCollisionShape(enemy);  // Update collision shape
        updateModelTransform(enemy);  // Synchronize marioData with physics body
    }
     
}
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




void StageController::updateCollisionShape(std::shared_ptr<PlayerData> playerData)
{
    
    // Get the rigid body's current transform
    btTransform transform = playerData->getRigidBody()->getWorldTransform();

    // Force the rotation to align with the Y-axis (capsule's up-axis)

    transform.setRotation(btQuaternion(0, 0, 0, 1));
    playerData->setRigidBodyTransform(transform);
}

void StageController::updateModelTransform(std::shared_ptr<PlayerData> playerData)
{
   

    // Get the rigid body's transform
    btTransform transform = playerData->getRigidBody()->getWorldTransform();
    btVector3 origin = transform.getOrigin();

    // Get the bounding box of the marioData
    BoundingBox marioDataBounds = GetModelBoundingBox(playerData->getPlayerModel());
    float marioDataHeight = (marioDataBounds.max.y - marioDataBounds.min.y) * playerData->getPlayerScale().y;

    // Retrieve the collision shape and calculate capsule dimensions
    btCollisionShape* collisionShape = playerData->getRigidBody()->getCollisionShape();
    btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(collisionShape);
    float capsuleRadius = capsuleShape->getRadius();
    float capsuleHeight = capsuleShape->getHalfHeight() * 2.0f + capsuleRadius * 2.0f;

    // Calculate the vertical offset to align the marioData's center with the capsule's center
    float yOffset = (capsuleHeight / 2) - capsuleRadius * 1.7f - (marioDataHeight / 2);

    // Update the marioData position
    playerData->setPlayerPos({ origin.getX(), origin.getY() + yOffset, origin.getZ() });

    // Apply rotation and scale to the marioData
    Matrix rotationMatrix = MatrixRotateY(playerData->getPlayerRotationAngle());
    Matrix scaleMatrix = MatrixScale(playerData->getPlayerScale().x, playerData->getPlayerScale().y, playerData->getPlayerScale().z);

    // Combine the transformations and apply to the marioData

    playerData->setPlayerModelTransform(MatrixMultiply(scaleMatrix, rotationMatrix));
}

bool StageController::checkGroundCollision(std::shared_ptr<PlayerData> playerData)
{
    
    if (playerData->getRigidBody()) {
        // Get the current motion state of the rigid body
        btTransform transform;
        playerData->getRigidBody()->getMotionState()->getWorldTransform(transform);

        // Perform a raycast below the character to check for ground
        btVector3 start = transform.getOrigin();
        btVector3 end = start - btVector3(0, 3.0f, 0);

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        playerData->getWorld()->rayTest(start, end, rayCallback);

        if (rayCallback.hasHit()) {
            // If the ray hits something, we are on the ground
            return true;
        }
    }

    return false;
}


void StageController::updateAnimationState(std::shared_ptr<PlayerData> marioData)
{

    PlayerAnimationState animationState = marioData->getPlayerAnimationState();

    switch (animationState) {
    case PlayerAnimationState::IDLE:
        AnimationManager::getInstance().playAnimation(3, marioData);
        std::cout << "ttttttttttttttttttttttttttttttttttttttttttttttttt\n";
        break;

    case PlayerAnimationState::WALKING:
        AnimationManager::getInstance().playAnimation(5, marioData);

        break;

    case PlayerAnimationState::JUMPING:
        AnimationManager::getInstance().playAnimation(4, marioData);

        break;

    case PlayerAnimationState::FALLING:
        AnimationManager::getInstance().playAnimation(1, marioData);

        break;

    case PlayerAnimationState::HIT:
        AnimationManager::getInstance().playAnimation(2, marioData);

        break;
    case PlayerAnimationState::DIE:
       
        AnimationManager::getInstance().playAnimation(0, marioData);

        break;
    }
    // Update the animation frame
   
    AnimationManager::getInstance().updateAnimation(GetFrameTime(), marioData);

}

void StageController::setPlayerAnimationState(std::shared_ptr<PlayerData> marioData)
{
    if (marioData->getPlayerAnimationState() == PlayerAnimationState::DIE) {
        std::cout << "11111111111111111111111111111111111111\n";
        return;
    }

    btVector3 velocity = marioData->getRigidBody()->getLinearVelocity();

    //if (m_isInvincible && m_animationState == PlayerAnimationState::HIT) {
    //    return; // Stay in HIT animation during invincibility
    //}

    if (!(marioData->getIsOnGround())) {
        if (velocity.getY() > 0.0f) {
            marioData->setPlayerAnimationState(PlayerAnimationState::JUMPING);
        }
        else {
            marioData->setPlayerAnimationState(PlayerAnimationState::FALLING);
        }
    }
    else {
        if (velocity.length() > 0.1f) {
            marioData->setPlayerAnimationState(PlayerAnimationState::WALKING);
        }
        else {
            marioData->setPlayerAnimationState(PlayerAnimationState::IDLE);
        }
    }
}
