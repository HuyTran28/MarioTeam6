#pragma once

#include "Event.h"
#include "memory"
#include "../Model/Item/ItemData.h"


class ItemTouchedEvent : public Event
{
private:
	ItemData* item;
public:
	ItemTouchedEvent(ItemData* preBlock) : Event("Item Touched Event")
	{
		item = preBlock;
	}

	ItemData* getItem() const
	{
		return item;
	}


};
