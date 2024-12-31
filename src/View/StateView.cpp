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
