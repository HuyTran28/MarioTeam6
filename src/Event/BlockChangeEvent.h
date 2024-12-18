#pragma once
#include "Event.h"
#include "memory"
#include "../Model/Block/BlockData.h"


class BlockChangeEvent : public Event
{
private:
	BlockData* preblockData;
	std::shared_ptr<BlockData> newblockData;
	std::string preblockType;
	std::string newblockType;
public:
	BlockChangeEvent(BlockData* preBlock, std::shared_ptr<BlockData> newblock) : Event("Block Change Event")
	{
		preblockData = preBlock;
		preblockType = preBlock->getObjectType();
		newblockData = newblock;
		newblockType = newblock->getObjectType();
	}

	BlockData* getPre() const
	{
		return preblockData;
	}

	std::shared_ptr<BlockData> getNew() const
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
