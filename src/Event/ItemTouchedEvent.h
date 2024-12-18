#pragma once

#include "Event.h"
#include "memory"
#include "../Model/Item/ItemData.h"


class ItemTouchedEvent : public Event
{
private:
	ItemData* m_item;
public:
	ItemTouchedEvent(ItemData* item) : Event("Item Touched Event")
	{
		m_item = item;
	}

	ItemData* getItem() const
	{
		return m_item;
	}


};
