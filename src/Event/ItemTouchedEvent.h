#pragma once

#include "Event.h"
#include "memory"
#include "../Model/Item/ItemData.h"


class ItemTouchedEvent : public Event
{
private:
	ItemData* m_item;
	std::string m_objectType;
public:
	ItemTouchedEvent(ItemData* item) : Event("Item Touched Event")
	{
		m_item = item;
		m_objectType = item->getObjectType();
	}

	ItemData* getItem() const
	{
		return m_item;
	}

	std::string getObjectType() const
	{
		return m_objectType;
	}


};
