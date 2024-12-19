#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Model/Character/Enemy/Enemy.h"

class EnemyDie : public Event
{
private:
	Enemy* enemy;
	std::string enemyType;
public:
	EnemyDie(Enemy* enemy) : Event("Enemy Die Event")
	{
		enemyType = enemy->getObjectType();
	}

	std::string getEnemyType() const
	{
		return enemyType;
	}

	Enemy* getEnemy() const
	{
		return enemy;
	}
};