#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include "../Model/Item/ItemData.h"
#include "../Model/ModelStage.h"
#include "../Model/Item/BoomerangFlower.h"
#include "../Model/Item/Coin.h"
#include "../Model/Item/GreenMushroom.h"
#include "../Model/Item/RedMushroom.h"
#include "../Model/Item/PurpleMushroom.h"
#include "../Model/Item/SuperStar.h"
#include "../Model/Item/Boomerang.h"
#include "../Model/Item/Fire.h"
enum ItemType
{
    BOOMERANG_FLOWER,
    RED_MUSHROOM,
    GREEN_MUSHROOM,
    PURPLE_MUSHROOM,
    SUPER_STAR,
    COIN,
    BOOMERANG_VK,
    FIRE,
};

class ItemFactory
{
public:
	static std::shared_ptr<ItemData> createItem(ItemType type, const Vector3& startPosition, const std::string& modelPath, const Vector3& scale, 
        const Vector3& rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> world);
};