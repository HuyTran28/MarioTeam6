#pragma once
#include "Event.h"
#include "memory"
#include "../Model/Character/Enemy/Enemy.h"


class EnemyChangeEvent : public Event
{
private:
	Enemy* preblockData;
	std::shared_ptr<Enemy> newblockData;
	std::string preblockType;
	std::string newblockType;
public:
	EnemyChangeEvent(Enemy* preBlock, std::shared_ptr<Enemy> newblock) : Event("Enemy Change Event")
	{
		preblockData = preBlock;
		preblockType = preBlock->getObjectType();
		newblockData = newblock;
		if (newblock != nullptr)
			newblockType = newblock->getObjectType();
		else
			newblockType = "";
	}

	Enemy* getPre() const
	{
		return preblockData;
	}

	std::shared_ptr<Enemy> getNew() const
	{
		return newblockData;
	}

	std::string getPreType() const
	{
		return preblockType;
	}

	std::string getNewType() const
	{
		return newblockType;
	}

};