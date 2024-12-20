#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Model/Character/Enemy/Enemy.h"

class EnemyDie : public Event
{
private:
	Enemy* m_enemy;
	std::string enemyType;
public:
	EnemyDie(Enemy* enemy) : Event("Enemy Die Event")
	{
		m_enemy = enemy;
		enemyType = enemy->getObjectType();
	}

	std::string getEnemyType() const
	{
		return enemyType;
	}

	Enemy* getEnemy() const
	{
		return m_enemy;
	}
};