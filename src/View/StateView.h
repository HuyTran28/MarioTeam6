#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Observer/IObserver.h"
#include "../Model/Block/BlockData.h"
#include "Model/GameData.h"
#include "../Model/Character/Enemy/Enemy.h"
#include "../Model/Item/ItemData.h"
#include "../Model/Character/Player/PlayerData.h"
#include "../Button/Button.h"


class StateView : public IObserver
{
public:
	virtual void render() = 0;
	virtual ~StateView() = default;
	virtual void registerSelf() = 0;

	void renderBlocks(std::vector<std::shared_ptr<BlockData>> map);
	void renderEnemies(std::vector<std::shared_ptr<Enemy>> enemies);
	void renderItems(std::vector<std::shared_ptr<ItemData>> items);

	void renderHealth(std::shared_ptr<PlayerData> playerData, std::shared_ptr<Button> healthButton);
	void renderCoin(int coins);
};