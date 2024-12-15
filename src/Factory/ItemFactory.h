#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include "../Model/Item/ItemData.h"

enum ItemType
{
    BOOMERANG,
    RED_MUSHROOM,
    GREEN_MUSHROOM,
    PURPLE_MUSHROOM,
    SUPER_STAR,
    COIN,
    BOOMERANG_VK
};

class ItemFactory
{
public:
	static std::shared_ptr<ItemData> createItem(ItemType type, const std::string& modelPath, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, float rotationAngle, std::shared_ptr<btDynamicsWorld> world);
};