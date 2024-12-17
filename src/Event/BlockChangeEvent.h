#pragma once
#include "Event.h"
#include "memory"
#include "../Model/Block/BlockData.h"


class BlockChangeEvent : public Event
{
private:
	BlockData* preblockData;
	std::shared_ptr<BlockData> newblockData;

public:
	BlockChangeEvent(BlockData* preBlock, std::shared_ptr<BlockData> newblock) : Event("Block Change Event")
	{
		preblockData = preBlock;
		newblockData = newblock;
	}

	BlockData* getPre() const
	{
		return preblockData;
	}

	std::shared_ptr<BlockData> getNew() const
	{
		return newblockData;
	}

};
