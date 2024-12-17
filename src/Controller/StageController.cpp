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
void StageController::updateBounceOfBlock(std::shared_ptr<BlockData> blockData)
{
    float deltaTime = GetFrameTime();
    if (blockData->getIsBouncing())
    {
        btTransform blockTransform;
        blockData->getRigidBody()->getMotionState()->getWorldTransform(blockTransform);
        btVector3 originPosition = blockTransform.getOrigin();

        float height = VELOCITY * (blockData->getBounceTime() * blockData->getBounceTime() - TILE_DURATION * blockData->getBounceTime());


        blockTransform.setOrigin(btVector3(
            originPosition.x(),
            originPosition.y() - height, //update position of block 
            originPosition.z()
        ));
        blockData->setWorldTransform(blockTransform);

        //decrease time bounce
        float tmp = blockData->getBounceTime() - deltaTime;
        blockData->setBouncetime(tmp);
        std::cout << blockData->getPosition().x << " " << blockData->getPosition().y << " " << blockData->getPosition().z << '\n';


        btVector3 position = blockTransform.getOrigin();
        //DrawModelEx(blockData->getModel(), { position.getX(), position.getY(), position.getZ() }, blockData->getRotationAxis(), blockData->getRotationAngle(), blockData->getScale(), WHITE);
        if (blockData->getBounceTime() <= 0)
        {
            blockData->setIsBounce(false);
            blockData->setBouncetime(0.0f);
            blockTransform.setOrigin(btVector3(blockData->getPosition().x, blockData->getPosition().y, blockData->getPosition().z));
            blockData->setWorldTransform(blockTransform);

        }
    }
}

void StageController::updateBlock(BlockData* preBlock, std::shared_ptr<BlockData> newBlock, std::vector<std::shared_ptr<BlockData>>& map)
{

    auto it = std::find_if(map.begin(), map.end(), [preBlock](const std::shared_ptr<BlockData>& block) {
        return block.get() == preBlock;
        });

    btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
    if (it != map.end()) {
        map.erase(it);
        CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability

    }
    map.push_back(newBlock);

    CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability

}


void StageController::registerSelf()
{
}

void StageController::updateMovementOfPlayer(std::shared_ptr<PlayerData> playerData)
{

    if (playerData->getRigidBody())
    {
        playerData->setIsOnGround(checkGroundCollision(playerData));
        if (!(playerData->getIsOnGround())) {
            // Apply gravity
            btVector3 velocity = playerData->getRigidBody()->getLinearVelocity();
            btVector3 gravity = playerData->getWorld()->getGravity();
            playerData->applyCentralForce(gravity);
            // Apply extra gravity for faster falling if needed
            const float extraGravityFactor = 100.0f;
            btVector3 additionalGravity(0, extraGravityFactor * gravity.getY(), 0);

            if (velocity.getY() < 0.0f) {
                velocity.setY(0.0f);  // Prevent the player from falling through the ground
                playerData->setLinearVelocity(velocity);
                playerData->applyCentralForce(additionalGravity * playerData->getRigidBody()->getMass());
            }
        }

        movePlayer(playerData);    // Update movement
        rotatePlayer(playerData);  // Update rotation
        jumpPlayer(playerData);  // Handle jumping

        updateCollisionShape(playerData);  // Update collision shape
        updateModelTransform(playerData);  // Synchronize playerData with physics body
        setPlayerAnimationState(playerData);
        updateAnimationState(playerData);  
    }
}

void StageController::movePlayer(std::shared_ptr<PlayerData> playerData)
{


    btVector3 desiredVelocity(0, 0, 0);

    // Calculate the desired movement direction based on input
    if (IsKeyDown(KEY_W)) {
        desiredVelocity = btVector3(playerData->getForwarDir().x, 0, playerData->getForwarDir().z).normalized() * playerData->getMoveSpeed();
    }
    // Smooth acceleration towards the desired velocity
    const float accelerationFactor = 100.0f; // Higher values mean faster acceleration
    btVector3 currentVelocity = playerData->getRigidBody()->getLinearVelocity();
    btVector3 acceleration = (desiredVelocity - currentVelocity) * accelerationFactor * GetFrameTime();

    // Update the player's velocity with acceleration
    btVector3 newVelocity = currentVelocity + acceleration;

    // Clamp the new velocity to the max speed
    if (newVelocity.length() > playerData->getMoveSpeed()) {
        newVelocity = newVelocity.normalized() * playerData->getMoveSpeed();
    }

    // Apply the new velocity if significant
    const float velocityThreshold = 0.01f;
    if (newVelocity.length() > velocityThreshold)
        playerData->setLinearVelocity(newVelocity);

    // marioData->setPlayerPos()
}

void StageController::rotatePlayer(std::shared_ptr<PlayerData> playerData)
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
    float rotationAngle = playerData->getPlayerRotationAngle();
    rotationAngle += angularVelocity * GetFrameTime();
    playerData->setPlayerRotationAngle(rotationAngle);

    Matrix rotationMatrix = MatrixRotateY(rotationAngle);
    playerData->setForwarDir(Vector3Normalize(Vector3Transform(Vector3{ 0.0f, 0.0f, 1.0f }, rotationMatrix)));
}

void StageController::jumpPlayer(std::shared_ptr<PlayerData> playerData)
{
   
    float invGravity = 1.0f / -(playerData->getWorld())->getGravity().getY();

    if (playerData->getIsOnGround() && IsKeyDown(KEY_SPACE)) {
        playerData->setIsJumping(true);      // Start the jump
        playerData->setJumpTimer(0.0f);      // Reset the jump timer
        playerData->setIsOnGround(false);   // Player is now airborne

        // Increase the jump force for a higher jump
        float acceleration = (playerData->getJumpForce() * 0.5f) / playerData->getRigidBody()->getMass();
        playerData->setMaxJumpDuaration(sqrt(acceleration / playerData->getRigidBody()->getMass() * invGravity)); // Simplified physics calculation
    }

    if (playerData->getIsJumping())
    {
        // Increment the jump timer
        float jumpTimer = playerData->getJumpTimer();
        playerData->setJumpTimer(jumpTimer += GetFrameTime());
        // Calculate the current jump force based on the elapsed time
        float currentJumpForce = playerData->getJumpForce() * 2.0f * (1.0f - (playerData->getJumpTimer() / playerData->getMaxJumpDuration()));

        // Apply the current jump force

        playerData->applyCentralImpulse(btVector3(0, currentJumpForce * GetFrameTime(), 0));
        // End the jump if the max jump duration is reached
        if (playerData->getJumpTimer() >= playerData->getMaxJumpDuration()) {
            playerData->setIsJumping(false);

            btVector3 velocity = playerData->getRigidBody()->getLinearVelocity();
            velocity.setY(0.0f);  // Prevent the player from falling through the ground
            playerData->setLinearVelocity(velocity);
        }
    }
}

void StageController::updateBigDuration(std::shared_ptr<PlayerData> playerData)
{
	if (playerData->getIsBig())
	{
		float bigDuration = playerData->getBigDuration();
		bigDuration -= GetFrameTime();
		playerData->setBigDuration(bigDuration);
		if (bigDuration <= 0)
		{
			playerData->setIsBig(false);
			playerData->setBigDuration(0.0f);
            playerData->setPlayerScale(Vector3Multiply(playerData->getPlayerScale(), Vector3{ 1.0f / 1.25f, 1.0f / 1.25f, 1.0f / 1.25f }));
		}
	}
}

void StageController::removeItem(std::vector<std::shared_ptr<ItemData>>& items, ItemData* item)
{
    auto it = std::find_if(items.begin(), items.end(), [item](const std::shared_ptr<ItemData>& block) {
        return block.get() == item;
        });

    if (it != items.end()) {
        items.erase(it);
        btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
        CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability
    }

}




void StageController::updateCollisionShape(std::shared_ptr<CharacterData> characterData)
{
    // Get the rigid body's current transform
    btTransform transform = characterData->getRigidBody()->getWorldTransform();

    // Force the rotation to align with the Y-axis (capsule's up-axis)
    transform.setRotation(btQuaternion(0, 0, 0, 1));
    characterData->setRigidBodyTransform(transform);
}

void StageController::updateModelTransform(std::shared_ptr<CharacterData> characterData)
{
    // Get the rigid body's transform
    btTransform transform = characterData->getRigidBody()->getWorldTransform();
    btVector3 origin = transform.getOrigin();

    // Get the bounding box of the marioData
    BoundingBox marioDataBounds = GetModelBoundingBox(characterData->getPlayerModel());
    float marioDataHeight = (marioDataBounds.max.y - marioDataBounds.min.y) * characterData->getPlayerScale().y;

    // Retrieve the collision shape and calculate capsule dimensions
    btCollisionShape* collisionShape = characterData->getRigidBody()->getCollisionShape();
    btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(collisionShape);
    float capsuleRadius = capsuleShape->getRadius();
    float capsuleHeight = capsuleShape->getHalfHeight() * 2.0f + capsuleRadius * 2.0f;

    // Calculate the vertical offset to align the marioData's center with the capsule's center
    float yOffset = (capsuleHeight / 2) - capsuleRadius * 1.7f - (marioDataHeight / 2);

    // Update the marioData position
    characterData->setPlayerPos({ origin.getX(), origin.getY() + yOffset, origin.getZ() });

    // Apply rotation and scale to the marioData
    Matrix rotationMatrix = MatrixRotateY(characterData->getPlayerRotationAngle());
    Matrix scaleMatrix = MatrixScale(characterData->getPlayerScale().x, characterData->getPlayerScale().y, characterData->getPlayerScale().z);

    // Combine the transformations and apply to the marioData

    characterData->setPlayerModelTransform(MatrixMultiply(scaleMatrix, rotationMatrix));
}

bool StageController::checkGroundCollision(std::shared_ptr<CharacterData> characterData)
{
    
    if (characterData->getRigidBody()) {
        // Get the current motion state of the rigid body
        btTransform transform;
        characterData->getRigidBody()->getMotionState()->getWorldTransform(transform);

        // Perform a raycast below the character to check for ground
        btVector3 start = transform.getOrigin();
        btVector3 end = start - btVector3(0, 2.1f, 0);

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        characterData->getWorld()->rayTest(start, end, rayCallback);

        if (rayCallback.hasHit()) {
            // If the ray hits something, we are on the ground
            return true;
        }
    }
    return false;
}


void StageController::updateAnimationState(std::shared_ptr<CharacterData> characterData)
{

    PlayerAnimationState animationState = characterData->getPlayerAnimationState();

    switch (animationState) {
    case PlayerAnimationState::IDLE:
        AnimationManager::getInstance().playAnimation(3, characterData);
        break;

    case PlayerAnimationState::WALKING:
        AnimationManager::getInstance().playAnimation(5, characterData);

        break;

    case PlayerAnimationState::JUMPING:
        AnimationManager::getInstance().playAnimation(4, characterData);

        break;

    case PlayerAnimationState::FALLING:
        AnimationManager::getInstance().playAnimation(1, characterData);

        break;

    case PlayerAnimationState::HIT:
        AnimationManager::getInstance().playAnimation(2, characterData);

        break;
    case PlayerAnimationState::DIE:
       
        AnimationManager::getInstance().playAnimation(0, characterData);

        break;
    }
    // Update the animation frame
   
    AnimationManager::getInstance().updateAnimation(GetFrameTime(), characterData);

}

void StageController::setPlayerAnimationState(std::shared_ptr<CharacterData> characterData)
{
    if (characterData->getPlayerAnimationState() == PlayerAnimationState::DIE) {
        return;
    }


    btVector3 velocity = characterData->getRigidBody()->getLinearVelocity();
    if (!(characterData->getIsOnGround())) {
        // Mario is airborne
        if (velocity.getY() > 0.01f) {
            // Ascending (jumping up)
            characterData->setPlayerAnimationState(PlayerAnimationState::JUMPING);
        }
        else if (velocity.getY() <= 0.0f) {
            // Descending (falling down)
            characterData->setPlayerAnimationState(PlayerAnimationState::FALLING);
        }
    }
    else {

        // Player is grounded
        if (velocity.length() > 0.1f) {

            characterData->setPlayerAnimationState(PlayerAnimationState::WALKING);
        }
        else {

            characterData->setPlayerAnimationState(PlayerAnimationState::IDLE);
        }
    }
}
