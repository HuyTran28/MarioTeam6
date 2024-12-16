#include "ItemFactory.h"

std::shared_ptr<ItemData> ItemFactory::createItem(ItemType type, const std::string& modelPath, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, float rotationAngle, std::shared_ptr<btDynamicsWorld> world)
{
	switch (type)
	{
	case BOOMERANG:
		break;
	case RED_MUSHROOM:
		break;
	case GREEN_MUSHROOM:
		break;
	case PURPLE_MUSHROOM:
		break;
	case SUPER_STAR:
		break;
	case COIN:
		break;
	case BOOMERANG_VK:
		break;
	default:
		break;
	}
	return nullptr;
}