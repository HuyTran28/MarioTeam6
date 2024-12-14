#pragma once
#include "StageModel.h"
#include <vector>
#include "btBulletDynamicsCommon.h"
#include "../../Model/Character/Player/Mario.h"
class Stage1Model : public StageModel
{
private:
	int m_width;
	int m_depth;
	int m_height;
	std::vector<std::shared_ptr<BlockData>> m_map;


public:
	Stage1Model();
	~Stage1Model();

	std::vector<std::shared_ptr<BlockData>> createMap();
	std::shared_ptr<Mario> createMarioModel();
	const std::vector<std::shared_ptr<BlockData>>& getMap() const;
	std::shared_ptr<PlayerData> getPlayerData() const;
};