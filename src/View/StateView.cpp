#include "StateView.h"


void StateView::renderBlocks(std::vector<std::shared_ptr<BlockData>> map, Camera3D cam)
{
    for (const auto& block : map)
    {
        if ((Vector3Distance(block->getPosition(), cam.position) > 140.0f && cam.position.x < block->getPosition().x)
            || (Vector3Distance(block->getPosition(), cam.position) > 10.0f && cam.position.x > block->getPosition().x))
            continue;
        std::shared_ptr<btRigidBody> rigidBodyOfBlock = block->getRigidBody();
        btTransform blockTransform;

        rigidBodyOfBlock->getMotionState()->getWorldTransform(blockTransform);

        btVector3 position = blockTransform.getOrigin();
        DrawModelEx(block->getModel(), { position.getX(), position.getY(), position.getZ() }, block->getRotationAxis(), block->getRotationAngle(), block->getScale(), WHITE);
		btCollisionShape* shape = rigidBodyOfBlock->getCollisionShape();

		if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
			btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
			btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
			Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };
			Vector3 boxPosition = { position.getX(), position.getY(), position.getZ() };
			//DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
			DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black

		}
		// Add handling for other shape types here
		else if (shape->getShapeType() == CYLINDER_SHAPE_PROXYTYPE) {
			btCylinderShape* cylinderShape = static_cast<btCylinderShape*>(shape);
			btVector3 halfExtents = cylinderShape->getHalfExtentsWithMargin();

			// Determine the up-axis of the cylinder
			int upAxis = cylinderShape->getUpAxis();
			float radius = halfExtents[upAxis == 0 ? 1 : 0];
			float height = halfExtents[upAxis] * 2;
			Vector3 boxPosition = { position.getX(), position.getY() - 3.9f, position.getZ() };

			DrawCylinderWires(boxPosition, radius, radius, height, 32, BLACK);
		}
    }
}

void StateView::renderEnemies(std::vector<std::shared_ptr<Enemy>> enemies, Camera3D cam)
{
    for (auto enemy : enemies)
    {
        if ((Vector3Distance(enemy->getPlayerPos(), cam.position) > 140.0f && cam.position.x < enemy->getPlayerPos().x)
            || (Vector3Distance(enemy->getPlayerPos(), cam.position) > 10.0f && cam.position.x > enemy->getPlayerPos().x))
			continue;

        DrawModelEx(enemy->getPlayerModel(), { enemy->getPlayerPos().x, enemy->getPlayerPos().y, enemy->getPlayerPos().z },
            enemy->getPlayerRotationAxis(), enemy->getPlayerRotationAngle(), enemy->getPlayerScale(), WHITE);
		btCollisionShape* shape = enemy->getRigidBody()->getCollisionShape();

		// Get the transform of the rigid body
		btTransform transform;
		enemy->getRigidBody()->getMotionState()->getWorldTransform(transform);

		// Convert Bullet's transform to your rendering library's format
		btVector3 origin = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();
		Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
		Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };

		if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
			btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
			btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
			Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };

			//DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
			DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
		}
		else if (shape->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
			btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(shape);

			// Get the bounding box of the model
			BoundingBox modelBounds = GetModelBoundingBox(enemy->getPlayerModel());
			float modelHeight = (modelBounds.max.y - modelBounds.min.y) * enemy->getPlayerScale().y;
			float modelRadius = std::max((modelBounds.max.x - modelBounds.min.x), (modelBounds.max.z - modelBounds.min.z)) * enemy->getPlayerScale().z / 2.0f;

			// Adjust the capsule size to wrap around the model
			float radius = modelRadius * 1.1f; // Slightly larger than the model radius
			float halfHeight = (modelHeight / 2.0f) - radius;

			Vector3 startPos = { boxPosition.x, boxPosition.y - halfHeight, boxPosition.z };
			Vector3 endPos = { boxPosition.x, boxPosition.y + halfHeight, boxPosition.z };
			//DrawCapsule(startPos, endPos, radius, RED); // Draw the capsule in red
			DrawCapsuleWires(startPos, endPos, radius, 16, 16, BLACK); // Draw the capsule wireframe in black
		}
		// Add handling for other shape types here
		else if (shape->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
			btSphereShape* sphereShape = static_cast<btSphereShape*>(shape);
			float radius = sphereShape->getMargin(); // Assuming margin is the radius
			//DrawSphere(boxPosition, radius, RED); // Draw the sphere in red
			DrawSphereWires(boxPosition, radius, 16, 16, BLACK); // Draw the sphere wireframe in black
		}
    }

    
}

void StateView::renderItems(std::vector<std::shared_ptr<ItemData>> items, Camera3D cam)
{
    for (const auto& item : items)
    {
		if ( ( Vector3Distance(item->getPosition(), cam.position) > 100.0f && cam.position.x < item->getPosition().x ) 
            || (Vector3Distance(item->getPosition(), cam.position) > 10.0f && cam.position.x > item->getPosition().x))
			continue;
        DrawModelEx(item->getModel(), {item->getPosition().x, item->getPosition().y, item->getPosition().z},
            item->getRotationAxis(), item->getRotationAngle(), item->getScale(), WHITE);

       
    }
}

void StateView::renderTimer(float timer, std::shared_ptr<Button> timerButton)
{
	timerButton->draw();
	std::string timerString = std::to_string((int)timer);
	if (timer < 0)
		timerString = "0";
    else if (timer < 10)
		timerString = "00" + timerString;
	else if (timer < 100)
		timerString = "0" + timerString;
	DrawTextEx(GameData::getInstance().getFont(), timerString.c_str(), {1615.0f, 30.0f}, 100.0f, 0.0f, RED);
}

void StateView::renderHealth(std::shared_ptr<PlayerData> playerData, std::shared_ptr<Button> healthButton)
{
	healthButton->draw();
	
	int health = playerData->getPlayerHealth();
    Texture2D heart = GameData::getInstance().getHp();
	Rectangle sourceRec = { 0.0f, 0.0f, (float)heart.width, (float)heart.height };
	Rectangle destRec = { 300.0f, 50.0f, 50.0f, 50.0f };
	Vector2 origin = { 0.0f, 0.0f };


	for (int i = 0; i < health; i++)
	{
		Rectangle destRecNew = { destRec.x + (i * 50), destRec.y, destRec.width, destRec.height };
		DrawTexturePro(heart, sourceRec, destRecNew, origin, 0.0f, WHITE);
    }
}

void StateView::renderScore(int score)
{
	std::string scoreString = std::to_string(score);

	int scoreLength = scoreString.length();
	if (scoreLength < 6)
	{
		for (int i = 0; i < 6 - scoreLength; i++)
		{
			scoreString = "0" + scoreString;
		}
	}

	DrawTextEx(GameData::getInstance().getFont(), scoreString.c_str(), { 1550.0f, 100.0f }, 80.0f, 0.0f, RAYWHITE);
}

void StateView::renderCoin(int coins)
{
	Texture2D coin1 = GameData::getInstance().getOneCoin();
	Texture2D coin5 = GameData::getInstance().getFiveCoin();
	Texture2D coin10 = GameData::getInstance().getTenCoin();

	Rectangle sourceRec1 = { 0.0f, 0.0f, (float)coin1.width, (float)coin1.height };
	Rectangle sourceRec5 = { 0.0f, 0.0f, (float)coin5.width, (float)coin5.height };
	Rectangle sourceRec10 = { 0.0f, 0.0f, (float)coin10.width, (float)coin10.height };

	Rectangle destRec = { 300.0f, 100.0f, 50.0f, 50.0f };
	Vector2 origin = { 0.0f, 0.0f };

    if (coins == 0)
    {
		DrawTexturePro(GameData::getInstance().getZeroCoin(), sourceRec1, destRec, origin, 0.0f, WHITE);
        return;
    }

	int coin10Count = coins / 10;
	int coin5Count = (coins % 10) / 5;
	int coin1Count = (coins % 10) % 5;

	for (int i = 0; i < coin10Count; i++)
	{
		DrawTexturePro(coin10, sourceRec10, destRec, origin, 0.0f, WHITE);
        destRec.x += 50.0f;
	}

	for (int i = 0; i < coin5Count; i++)
	{
		DrawTexturePro(coin5, sourceRec5, destRec, origin, 0.0f, WHITE);
        destRec.x += 50.0f;
	}

	for (int i = 0; i < coin1Count; i++)
	{
		DrawTexturePro(coin1, sourceRec1, destRec, origin, 0.0f, WHITE);
        destRec.x += 50.0f;
	}
}
